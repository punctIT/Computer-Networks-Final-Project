#pragma once

#include <string>

inline std::string get_dashboard_menu_Style(){
    return R"(
        QPushButton {
            background-color: rgba(255, 255, 255, 0.05);
            color: #B0B0B0;
            border: none;
            border-radius: 20px;
            padding: 10px 30px;
            font-size: 14px;
            font-weight: 600;
            min-width: 100px;
        }

        QPushButton:hover {
            background-color: #1ABC9C;
            color: #121212;
        }

        QPushButton:pressed {
            background-color: #0E6655;
            color: #FFFFFF;
            padding-top: 12px;
            padding-bottom: 8px;
        }
    )";
}
inline std::string get_table_style(){
    return R"(
        /* 1. Cadrul principal - GRI ÎNCHIS (nu negru) */
        QFrame#TableFrame {
            background-color: #252525;    /* Gri solid */
            border-radius: 15px;
            border: 1px solid #404040;    /* Bordură un pic mai deschisă */
        }

        /* 2. Tabelul */
        QTableWidget {
            background-color: #252525;    /* Același gri și aici */
            gridline-color: #353535;
            border: none;
        }

        /* 3. Capul de tabel - GRI ÎNCHIS (NU ALB, NU TRANSPARENT) */
        QHeaderView::section {
            background-color: #252525;    /* Fundal gri închis solid */
            color: #1ABC9C;               /* Textul rămâne turcoaz */
            font-weight: bold;
            border: none;
            padding: 5px;
            font-size: 13px;
            border-bottom: 2px solid #1ABC9C;
        }

        /* 4. Rândurile */
        QTableWidget::item {
            color: #DDDDDD;               /* Text gri deschis */
            padding: 10px;
            border-bottom: 1px solid #303030;
        }

        /* Selecție */
        QTableWidget::item:selected {
            background-color: #0E6655;
            color: #FFFFFF;
        }

        /* Hover */
        QTableWidget::item:hover {
            background-color: #2E2E2E;    /* Un gri puțin mai deschis la mouse */
        }

        /* Colțul */
        QTableCornerButton::section {
            background-color: #252525;
            border: none;
        }
    )";
}
inline std::string get_combobox(){
    return R"(
        QComboBox {
            background-color: #1E1E1E;
            color: #FFFFFF;
            border: 2px solid #333333;
            border-radius: 15px;
            padding: 8px 15px;
            font-size:  15px;
        }
        QComboBox: hover, QComboBox:on {
            border:  2px solid #1ABC9C;
        }

        /* Dropdown arrow verde */
        QComboBox:: drop-down { 
            border: none; 
            width: 30px; 
        }
        QComboBox:: down-arrow {
            border-left: 6px solid transparent;
            border-right: 6px solid transparent;
            border-top: 8px solid #1ABC9C;
            margin-right: 10px;
        }

        /* Lista dropdown - FORȚEAZĂ VERDE */
        QListView {
            background-color: #1E1E1E;
            border: 2px solid #1ABC9C;  /* VERDE */
            border-radius: 10px;
            color: #E0E0E0;
            outline: 0;
            padding: 4px;
            selection-background-color: #1ABC9C; /* VERDE pentru selecție */
        }

        QListView::item {
            padding: 8px;
            border-radius: 5px;
            background-color: transparent;
            color: #FFFFFF;
        }

        QListView::item:selected, QListView::item:hover {
            background-color: #1ABC9C; /* VERDE */
            color:  #121212;
        }

        /* Dacă ai scrollbar în dropdown */
        QScrollBar: vertical {
            background: #1E1E1E;
            width: 12px;
            border-radius: 6px;
        }
        QScrollBar::handle:vertical {
            background: #1ABC9C; /* VERDE */
            border-radius: 6px;
        }
        QScrollBar::handle:vertical:hover {
            background: #16A085; /* VERDE mai închis */
        }
    )";
}