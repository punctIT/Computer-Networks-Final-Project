#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QApplication>
#include "../page_system/PageManager.h"
#include <memory>

class AlertPopup : public QWidget {
    Q_OBJECT
private:
    QLabel* titleLabel;
    QLabel* messageLabel;
    QFrame* container;
    std::shared_ptr<PageManager> page_manager;
public:
    AlertPopup(QWidget* parent,std::shared_ptr<PageManager> page) : QWidget(parent),page_manager(page) {
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        this->setAttribute(Qt::WA_TranslucentBackground);
        this->setFixedSize(420, 210);

     
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(20);
        shadow->setColor(QColor(0, 0, 0, 150));
        shadow->setOffset(0, 5);
        this->setGraphicsEffect(shadow);

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(15, 15, 15, 15);

        container = new QFrame(this);
        container->setObjectName("AlertFrame");
        container->setAttribute(Qt::WA_StyledBackground, true);
        
        container->setStyleSheet(
            "QFrame#AlertFrame {"
            "    background-color:  #252525;"
            "    border: 1px solid #1ABC9C;"
            "    border-radius: 10px;"
            "}"
            "QLabel {"
            "    color:  #E0E0E0;"
            "    border: none;"
            "}"
        );

        QVBoxLayout* contentLayout = new QVBoxLayout(container);

        titleLabel = new QLabel("Notification", container);
        titleLabel->setStyleSheet("color:  #1ABC9C; font-weight: bold; font-size:  14px;");
        
        messageLabel = new QLabel("", container);
        messageLabel->setWordWrap(true);
        messageLabel->setStyleSheet("font-size: 12px;");

        QPushButton* closeBtn = new QPushButton("×", container);
        closeBtn->setFixedSize(25, 25);
        closeBtn->setCursor(Qt::PointingHandCursor);
        closeBtn->setStyleSheet(
            "QPushButton { "
            "    background: transparent; "
            "    color: #888; "
            "    border: none; "
            "    font-weight:  bold; "
            "    font-size: 18px; "
            "}"
            "QPushButton:hover { "
            "    color: #FF5555; "
            "    background-color: rgba(255, 85, 85, 30);"
            "}"
        );
        connect(closeBtn, &QPushButton::clicked, this, [this]() {
          
            this->hide();
        });

        QHBoxLayout* headerLayout = new QHBoxLayout();
        headerLayout->addWidget(titleLabel);
        headerLayout->addStretch();
        headerLayout->addWidget(closeBtn);

        contentLayout->addLayout(headerLayout);
        contentLayout->addWidget(messageLabel);
        
        QPushButton* debugBtn = new QPushButton("Show Alerts", container);
        debugBtn->setFixedHeight(40);
        debugBtn->setCursor(Qt::PointingHandCursor);
        debugBtn->setStyleSheet(
            "QPushButton { "
            "    background-color: #1ABC9C; "   /* Verdele principal (Teal) */
            "    color: white; "
            "    border: 2px solid #16A085; "   /* Un verde puțin mai închis pentru contur */
            "    border-radius: 5px; "
            "    font-weight: bold; "
            "    font-size: 13px; "
            "    padding: 8px;"
            "}"
            "QPushButton:hover { "
            "    background-color: #16A085; "   /* Verde mai închis la hover */
            "}"
            "QPushButton:pressed { "
            "    background-color: #0E6655; " 
            "}"
        );
        connect(debugBtn, &QPushButton::clicked, this, [this]() {
            this->page_manager->change_page(7);
            this->hide();
        });
        contentLayout->addSpacing(10);
        contentLayout->addWidget(debugBtn);
        
        mainLayout->addWidget(container);

        this->hide();
    }

    void showMessage(const QString& title, const QString& message, bool isError = false) {
        titleLabel->setText(title);
        messageLabel->setText(message);

        if(isError) {
            titleLabel->setStyleSheet("color:  #E74C3C; font-weight: bold; font-size: 14px;");
            container->setStyleSheet(
                "QFrame#AlertFrame { "
                "    background-color: #252525; "
                "    border: 1px solid #E74C3C; "
                "    border-radius: 10px; "
                "}"
                "QLabel {"
                "    color: #E0E0E0;"
                "    border: none;"
                "}"
            );
        } else {
            titleLabel->setStyleSheet("color: #1ABC9C; font-weight: bold; font-size: 14px;");
            container->setStyleSheet(
                "QFrame#AlertFrame { "
                "    background-color: #252525; "
                "    border: 1px solid #1ABC9C; "
                "    border-radius: 10px; "
                "}"
                "QLabel {"
                "    color: #E0E0E0;"
                "    border:  none;"
                "}"
            );
        }

        positionBottomRight();
        this->raise();
        this->show();
        QApplication::beep();
        
        qDebug() << "AlertPopup displayed at:" << this->pos();
    }

private:
    void positionBottomRight() {
        if(parentWidget()) {
            QWidget* parent = parentWidget();
            QPoint globalParentPos = parent->mapToGlobal(QPoint(0,0));
            
            int margin = 20;

            int x = globalParentPos.x() + parent->width() - this->width() - margin - 10;
            int y = globalParentPos.y() + parent->height() - this->height() - margin - 10;

            this->move(x, y);
        }
    }
};