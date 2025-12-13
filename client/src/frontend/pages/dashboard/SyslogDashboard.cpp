#include "SyslogDashboard.h"
#include "../../style/DashboardStyle.hpp"
#include <QCheckBox>
void SyslogDashboardScreen::bind_buttons()
{

}

SyslogDashboardScreen::SyslogDashboardScreen(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    QGridLayout *layout = new QGridLayout;
    SyslogDashboard_table= std::make_shared<SyslogTable>();
    syslog_donut_chart = std::make_shared<SyslogDonutChart>();
    syslog_line_chart = std::make_shared<SyslogLineChart>();
    syslog_data = std::make_shared<SyslogData>();
    btn = new QPushButton("Dashboard Syslog");
    btn->setStyleSheet("background-color: black; color: black;");
    layout->addWidget(get_top_menu(),0,0);
    QGridLayout *top_layout= new QGridLayout();
    top_layout->addWidget(syslog_donut_chart->get_chart(),0,1);
    top_layout->addWidget(syslog_data->get_widget(),0,0);
    layout->addLayout(top_layout,1,0);
    QGridLayout *bottom_layout= new QGridLayout();
    bottom_layout->addWidget(syslog_line_chart->get_chart(),0,0);
    bottom_layout->addWidget(SyslogDashboard_table->get_widget(),0,1);
    layout->addLayout(bottom_layout,2,0);
    bind_buttons();
    page->setLayout(layout);
}
QWidget* SyslogDashboardScreen::get_top_menu(){
    QWidget *widget = new QWidget();
    QCheckBox *syslog_table_checkbox = new QCheckBox("Table", this);
    syslog_table_checkbox->setCheckState(Qt::Checked);
    QCheckBox *syslog_dount_chart_checkbox = new QCheckBox("Donut Chart", this);
    syslog_dount_chart_checkbox->setCheckState(Qt::Checked);
    QCheckBox *syslog_line_chart_checkbox = new QCheckBox("LineChart", this);
    syslog_line_chart_checkbox->setCheckState(Qt::Checked);
    QCheckBox *syslog_data_checkbox = new QCheckBox("Data", this);
    syslog_data_checkbox->setCheckState(Qt::Checked);
    QGridLayout *layout= new QGridLayout();

    layout->addWidget(syslog_table_checkbox,0,0);
    layout->addWidget(syslog_dount_chart_checkbox,0,1);
    layout->addWidget(syslog_line_chart_checkbox,0,2);
    layout->addWidget(syslog_data_checkbox,0,3);
    connect(syslog_table_checkbox, &QCheckBox::stateChanged, [this](int state){
        if(state == Qt::Checked) {
            this->SyslogDashboard_table->get_widget()->show();
        } else {
            this->SyslogDashboard_table->get_widget()->hide();
        }
    });
    connect(syslog_dount_chart_checkbox, &QCheckBox::stateChanged, [this](int state){
        if(state == Qt::Checked) {
           this->syslog_donut_chart->get_chart()->show();
        } else {
             this->syslog_donut_chart->get_chart()->hide();
        }
    });
    connect(syslog_line_chart_checkbox, &QCheckBox::stateChanged, [this](int state){
        if(state == Qt::Checked) {
           this->syslog_line_chart->get_chart()->show();
        } else {
             this->syslog_line_chart->get_chart()->hide();
        }
    });
    connect(syslog_data_checkbox, &QCheckBox::stateChanged, [this](int state){
        if(state == Qt::Checked) {
           this->syslog_data->get_widget()->show();
        } else {
           this->syslog_data->get_widget()->hide();
        }
    });
    widget->setLayout(layout);
    return widget;
}
void SyslogDashboardScreen::on_enter()
{
    syslog_donut_chart->updateValues(40,20,40);
}

void SyslogDashboardScreen::on_exit() {
    qDebug()<<"whitelsit leave";
 
}




SyslogTable::SyslogTable()
{
    widget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    QFrame *frame = new QFrame();
    frame->setObjectName("TableFrame");
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    frameLayout->setContentsMargins(0, 10, 0, 10); 

    table = new QTableWidget();
    table->setColumnCount(5);
    
    QStringList headers = {"Nume", "IP Address", "Timp", "Admin", ""}; 
    table->setHorizontalHeaderLabels(headers);

  
    table->setShowGrid(false);
    table->setFocusPolicy(Qt::NoFocus); 
    table->setSelectionMode(QAbstractItemView::NoSelection); 
    table->verticalHeader()->setVisible(false); 
   
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed); 
    table->setColumnWidth(4, 120); 

    widget->setStyleSheet(QString::fromStdString(get_table_style()));

   
    frameLayout->addWidget(table);
    mainLayout->addWidget(frame);
}

QWidget *SyslogTable::get_widget()
{
    return this->widget;
}

void SyslogTable::clear()
{
    table->setRowCount(0); 
}
void SyslogTable::add(std::vector<std::string> whitelist_data)
{
    table->setUpdatesEnabled(false); 

    for(auto entry : whitelist_data) 
    {
       
        auto content = BetterString::split(entry, "[]");
        if(content.size() <= 4) { 
            qDebug() << "Skip invalid entry (size too small):" << QString::fromStdString(entry);
            continue; 
        }

        table->insertRow(0);

        for(int i = 0; i < 4; ++i) {
            if((i + 1) >= content.size()) break;

            QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(content[i+1]));
            item->setTextAlignment(Qt::AlignCenter); // Centrat frumos
            table->setItem(0, i, item);
        }

        QWidget* btnWidget = new QWidget();
        QHBoxLayout* btnLayout = new QHBoxLayout(btnWidget);
        btnLayout->setContentsMargins(0,0,0,0);
        btnLayout->setAlignment(Qt::AlignCenter);

        QPushButton *deleteBtn = new QPushButton("Șterge");
        deleteBtn->setCursor(Qt::PointingHandCursor);
     
        deleteBtn->setStyleSheet(R"(
            QPushButton {
                background-color: #FFEBEE;
                color: #D32F2F;
                border-radius: 15px; 
                padding: 6px 15px;
                font-weight: bold;
                border: none;
            }
            QPushButton:hover {
                background-color: #FFCDD2;
            }
        )");

        QObject::connect(deleteBtn, &QPushButton::clicked, [this, deleteBtn]() {
            QWidget *w = deleteBtn->parentWidget();
            if(!w) return;
            for(int r = 0; r < table->rowCount(); ++r) {
                if(table->cellWidget(r, 4) == w) {
                    table->removeRow(r);
                    break;
                }
            }
        });

        btnLayout->addWidget(deleteBtn);
        table->setCellWidget(0, 4, btnWidget);
    }

    table->setUpdatesEnabled(true);
}

SyslogDonutChart::SyslogDonutChart()
{
    series = new QPieSeries();   
    series->append("Info", 70);      
    series->append("Warning", 20);   
    series->append("Error", 10);
    series->setHoleSize(0.40);

    QPieSlice *sliceInfo = series->slices().at(0);
    sliceInfo->setLabelVisible(true);
    sliceInfo->setBrush(QColor("#2ecc71")); 
    sliceInfo->setLabel("Info: 70");

    QPieSlice *sliceWarning = series->slices().at(1);
    sliceWarning->setLabelVisible(true);
    sliceWarning->setBrush(QColor("#f1c40f")); 
    sliceWarning->setLabel("Warning: 20");

    QPieSlice *sliceError = series->slices().at(2);
    sliceError->setLabelVisible(true);
    sliceError->setBrush(QColor("#e74c3c")); 
    sliceError->setLabel("Error: 10");
    sliceError->setExploded(true);          
    sliceError->setExplodeDistanceFactor(0.1);

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistici Log-uri Sistem");
    chart->setAnimationOptions(QChart::AllAnimations);

    chart->setTheme(QChart::ChartThemeDark);
    chartView =new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}


QWidget* SyslogDonutChart::get_chart(){
    return chartView;
}

void SyslogDonutChart::updateValues(int info, int warning, int error)
{
    chart->removeSeries(series);

    QPieSlice *sliceInfo = series->slices().at(0);
    sliceInfo->setValue(info);
    sliceInfo->setLabel("Info: " + QString::number(info));

    QPieSlice *sliceWarning = series->slices().at(1);
    sliceWarning->setValue(warning);
    sliceWarning->setLabel("Warning: " + QString::number(warning));

    QPieSlice *sliceError = series->slices().at(2);
    sliceError->setValue(error);
    sliceError->setLabel("Error: " + QString::number(error));

    chart->addSeries(series);
}

SyslogLineChart::SyslogLineChart()
{
   
    series = new QLineSeries();
    series->setName("Total Logs");
    
    
    QPen pen(QColor("#00bcd4"));
    pen.setWidth(2);
    series->setPen(pen);

   
    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Log Traffic Over Time");
    chart->legend()->hide();
    chart->setTheme(QChart::ChartThemeDark); 
    chart->setAnimationOptions(QChart::SeriesAnimations);

    
    axisX = new QDateTimeAxis();
    axisX->setTickCount(5); 
    axisX->setFormat("HH:mm:ss");
    axisX->setTitleText("Time");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    
    axisY = new QValueAxis();
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Hits");
    axisY->setRange(0, 100);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    
    
    QDateTime moment = QDateTime::currentDateTime();
    axisX->setRange(moment.addSecs(-60), moment); 
}

QWidget* SyslogLineChart::get_chart() {
    return chartView;
}

void SyslogLineChart::updateValues()
{

    int totalHits = 100;
    
    
    qint64 now = QDateTime::currentMSecsSinceEpoch();

   
    series->append(now, totalHits);

  
    if (series->count() > 20) {
        series->remove(0);
    }

    QDateTime firstPointTime = QDateTime::fromMSecsSinceEpoch(series->at(0).x());
    QDateTime lastPointTime = QDateTime::fromMSecsSinceEpoch(now);
    axisX->setRange(firstPointTime, lastPointTime.addSecs(1));


    if (totalHits > axisY->max()) {
        axisY->setMax(totalHits + 10); 
    }
}

SyslogData::SyslogData()
{
    widget = new QWidget();
    QGridLayout *layout = new QGridLayout();
    QLabel *text = new QLabel("URMEAZA ADAUGAT");
    layout->addWidget(text,0,0);
    widget->setLayout(layout);
}
QWidget * SyslogData::get_widget(){
    return widget;

}
