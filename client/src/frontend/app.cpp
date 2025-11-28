#include "app.h"
#include "../server_request/DataRequester.hpp"
#include "pages/LoginPage.h"
#include "page_system/PageManager.h"
#include "pages/home/HomePage.h"
#include "pages/settings/SettingsPage.h"
#include "pages/dashboard/DashboardPage.h"
#include "pages/ConnectPage.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include "widgets/MainMenu.hpp"

QWidget* App::get_window()
{
    layout->addWidget(page_manager->GetStack(), 1, 0);
    layout->addWidget(main_menu->get_widget(),0,0);
    return page;  
}

void App::show_menu()
{
    main_menu->get_widget()->show();
    //qDebug() << "show";
}

void App::hide_menu()
{
    main_menu->get_widget()->hide();
    //qDebug() << "HIde";
}

App::App()
{
    page = new QWidget();      
    layout = new QGridLayout(page); 
    data_requster=std::make_shared<DataRequester>();
    
    window =  std::make_shared<QMainWindow>();
    window->setFixedSize(500, 300);
    window->setWindowTitle("Network Device Monitor");

    auto app_ptr = std::shared_ptr<App>(this, [](App*) {});
    page_manager = std::make_shared<PageManager>(app_ptr);
    main_menu = std::make_shared<MainMenu>(page_manager);
    pages = std::make_shared<std::vector<std::shared_ptr<Page>>>();
    pages->push_back(std::make_shared<ConnectPage>(data_requster,page_manager,window));
    pages->push_back(std::make_shared<LoginPage>(data_requster,page_manager,window));
    pages->push_back(std::make_shared<HomePage>(data_requster,page_manager,window));
    pages->push_back(std::make_shared<DashboardPage>(data_requster,page_manager,window));
    pages->push_back(std::make_shared<SettingsPage>(data_requster,page_manager,window));

    page_manager->set(pages);
    for (auto page : *pages){
        page_manager->add_page(page->get_page());
    }
    page_manager->change_page(0);
    window->setCentralWidget(get_window());
    window->show();
}
