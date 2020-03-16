#include "Log.h"

void Log::log(int lvl, const char *format, ...) {
    va_list argptr;
    va_start(argptr, format);
    log(lvl, format, argptr);
    va_end(argptr);
}

void Log::log(int lvl, const char *format, va_list argptr) {
    if (lvl > enabledLvl)
        return;

    char formatted[200];
    vsprintf(formatted, format, argptr);

    char* levelName = lvlName(lvl);

    char timeFormatted[30];
    currentTime(timeFormatted);

    Serial.printf("%s \t[%s] - %s\n", timeFormatted, levelName, formatted);
}

char* Log::lvlName(int lvl) {
    switch(lvl) {
        case 10:
            return "ERROR";
        case 20:
            return "WARN";
        case 30:
            return "INFO";
        case 40:
            return "DEBUG";
        case 50:
            return "TRACE";
    }
    return "";
}

void Log::currentTime(char* buffer) {
    long time = millis();

    int mills = time % 1000;
    time /= 1000;
    int sec = time % 60;
    time /= 60;
    int mins = time % 60;
    int hrs = time / 60;

    sprintf(buffer, "%iH-%02iM-%02iS:%03i", hrs, mins, sec, mills);
}

void Log::t(const char *format, ...) {
    va_list argptr;
    va_start(argptr, format);
    log(50, format, argptr);
    va_end(argptr);
}

void Log::d(const char *format, ...) {
    va_list argptr;
    va_start(argptr, format);
    log(40, format, argptr);
    va_end(argptr);
}

void Log::i(const char *format, ...) {
    va_list argptr;
    va_start(argptr, format);
    log(30, format, argptr);
    va_end(argptr);
}

void Log::w(const char *format, ...) {
    va_list argptr;
    va_start(argptr, format);
    log(20, format, argptr);
    va_end(argptr);
}

void Log::e(const char *format, ...) {
    va_list argptr;
    va_start(argptr, format);
    log(10, format, argptr);
    va_end(argptr);
}
