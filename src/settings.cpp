#include "settings.h"

CGL::Settings::Settings()
{

}

CGL::Settings &CGL::Settings::get()
{
    static Settings settings;

    return settings;
}

CGL::LogSettings::LogSettings()
{

}

CGL::LogSettings &CGL::LogSettings::get()
{
    static LogSettings settings;

    return settings;
}
