#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <sstream>

#define quick_mtrace(m) cgl::Logger::trace(cgl::cat("[", __FILE__, ":", __LINE__, " ", __FUNCTION__, "] ", m))
#define quick_trace()   cgl::Logger::trace(cgl::cat("[", __FILE__, ":", __LINE__, " ", __FUNCTION__, "]"))

namespace spdlog{
class logger;
}

namespace cgl {

//!
//! \brief The Logger class
//! Журналирование.
//!
//! Этот класс является обёрткой для spdlog.
//! Тут реализовано четыре типа журналирования:
//! - дозапись в единый файл журнала
//! - запись в файла журнала для последнего запуска, это файл перезаписыватся
//! - стандартный поток вывода
//! - поток вывода ошибок
//!
//! При чём _стандартный поток вывода_ или _стандартный поток вывода_
//! выбирается в зависимости от типа сообщения и при влючённой настройке
//! \link cgl::LogSettings::logToStdout \link
//!
class Logger
{
    static std::shared_ptr<spdlog::logger> &file_log();
    static std::shared_ptr<spdlog::logger> &last_log();
    static std::shared_ptr<spdlog::logger> &stdout_log();
    static std::shared_ptr<spdlog::logger> &stderr_log();

public:

    static void trace(const std::string &msg);
    static void debug(const std::string &msg);
    static void info(const std::string &msg);
    static void warning(const std::string &msg);
    static void error(const std::string &msg);
};

inline std::string cat(){
    return std::stringstream().str();
}

template <class T, class ... Args>
auto cat(T&& cur, Args&& ... args){
    std::stringstream str;
    str << cur << cat(std::forward<Args>(args)...);
    return str.str();
}


inline std::string cat(char){
    return std::stringstream().str();
}

template <class T>
auto cat(char, T&& cur){
    std::stringstream str;
    str << cur;
    return str.str();
}

template <class T, class ... Args>
auto cat(char sep, T&& cur, Args&& ... args){
    std::stringstream str;
    str << cur << sep << cat(sep, std::forward<Args>(args)...);
    return str.str();
}

template <class ... Args>
std::string makeStr(Args&& ... args){
    return cat(' ', std::forward<Args>(args)...);
}

}

#endif // LOGGER_H
