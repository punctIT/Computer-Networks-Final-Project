#include "server_request/DataRequester.hpp"


int  main(){
    DataRequester data;
    data.set_ip("0.0.0.0").set_port(8080).configure();
    data.sent_request("sa");
}