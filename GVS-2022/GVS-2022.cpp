#include<iostream>
#include"Lexica.h";
#include"Error.h";
#include"Semantica.h";
#include"PolishNotation.h";
#include"Gen.h";
#include"FST.h";
#include"MFST.h";
#include"Greibach.h";
#include"parm.h";
#include"Log.h";
#include"IN.h";
#include"IT.h";
#include"LT.h";
#include<fstream>
#include<ostream>
#include<tchar.h>
#include<cwchar>
#include<wchar.h>
using namespace std;
int _tmain(int argc, _TCHAR* argv[]) {
    Log::LOG log = Log::INITLOG;
    try {
        Parm::PARM param = Parm::getparm(argc, argv);
        log = Log::getlog(param.log);
        In::IN in = In::getin(param.in);
        LexAn::LEX lex = LexAn::Lexica(log, in);
        MFST::Mfst mfst(lex.lextable, GRB::getGreibach());
        mfst.start(log);
        mfst.savededucation(log);
        mfst.printrules(log);
        if (!Semantic::semanticsCheck(lex, log)) {
            std::cout << "Semantic errors. Check log file to get more info";
            exit(-1);
        }
        PN::startPolish(lex);
        IT::Write(lex.idtable, log.stream);
        LT::PrintIt(lex.lextable, log.stream);
        Gen::GeneratorCode(lex.lextable, lex.idtable, param.out);
        Log::WriteLine(log, (char*)"Test: ", (char*)" no mistakes \n", "");
        Log::WriteIn(log, in);
    }
    catch (Error::ERROR e) {
        Log::WriteError(log, e);
    }
}