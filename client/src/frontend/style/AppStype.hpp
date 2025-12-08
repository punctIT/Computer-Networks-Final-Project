#pragma once 

#include <string>

inline std::string main_app_style(){
    return R"(
        /* 1. SETĂRI GLOBALE */
        QMainWindow, QDialog {
            background-color: #121212; /* Fundalul principal negru-profund */
            color: #E0E0E0; /* Text alb-gri peste tot */
        }
        
        QWidget {
            font-family: 'Segoe UI', sans-serif;
            font-size: 14px;
            color: #E0E0E0;
        }

        /* 2. SCROLLBAR VERTICAL (Foarte important pentru tabel) */
        QScrollBar:vertical {
            border: none;
            background: #1E1E1E; /* Canalul barei - gri închis */
            width: 10px; /* Subțire */
            margin: 0px 0px 0px 0px;
        }

        QScrollBar::handle:vertical {
            background: #333333; /* Butonul de scroll - gri mai deschis */
            min-height: 20px;
            border-radius: 5px; /* Rotunjit */
        }

        QScrollBar::handle:vertical:hover {
            background: #1ABC9C; /* Devine TURCOAZ când pui mouse-ul pe el */
        }

        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px; /* Ascundem săgețile sus/jos standard */
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

        /* 4. TOOLTIPS (Mesajele care apar când ții mouse-ul) */
        QToolTip {
            background-color: #333333;
            color: #1ABC9C;
            border: 1px solid #1ABC9C;
            padding: 5px;
            border-radius: 3px;
        }

        /* 5. MENIURI (Dacă ai meniu sus File/Edit etc.) */
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

    )";
}

#pragma once 

#include <string>

inline std::string main_menu_style(){
    return R"(
        /* 1. CONTAINERUL PRINCIPAL (Bara de sus) */
        QWidget#mainMenuContainer {
            background-color: #1E1E1E; /* Puțin mai deschis decât fundalul paginii (#121212) */
            border-bottom: 2px solid #1ABC9C; /* Linie de accent Turcoaz jos */
        }

        /* 2. BUTOANELE DIN MENIU */
        QPushButton {
            background-color: transparent;
            border: none;
            border-radius: 5px;     
            color: #B0B0B0; /* Gri deschis */        
            font-weight: 600;
            font-size: 14px;
            padding: 8px 15px;    
            text-align: left;
            margin-right: 5px;
        }

        /* 3. HOVER (Când pui mouse-ul) */
        QPushButton:hover {      
            background-color: rgba(26, 188, 156, 0.1); /* Turcoaz foarte transparent */
            color: #1ABC9C; /* Textul devine Turcoaz vibrant */
        }

        /* 4. PRESSED */
        QPushButton:pressed {
            background-color: rgba(26, 188, 156, 0.2);
            color: #16A085;
        }
    )";
}