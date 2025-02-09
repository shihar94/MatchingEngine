#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <mutex>
#include <memory>
#include <string>

class Logger 
{
    public:
        Logger& operator= (const Logger&) = delete;
        void init(std::string file);
        void logStmt(const char* stmt);
        void endLogging(std::string closeStmt);
    
        static std::shared_ptr<Logger> getInstance();

        std::string m_fileName;
        std::mutex m_mutex;
        FILE *fp = nullptr;

    private:
        Logger()
        {
            std::cout << "Singleton Logging File object created" << std::endl;
        };
        void flush();

        static std::shared_ptr<Logger> m_instance ;

};




#endif

