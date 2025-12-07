#pragma once 



#include <mutex>
#include <queue>
#include <expected>
#include <iostream>
#include <string>

template<class T>
class ThreadSafeQueue{
    private:
    std::queue<T> queue;
    std::mutex _mutex;
    public:
    void push(T value){
        std::lock_guard<std::mutex> lock(_mutex);
        this->queue.push(value);
    }
    std::expected<T,std::string> pop(){
        std::lock_guard<std::mutex> lock(_mutex);
        if(queue.empty()){
            return std::unexpected("Empty queue");
        }
        auto value = queue.front();
        queue.pop();
        return value;
    }
    
};


enum EventType { SYSLOG, AGENT_METRIC };

struct LogEvent {
    EventType type;       
    std::string source_ip;   
    std::string payload;  
};