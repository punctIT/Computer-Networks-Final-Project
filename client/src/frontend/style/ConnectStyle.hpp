#pragma once 

#include <string>

inline std::string connect_style(){
    return R"(
        QWidget {
            background-color: #121212;
            font-family: 'Segoe UI', sans-serif;
            font-size: 14px;
            color: #E0E0E0;
        }

        QLabel#titleLabel {
            font-size: 26px;
            font-weight: bold;
            color: #1ABC9C;
            margin-bottom: 20px;
        }

        QLabel {
            font-size: 14px;
            color: #B0B0B0;
            margin-top: 10px;
        }

        QLineEdit {
            background-color: #1E1E1E;
            border: 2px solid #333333;
            border-radius: 15px;
            padding: 8px 15px;
            color: #ffffff;
            font-size: 15px;
        }

        QLineEdit:focus {
            border: 2px solid #1ABC9C;
            background-color: #252525;
        }

        QPushButton {
            background-color: transparent;
            border: 2px solid #1ABC9C;
            color: #1ABC9C;
            border-radius: 20px;
            
          
            padding: 10px 20px;  
            font-weight: bold;  
            font-size: 16px;
            
            margin-top: 5px;
        }


        QPushButton:hover {
            background-color: #1ABC9C;
            color: #121212;
        }

        QPushButton:pressed {
            background-color: #0E6655;
            margin-top: 15px;
            margin-bottom: 0px;
        }

        QPushButton#secondaryButton {
            background-color: transparent;
            border: 2px solid #1ABC9C;
            color: #1ABC9C;
            border-radius: 20px;
            margin-top: 5px;
        }

        QPushButton#secondaryButton:hover {
            background-color: #1ABC9C;
            color: #121212;
        }

        QLabel#errorLabel {
            color: #FF5252;
            font-weight: bold;
            padding: 5px;
        }
    )";
}