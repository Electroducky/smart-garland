#ifndef GARLAND_LOG
#define GARLAND_LGO

#include <Arduino.h>

class Log
{
private:
    static const int enabledLvl = 40;

    static char* lvlName(int lvl);
    static void currentTime(char* buffer);
public:
    Log();
    ~Log();

    static void t(const char *format, ...);
    static void d(const char *format, ...);
    static void i(const char *format, ...);
    static void w(const char *format, ...);
    static void e(const char *format, ...);

    static void log(int lvl, const char *format, ...);
    static void log(int lvl, const char *format, va_list argptr);
};

#endif //GARLAND_LOG