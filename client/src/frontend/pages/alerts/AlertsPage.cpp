
#include "AlertsPage.h"
#include <format>
void AlertsPage::bind_buttons()
{
   connect(data_requester.get(), &DataRequester::UpdateAlertsDashboard, 
        this, [this](QString mesaj) {
          qDebug()<<mesaj;
        });
   
}

AlertsPage::AlertsPage(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(new QLabel("Alerts"));
    updateTimer = new QTimer();
   
    page->setLayout(layout);
    connect(updateTimer, &QTimer::timeout, this, &AlertsPage::update);
    updateTimer->setInterval(2000); 
    bind_buttons();
}

void AlertsPage::on_enter()
{
    updateTimer->start();
    window->showMaximized();
   
}
void AlertsPage::update(){
    this->data_requester->sent(std::format("type:{{alerts_dashboard}};"));
}
void AlertsPage::on_exit()
{
    updateTimer->stop();
}
