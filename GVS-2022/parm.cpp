#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NO_CONFORMING_WCSTOK
#include<iostream>
#include<tchar.h>
#include"Error.h";
#include"Parm.h"
#include<wchar.h>

Parm::PARM Parm::getparm(int argc, _TCHAR* argv[]) {
    if (argc < 2) {
        throw ERROR_THROW(100);
    }
    Parm::PARM parm;
    for (int i = 1; i < argc; i++) {
        if (wcslen(argv[i]) > PARM_MAX_SIZE) {
            throw ERROR_THROW(104);
        }
        if (wcsstr(argv[i], PARM_IN)) {
            if (wcslen(argv[i]) > wcslen(PARM_IN)) {
                wcscpy_s(parm.in, argv[i] + wcslen(PARM_IN));
            }
            else {
                throw ERROR_THROW(100)
            }
        }
        else {
            continue;
        }
    }
    if (wcslen(argv[argc - 1]) <= wcslen(PARM_IN)) {
        throw ERROR_THROW(100);
    }
    if (argc < 3) {
        wcscpy_s(parm.out, parm.in);
        wcscpy_s(parm.log, parm.in);
        wcsncat_s(parm.out, PARM_OUT_DEFAULT_EXT, wcslen(parm.in));
        wcsncat_s(parm.log, PARM_LOG_DEFAULT_EXT, wcslen(parm.in));
    }
    else {
        wcscpy_s(parm.out, argv[2] + wcslen(PARM_OUT));
    }
    if (argc < 4) {
        wcscpy_s(parm.log, parm.in);
        wcsncat_s(parm.log, PARM_LOG_DEFAULT_EXT, wcslen(parm.in));
    }
    else {
        wcscpy_s(parm.log, argv[3] + wcslen(PARM_LOG));
    }
    return parm;
}