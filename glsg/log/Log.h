#ifndef GLSG_LOG_H
#define GLSG_LOG_H

#include <sstream>

namespace glsg {

class Log {
public:
    enum Level {
        DEBUG = 0,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    enum Color {
        FG_RED = 31,
        FG_GREEN = 32,
        FG_YELLOW = 33,
        FG_BLUE = 34,
        FG_PURPLE = 35,
        FG_DEFAULT = 39
    };

    static Level AppLogLevel;

    Log();

    ~Log();

    std::ostringstream &getLogger(Level l);

    std::string levelString(Level l);

    std::string levelColor(Level l);

    std::string timeString();

private:
    std::ostringstream _os;
};

#define LDEBUG(msg) LOG(Log::DEBUG)<<__FILE__<<":"<<__LINE__<<" - "<<msg
#define LINFO(msg) LOG(Log::INFO)<<__FILE__<<":"<<__LINE__<<" - "<<msg
#define LWARNING(msg) LOG(Log::WARNING)<<__FILE__<<":"<<__LINE__<<" - "<<msg
#define LERROR(msg) LOG(Log::ERROR)<<__FILE__<<":"<<__LINE__<<" - "<<msg
#define LFATAL(msg) LOG(Log::FATAL)<<__FILE__<<":"<<__LINE__<<" - "<<msg

#define LOG(llevel) \
if (llevel < Log::AppLogLevel) ; \
else Log().getLogger(llevel)

// script exports
void SDEBUG(std::string msg);

void SINFO(std::string msg);

void SWARNING(std::string msg);

void SERROR(std::string msg);

void SFATAL(std::string msg);

}

#endif
