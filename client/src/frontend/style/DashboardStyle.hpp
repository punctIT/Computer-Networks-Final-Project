#pragma once

#include <string>

const std::string get_dashboard_menu_Style(){
    return R"(
        QPushButton {
            /* STARE NORMALĂ: Subtilă, se integrează în fundalul negru */
            background-color: rgba(255, 255, 255, 0.05); /* Foarte puțin vizibil, doar conturează */
            color: #B0B0B0; /* Gri deschis, nu alb pur, pentru a nu distrage atenția */
            border: none;
            
            /* Forma de capsulă */
            border-radius: 20px; /* Rotunjire consistentă cu Login/Connect */
            
            padding: 10px 30px; 
            font-size: 14px;
            font-weight: 600;
            min-width: 100px;
        }

        QPushButton:hover {
            /* HOVER: Turcoaz vibrant */
            background-color: #1ABC9C; 
            color: #121212; /* Textul devine negru (contrast excelent pe turcoaz) */
        }

        QPushButton:pressed {
            /* PRESSED: Turcoaz închis */
            background-color: #0E6655;
            color: #FFFFFF; /* Textul revine la alb */
            padding-top: 12px; 
            padding-bottom: 8px;
        }
    )";
}