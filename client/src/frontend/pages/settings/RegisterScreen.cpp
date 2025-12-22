#include "RegisterScreen.h"

void RegisterScreen::bind_buttons()
{
    QObject::connect(this->signin_btn, &QPushButton::clicked, [this]() {
        error_lbn->setText("");
        if(password_input->text()!= password2_input->text()){
            error_lbn->show();
            error_lbn->setText("Diffenent password");
            return;
        }  
        auto response = this->data_requester->sent(this->data_requester->register_request(username_input->text().toStdString(),password_input->text().toStdString()));
        if(!response.has_value()){
            qDebug()<<response.error().c_str();
            return;
        }
    });
}

RegisterScreen::RegisterScreen(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager)
{
    screen = new QWidget();
    this->data_requester = data;
    this->page_manager = page_manager;
    
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(10);
    layout->setContentsMargins(60, 40, 60, 40);

    QLabel *title_label = new QLabel("CREATE ACCOUNT");
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setStyleSheet("font-size: 28px; font-weight: 800; color: #1ABC9C; margin-bottom: 20px; font-family: 'Segoe UI', sans-serif;");

    QString labelStyle = "color: #B0B0B0; font-size: 11px; font-weight: bold; margin-bottom: 2px; margin-top: 8px; letter-spacing: 1px;";
    
    QLabel *user_lbl = new QLabel("USERNAME");
    user_lbl->setStyleSheet(labelStyle);
    
    QLabel *pass_lbl = new QLabel("PASSWORD");
    pass_lbl->setStyleSheet(labelStyle);
    
    QLabel *pass2_lbl = new QLabel("CONFIRM PASSWORD");
    pass2_lbl->setStyleSheet(labelStyle);

    error_lbn = new QLabel();
    error_lbn->setStyleSheet("color: #E74C3C; font-size: 12px; font-weight: bold;");
    error_lbn->setAlignment(Qt::AlignCenter);
    error_lbn->hide();

    username_input = new QLineEdit();
    username_input->setPlaceholderText("Username");
    
    password_input = new QLineEdit();
    password_input->setPlaceholderText("Password");
    password_input->setEchoMode(QLineEdit::Password);

    password2_input = new QLineEdit();
    password2_input->setPlaceholderText("Confirm Password");
    password2_input->setEchoMode(QLineEdit::Password);

    QString inputStyle = "QLineEdit { "
                         "background-color: #252525; "
                         "color: #FFFFFF; "
                         "border: 2px solid #333333; "
                         "border-radius: 15px; "
                         "padding: 10px 15px; "
                         "font-size: 14px; "
                         "} "
                         "QLineEdit:focus { border: 2px solid #1ABC9C; background-color: #2A2A2A; }";

    username_input->setStyleSheet(inputStyle);
    password_input->setStyleSheet(inputStyle);
    password2_input->setStyleSheet(inputStyle);

    signin_btn = new QPushButton("REGISTER");
    signin_btn->setCursor(Qt::PointingHandCursor);
    signin_btn->setStyleSheet(
        "QPushButton {"
        "   background-color: #1ABC9C;"
        "   color: #121212;"
        "   border: none;"
        "   border-radius: 20px;"
        "   padding: 12px 30px;"
        "   font-size: 14px;"
        "   font-weight: 600;"
        "   margin-top: 20px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #48C9B0;"
        "   color: #121212;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #0E6655;"
        "   color: #FFFFFF;"
        "   padding-top: 14px;"
        "   padding-bottom: 10px;"
        "}"
    );



    layout->addWidget(title_label);
    layout->addWidget(user_lbl);
    layout->addWidget(username_input);
    layout->addWidget(pass_lbl);
    layout->addWidget(password_input);
    layout->addWidget(pass2_lbl);
    layout->addWidget(password2_input);
    layout->addWidget(error_lbn);
    layout->addSpacing(5);
    layout->addWidget(signin_btn);
    layout->addStretch();
    
    screen->setLayout(layout);
    screen->setStyleSheet("background-color: #1E1E1E;");
    
    bind_buttons();
}

QWidget *RegisterScreen::get_screen()
{
    return screen;
}