#pragma once 

#include <string>

// Am pus inline pentru a evita erorile de multiple definition
inline std::string connect_style(){
    return R"(
        /* 1. FUNDAL GENERAL - Dark Mode profund */
        QWidget {
            background-color: #121212; /* Negru-gri foarte închis */
            font-family: 'Segoe UI', sans-serif;
            font-size: 14px;
            color: #E0E0E0; /* Alb stins */
        }

        /* 2. TITLUL (Connect) - Turcoaz */
        QLabel#titleLabel {
            font-size: 26px;
            font-weight: bold;
            color: #1ABC9C; /* Turcoaz vibrant */
            margin-bottom: 20px;
        }

        /* 3. ETICHETE NORMALE (IP, Port) */
        QLabel {
            font-size: 14px;
            color: #B0B0B0; /* Gri deschis */
            margin-top: 10px;
        }

        /* 4. INPUT-URI - Fundal închis */
        QLineEdit {
            background-color: #1E1E1E;
            border: 2px solid #333333;
            border-radius: 15px; /* Colțuri rotunde */
            padding: 8px 15px;
            color: #ffffff;
            font-size: 15px;
        }

        /* Focus cu Turcoaz */
        QLineEdit:focus {
            border: 2px solid #1ABC9C; /* Bordură turcoaz */
            background-color: #252525;
        }

        /* 5. BUTON PRINCIPAL (Connect) - Gradient Verde-Turcoaz */
        QPushButton {
            background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #16A085, stop:1 #1ABC9C);
            color: white;
            border-radius: 20px; /* Foarte rotund */
            padding: 10px 20px;
            font-weight: bold;
            font-size: 16px;
            border: none;
            margin-top: 15px;
        }

        QPushButton:hover {
            background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #1ABC9C, stop:1 #2ECC71);
            margin-top: 13px; /* Mic efect de ridicare */
            margin-bottom: 2px;
        }

        QPushButton:pressed {
            background-color: #0E6655; /* Întunecat la apăsare */
            margin-top: 15px; /* Revine la loc */
            margin-bottom: 0px;
        }

        /* 6. BUTON SECUNDAR (Localhost) - Outline Turcoaz */
        QPushButton#secondaryButton {
            background-color: transparent;
            border: 2px solid #1ABC9C; /* Contur Turcoaz */
            color: #1ABC9C;
            border-radius: 20px;
            margin-top: 5px;
        }

        QPushButton#secondaryButton:hover {
            background-color: #1ABC9C; /* Umple cu turcoaz la hover */
            color: #121212; /* Text negru */
        }

        /* 7. EROAREA */
        QLabel#errorLabel {
            color: #FF5252; /* Roșu aprins */
            font-weight: bold;
            padding: 5px;
        }
    )";
}