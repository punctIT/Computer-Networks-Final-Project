#include "server_request/DataRequester.h"
#include <iostream>
#include "utils/JUNK.hpp"
#include "frontend/app.h"
#include <QtWidgets/QApplication>
int  main(){
    int argc = 0;
    char *argv[] = {};
    QApplication app(argc, argv);
    App a;
    return app.exec();
    
}