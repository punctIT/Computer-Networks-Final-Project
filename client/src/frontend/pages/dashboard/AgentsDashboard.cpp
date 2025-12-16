#include "AgentsDashboard.h"

#include "../../style/DashboardStyle.hpp"
#include <QCheckBox>
#include <QWidget>
#include "../../../utils/JUNK.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

void AgentsDashboardScreen::bind_buttons()
{
}

AgentsDashboardScreen:: AgentsDashboardScreen(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    QGridLayout *layout = new QGridLayout;
    last_log=0;
    total_logs=0;
    ram_chart = std:: make_shared<AgentsDonutChart>("Ram", "#3498db", "#1abc9c");
    disk_chart = std::make_shared<AgentsDonutChart>("Disk", "#e74c3c", "#95a5a6");
    cpu_chart = std::make_shared<AgentsDonutChart>("Cpu", "#9b59b6", "#f39c12");

    btn = new QPushButton("Dashboard Agents");
    btn->setStyleSheet("background-color: black; color:  black;");
    layout->addWidget(get_top_menu(),0,0);

    QGridLayout *top_layout= new QGridLayout();
    top_layout->addWidget(ram_chart->get_chart(),0,0);
    top_layout->addWidget(cpu_chart->get_chart(),0,1);
    layout->addLayout(top_layout,1,0);
    QGridLayout *bottom_layout= new QGridLayout();
    bottom_layout->addWidget(disk_chart->get_chart(),0,0);
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
    disk_checkbox->setCheckState(Qt:: Checked);

    QGridLayout *layout= new QGridLayout();

    layout->addWidget(ram_checkbox,0,0);
    layout->addWidget(cpu_checkbox,0,1);
    layout->addWidget(disk_checkbox,0,2);
    
    connect(cpu_checkbox, &QCheckBox::stateChanged, [this](int state){
       if(state == Qt::Checked) {
           this->cpu_chart->get_chart()->show();
        } else {
            this->cpu_chart->get_chart()->hide();
        }
    });
    connect(ram_checkbox, &QCheckBox::stateChanged, [this](int state){
        if(state == Qt:: Checked) {
           this->ram_chart->get_chart()->show();
        } else {
            this->ram_chart->get_chart()->hide();
        }
    });
    connect(disk_checkbox, &QCheckBox:: stateChanged, [this](int state){
       if(state == Qt::Checked) {
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
    auto status = data_requester->sent("type:{update_Agents_dashboard};");
    
    ram_chart->updateAnim();
    cpu_chart->updateAnim();
    disk_chart->updateAnim();
}

void AgentsDashboardScreen::on_exit() {
    qDebug()<<"whitelsit leave";
}

AgentsDonutChart:: AgentsDonutChart(const std::string name, const std::string usedColor, const std::string freeColor)
{
    last_val=32;
    series = new QPieSeries();
    series->setHoleSize(0.50); 

    series->append("Used", 70);
    series->append("Free", 30);
   
    
    QPieSlice *sliceUsed = series->slices().at(0);
    sliceUsed->setLabelVisible(true);
    sliceUsed->setBrush(QColor(QString:: fromStdString(usedColor))); 
    sliceUsed->setLabelColor(Qt:: white);   
    sliceUsed->setLabel("Used:  70");
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
    sliceUsed->setLabel("Used: " + QString:: number(last_val));

    QPieSlice *sliceFree = series->slices().at(1);
    sliceFree->setValue(100-last_val);
    sliceFree->setLabel("Free:  " + QString::number(100-last_val));


    chart->addSeries(series);
}