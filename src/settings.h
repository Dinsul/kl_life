#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

namespace CGL {
//!
//! \brief The Settings class
//! Это класс который содержит все необходимые параметры игры.
//!
//! Класс является одиночкой, копировать и самостоятельно создавать
//! экземпляры класса запрещено.
//!
//! Доступ к всем переменным открыт и разрешено их изменение.
//! \todo возможно понадобятся readonly параметры
//! Достум к экземпляру класса осуществляется по ссылке возвращаемой
//! статическим методом get().
//!
//! \code(.cpp)
//!
//! auto &set = Settings::get();
//! set.parameter = 1;
//! ...
//! use(set.parameter);
//!
//! \endcode
//!
//! \todo Убрать load() из конструктора. Сделать значения поумолчанию.
class Settings
{
    Settings();
    Settings(Settings&) = delete;

    void operator =(Settings&) = delete;

public:
    // Журналирование
    enum class LogLevel {
        trace    = 0,
        debug    = 1,
        info     = 2,
        warn     = 3,
        err      = 4,
        critical = 5,
        off      = 6
    } logLevel;

    bool logToFile;
    bool logToStdout;
    bool logLast;

    std::string logPath;

    // Отображение
    size_t mainFrameHeight;
    size_t mainFrameWidth;
    size_t drawPeriod;
    size_t cellSize;
    int    scale;


    // Вселенная
    size_t universeHeight;
    size_t universeWidth;
    size_t generationPeriod;
    bool   cycled;

    static Settings &get();
    void load(const std::string &filename);
    void load();
    void save(const std::string &filename);
    void save();
};

} // CGL

#endif // SETTINGS_H
