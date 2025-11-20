#include "app.h"
#include "../server_request/DataRequester.hpp"
#include "pages/LoginPage.h"
#include "pages/ConnectPage.h"
#include "page_system/PageManager.h"
#include "pages/home/HomePage.h"

App::App()
{
    data_requster=std::make_shared<DataRequester>();
    
    try{
        data_requster->set_ip("127.0.0.1")
                    .set_port(8080)
                    .configure();
    }
    catch(std::exception &e){
        qDebug()<<e.what();
    }
    window = new QMainWindow();
    window->setFixedSize(400, 200);
    window->setWindowTitle("Network Device Monitor");

    page_manager = std::make_shared<PageManager>();
    pages = std::make_shared<std::vector<std::shared_ptr<Page>>>();
    pages->push_back(std::make_shared<ConnectPage>(data_requster,page_manager));
    pages->push_back(std::make_shared<LoginPage>(data_requster,page_manager));
    pages->push_back(std::make_shared<HomePage>(data_requster,page_manager));
   
    page_manager->set(pages);
    for (auto page : *pages){
        page_manager->add_page(page->get_page());
    }
    page_manager->change_page(1);
    
    window->setCentralWidget(page_manager->GetStack());
    window->show();
}
