//#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
//#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <boost/filesystem.hpp>

#include "logger.h"
#include "info.h"
#include "settings.h"

std::shared_ptr<spdlog::logger> &cgl::Logger::file_log()
{
    static std::shared_ptr<spdlog::logger> _fileLogger;
    if (!_fileLogger)
    {
        boost::filesystem::path logPath(Settings::get().logPath);

        // Проверяем существование директории
        // Если такой нет, создаём
        if (!boost::filesystem::exists(logPath)) {
            boost::filesystem::create_directories(logPath);
        }

        logPath.append(PRJ_NAME".log");

        _fileLogger = spdlog::daily_logger_mt(PRJ_NAME, logPath.string());

        _fileLogger->set_level(static_cast<spdlog::level::level_enum>(Settings::get().logLevel));

        // Информацию о запуске пишем всегда
        _fileLogger->set_pattern("\n--~==# %H:%M:%S.%e %v #==~--");
        _fileLogger->log(spdlog::level::off, cat(PRJ_NAME, " ", PRJ_VERSION));

        _fileLogger->set_pattern("%H:%M:%S.%e [%l] %v");
    }

    return _fileLogger;
}

std::shared_ptr<spdlog::logger> &cgl::Logger::last_log()
{
    static std::shared_ptr<spdlog::logger> _lastLogger;
    if (!_lastLogger)
    {
        boost::filesystem::path logPath(Settings::get().logPath);

        // Проверяем существование директории
        // Если такой нет, создаём
        if (!boost::filesystem::exists(logPath)) {
            boost::filesystem::create_directories(logPath);
        }

        logPath.append(PRJ_NAME"_last.log");

        _lastLogger = spdlog::basic_logger_st(PRJ_NAME"_last", logPath.string(), true);

        // Информацию о запуске пишем всегда
        _lastLogger->set_pattern("%v run %c\n--------====================--------");
        _lastLogger->log(spdlog::level::off, cat(PRJ_NAME, ":", PRJ_VERSION));

        _lastLogger->set_pattern("%H:%M:%S.%e [%l] %v");

        _lastLogger->set_level(static_cast<spdlog::level::level_enum>(Settings::get().logLevel));
    }

    return _lastLogger;
}

std::shared_ptr<spdlog::logger> &cgl::Logger::stdout_log()
{
    static std::shared_ptr<spdlog::logger> _constd;

    if (!_constd)
    {
        _constd = spdlog::stdout_logger_mt("stdout");

        _constd->set_pattern("%H:%M:%S.%e [%l] %v");
        _constd->set_level(static_cast<spdlog::level::level_enum>(Settings::get().logLevel));
    }

    return _constd;
}

std::shared_ptr<spdlog::logger> &cgl::Logger::stderr_log()
{
    static std::shared_ptr<spdlog::logger> _conerr;

    if (!_conerr)
    {
        _conerr = spdlog::stderr_logger_mt("stderr");

        _conerr->set_pattern("%H:%M:%S.%e [%l] %v");
        _conerr->set_level(static_cast<spdlog::level::level_enum>(Settings::get().logLevel));
    }

    return _conerr;
}

void cgl::Logger::trace(const std::string &msg)
{
    if (Settings::get().logToFile) {
        file_log()->trace(msg);
        file_log()->flush();
    }

    if (Settings::get().logToStdout) {
        stdout_log()->trace(msg);
    }

    if (Settings::get().logLast) {
        last_log()->trace(msg);
        last_log()->flush();
    }
}

void cgl::Logger::debug(const std::string &msg)
{
    if (Settings::get().logToFile) {
        file_log()->debug(msg);
        file_log()->flush();
    }

    if (Settings::get().logToStdout) {
        stdout_log()->debug(msg);
    }

    if (Settings::get().logLast) {
        last_log()->debug(msg);
        last_log()->flush();
    }
}

void cgl::Logger::info(const std::string &msg)
{
    if (Settings::get().logToFile) {
        file_log()->info(msg);
        file_log()->flush();
    }

    if (Settings::get().logToStdout) {
        stdout_log()->info(msg);
    }

    if (Settings::get().logLast) {
        last_log()->info(msg);
        last_log()->flush();
    }
}

void cgl::Logger::warning(const std::string &msg)
{
    if (Settings::get().logToFile) {
        file_log()->warn(msg);
        file_log()->flush();
    }

    if (Settings::get().logToStdout) {
        stderr_log()->warn(msg);
    }

    if (Settings::get().logLast) {
        last_log()->warn(msg);
        last_log()->flush();
    }
}

void cgl::Logger::error(const std::string &msg)
{
    if (Settings::get().logToFile) {
        file_log()->error(msg);
        file_log()->flush();
    }

    if (Settings::get().logToStdout) {
        stderr_log()->error(msg);
    }

    if (Settings::get().logLast) {
        last_log()->error(msg);
        last_log()->flush();
    }
}




