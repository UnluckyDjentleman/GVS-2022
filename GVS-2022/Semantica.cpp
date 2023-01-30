#include<iostream>
#include"LT.h"
#include"IT.h"
#include"Error.h"
#include"Semantica.h"
#include"Log.h"
namespace Semantic {
	bool semanticsCheck(LexAn::LEX lex, Log::LOG log) {
		bool is_ok = true;
		int j = 0;
		std::vector<std::string> functional;
		for (int i = 0; i < lex.lextable.size; i++) {
			switch (lex.lextable.table[i].lexema) {
			case LEX_EQUAL:
				j = i + 1;
				for (j; lex.lextable.table[j].lexema != LEX_SEMICOLON; j++) {
					switch (lex.lextable.table[j].lexema) {
					case LEX_ID:
					case LEX_LITERAL:
						if ((lex.idtable.table[lex.lextable.table[j].idxTI].iddatatype != lex.idtable.table[lex.lextable.table[i - 1].idxTI].iddatatype)) {
							Log::WriteError(log, Error::geterrorin(312, lex.lextable.table[j].sn, -1));
							is_ok = false;
						}
						continue;

					case LEFTHESIS:
						if (lex.lextable.table[j - 1].lexema != LEX_OPERATOR && lex.lextable.table[j - 1].lexema != LEFTHESIS) {
							do {
								j++;
							} while (lex.lextable.table[j].lexema != RIGHTHESIS);
						}
						continue;
					case LEX_DIRSLASH:
						if (lex.idtable.table[lex.lextable.table[j+1].idxTI].value.vint==0) {
							Log::WriteError(log, Error::geterrorin(311, lex.lextable.table[j].sn, -1));
							is_ok = false;
						}
						continue;
					}
				}
				continue;
			case LEX_FUNCTION:
				if (std::count(functional.begin(), functional.end(), lex.idtable.table[lex.lextable.table[i + 1].idxTI].id)) {
					Log::WriteError(log, Error::geterrorin(307, lex.lextable.table[i + 1].sn, -1));
					is_ok = false;
				}
				functional.push_back(lex.idtable.table[lex.lextable.table[i + 1].idxTI].id);

				j = i + 1;
				int type = lex.idtable.table[lex.lextable.table[j].idxTI].iddatatype;
				do {
					j++;
				} while ((lex.lextable.table[j].lexema != LEX_BRING));
				if (lex.idtable.table[lex.lextable.table[j + 1].idxTI].iddatatype != type) {
					Log::WriteError(log, Error::geterrorin(314, lex.lextable.table[j].sn, -1));
					is_ok = false;
				}
			}
		}
		return is_ok;
	}
}
