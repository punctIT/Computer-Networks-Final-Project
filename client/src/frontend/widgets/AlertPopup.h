#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>

class AlertPopup : public QWidget {
    Q_OBJECT
private:
    QLabel* titleLabel;
    QLabel* messageLabel;

public:
    AlertPopup(QWidget* parent) : QWidget(parent) {
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
        this->setAttribute(Qt::WA_TranslucentBackground);
        this->setAttribute(Qt::WA_ShowWithoutActivating);

        this->setFixedSize(320, 110);

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(10, 10, 10, 10);

        QFrame* container = new QFrame(this);
        container->setObjectName("AlertFrame");
        
        container->setStyleSheet(
            "QFrame#AlertFrame {"
            "    background-color: #252525;"
            "    border: 1px solid #1ABC9C;"
            "    border-radius: 10px;"
            "}"
            "QLabel {"
            "    color: #E0E0E0;"
            "    border: none;"
            "}"
        );

        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(15);
        shadow->setColor(QColor(0, 0, 0, 150));
        shadow->setOffset(0, 4);
        container->setGraphicsEffect(shadow);

        QVBoxLayout* contentLayout = new QVBoxLayout(container);

        titleLabel = new QLabel("Notification", container);
        titleLabel->setStyleSheet("color: #1ABC9C; font-weight: bold; font-size: 14px;");
        
        messageLabel = new QLabel("", container);
        messageLabel->setWordWrap(true);
        messageLabel->setStyleSheet("font-size: 12px;");

        QPushButton* closeBtn = new QPushButton("×", container);
        closeBtn->setFixedSize(20, 20);
        closeBtn->setCursor(Qt::PointingHandCursor);
        closeBtn->setStyleSheet(
            "QPushButton { background: transparent; color: #888; border: none; font-weight: bold; font-size: 16px; }"
            "QPushButton:hover { color: #FF5555; }"
        );
        connect(closeBtn, &QPushButton::clicked, this, &AlertPopup::hide);

        QHBoxLayout* headerLayout = new QHBoxLayout();
        headerLayout->addWidget(titleLabel);
        headerLayout->addStretch();
        headerLayout->addWidget(closeBtn);

        contentLayout->addLayout(headerLayout);
        contentLayout->addWidget(messageLabel);
        
        mainLayout->addWidget(container);

        this->hide();
    }

    void showMessage(const QString& title, const QString& message, bool isError = false) {
        titleLabel->setText(title);
        messageLabel->setText(message);

        QFrame* frame = this->findChild<QFrame*>("AlertFrame");
        if(isError && frame) {
            titleLabel->setStyleSheet("color: #E74C3C; font-weight: bold; font-size: 14px;");
            frame->setStyleSheet("QFrame#AlertFrame { background-color: #252525; border: 1px solid #E74C3C; border-radius: 10px; }");
        } else if (frame) {
             titleLabel->setStyleSheet("color: #1ABC9C; font-weight: bold; font-size: 14px;");
             frame->setStyleSheet("QFrame#AlertFrame { background-color: #252525; border: 1px solid #1ABC9C; border-radius: 10px; }");
        }

        positionBottomRight();
        this->show();
        this->raise();
    }

private:
    void positionBottomRight() {
        if(parentWidget()) {
            int margin = 20;
            int x = parentWidget()->width() - this->width() - margin;
            int y = parentWidget()->height() - this->height() - margin;
            this->move(x, y);
        }
    }
};