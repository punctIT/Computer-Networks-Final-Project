#pragma once 

#include <string>

inline std::string top_part_home_style(){
    return R"(
        QWidget {
            background-color: #121212; 
            font-family: 'Segoe UI', sans-serif;
        }

        QLabel {
            font-size: 24px;
            font-weight: bold;
            color: #E0E0E0;
            padding: 10px;
            margin-bottom: 10px;
        }

        QPushButton {
            background-color: #1E1E1E;
            color: #E0E0E0;
            border: 2px solid #333333;
            border-radius: 20px;
            min-width: 130px;
            min-height: 130px;
            font-size: 18px;
            font-weight: 600;
            margin: 5px;
        }

        QPushButton:hover {
            background-color: #1ABC9C;
            color: #121212;
            border: 2px solid #16A085;
            margin-top: 2px;
        }

        QPushButton:pressed {
            background-color: #0E6655;
            color: white;
            margin-top: 5px;
        }
    )";
}

inline std::string table_style(){
    return R"(
        QTableWidget {
            background-color: #1E1E1E;
            color: #E0E0E0;
            border: 1px solid #333333;
            gridline-color: #333333;
            selection-background-color: #1ABC9C;
        }

        QTableWidget::item {
            padding: 8px; 
            border-bottom: 1px solid #2A2A2A;
        }

        QTableWidget::item:selected {
            background-color: #0E6655;
            color: #FFFFFF;
        }
        
        QTableWidget::item:hover {
            background-color: #252525;
        }

        QHeaderView::section {
            background-color: #252525;
            color: #1ABC9C;
            padding: 8px;
            font-weight: bold;
            border: none;
            border-bottom: 2px solid #1ABC9C;
            text-transform: uppercase;
            font-size: 12px;
        }

        QTableCornerButton::section {
            background-color: #252525;
            border: none;
        }
             QPushButton {
            background-color: transparent;
            border: 2px solid #1ABC9C;
            color: #1ABC9C;
            border-radius: 20px;
            
          
            padding: 5px 15px;  
            font-weight: bold;  
            font-size: 12px;
            
            margin-top: 5px;
        }

        QPushButton:hover {
            background-color: #1ABC9C;
            color: #121212;
        }

        QPushButton:pressed {
            background-color: #0E6655;
            margin-top: 15px; /* Efectul de apăsare */
            margin-bottom: 0px;
        }

    )";   
}