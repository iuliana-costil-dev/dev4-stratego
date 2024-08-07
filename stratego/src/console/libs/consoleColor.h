#ifndef CONSOLECOLOR_H
#define CONSOLECOLOR_H

#pragma once

#include <iostream>

#if defined (WIN32)
#include <windows.h>
#endif

inline std::ostream &blue(std::ostream &s) {
#if defined (WIN32)
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
                            | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#else
    s << "\033[36m";
#endif
    return s;
}

inline std::ostream &red(std::ostream &s) {
#if defined (WIN32)
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_RED | FOREGROUND_INTENSITY);
#else
    s << "\033[36m";
#endif
    return s;
}

inline std::ostream &white(std::ostream &s) {
#if defined (WIN32)
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_INTENSITY | FOREGROUND_RED
                            | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    s << "\033[37m";
#endif
    return s;
}

inline std::ostream &gray(std::ostream &s) {
#if defined (WIN32)
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    s << "\033[38m";
#endif
    return s;
}

inline std::ostream &reset(std::ostream &s) {
#if defined (WIN32)
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    s << "\033[0m";
#endif
    return s;
}


// Copyleft Vincent Godin

#endif //CONSOLECOLOR_H
