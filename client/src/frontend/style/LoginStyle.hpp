#pragma once 

#include <string>

const std::string login_style(){
    return R"(
        /* 1. FUNDAL GENERAL - Mult mai închis */
        QWidget {
            background-color: #121212; /* Negru-gri foarte închis */
            font-family: 'Segoe UI', sans-serif;
            font-size: 14px;
            color: #E0E0E0; /* Alb mai stins pentru text */
        }

        /* 2. TITLUL (Welcome Back) - Turcoaz */
        QLabel#titleLabel {
            font-size: 28px;
            font-weight: bold;
            color: #1ABC9C; /* Turcoaz vibrant */
            margin-bottom: 25px;
        }

        /* 3. ETICHETE (Username, Password) */
        QLabel {
            font-size: 14px;
            color: #B0B0B0; /* Gri deschis */
            margin-top: 10px;
        }

        /* 4. INPUT-URI - Fundal închis */
        QLineEdit {
            background-color: #1E1E1E; /* Puțin mai deschis ca fundalul */
            border: 2px solid #333333;
            border-radius: 15px;
            padding: 8px 15px;
            color: #ffffff;
            font-size: 15px;
        }

        /* Focus cu Turcoaz */
        QLineEdit:focus {
            border: 2px solid #1ABC9C; /* Bordură turcoaz la focus */
            background-color: #252525;
        }

        /* 5. BUTON (Login) - Gradient Verde-Turcoaz */
        QPushButton {
            /* Gradient de la un Verde-Marin închis spre Turcoaz */
            background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #16A085, stop:1 #1ABC9C);
            color: white;
            border-radius: 20px;
            padding: 10px 20px;
            font-weight: bold;
            font-size: 16px;
            border: none;
            margin-top: 20px;
        }

        QPushButton:hover {
            /* Gradient puțin mai luminos la hover */
            background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #1ABC9C, stop:1 #2ECC71);
            margin-top: 18px;
            margin-bottom: 2px;
        }

        QPushButton:pressed {
            background-color: #0E6655; /* Foarte închis la apăsare */
            margin-top: 20px;
            margin-bottom: 0px;
        }

        /* 6. EROARE */
        QLabel#errorLabel {
            color: #FF5252; /* Roșu aprins pentru vizibilitate pe fundal negru */
            font-weight: bold;
            font-size: 13px;
            margin-top: 10px;
        }
    )";
}