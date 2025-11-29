#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>

#include <memory>

class DataRequester;

class Popup : public QWidget {
    Q_OBJECT
protected:
    QGridLayout* layout;
    std::shared_ptr <DataRequester> data_requester;
public:
    Popup(QWidget* parent,std::shared_ptr<DataRequester> data,int sizeX,int sizeY) : QWidget(parent),data_requester(data) {
        
        this->setFixedSize(sizeX, sizeY); 
        this->setStyleSheet("background-color: white; border-radius: 10px; border: 1px solid #ccc;");
        QVBoxLayout *main_layout = new QVBoxLayout(this);
        
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(20);
        shadow->setOffset(0, 5);
        this->setGraphicsEffect(shadow);
        layout = new QGridLayout();

        QPushButton* closeBtn = new QPushButton("Close", this);
        closeBtn->setStyleSheet("background-color: #007BFF; color: white; border-radius: 5px; padding: 5px;");

        main_layout->addLayout(layout);
        main_layout->addWidget(closeBtn);
        connect(closeBtn, &QPushButton::clicked, this, &QWidget::hide);
        this->hide();
    }

    void showCentered() {
        if(parentWidget()) {
            int px = (parentWidget()->width() - width()) / 2;
            int py = (parentWidget()->height() - height()) / 2;
            this->move(px, py);
        }
        this->raise(); 
        this->show();
    }
};