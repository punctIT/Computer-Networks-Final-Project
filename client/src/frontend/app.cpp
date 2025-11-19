#include "app.h"
#include "../server_request/DataRequester.hpp"
#include "pages/LoginPage.h"
#include "pages/ConnectPage.h"
#include "managers/PageManager.h"
App::App()
{
    data_requster=std::make_shared<DataRequester>();
    page_manager = std::make_shared<PageManager>();
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

    login_page= std::make_shared<LoginPage>(data_requster,page_manager);
    connect_page= std::make_shared<ConnectPage>(data_requster);
    page_manager->add_page(login_page->get_page());
    page_manager->add_page(connect_page->get_page());
    
    window->setCentralWidget(page_manager->GetStack());
    window->show();
}
