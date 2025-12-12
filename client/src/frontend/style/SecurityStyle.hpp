#pragma once 

#include <string>


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