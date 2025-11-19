#include "app.h"
#include "../server_request/DataRequester.hpp"
#include "pages/LoginPage.h"
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

    std::shared_ptr<LoginPage> login_page= std::make_shared<LoginPage>(data_requster);

    stack= new QStackedWidget();
    stack->addWidget(login_page->get_page());
    stack->setCurrentIndex(0);
    window->setCentralWidget(stack);
    window->show();
}
