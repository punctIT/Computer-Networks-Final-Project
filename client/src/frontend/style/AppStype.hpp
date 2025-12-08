#pragma once 

#include <string>

inline std::string main_app_style(){
    return R"(
        QMainWindow, QDialog {
            background-color: #121212; 
            color: #E0E0E0;
        }
        
        QWidget {
            font-family: 'Segoe UI', sans-serif;
            font-size: 14px;
            color: #E0E0E0;
        }

        QScrollBar:vertical {
            border: none;
            background: #1E1E1E; 
            width: 10px;
            margin: 0px 0px 0px 0px;
        }

        QScrollBar::handle:vertical {
            background: #333333;
            min-height: 20px;
            border-radius: 5px; 
        }

        QScrollBar::handle:vertical:hover {
            background: #1ABC9C; 
        }

        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }

        /* 3. SCROLLBAR ORIZONTAL */
        QScrollBar:horizontal {
            border: none;
            background: #1E1E1E;
            height: 10px;
            margin: 0px 0px 0px 0px;
        }

        QScrollBar::handle:horizontal {
            background: #333333;
            min-width: 20px;
            border-radius: 5px;
        }

        QScrollBar::handle:horizontal:hover {
            background: #1ABC9C;
        }

        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
            width: 0px;
        }

        QToolTip {
            background-color: #333333;
            color: #1ABC9C;
            border: 1px solid #1ABC9C;
            padding: 5px;
            border-radius: 3px;
        }

        QMenuBar {
            background-color: #1E1E1E;
            color: #E0E0E0;
        }
        
        QMenuBar::item:selected {
            background-color: #1ABC9C;
            color: #121212;
        }
        
        QMenu {
            background-color: #252525;
            color: #E0E0E0;
            border: 1px solid #333333;
        }
        
        QMenu::item:selected {
            background-color: #1ABC9C;
            color: #121212;
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

    )";
}

inline std::string main_menu_style(){
    return R"(
       
        QWidget#mainMenuContainer {
            background-color: #1E1E1E;
            border-bottom: 2px solid #1ABC9C; 
        }
        QPushButton {
            background-color: transparent;
            border: none;
            border-radius: 5px;     
            color: #B0B0B0;        
            font-weight: 600;
            font-size: 14px;
            padding: 8px 15px;    
            text-align: left;
            margin-right: 5px;
        }
        QPushButton:hover {      
            background-color: rgba(26, 188, 156, 0.1);
            color: #1ABC9C;
        }

        QPushButton:pressed {
            background-color: rgba(26, 188, 156, 0.2);
            color: #16A085;
        }
    )";
}