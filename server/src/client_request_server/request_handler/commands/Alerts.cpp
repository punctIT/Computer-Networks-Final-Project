#include "Alerts.hpp"

Alerts::Alerts(std::shared_ptr<DBManager> &alerts):alerts(alerts)
{
}

std::expected<std::string, std::string> Alerts::last_alert(JUNK &request)
{
    return response_formater(true,"update_alerts","NIMIC ");
}