#include "UnknownAgentDashboard.h"
#include "../../style/DashboardStyle.hpp"

void UnknownAgentDashboardScreen::bind_buttons()
{
    connect(data_requester. get(), &DataRequester::UpdateUnknownAgent, this, [this](QString msg) {
        auto data = JUNK::deserialize(msg.toStdString());
        if (data.value()["sources"].has_value()){
            sources_table->add(BetterString::split(data. value()["sources"].value(),"{}"));
        }
        if (data.value()["agents"].has_value()){
            Logs_table->add(BetterString::split(data. value()["agents"].value(),"{}"));
        }
    });
}

UnknownAgentDashboardScreen::UnknownAgentDashboardScreen(std::shared_ptr<DataRequester> data, const std::shared_ptr<PageManager> &page_manager, std::shared_ptr<QMainWindow> window) : Page(data, page_manager, window)
{
    QGridLayout *layout = new QGridLayout;
    
    Logs_table = std::make_shared<AgentLogsTable>();
    sources_table = std:: make_shared<AgentSourcesTable>();
    
    btn = new QPushButton("UNKNOWN Dashboard AGENT");
    btn->setStyleSheet("background-color: black; color: white;");
    
    layout->addWidget(btn, 0, 0, 1, 2);
    layout->addWidget(Logs_table->get_widget(), 1, 0);
    layout->addWidget(sources_table->get_widget(), 1, 1);
    
    bind_buttons();
    page->setLayout(layout);
}

void UnknownAgentDashboardScreen::on_enter() {
    qDebug()<<"whitelsit enter";
}

void UnknownAgentDashboardScreen::on_exit() {
    qDebug()<<"whitelsit leave";
}

AgentLogsTable::AgentLogsTable()
{
    widget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    QFrame *frame = new QFrame();
    frame->setObjectName("TableFrame");
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    frameLayout->setContentsMargins(0, 10, 0, 10);

    table = new QTableWidget();
    table->setColumnCount(1);
    
    QStringList headers = {"Unknowns ip source"};
    table->setHorizontalHeaderLabels(headers);

    table->setShowGrid(false);
    table->setFocusPolicy(Qt::NoFocus);
    table->setSelectionMode(QAbstractItemView:: NoSelection);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    widget->setStyleSheet(QString::fromStdString(get_table_style()));

    frameLayout->addWidget(table);
    mainLayout->addWidget(frame);
}

QWidget *AgentLogsTable::get_widget()
{
    return this->widget;
}

void AgentLogsTable::clear()
{
    table->setRowCount(0);
}

void AgentLogsTable::add(std::vector<std::string> data)
{
    table->setUpdatesEnabled(false);
    clear();

    for(auto entry : data) 
    {
        if(entry.empty()){
            continue;
        }
        table->insertRow(table->rowCount());
        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(entry));
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        table->setItem(table->rowCount() - 1, 0, item);
    }

    table->setUpdatesEnabled(true);
}

AgentSourcesTable::AgentSourcesTable()
{
    widget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    QFrame *frame = new QFrame();
    frame->setObjectName("TableFrame");
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    frameLayout->setContentsMargins(0, 10, 0, 10);

    table = new QTableWidget();
    table->setColumnCount(1);
    
    QStringList headers = {"IP Sources"};
    table->setHorizontalHeaderLabels(headers);

    table->setShowGrid(false);
    table->setFocusPolicy(Qt::NoFocus);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    widget->setStyleSheet(QString:: fromStdString(get_table_style()));

    frameLayout->addWidget(table);
    mainLayout->addWidget(frame);
}

QWidget *AgentSourcesTable::get_widget()
{
    return this->widget;
}

void AgentSourcesTable::clear()
{
    table->setRowCount(0);
}

void AgentSourcesTable::add(std::vector<std::string> data)
{
    table->setUpdatesEnabled(false);
    clear();

    for(auto entry : data) 
    {
        if(entry.empty()){
            continue;
        }
        table->insertRow(table->rowCount());
        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(entry));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(table->rowCount() - 1, 0, item);
    }

    table->setUpdatesEnabled(true);
}