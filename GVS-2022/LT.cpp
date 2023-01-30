#include<iostream>
#include<iomanip>
#include<fstream>
#include"LT.h"
#include"Error.h"
namespace LT {
	Entry::Entry() {
		this->lexema = NULL;
		this->sn = NULL;
		this->idxTI = LT_TI_NULLIDX;
	}
	Entry::Entry(char lexema) {
		this->lexema = lexema;
	}
	Entry::Entry(char lexema, int sn) {
		this->lexema = lexema;
		this->sn = sn;
	}
	LexTable Create(int size) {
		LexTable tablet;
		if (size > LT_MAXSIZE) {
			ERROR_THROW(104);
		}
		tablet.maxsize = LT_MAXSIZE;
		tablet.table = new Entry[tablet.maxsize];
		tablet.size = NULL;
		return tablet;
	}
	void Add(LexTable& lextable, Entry entry) {
		lextable.table[lextable.size++] = entry;
	}
	Entry GetEntry(LexTable& lextable, int n) {
		return lextable.table[n];
	}
	void Delete(LexTable& lextable) {
		delete lextable.table;
	}
	void WriteIn(LexTable& lextable, std::ostream* streamline) {
		*streamline << "=============================  Lexem table  ============================\n";
		*streamline << std::setw(2) << "N" << std::setw(2) << "|" << std::setw(2) << "Lexem" << std::setw(2) << "|" << std::setw(2) << "" << std::setw(2) << std::endl;
			for (int i = 0; i < lextable.size; i++) {
				*streamline<< std::setw(2) << lextable.table[i].idxTI << std::setw(2) << "|" << std::setw(2) << lextable.table[i].lexema << std::setw(2) << "|" << std::setw(2) << lextable.table[i].sn << std::setw(2) << std::endl;
			}
		*streamline << "\n===================================================================================\n\n";
	}
	Entry WriteEntry(Entry& entry, char lexema, int indx, int line) {
		entry.lexema = lexema;
		entry.idxTI = indx;
		entry.sn= line;
		return entry;
	}
	void PrintIt(LexTable& lextable, std::ostream* streamline) {
		int str_num = 0;
		for (int i = 0; i < lextable.size; i++) {
			if (str_num == lextable.table[i].sn) {
				*streamline << lextable.table[i].lexema;
			}
			else {
				str_num++;
				if (lextable.table[i].sn != str_num) {
					continue;
				}
				*streamline << "\n" << str_num << "\t";
				if (str_num == lextable.table[i].sn) {
					*streamline << lextable.table[i].lexema;
				}
			}
		}
	}
}