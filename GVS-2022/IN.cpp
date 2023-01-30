#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include"IN.h"
#include"IT.h"
#include"LT.h"
#include"Error.h"
#include"Log.h"
#include"Parm.h"
#include<wchar.h>
#include<tchar.h>
#include<queue>
#include<iomanip>
namespace In {
	int mas[256] = IN_CODE_TABLE;
	IN getin(wchar_t infile[]) {
		setlocale(LC_ALL, "rus");
		std::ifstream inget(infile);
		IN ing;
		memcpy(ing.code, mas, sizeof(mas));
		ing.lines = 0;
		ing.ignor = 0;
		ing.size = 0;
		int position = 0;
		int line = 1;
		char* stringer = new char[200000];
		ing.text = new unsigned char[200000];
		if (!inget.is_open()) {
			throw ERROR_THROW(110);
		}
		else {
			for (int i = 0; !inget.eof(); i++) {
				inget.get(stringer[i]);
				if ((unsigned)stringer[i] == IN_CODE_ENDL) {
					ing.lines++;
					line++;
					position = 0;
				}
				if (ing.code[(unsigned int)stringer[i]] == IN::F) {
					throw ERROR_THROW_IN(201, ing.lines + 1, i);
				}
				if (ing.code[(unsigned int)stringer[i]] == IN::I) {
					ing.size--; ing.ignor++;
					i--;
				}
				else {
					ing.size++;
					position++;
				}
			}
			if (ing.size == IN_MAX_LEN_TEXT) {
				throw ERROR_THROW(110);
			}
		}
		stringer[ing.size - 1] = '\0';
		ing.text = (unsigned char*)stringer;
		inget.close();
		return ing;
	}
}