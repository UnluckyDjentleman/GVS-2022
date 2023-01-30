#include"Error.h"
#include"IN.h"
#include"Log.h"
#include"Parm.h"
Log::LOG Log::getlog(wchar_t logfile[]) {
    Log::LOG log;
    log.stream = new std::ofstream;
    log.stream->open(logfile);
    if (!log.stream->is_open()) {
        throw ERROR_THROW(112);
    }
    wcscpy_s(log.logfile, logfile);
    return log;
}

void Log::WriteLine(LOG log, char* c, ...) {
    char** cptr = &c;
    if (log.stream == NULL) {
        throw ERROR_THROW(110);
    }
    while (*cptr != "") {
        *log.stream << *cptr;
        cptr++;
    }
}

//void Log::WriteLine(LOG log, wchar_t* c, ...) {
//  //std::ofstream& out = *log.stream;
//  char buf[PARM_MAX_SIZE];
//  wchar_t** cptr = &c;
//  for (int i = 0; cptr[i] != L""; i++) {
//    wcstombs_s(nullptr, buf, cptr[i], sizeof(buf));
//    std::wcout << cptr[i];
//  }
//}

void Log::WriteLog(LOG log)
{
    char timeNow[100];
    const time_t currentTime = time(NULL);
    tm currentTimeConverted;
    localtime_s(&currentTimeConverted, &currentTime);
    strftime(timeNow, sizeof(timeNow), "%c", &currentTimeConverted);
    *log.stream << "\n------- Protocol -------\n" << timeNow << "\n------ Paramenters ------\n\n";
}

void Log::WriteParm(LOG log, Parm::PARM parm) {
    char parmIn[200];
    char parmInTitle[200];
    char parmOut[200];
    char parmOutTitle[200];
    char parmLog[200];
    char parmLogTitle[200];
    wcstombs_s(nullptr, parmIn, parm.in, sizeof(parmIn));
    wcstombs_s(nullptr, parmInTitle, PARM_IN, sizeof(PARM_IN));
    wcstombs_s(nullptr, parmOut, parm.out, sizeof(parmOut));
    wcstombs_s(nullptr, parmOutTitle, PARM_OUT, sizeof(PARM_OUT));
    wcstombs_s(nullptr, parmLog, parm.log, sizeof(parmLog));
    wcstombs_s(nullptr, parmLogTitle, PARM_LOG, sizeof(PARM_LOG));
    strncat_s(parmInTitle, sizeof(parmInTitle), parmIn, sizeof(parmIn));
    strncat_s(parmOutTitle, sizeof(parmOutTitle), parmOut, sizeof(parmOut));
    strncat_s(parmLogTitle, sizeof(parmLogTitle), parmLog, sizeof(parmLog));
    *log.stream << parmInTitle << "\n";
    *log.stream << parmOutTitle << "\n";
    *log.stream << parmLogTitle << "\n";
}

void Log::WriteError(LOG log, Error::ERROR error) {
    *log.stream << error.message << "\n" << "line: " << error.inext.line
        << " column: " << error.inext.col;
}

void Log::WriteError(std::ostream* stream, Error::ERROR error) {
    *stream << error.message << "\n" << "line: " << error.inext.line
        << " column: " << error.inext.col;
}

void Log::WriteIn(LOG log, In::IN in) {
    *log.stream << "\n\nTotal amount of symbols: " << in.size;
    *log.stream << "\nIgnored: " << in.ignor;
    *log.stream << "\nTotal amount of lines: " << in.lines;
}

void Log::Close(LOG log) {
    log.stream->close();
}