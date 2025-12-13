#include "app.h"
#include <QtCore/QThread>

#include "widgets/MainMenu.hpp"
#include "style/AppStype.hpp"
#include "widgets/AlertPopup.h"
#include <QPushButton>
#include "../utils/JUNK.hpp"
QWidget* App::get_window()
{
    layout->addWidget(page_manager->GetStack(), 1, 0);
    layout->addWidget(main_menu->get_widget(),0,0);
    return page;  
}

void App::show_menu()
{
    main_menu->get_widget()->show();
    alerts_update->start();
    //qDebug() << "show";
}

void App::hide_menu()
{
    main_menu->get_widget()->hide();
    alerts_update->stop();
    //qDebug() << "HIde";
}

App::App()
{
    page = new QWidget();      
    layout = new QGridLayout(page); 
    data_requster=std::make_shared<DataRequester>();
    alerts_update = new QTimer();
    alerts_update->setInterval(3000);
    QThread *receiveThread = QThread::create([this]() {
        data_requster->start_receiving(); 
    });
    receiveThread->start();
    window =  std::make_shared<QMainWindow>();
    window->setFixedSize(600, 400);
    window->setWindowTitle("Network Device Monitor");
    window->setStyleSheet(QString::fromStdString(main_app_style()));
    auto app_ptr = std::shared_ptr<App>(this, [](App*) {});
    page_manager = std::make_shared<PageManager>(app_ptr);
    main_menu = std::make_shared<MainMenu>(page_manager);
    alert_popup = std::make_shared<AlertPopup>(window.get());
    pages = std::make_shared<std::vector<std::shared_ptr<Page>>>();
    pages->push_back(std::make_shared<ConnectPage>(data_requster,page_manager,window));
    pages->push_back(std::make_shared<LoginPage>(data_requster,page_manager,window));
    pages->push_back(std::make_shared<HomePage>(data_requster,page_manager,window));
    pages->push_back(std::make_shared<DashboardPage>(data_requster,page_manager,window));
    pages->push_back(std::make_shared<SettingsPage>(data_requster,page_manager,window));
    pages->push_back(std::make_shared<SecurityPage>(data_requster,page_manager,window));

    page_manager->set(pages);
    for (auto page : *pages){
        page_manager->add_page(page->get_page());
    }
    page_manager->change_page(0);
    QObject::connect(this->alerts_update, &QTimer::timeout, [this]() {
        auto data = data_requster->sent("type:{update_alerts};");
        if (!data.has_value()){
            qDebug()<<data.error().c_str();
        }
    });
    QObject::connect(data_requster.get(), &DataRequester::UpdateAlersPopup, window.get(), [this](QString mesaj) {
        qDebug()<<mesaj;
        auto data = JUNK::deserialize(mesaj.toStdString());
        if(!data.has_value() || !data.value()["succes"].has_value()|| data.value()["succes"].value()=="false"){
            return;
        }
        alert_popup->showMessage("Security Alert", "Port 8080 accessed.", true);
    });
    window->setCentralWidget(get_window());
    window->show();
}
