#include "server_request/DataRequester.hpp"


int  main(){
    DataRequester data;
    data.set_ip("127.0.0.1").set_port(8080).configure();
    data.sent_request("sa");
}