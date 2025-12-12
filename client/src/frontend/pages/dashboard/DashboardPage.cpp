#include "DashboardPage.h"
#include "SyslogDashboard.h"
#include "AgentsDashboard.h"
#include "UnknownSyslogDashboard.h"
#include "UnknownAgentDashboard.h"
#include "../../style/DashboardStyle.hpp"

void DashboardPage::bind_buttons(){
    QObject::connect(syslog_dashbord, &QPushButton::clicked, [this](){
        this->dashboard_pages->change_page(0);
    });
    QObject::connect(agents_dashbord, &QPushButton::clicked, [this](){
        this->dashboard_pages->change_page(1);
    });
    QObject::connect(unknown_syslog_dashboard, &QPushButton::clicked, [this](){
        this->dashboard_pages->change_page(2);
    });
    QObject::connect(unknown_agent_dashboard, &QPushButton::clicked, [this](){
        this->dashboard_pages->change_page(3);
    });
}
QWidget *DashboardPage::get_bottom_menu()
{
    QWidget *menu = new QWidget();
    menu->setStyleSheet("background-color: #1E1E1E; border-top: 1px solid #333333;"); 

    QHBoxLayout *layout = new QHBoxLayout;
    
    layout->setContentsMargins(20, 10, 20, 20);
    layout->setSpacing(15); 

    QString buttonStyle = QString::fromStdString(get_dashboard_menu_Style());

    syslog_dashbord = new QPushButton("Syslog Dashboard");
    syslog_dashbord->setCursor(Qt::PointingHandCursor);
    syslog_dashbord->setStyleSheet(buttonStyle);
    layout->addWidget(syslog_dashbord);

    agents_dashbord = new QPushButton("Agents Dashboard");
    agents_dashbord->setCursor(Qt::PointingHandCursor);
    agents_dashbord->setStyleSheet(buttonStyle);
    layout->addWidget(agents_dashbord);

    unknown_syslog_dashboard = new QPushButton("Unknown Syslog Data");
    unknown_syslog_dashboard->setCursor(Qt::PointingHandCursor);
    unknown_syslog_dashboard->setStyleSheet(buttonStyle);
    layout->addWidget(unknown_syslog_dashboard);

    unknown_agent_dashboard = new QPushButton("Unknown Agent Data");
    unknown_agent_dashboard->setCursor(Qt::PointingHandCursor);
    unknown_agent_dashboard->setStyleSheet(buttonStyle);
    layout->addWidget(unknown_agent_dashboard);

    layout->addStretch(); 

    menu->setLayout(layout);
    menu->setFixedHeight(80); 

    return menu;
}
DashboardPage::DashboardPage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{

    QVBoxLayout *main_layout = new QVBoxLayout(); 
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setSpacing(0);

    pages = std::make_shared<std::vector<std::shared_ptr<Page>>>();

  
    auto app_ptr = std::shared_ptr<DashboardPage>(this, [](DashboardPage*) {});
    dashboard_pages = std::make_shared<PageManager>(app_ptr);

    pages->push_back(std::make_shared<SyslogDashboardScreen>(data, page_manager, window));
    pages->push_back(std::make_shared<AgentsDashboardScreen>(data, page_manager, window));
    pages->push_back(std::make_shared<UnknownSyslogDashboardScreen>(data, page_manager, window));
    pages->push_back(std::make_shared<UnknownAgentDashboardScreen>(data, page_manager, window));
    for (auto page : *pages){
       dashboard_pages->add_page(page->get_page());
    }

    main_layout->addWidget(dashboard_pages->GetStack());
    main_layout->addWidget(get_bottom_menu());
    
    dashboard_pages->change_page(0);
    page->setLayout(main_layout);
    bind_buttons();
}

void DashboardPage::on_enter()
{
    window->showMaximized();
    qDebug() << "enter dashboard";
}

void DashboardPage::on_exit()
{
     qDebug() << "leave dashboard";
}