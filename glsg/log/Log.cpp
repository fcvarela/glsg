#include <string>
#include <sys/time.h>

#include <log/Log.h>

namespace glsg {

Log::Level Log::AppLogLevel;

// script exports
void SDEBUG(std::string msg) {
    LDEBUG(msg);
};

void SINFO(std::string msg) {
    LINFO(msg);
};

void SWARNING(std::string msg) {
    LWARNING(msg);
};

void SERROR(std::string msg) {
    LERROR(msg);
};

void SFATAL(std::string msg) {
    LFATAL(msg);
};

Log::Log() {
}

Log::~Log() {
    _os << std::endl;
    fprintf(stderr, "%s", _os.str().c_str());
    fflush(stderr);
}

std::ostringstream &Log::getLogger(Level l) {
    _os << levelColor(l);
    _os << timeString() << " - ";
    _os << levelString(l);
    _os << std::string("\033[39m") << " - ";
    return _os;
}

std::string Log::levelString(Level l) {
    if (l == DEBUG) {return "DEBUG";}
    if (l == INFO) {return "INFO";}
    if (l == WARNING) {return "WARNING";}
    if (l == ERROR) {return "ERROR";}
    if (l == FATAL) {return "FATAL";}

    return "<ERROR>";
}

std::string Log::levelColor(Level l) {
    const char *fmt = "\033[%2dm";
    char out[128];

    int color = FG_DEFAULT;

    if (l == DEBUG) {color = FG_BLUE;}
    if (l == INFO) {color = FG_GREEN;}
    if (l == WARNING) {color = FG_YELLOW;}
    if (l == ERROR) {color = FG_PURPLE;}
    if (l == FATAL) {color = FG_RED;}

    sprintf(out, fmt, color);
    return std::string(out);
}

std::string Log::timeString() {
    struct timeval tv;
    gettimeofday(&tv, 0);

    char buffer[100];

    tm r;
    strftime(buffer, sizeof(buffer), "%F - %X", localtime_r(&tv.tv_sec, &r));

    char result[100];
    sprintf(result, "%s.%06ld", buffer, (long) tv.tv_usec);

    return std::string(result);
}

}
