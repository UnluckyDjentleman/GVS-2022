#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<iomanip>
#include"IT.h"
#include"Error.h"
#define W(x, y)\
		<< std::setw(x) << (y) <<
#define STR(n, line, type, id)\
		"|" W(4,n) " |  " W(6,line) "    |" W(21,type) " |  " W(16, id) " |"
using namespace std;
namespace IT {
	IdTable Create(int size) {
		IdTable* table = new IdTable;
		table->maxsize = TI_MAXSIZE;
		table->table = new Entry[table->maxsize];
		table->size = NULL;
		if (size > table->maxsize && table->maxsize < table->size) {
			ERROR_THROW(104);
		}
		return *table;
	}
	void Add(IdTable& idtable, Entry entry) {
		if (idtable.size < idtable.maxsize) {
			idtable.table[idtable.size] = entry;
			idtable.size++;
		}
		else ERROR_THROW(205);
	}
	Entry GetEntry(IdTable& idtable, int n) {
		return idtable.table[n];
	}
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]) {
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].id, id) == 0) {
				return i;
			}
		}
		return TI_NULLIDX;
	}
	void Delete(IdTable& idtable) {
		delete[] idtable.table;
	}
	void Write(IdTable& idtable, std::ostream* streamline) {
		*streamline << "=============================  Identificator table  ============================\n";
		*streamline << "|  N  |Line in LT |  Identificator type  |        Name       | Value(parameters)" << std::endl;
		for (int i = 0; i < idtable.size; i++)
		{
			char type[SCOPE_NAME_MAX] = "";
			switch (idtable.table[i].iddatatype) {
			case IT::IDDATATYPE::INT:
				strcat(type, "  integer ");
				break;
			case IT::IDDATATYPE::SYM: {
					strcat(type, "   symbol  ");
				break;
			}
			}
			switch (idtable.table[i].idtype) {
			case IT::IDTYPE::V:
				strcat(type, "  variable");
				break;
			case IT::IDTYPE::F:
				strcat(type, "  func");
				break;
			case IT::IDTYPE::P:
				strcat(type, " parameter");
				break;
			case IT::IDTYPE::L:
				strcat(type, "   literal");
				break;
			default:
				strcat(type, "UNDEFINED ");
				break;
			}
			*streamline << STR(i, idtable.table[i].idxfirstLE, type, idtable.table[i].id);
			if (idtable.table[i].idtype == IT::IDTYPE::L || idtable.table[i].idtype == IT::IDTYPE::V)
			{
				if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT)
					*streamline << idtable.table[i].value.vint;
				else if (idtable.table[i].iddatatype == SYM && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
					*streamline << "[" << idtable.table[i].value.vstr.len << "]\"" << idtable.table[i].value.vstr.str << "\"";
			}
			else *streamline << "-";
			*streamline << endl;
			*streamline << std::endl;
			*streamline << "\n-------------------------------------------------------------------------\n\n";
		}
	}
}