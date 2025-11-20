#include "HomePage.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>




HomePage::HomePage(std::shared_ptr <DataRequester> data,const std::shared_ptr <PageManager> &page_manager):Page(data,page_manager){
    QVBoxLayout *layout = new QVBoxLayout();
    QLabel *label = new QLabel("HOME");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    page->setLayout(layout);
}

void HomePage::on_enter()
{
    qDebug()<<"Home";
}
