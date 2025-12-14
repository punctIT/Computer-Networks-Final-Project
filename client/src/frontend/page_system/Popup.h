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
    Popup(QWidget* parent, std::shared_ptr<DataRequester> data, int sizeX, int sizeY) 
        : QWidget(parent), data_requester(data) 
    {
        this->setAttribute(Qt::WA_StyledBackground, true);
        this->setFixedSize(sizeX, sizeY); 
        
        // MODIFICARE STYLE: Fundal Gri Foarte Inchis (#2B2B2B) cu Border Verde (#1ABC9C)
        this->setStyleSheet(R"(
            QWidget {
                background-color: #2B2B2B; 
                color: #ECF0F1;
                border-radius: 12px;
                border: 2px solid #1ABC9C;
                font-family: 'Segoe UI', sans-serif;
            }
            QLabel {
                border: none; /* Previne border dublu la label-uri */
                color: #ECF0F1;
                font-size: 14px;
            }
        )");

        QVBoxLayout *main_layout = new QVBoxLayout(this);
        main_layout->setSpacing(15);
        main_layout->setContentsMargins(20, 20, 20, 20);
        
        // Umbra mai pronuntata pentru contrast pe dark mode
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(30);
        shadow->setOffset(0, 8);
        shadow->setColor(QColor(0, 0, 0, 180)); 
        this->setGraphicsEffect(shadow);
        
        layout = new QGridLayout();

        QPushButton* closeBtn = new QPushButton("Close", this);
        closeBtn->setCursor(Qt::PointingHandCursor);
        
        // MODIFICARE BUTON: Verde (#1ABC9C) consistent cu restul aplicatiei
        closeBtn->setStyleSheet(R"(
            QPushButton {
                background-color: #1ABC9C;
                color: white;
                border-radius: 6px;
                padding: 8px 15px;
                font-weight: bold;
                font-size: 14px;
                border: none;
            }
            QPushButton:hover {
                background-color: #16A085;
            }
            QPushButton:pressed {
                background-color: #0E6655;
            }
        )");

        main_layout->addLayout(layout);
        
      
        main_layout->addStretch(); 
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