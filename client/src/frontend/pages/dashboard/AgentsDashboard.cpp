#include "AgentsDashboard.h"

#include "../../style/DashboardStyle.hpp"
#include <QCheckBox>
#include <QWidget>
#include "../../../utils/JUNK.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QListView>
void AgentsDashboardScreen::  bind_buttons()
{
    connect(data_requester. get(), &DataRequester::UpdateAgentsDashboard, this, [this](QString msg) {
        auto data = JUNK::deserialize(msg.toStdString());
        if(data.has_value()==false || data.value()["sources"].has_value()==false){
            qDebug()<<"invalid data";
            return;
        }   
        auto sources = BetterString:: split(data.value()["sources"].value(),"{}");
        
        bool needsUpdate = false;
        if(types->count() != sources.size()){
            needsUpdate = true;
        } else {
            for(int i = 0; i < sources.size(); i++){
                if(sources[i].empty()){
                    continue;
                }
                bool found = false;
                for(int j = 0; j < types->count(); j++){
                    if(types->itemText(j).toStdString() == sources[i]){
                        found = true;
                        break;
                    }
                }
                if(! found){
                    needsUpdate = true;
                    break;
                }
            }
        }
        
        if(needsUpdate){
            QString currentText = types->currentText();
            types->clear();
            int indexToRestore = -1;
            int currentIndex = 0;
            for(auto source : sources){
                if(source.empty()){
                    continue;
                }
                types->addItem(QString::fromStdString(source));
                if(QString::fromStdString(source) == currentText){
                    indexToRestore = currentIndex;
                }
                currentIndex++;
            }
            if(indexToRestore >= 0){
                types->setCurrentIndex(indexToRestore);
            }
        }
    
        if (types->currentText().isEmpty() && types->count() > 0) {     
            this->source = types->itemText(0).toStdString();    
        }
        
        if(data.value()["agent_data"].has_value()){
            auto metrics = BetterString:: split(data.value()["agent_data"].value(),"[]");
            if(metrics. size()>=5){
                try{
                    this->cpu_chart->updateValues(stoi(metrics[2]));
                    this->ram_chart->updateValues(stoi(metrics[3]));
                    this->disk_chart->updateValues(stoi(metrics[4]));
                }
                catch(std::exception &e){
                    qDebug()<<e.what();
                }
            }
        }
        if(data.value()["agents"].has_value()){
            this->agents_table->add(BetterString::split(data. value()["agents"].value(),"{}"));
        }
                
    });
    QObject::connect(types, &QComboBox::currentTextChanged, [this](const QString &text){
        //qDebug()<<text;
        this->source=text. toStdString();
    });
}

AgentsDashboardScreen:: AgentsDashboardScreen(std::shared_ptr<DataRequester> data, const std:: shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    source ="NONE";
    QGridLayout *layout = new QGridLayout;
    types = new QComboBox();
    types->setStyleSheet(QString::fromStdString(get_combobox()));
    last_log=0;
    total_logs=0;
    ram_chart = std::  make_shared<AgentsDonutChart>("RAM", "#3498db", "#1abc9c");
    disk_chart = std::make_shared<AgentsDonutChart>("DISK", "#e74c3c", "#95a5a6");
    cpu_chart = std::make_shared<AgentsDonutChart>("CPU", "#9b59b6", "#f39c12");

    agents_table = std::make_shared<AgentsTable>();
    btn = new QPushButton("Dashboard Agents");  
    btn->setStyleSheet("background-color: black; color:  black;");
    layout->addWidget(get_top_menu(),0,0);

    QGridLayout *top_layout= new QGridLayout();
    top_layout->addWidget(ram_chart->get_chart(),0,0);
    top_layout->addWidget(cpu_chart->get_chart(),0,1);
    layout->addLayout(top_layout,1,0);
    QGridLayout *bottom_layout= new QGridLayout();
    bottom_layout->addWidget(disk_chart->get_chart(),0,1);
     bottom_layout->addWidget(agents_table->get_widget(),0,0);
    layout->addLayout(bottom_layout,2,0);
    bind_buttons();
    page->setLayout(layout);
}

QWidget* AgentsDashboardScreen::get_top_menu(){
    QWidget *widget = new QWidget();
    QCheckBox *ram_checkbox = new QCheckBox("RAM", this);
    ram_checkbox->setCheckState(Qt::Checked);
    QCheckBox *cpu_checkbox = new QCheckBox("CPU", this);
    cpu_checkbox->setCheckState(Qt::Checked);
    QCheckBox *disk_checkbox = new QCheckBox("DISK", this);
    disk_checkbox->setCheckState(Qt::  Checked);

    QGridLayout *layout= new QGridLayout();
    QListView *listView = new QListView(types);
    types->setView(listView);
    listView->setStyleSheet(QString::fromStdString(get_combobox()));

    layout->addWidget(types,0,0);   
    layout->addWidget(ram_checkbox,0,1);
    layout->addWidget(cpu_checkbox,0,2);
    layout->addWidget(disk_checkbox,0,3);
    
    connect(cpu_checkbox, &QCheckBox::stateChanged, [this](int state){
       if(state == Qt::Checked) {
           this->cpu_chart->get_chart()->show();
        } else {
            this->cpu_chart->get_chart()->hide();
        }
    });
    connect(ram_checkbox, &QCheckBox::stateChanged, [this](int state){
        if(state == Qt::Checked) {
           this->ram_chart->get_chart()->show();
        } else {
            this->ram_chart->get_chart()->hide();
        }
    });
    connect(disk_checkbox, &QCheckBox:: stateChanged, [this](int state){
       if(state == Qt:: Checked) {
           this->disk_chart->get_chart()->show();
        } else {
            this->disk_chart->get_chart()->hide();
        }
    });
    
    widget->setLayout(layout);
    return widget;
}

void AgentsDashboardScreen:: on_enter()
{

    ram_chart->updateAnim();
    cpu_chart->updateAnim();
    disk_chart->updateAnim();
}

void AgentsDashboardScreen::on_exit() {
    qDebug()<<"whitelsit leave";
}

AgentsDonutChart:: AgentsDonutChart(const std::string name, const std::string usedColor, const std::string freeColor)
{
    last_val=0;
    series = new QPieSeries();
    series->setHoleSize(0.50); 

    series->append("Used", 70);
    series->append("Free", 30);
   
    
    QPieSlice *sliceUsed = series->slices().at(0);
    sliceUsed->setLabelVisible(true);
    sliceUsed->setBrush(QColor(QString:: fromStdString(usedColor))); 
    sliceUsed->setLabelColor(Qt::white);   
    sliceUsed->setLabel("Used:   70");
    sliceUsed->setBorderColor(QColor("#2d2d2d")); 
    sliceUsed->setBorderWidth(2);

    QPieSlice *sliceFree = series->slices().at(1);
    sliceFree->setLabelVisible(true);
    sliceFree->setBrush(QColor(QString::fromStdString(freeColor))); 
    sliceFree->setLabelColor(Qt::white);
    sliceFree->setLabel("Free:  20");
    sliceFree->setBorderColor(QColor("#2d2d2d"));
    sliceFree->setBorderWidth(2);
    
    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(QString:: fromStdString(name)+" Statistics");
    chart->setAnimationOptions(QChart::AllAnimations);

    chart->setBackgroundBrush(QBrush(QColor("#2d2d2d"))); 
    chart->setTitleBrush(QBrush(Qt:: white));          
    QFont titleFont("Segoe UI", 12, QFont::Bold);
    chart->setTitleFont(titleFont);
    
    chart->legend()->hide(); 

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("background:  transparent; border: none;");
}

QWidget* AgentsDonutChart::get_chart(){
    return chartView;
}

void AgentsDonutChart::updateValues(int val)
{
    last_val=val;
    if (series->slices().size() < 2) return;
    
    QPieSlice *sliceUsed = series->slices().at(0);
    sliceUsed->setValue(val);
    sliceUsed->setLabel("Used: " + QString::number(val));

    QPieSlice *sliceFree = series->slices().at(1);
    sliceFree->setValue(100-val);
    sliceFree->setLabel("Free: " + QString:: number(100-val));
}

void AgentsDonutChart:: updateAnim()
{
    chart->removeSeries(series);

    QPieSlice *sliceUsed = series->slices().at(0);
    sliceUsed->setValue(last_val);
    sliceUsed->setLabel("Used: " + QString::number(last_val));

    QPieSlice *sliceFree = series->slices().at(1);
    sliceFree->setValue(100-last_val);
    sliceFree->setLabel("Free:   " + QString::number(100-last_val));


    chart->addSeries(series);
}

AgentsTable::AgentsTable()
{
    widget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    QFrame *frame = new QFrame();
    frame->setObjectName("TableFrame");
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    frameLayout->setContentsMargins(0, 10, 0, 10);

    table = new QTableWidget();
    table->setColumnCount(2);
    
    QStringList headers = {"Hostname", "Status"};
    table->setHorizontalHeaderLabels(headers);

    table->setShowGrid(false);
    table->setFocusPolicy(Qt:: NoFocus);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->verticalHeader()->setVisible(false);
    table->verticalHeader()->setDefaultSectionSize(60);
   
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::  Stretch);

    widget->setStyleSheet(QString::fromStdString(get_table_style()));

    frameLayout->addWidget(table);
    mainLayout->addWidget(frame);
}

QWidget *AgentsTable:: get_widget()
{
    return this->widget;
}

void AgentsTable::clear()
{
    table->setRowCount(0);
}

void AgentsTable::add(std::vector<std::string> metrics_data)
{
    table->setUpdatesEnabled(false);
    this->clear();
    for(auto entry : metrics_data)
    {
        auto content = BetterString:: split(entry, "[]");
        if(content.size() < 2) {
            continue;
        }

        table->insertRow(0);
        table->setRowHeight(0, 60);

        QString hostname = QString::fromStdString(content[0]);
        QTableWidgetItem *hostnameItem = new QTableWidgetItem(hostname);
        hostnameItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(0, 0, hostnameItem);

        QString status = QString::fromStdString(content[1]).toUpper();
        QTableWidgetItem *statusItem = new QTableWidgetItem(status);
        statusItem->setTextAlignment(Qt::AlignCenter);
        
        if(status == "ACTIVE") {
            statusItem->setForeground(QBrush(QColor("#4CAF50")));
            statusItem->setFont(QFont("Arial", 12, QFont::Bold));
        } else if(status == "INACTIVE") {
            statusItem->setForeground(QBrush(QColor("#F44336")));
            statusItem->setFont(QFont("Arial", 12, QFont::Bold));
        }
        
        table->setItem(0, 1, statusItem);

    }

    table->setUpdatesEnabled(true);
}