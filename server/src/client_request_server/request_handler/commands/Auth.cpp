#include "Auth.hpp"

Auth::Auth(std::shared_ptr<SessionManager> &session, std::shared_ptr<AuthManager> &auth): session(session), auth(auth) {};

std::expected<std::string, std::string> Auth::login_request(JUNK &request)
{
    if(!request["username"].has_value()||!request["password"].has_value()){
        return std::unexpected("invalid format , username or password");
    }
    
    auto credentials_check=auth->check_credentials(request["username"].value(),request["password"].value());
    if(!credentials_check){
        return std::unexpected("Auth Error");
     }
    if(*credentials_check){
        std::string token = session->create_session(request["username"].value());
        //session->debug();
        return response_formater(true,"login",token);
    }
    return response_formater(false,"login","Invalid username or password");
}

std::expected<std::string, std::string> Auth::register_request(JUNK &request)
{
    //request.display();
    if(request["username"].has_value()&&request["password"].has_value()){
        auto credentials_check=auth->_register(request["username"].value(),request["password"].value());
        if(!credentials_check){
            return std::unexpected(credentials_check.error());
        }
        return response_formater(true,"register","NONE");
    }
    else {
        return std::unexpected("invalid format , username or password");
    } 
}

std::expected<std::string, std::string> Auth::logout_request(JUNK &request)
{
    if(!request["token"].has_value()){

    }
    auto result = session->remove_session(request["token"].value());
    if(!result){
        return std::unexpected(result.error());
    }
    //std::cout<<"[LOGOUT]"<<request["token"].value()<<std::endl;
    return response_formater(true,"logout","NONE");
}
