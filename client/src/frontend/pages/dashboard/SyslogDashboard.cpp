#include "SyslogDashboard.h"
#include "../../style/DashboardStyle.hpp"
#include <QCheckBox>
#include <QWidget>
#include "../../../utils/JUNK.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

void SyslogDashboardScreen::bind_buttons()
{
    connect(data_requester. get(), &DataRequester::UpdateSyslogDashboard, this, [this](QString msg) {
        //qDebug()<<msg;
        auto data = JUNK::deserialize(msg. toStdString());
        if(! data.has_value()||! data. value()["content"].has_value()){
            qDebug()<<data.error().c_str();
            return;
        }
        auto content = JUNK::deserialize(data. value()["content"].value());
        if(!content.has_value()){
            qDebug()<<content.error().c_str();
            return;
        }
        auto info = content.value();
        if(!info["high"].has_value()||!info["medium"].has_value()||!info["low"].has_value()){
            qDebug()<<"invalid daata";
            return;
        }
        if(! info["last_log"]. has_value()){
            qDebug()<<"no last log";
            return;
        }
        
        try{
            this->syslog_donut_chart->updateValues(stoi(info["low"].value()),stoi(info["medium"].value()),stoi(info["high"].value()));
            int current_log = stoi(info["last_log"].value());
            int new_logs = current_log - last_log;
            if(last_log != 0){
                syslog_line_chart->updateValues(new_logs);
                total_logs += new_logs;
                syslog_data->updateTotalLogs(total_logs);
                syslog_data->updateLogsPerSecond(new_logs);
            }
            last_log = current_log;
        }
        catch(std::exception &e){
            qDebug()<<e.what();
        }
        
        if(! info["logs"]. has_value()){
            return ;
        }
        SyslogDashboard_table->add(BetterString::split(info["logs"].value(),"**"));
        
    });
}

SyslogDashboardScreen::SyslogDashboardScreen(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    QGridLayout *layout = new QGridLayout;
    last_log=0;
    total_logs=0;
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
    syslog_data_checkbox->setCheckState(Qt:: Checked);
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
    auto status = data_requester->sent("type:{update_syslog_dashboard};");
    
    syslog_donut_chart->updateAnim();
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
    table->setColumnCount(7);
    
    QStringList headers = {"Name", "Type", "Hostname", "Source", "Timestamp", "Message", ""}; 
    table->setHorizontalHeaderLabels(headers);

    table->setShowGrid(false);
    table->setFocusPolicy(Qt::NoFocus); 
    table->setSelectionMode(QAbstractItemView::NoSelection); 
    table->verticalHeader()->setVisible(false); 
    table->verticalHeader()->setDefaultSectionSize(60);
   
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(4, QHeaderView:: Stretch);
    table->horizontalHeader()->setSectionResizeMode(5, QHeaderView:: Stretch);
    table->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Fixed);
    
    table->setColumnWidth(6, 180);

    widget->setStyleSheet(QString:: fromStdString(get_table_style()));

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
        if(content.size() < 7) { 
            //qDebug() << "Skip invalid entry (size too small):" << QString::fromStdString(entry);
            continue; 
        }

        table->insertRow(0);
        table->setRowHeight(0, 70);

        int columnMapping[] = {6, 1, 3, 4, 2, 10};
        
        for(int col = 0; col < 6; ++col) {
            int contentIndex = columnMapping[col];
            QString value;
            
            if(contentIndex >= content.size()) {
                value = "";
            } else {
                value = QString::fromStdString(content[contentIndex]);
            }
            
            QTableWidgetItem *item = new QTableWidgetItem(value);
            item->setTextAlignment(Qt::AlignCenter);
            table->setItem(0, col, item);
        }

        QWidget* deleteWidget = new QWidget();
        QHBoxLayout* deleteLayout = new QHBoxLayout(deleteWidget);
        deleteLayout->setContentsMargins(5, 5, 5, 5);
        deleteLayout->setAlignment(Qt::AlignCenter);

        QPushButton *deleteBtn = new QPushButton("Delete");
        deleteBtn->setCursor(Qt:: PointingHandCursor);
        deleteBtn->setMinimumHeight(40);
        deleteBtn->setStyleSheet(R"(
            QPushButton {
                background-color: #C62828;
                color: #FFFFFF;
                border-radius: 15px; 
                padding: 10px 20px;
                font-weight: bold;
                border: none;
                font-size: 13px;
            }
            QPushButton:hover {
                background-color: #B71C1C;
            }
        )");

        QObject::connect(deleteBtn, &QPushButton::clicked, [this, deleteBtn]() {
            QWidget *w = deleteBtn->parentWidget();
            if(!w) return;
            for(int r = 0; r < table->rowCount(); ++r) {
                if(table->cellWidget(r, 6) == w) {
                    table->removeRow(r);
                    break;
                }
            }
        });

        deleteLayout->addWidget(deleteBtn);
        table->setCellWidget(0, 6, deleteWidget);
        while(table->rowCount() > 100) {
            table->removeRow(table->rowCount() - 1);
        }
    }

    table->setUpdatesEnabled(true);
}
SyslogDonutChart:: SyslogDonutChart()
{
    high=medium=low=0;
    series = new QPieSeries();
    series->setHoleSize(0.40); 

    series->append("Info", 70);
    series->append("Warning", 20);
    series->append("Error", 10);
    
    QPieSlice *sliceInfo = series->slices().at(0);
    sliceInfo->setLabelVisible(true);
    sliceInfo->setBrush(QColor("#2ecc71")); 
    sliceInfo->setLabelColor(Qt::white);   
    sliceInfo->setLabel("Info:  70");
    sliceInfo->setBorderColor(QColor("#2d2d2d")); 
    sliceInfo->setBorderWidth(2);

    QPieSlice *sliceWarning = series->slices().at(1);
    sliceWarning->setLabelVisible(true);
    sliceWarning->setBrush(QColor("#f1c40f")); 
    sliceWarning->setLabelColor(Qt::white);
    sliceWarning->setLabel("Warning: 20");
    sliceWarning->setBorderColor(QColor("#2d2d2d"));
    sliceWarning->setBorderWidth(2);
    
    QPieSlice *sliceError = series->slices().at(2);
    sliceError->setLabelVisible(true);
    sliceError->setBrush(QColor("#e74c3c")); 
    sliceError->setLabelColor(Qt::white);
    sliceError->setLabel("Error: 10");
    sliceError->setExploded(true);
    sliceError->setExplodeDistanceFactor(0.1);
    sliceError->setBorderColor(QColor("#2d2d2d"));
    sliceError->setBorderWidth(2);

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Logs Statistics");
    chart->setAnimationOptions(QChart::AllAnimations);

    chart->setBackgroundBrush(QBrush(QColor("#2d2d2d"))); 
    chart->setTitleBrush(QBrush(Qt::white));          
    QFont titleFont("Segoe UI", 12, QFont::Bold);
    chart->setTitleFont(titleFont);
    
    chart->legend()->hide(); 

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("background:  transparent; border: none;");
}

QWidget* SyslogDonutChart::get_chart(){
    return chartView;
}

void SyslogDonutChart::updateValues(int info, int warning, int error)
{
    low=info;
    medium=warning;
    high=error;
    if (series->slices().size() < 3) return;
    
    QPieSlice *sliceInfo = series->slices().at(0);
    sliceInfo->setValue(info);
    sliceInfo->setLabel("Low: " + QString::number(info));

    QPieSlice *sliceWarning = series->slices().at(1);
    sliceWarning->setValue(warning);
    sliceWarning->setLabel("Medium: " + QString::number(warning));

    QPieSlice *sliceError = series->slices().at(2);
    sliceError->setValue(error);
    sliceError->setLabel("High: " + QString:: number(error));
}

void SyslogDonutChart::updateAnim()
{
    chart->removeSeries(series);

    QPieSlice *sliceInfo = series->slices().at(0);
    sliceInfo->setValue(low);
    sliceInfo->setLabel("Low: " + QString:: number(low));

    QPieSlice *sliceWarning = series->slices().at(1);
    sliceWarning->setValue(medium);
    sliceWarning->setLabel("Medium:  " + QString::number(medium));

    QPieSlice *sliceError = series->slices().at(2);
    sliceError->setValue(high);
    sliceError->setLabel("High: " + QString::number(high));

    chart->addSeries(series);
}

SyslogLineChart::SyslogLineChart()
{
    series = new QLineSeries();
    series->setName("New Logs");
    QPen pen(QColor("#00bcd4"));
    pen.setWidth(3);
    series->setPen(pen);

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("New Logs Over Time");
    
    chart->setBackgroundBrush(QBrush(QColor("#2d2d2d")));
    chart->setBackgroundRoundness(0); 
    chart->setTitleBrush(QBrush(Qt::white));
    QFont titleFont("Segoe UI", 12, QFont::Bold);
    chart->setTitleFont(titleFont);
    
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::SeriesAnimations);

    axisX = new QDateTimeAxis();
    axisX->setTickCount(5);
    axisX->setFormat("HH:mm: ss");
    axisX->setTitleText("Time");
    axisX->setLabelsColor(Qt::white);           
    axisX->setTitleBrush(Qt::white);            
    axisX->setGridLineColor(QColor("#404040")); 
    axisX->setLinePenColor(QColor("#404040")); 
    
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QValueAxis();
    axisY->setLabelFormat("%i");
    axisY->setTitleText("New Logs Count");
    axisY->setRange(0, 50);
    axisY->setLabelsColor(Qt::white);
    axisY->setTitleBrush(Qt::white);
    axisY->setGridLineColor(QColor("#404040")); 
    axisY->setLinePenColor(QColor("#404040"));

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("background: transparent; border: none;");

    QDateTime moment = QDateTime::currentDateTime();
    axisX->setRange(moment.addSecs(-60), moment);
}

QWidget* SyslogLineChart::get_chart() {
    return chartView;
}

void SyslogLineChart::updateValues(int newLogsCount)
{
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    series->append(now, newLogsCount);
    
    if (series->count() > 20) {
        series->remove(0);
    }
    
    if(series->count() > 0){
        QDateTime firstPointTime = QDateTime::fromMSecsSinceEpoch(series->at(0).x());
        QDateTime lastPointTime = QDateTime:: fromMSecsSinceEpoch(now);
        axisX->setRange(firstPointTime, lastPointTime. addSecs(1));
    }
    
    int maxVal = 50;
    for(int i = 0; i < series->count(); i++){
        if(series->at(i).y() > maxVal){
            maxVal = series->at(i).y();
        }
    }
    axisY->setMax(maxVal + 10);
}

SyslogData::SyslogData()
{
    widget = new QWidget();

    QHBoxLayout *mainLayout = new QHBoxLayout(widget);
    mainLayout->setSpacing(20); 
    mainLayout->setContentsMargins(25, 25, 25, 25); 

    widget->setStyleSheet(
        "QWidget { background-color: #1e1e1e; font-family: 'Segoe UI', Arial, sans-serif; }"
    );

    card1 = new QFrame();
    card1->setStyleSheet(
        "QFrame {"
        "   background-color: #2d2d2d;" 
        "   border:  1px solid #3e3e3e;"
        "   border-radius:  8px;"
        "}"
        "QLabel { border: none; background:  transparent; }"
    );
    QVBoxLayout *card1Layout = new QVBoxLayout(card1);
    lbl1Title = new QLabel("Logs Per Second");
    lbl1Title->setStyleSheet("color: #bbbbbb; font-weight: bold; font-size: 14px;");
    lbl1Value = new QLabel("0");
    lbl1Value->setStyleSheet("color: #ffffff; font-weight: bold; font-size: 32px;");
    lbl1Value->setAlignment(Qt::AlignCenter);
    lbl1Sub = new QLabel("logs/s");
    lbl1Sub->setStyleSheet("color: #888888; font-size: 12px;");
    lbl1Sub->setAlignment(Qt::AlignCenter);
    card1Layout->addWidget(lbl1Title);
    card1Layout->addStretch();
    card1Layout->addWidget(lbl1Value);
    card1Layout->addWidget(lbl1Sub);
    card1Layout->addStretch();

    card2 = new QFrame();
    card2->setStyleSheet(
        "QFrame {"
        "   background-color:  #2d2d2d;" 
        "   border: 1px solid #3e3e3e;"
        "   border-radius: 8px;"
        "}"
        "QLabel { border: none; background: transparent; }"
    );
    QVBoxLayout *card2Layout = new QVBoxLayout(card2);
    lbl2Title = new QLabel("Total Logs Current Session");
    lbl2Title->setStyleSheet("color:  #bbbbbb; font-weight: bold; font-size: 14px;");
    lbl2Value = new QLabel("0");
    lbl2Value->setStyleSheet("color: #ffffff; font-weight: bold; font-size: 32px;");
    lbl2Value->setAlignment(Qt::AlignCenter);
    lbl2Sub = new QLabel("total");
    lbl2Sub->setStyleSheet("color: #888888; font-size: 12px;");
    lbl2Sub->setAlignment(Qt::AlignCenter);
    card2Layout->addWidget(lbl2Title);
    card2Layout->addStretch();
    card2Layout->addWidget(lbl2Value);
    card2Layout->addWidget(lbl2Sub);
    card2Layout->addStretch();

    card4 = new QFrame();
    card4->setStyleSheet(
        "QFrame {"
        "   background-color: #2d2d2d;" 
        "   border: 1px solid #3e3e3e;"
        "   border-radius: 8px;"
        "}"
        "QLabel { border: none; background: transparent; }"
    );
    QVBoxLayout *card4Layout = new QVBoxLayout(card4);
    lbl4Title = new QLabel("Database Size");
    lbl4Title->setStyleSheet("color: #bbbbbb; font-weight: bold; font-size: 14px;");
    lbl4Value = new QLabel("UNKNOWN");
    lbl4Value->setStyleSheet("color: #ffffff; font-weight: bold; font-size: 32px;");
    lbl4Value->setAlignment(Qt::AlignCenter);
    lbl4Sub = new QLabel("size");
    lbl4Sub->setStyleSheet("color: #888888; font-size: 12px;");
    lbl4Sub->setAlignment(Qt::AlignCenter);
    card4Layout->addWidget(lbl4Title);
    card4Layout->addStretch();
    card4Layout->addWidget(lbl4Value);
    card4Layout->addWidget(lbl4Sub);
    card4Layout->addStretch();

    mainLayout->addWidget(card1);
    mainLayout->addWidget(card2);
    mainLayout->addWidget(card3);
    mainLayout->addWidget(card4);

    widget->setLayout(mainLayout);
}

QWidget* SyslogData::get_widget(){
    return widget;
}

void SyslogData::updateLogsPerSecond(int logsPerSecond)
{
    lbl1Value->setText(QString::number(logsPerSecond));
}

void SyslogData::updateTotalLogs(int totalLogs)
{
    lbl2Value->setText(QString::number(totalLogs));
}

void SyslogData::updateUptime(std::string uptime)
{
    lbl3Value->setText(QString::fromStdString(uptime));
}

void SyslogData::updateDatabaseSize(std::string dbSize)
{
    lbl4Value->setText(QString::fromStdString(dbSize));
}