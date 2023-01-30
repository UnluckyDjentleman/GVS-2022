#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include"Lexica.h"
#include"IT.h"
#include"IN.h"
#include"LT.h"
#include"FST.h"
#include"Error.h"
#include<stack>
using namespace std;
namespace LexAn {
	void RemoveFromP(char source[], int size, Log::LOG logfile) {// deleting probs and tabs
		char Separators[] = { " ,;(){}=+-*/|&?\n<>" };
		bool findLiteral = false;
		int count = NULL;

		for (int i = 0; i < size; i++) {
			if (source[i] == '\'') {
				findLiteral = !findLiteral;
				count++;
			}

			if ((source[i] == ' ' || source[i] == '\t') && !findLiteral) {
				for (int j = 0; j < sizeof(Separators) - 1; j++) {
					if (source[i + 1] == Separators[j] || source[i - 1] == Separators[j] || i == 0) {
						for (int k = i; k < size; k++) {
							source[k] = source[k + 1];
						}
						i--;
						break;
					}
				}
			}
		}

		if (count % 2 != 0)
			Log::WriteError(logfile, Error::geterror(300));
	}
	char** Edit(char source[], int size)//divide word after deleting probs and tabs
	{
		char** word = new char* [TI_STR_MAXSIZE];
		for (int i = 0; i < TI_STR_MAXSIZE; i++) {
			word[i] = new char[30] {NULL};
		}

		bool findSeparator, findLiteral = false;
		int j = 0;
		char Separators[] = { " ,;(){}=+-*/|&?\n<>" };
		for (int i = 0, k = 0; i < size - 1; i++, k++) {
			findSeparator = false;
			if (source[i] == '\'') findLiteral = !findLiteral;
			for (int t = 0; t < sizeof(Separators) - 1; t++) {
				if (source[i] == Separators[t] && !findLiteral) {
					findSeparator = true;
					if (word[j][0] != NULL) {
						word[j++][k] = '\0';
						k = 0;
					}
					if (Separators[t] == ' ') {
						k = -1;
						break;
					}
					word[j][k++] = Separators[t];
					word[j++][k] = '\0';
					k = -1;
					break;
				}
			}

			if (!findSeparator) word[j][k] = source[i];
		}

		word[j] = NULL;
		for (int i = 0; i < j; i++) {
			if (!strcmp((char*)word[i], "")) return NULL;
		}
		return word;
	}
	LEX Lexica(Log::LOG log, In::IN in) {
		LEX lex;
		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(TI_MAXSIZE);

		RemoveFromP((char*)in.text, in.size, log);

		char** word = new char* [TI_STR_MAXSIZE];
		for (int i = 0; i < TI_STR_MAXSIZE; i++)
			word[i] = new char[30] {NULL};

		do {
			word = Edit((char*)in.text, in.size);
		} while (word == NULL);

		int indexLex = 0;
		int literalCounter = 1;
		int line = 1;
		int position = 0;
		bool findMain = false;
		int mainCounter = 0;
		bool findDeclaration = false;
		bool findType = false;
		bool findProc = false;
		int is_cycle = 0;
		int bufPos = 0;
		bool findMath = false;
		bool findString = false;

		std::stack<std::string> functions;
		char* bufprefix = new char[10]{ "" };
		char* L = new char[2]{ "L" };
		char* bufL = new char[TI_STR_MAXSIZE];
		char* nameLiteral = new char[10]{ "" };
		char* charclit = new char[10]{ "" };

		bool findFunc = false;
		bool findParm = false;
		IT::Entry entryIT;

		for (int i = 0; word[i] != NULL; i++, indexLex++) {
			bool findSameID = false;
			position += strlen(word[i]);
			if (FSTN::execute(FSTN::FST(word[i], CREATE))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_CREATE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findDeclaration = true;
			}
			else if (FSTN::execute(FSTN::FST(word[i], INTEGER))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_INTEGER, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findType = true;
				entryIT.iddatatype = IT::INT;
			}
			else if (FSTN::execute(FSTN::FST(word[i], SYMBOL))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_SYMBOL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findType = true;
				entryIT.iddatatype = IT::SYM;
			}
			else if (FSTN::execute(FSTN::FST(word[i], FUNC))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_FUNCTION, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findFunc = true;
			}
			else if (FSTN::execute(FSTN::FST(word[i], BRING))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_BRING, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], OUTPUT))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_OUTPUT, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], JUMP))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_JUMP, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], START))) {
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indexLex;
				entryIT.idtype = IT::F;
				entryIT.iddatatype = IT::INT;
				IT::Add(idtable, entryIT);
				entryIT = {};

				LT::Entry entryLT = WriteEntry(entryLT, LEX_START, IT::IsId(idtable, word[i]), line);
				LT::Add(lextable, entryLT);
				functions.push(word[i]);
				findMain = true;
				mainCounter++;
			}
			else if (FSTN::execute(FSTN::FST(word[i], UNTIL))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_UNTIL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				is_cycle++;
			}
			else if (FSTN::execute(FSTN::FST(word[i], IF))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_IF, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				is_cycle++;
			}
			else if (FSTN::execute(FSTN::FST(word[i], OTHERWISE))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_OTHERWISE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				is_cycle++;
			}
			else if (FSTN::execute(FSTN::FST(word[i], STD_MODULE)) || FSTN::execute(FSTN::FST(word[i], STD_RAISE))) {
				if (int idx = IT::IsId(idtable, word[i]) == TI_NULLIDX) {
					entryIT.idtype = IT::F;
					entryIT.iddatatype = IT::INT;
					entryIT.idxfirstLE = indexLex;
					strcpy(entryIT.id, word[i]);
					IT::Add(idtable, entryIT);
					entryIT = {};
				}

				LT::Entry entryLT = WriteEntry(entryLT, LEX_ID, IT::IsId(idtable, word[i]), line);
				LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], GRAPH_INT_LITERAL))) {
				int value;
				if (word[i][0] == '-' && (word[i][1] == '0' && word[i][2] == 'x') || (word[i][0] == '0' && word[i][1] == 'x')) {
					value = strtol(word[i], NULL, 16);
				}
				else if(word[i][0] == '-' && (word[i][1] == '0') || (word[i][0] == '0')) {
					value = strtol(word[i], NULL, 8);
				}
				else {
					value = strtol(word[i], NULL, 10);
				}
				if (value > TI_INT_MAXVAL|| value < TI_INT_MINVAL)
					throw ERROR_THROW_IN(315, line, position);
				for (int k = 0; k < idtable.size; k++) {
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L && idtable.table[k].iddatatype == IT::INT) {
						LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						findSameID = true;
						break;
					}
				}

				if (findSameID) continue;
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::INT;
				entryIT.value.vint = value;
				entryIT.idxfirstLE = indexLex;
				_itoa_s(literalCounter++, charclit, sizeof(char) * 10, 10);
				strcpy(bufL, L);
				word[i] = strcat(bufL, charclit);
				strcpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				entryIT = {};

				LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, IT::IsId(idtable, word[i]), line);
				LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], STR_LIT))) {
			int length = strlen(word[i]);
			for (int k = 0; k < length; k++)
				word[i][k] = word[i][k + 1];
			word[i][length - 2] = 0;

			for (int k = 0; k < idtable.size; k++) {
				if (!(strcmp(idtable.table[k].value.vstr.str, word[i]))) {
					findSameID = true;
					LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
					LT::Add(lextable, entryLT);
					break;
				}
			}
			if (findSameID) continue;

			strcpy(entryIT.value.vstr.str, word[i]);
			entryIT.value.vstr.len = length - 2;
			entryIT.idtype = IT::L;
			entryIT.iddatatype = IT::SYM;
			entryIT.idxfirstLE = indexLex;

			_itoa_s(literalCounter++, charclit, sizeof(char) * 10, 10);
			strcpy(bufL, L);
			nameLiteral = strcat(bufL, (char*)charclit);
			strcpy(entryIT.id, nameLiteral);
			IT::Add(idtable, entryIT);
			entryIT = {};

			int k = 0;
			for (k = 0; k < idtable.size; k++) {
				if (!(strcmp(idtable.table[k].value.vstr.str, word[i])))
					break;
			}
			LT::Entry entryLT = WriteEntry(entryLT, LEX_LITERAL, k, line);
			LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], IDENTIFICATOR))) {
			if (findParm) {
				entryIT.idtype = IT::P;
				}
					
				else if (findFunc) {
					entryIT.idtype = IT::F;
					functions.push(word[i]);
				}
				else {
					entryIT.idtype = IT::V;
					int idx = IT::IsId(idtable, word[i]);
					if (idx != TI_NULLIDX) {
						LT::Entry entryLT = WriteEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						entryIT = { };
						continue;
					}
					if (entryIT.iddatatype == IT::INT)
						entryIT.value.vint = TI_INT_DEFAULT;
					else if (entryIT.iddatatype == IT::SYM) {
						entryIT.value.vstr.len = TI_INT_DEFAULT;
						memset(entryIT.value.vstr.str,TI_STR_DEFAULT,sizeof(char));
					}
				}

				entryIT.idxfirstLE = indexLex;
				if (entryIT.idtype != IT::F && !functions.empty()) {
					strcpy(bufprefix, functions.top().c_str());
					word[i] = strcat(bufprefix, word[i]);
				}
				strcpy(entryIT.id, word[i]);
				int idx = IT::IsId(idtable, word[i]);
				if (idx == TI_NULLIDX)
					IT::Add(idtable, entryIT);
				LT::Entry entryLT = WriteEntry(entryLT, LEX_ID, IT::IsId(idtable, word[i]), line);
				LT::Add(lextable, entryLT);
				entryIT = { };
			}
			else if (FSTN::execute(FSTN::FST(word[i], PLUS))) {
				strcpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indexLex;
				entryIT.idtype = IT::OP;
				if (IT::IsId(idtable, word[i]) == TI_NULLIDX)
					IT::Add(idtable, entryIT);
				entryIT = { };

				LT::Entry entryLT = WriteEntry(entryLT, LEX_OPERATOR, IT::IsId(idtable, word[i]), line);
				entryLT.op = LT::OPLUS;
				LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], MINUS))) {
			strcpy(entryIT.id, word[i]);
			entryIT.idxfirstLE = indexLex;
			entryIT.idtype = IT::OP;
			if (IT::IsId(idtable, word[i]) == TI_NULLIDX)
				IT::Add(idtable, entryIT);
			entryIT = { };

			LT::Entry entryLT = WriteEntry(entryLT, LEX_OPERATOR, IT::IsId(idtable, word[i]), line);
			entryLT.op = LT::OMINUS;
			LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], STAR))) {
			strcpy(entryIT.id, word[i]);
			entryIT.idxfirstLE = indexLex;
			entryIT.idtype = IT::OP;
			if (IT::IsId(idtable, word[i]) == TI_NULLIDX)
				IT::Add(idtable, entryIT);
			entryIT = { };

			LT::Entry entryLT = WriteEntry(entryLT, LEX_OPERATOR, IT::IsId(idtable, word[i]), line);
			entryLT.op = LT::OMUL;
			LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], DIRSLASH))) {
			strcpy(entryIT.id, word[i]);
			entryIT.idxfirstLE = indexLex;
			entryIT.idtype = IT::OP;
			if (IT::IsId(idtable, word[i]) == TI_NULLIDX)
				IT::Add(idtable, entryIT);
			entryIT = { };

			LT::Entry entryLT = WriteEntry(entryLT, LEX_OPERATOR, IT::IsId(idtable, word[i]), line);
			entryLT.op = LT::ODIV;
			LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], LESS))) {
			strcpy(entryIT.id, word[i]);
			entryIT.idxfirstLE = indexLex;
			entryIT.idtype = IT::OP;
			if (IT::IsId(idtable, word[i]) == TI_NULLIDX)
				IT::Add(idtable, entryIT);
			entryIT = { };

			LT::Entry entryLT = WriteEntry(entryLT, LEX_OPERATOR, IT::IsId(idtable, word[i]), line);
			entryLT.op = LT::OLESS;
			LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], MORE))) {
			strcpy(entryIT.id, word[i]);
			entryIT.idxfirstLE = indexLex;
			entryIT.idtype = IT::OP;
			if (IT::IsId(idtable, word[i]) == TI_NULLIDX)
				IT::Add(idtable, entryIT);
			entryIT = { };

			LT::Entry entryLT = WriteEntry(entryLT, LEX_OPERATOR, IT::IsId(idtable, word[i]), line);
			entryLT.op = LT::OMORE;
			LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], AND))) {
			strcpy(entryIT.id, word[i]);
			entryIT.idxfirstLE = indexLex;
			entryIT.idtype = IT::OP;
			if (IT::IsId(idtable, word[i]) == TI_NULLIDX)
				IT::Add(idtable, entryIT);
			entryIT = { };

			LT::Entry entryLT = WriteEntry(entryLT, LEX_OPERATOR, IT::IsId(idtable, word[i]), line);
			entryLT.op = LT::OAND;
			LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], OR))) {
			strcpy(entryIT.id, word[i]);
			entryIT.idxfirstLE = indexLex;
			entryIT.idtype = IT::OP;
			if (IT::IsId(idtable, word[i]) == TI_NULLIDX)
				IT::Add(idtable, entryIT);
			entryIT = { };

			LT::Entry entryLT = WriteEntry(entryLT, LEX_OPERATOR, IT::IsId(idtable, word[i]), line);
			entryLT.op = LT::OOR;
			LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], NO))) {
			strcpy(entryIT.id, word[i]);
			entryIT.idxfirstLE = indexLex;
			entryIT.idtype = IT::OP;
			if (IT::IsId(idtable, word[i]) == TI_NULLIDX)
				IT::Add(idtable, entryIT);
			entryIT = { };

			LT::Entry entryLT = WriteEntry(entryLT, LEX_OPERATOR, IT::IsId(idtable, word[i]), line);
			entryLT.op = LT::ONO;
			LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], SEMICOLON))) {
				if (findDeclaration && findFunc && findType)
					functions.pop();
				LT::Entry entryLT = WriteEntry(entryLT, LEX_SEMICOLON, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				findDeclaration = findFunc = findType = findParm = false;
				entryIT = { };
			}
			else if (FSTN::execute(FSTN::FST(word[i], COMMA))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_COMMA, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], LEFTBRACE))) {
				findType = findDeclaration = findFunc = findParm = findProc = false;
				LT::Entry entryLT = WriteEntry(entryLT, LEX_LEFTBRACE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], BRACELET))) {
				if (!functions.empty() && is_cycle == 0)
					functions.pop();
				else if (is_cycle != 0) is_cycle--;
				LT::Entry entryLT = WriteEntry(entryLT, LEX_BRACELET, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], LEFTTHESIS))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEFTHESIS, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				if (findFunc || findProc)
					findParm = true;
			}
			else if (FSTN::execute(FSTN::FST(word[i], RIGHTTHESIS))) {
				LT::Entry entryLT = WriteEntry(entryLT, RIGHTHESIS, LT_TI_NULLIDX, line);
				findParm = false;
				LT::Add(lextable, entryLT);
			}
			else if (FSTN::execute(FSTN::FST(word[i], EQUALS))) {
				LT::Entry entryLT = WriteEntry(entryLT, LEX_EQUAL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
			}
			else if (word[i][0] == LEX_NEXTLINE) {
			line++;
			position = 0;
			indexLex--;
			}
			else
				throw ERROR_THROW_IN(205, line, position);
		}
		if (mainCounter != 1) throw ERROR_THROW(301);

		lex.idtable = idtable;
		lex.lextable = lextable;
		return lex;
	}
}
