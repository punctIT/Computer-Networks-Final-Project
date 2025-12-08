#pragma once 

#include <string>
inline  std::string top_part_home_style(){
    return R"(
        /* 1. FUNDAL PAGINĂ */
        QWidget {
            background-color: #121212; 
            font-family: 'Segoe UI', sans-serif;
        }

        /* 2. TITLUL (Home) */
        QLabel {
            font-size: 24px;
            font-weight: bold;
            color: #E0E0E0;
            padding: 10px;
            margin-bottom: 10px;
        }

        /* 3. BUTOANELE TILE (Stil Nokia / Metro) */
        QPushButton {
            background-color: #1E1E1E; /* Gri închis (Card) */
            color: #E0E0E0;
            border: 2px solid #333333; /* Contur subtil */
            border-radius: 20px; /* Colțuri ușor rotunjite, dar păstrează forma pătrată */
            
            /* DIMENSIUNI PENTRU ASPECT PĂTRAT */
            min-width: 130px;
            min-height: 130px;
            
            font-size: 18px;
            font-weight: 600;
            margin: 5px; /* Spațiu între ele */
        }

        /* HOVER - Se aprinde tot pătratul */
        QPushButton:hover {
            background-color: #1ABC9C; /* Turcoaz */
            color: #121212; /* Text negru pentru contrast */
            border: 2px solid #16A085;
            margin-top: 2px; /* Mic efect de mișcare */
        }

        /* PRESSED */
        QPushButton:pressed {
            background-color: #0E6655;
            color: white;
            margin-top: 5px;
        }
    )";
}
inline std::string table_style(){
    return R"(
        /* 1. TABLE WIDGET (Containerul) */
        QTableWidget {
            background-color: #1E1E1E; /* Gri închis (Surface color) */
            color: #E0E0E0; /* Text deschis */
            border: 1px solid #333333; /* Bordură exterioară subtilă */
            gridline-color: #333333; /* Liniile dintre celule (întunecate) */
            selection-background-color: #1ABC9C; /* Setează culoarea de bază pt selecție */
        }

        /* 2. CELULELE (Items) */
        QTableWidget::item {
            padding: 8px; 
            border-bottom: 1px solid #2A2A2A; /* Separator orizontal discret */
        }

        /* 3. SELECȚIA (Când dai click pe un rând) */
        QTableWidget::item:selected {
            background-color: #0E6655; /* Turcoaz închis (ca la butonul pressed) */
            color: #FFFFFF; /* Text alb pur pentru contrast */
        }
        
        /* HOVER pe celulă (Opțional, dar arată modern) */
        QTableWidget::item:hover {
            background-color: #252525; /* Se luminează puțin când treci cu mouse-ul */
        }

        /* 4. HEADERUL (Capul de tabel) */
        QHeaderView::section {
            background-color: #252525; /* Puțin mai deschis decât tabelul */
            color: #1ABC9C; /* Text TURCOAZ pentru titlurile de coloane */
            padding: 8px;
            font-weight: bold;
            border: none;
            border-bottom: 2px solid #1ABC9C; /* Linie de accent turcoaz sub header */
            text-transform: uppercase;
            font-size: 12px;
        }

        /* 5. Colțul din stânga-sus (unde se întâlnesc headerele) */
        QTableCornerButton::section {
            background-color: #252525;
            border: none;
        }
    )";   
}