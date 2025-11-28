#include "TableWidget.h"
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <string>
#include <iostream>

#include "../../../utils/BetterString.hpp"
TableMenu::TableMenu()
{
    last_id=0;
    widget= new QWidget();
    QGridLayout *layout = new QGridLayout();
    table = new QTableWidget();
    table->setColumnCount(6);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList headers = {"ID","Timestamp", "Severity", "Hostname", "Source", "Content"};
    table->setHorizontalHeaderLabels(headers);
    auto header = table->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::Interactive);
    header->setSectionResizeMode(1, QHeaderView::Interactive);
    header->setSectionResizeMode(2, QHeaderView::Interactive);
    header->setSectionResizeMode(3, QHeaderView::Interactive);
    header->setSectionResizeMode(4, QHeaderView::Interactive);
    header->setSectionResizeMode(5, QHeaderView::Stretch); 
    
    
    header->resizeSection(0, 100); 
    header->resizeSection(1, 100);  
    header->resizeSection(2, 150);
    header->resizeSection(3, 100); 
    header->resizeSection(4, 100);  
    layout->addWidget(table);
    widget->setLayout(layout);
}

QWidget *TableMenu::get_widget()
{
    return widget;
}
void TableMenu::pop()
{
    int lastRow = table->rowCount() - 1;
    if (lastRow >= 0)
        table->removeRow(lastRow);
}
unsigned int TableMenu::get_id()
{
    return last_id;
}
void TableMenu::add(std::vector<std::string> logs)
{
    for(auto log : logs ){
        auto content = BetterString::split(log,"[]");
        //qDebug()<<log.c_str()<< content.size();
        if(content.size()<6){
           continue;
        }
        table->insertRow(0);
        for(int i=0;i<=5;++i){
            table->setItem(0, i, new QTableWidgetItem(QString::fromStdString(content[i])));
            
        }
        try{
            last_id = std::stoi(content[0])+1;
        }
        catch(std::exception & e){
            qDebug()<<e.what();
        }
        
    }
   
}
