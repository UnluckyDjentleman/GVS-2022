#pragma once
#include"LT.h"
#include"IT.h"
#include"Log.h"
#include"IN.h"
#include"FST.h"
namespace LexAn {
	struct flags {
		enum FLAG { INT = 0, STR = 1 }F;
		int pos;
	};
	struct LEX {
		IT::IdTable idtable;
		LT::LexTable lextable;
	};
	char** Edit(char source[], int size);
	void RemoveFromP(char source[], int size, Log::LOG logfile);
	LEX Lexica(Log::LOG log, In::IN in);
}