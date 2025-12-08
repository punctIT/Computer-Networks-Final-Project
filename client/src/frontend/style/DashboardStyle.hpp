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
        QFrame#TableFrame {
            background-color: #1E1E1E;
            border-radius: 15px;
            border: 2px solid #333333;
        }

        QTableWidget {
            background-color: transparent;
            border: none;
            gridline-color: #333333;
        }

        QHeaderView::section {
            background-color: transparent;
            color: #1ABC9C;
            font-weight: bold;
            border: none;
            padding: 8px;
            font-size: 13px;
            border-bottom: 2px solid #1ABC9C;
        }

        QTableWidget::item {
            color: #E0E0E0;
            padding: 10px;
            border-bottom: 1px solid #2A2A2A;
        }

        QTableWidget::item:selected {
            background-color: #0E6655;
            color: #FFFFFF;
        }

        QTableWidget::item:hover {
            background-color: #252525;
        }

        QTableCornerButton::section {
            background-color: transparent;
            border: none;
        }
    )";
}