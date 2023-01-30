#pragma once
#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 4096
#define LT_TI_NULLIDX 0xffffffff
#define LEX_INTEGER 't'
#define LEX_STRING 't'
#define LEX_SYMBOL 't'
#define LEX_TYPE 't'
#define LEX_ID 'i'
#define LEX_LITERAL 'l'
#define LEX_FUNCTION 'f'
#define LEX_BRING 'b'
#define LEX_OUTPUT 'o'
#define LEX_SEMICOLON ';'
#define LEX_COMMA ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEFTHESIS '('
#define QUOTE '\''
#define QUOTE2 '\"'
#define LEX_OPERATOR 'v'
#define LEFTHESIS '('
#define RIGHTHESIS ')'
#define LEX_PLUS '+'
#define LEX_MINUS '-'
#define LEX_STAR '*'
#define LEX_DIRSLASH '/'
#define LEX_OR '|'
#define LEX_AND '&'
#define LEX_NO '?'
#define LEX_MORE '>'
#define LEX_LESS '<'
#define LEX_EQUAL '='
#define LEX_NEXTLINE '\n'
#define LEX_START 's'
#define LEX_UNTIL 'u'
#define LEX_IF 'y'
#define LEX_JUMP '^'
#define LEX_SQ_LBRACELET '['
#define LEX_SQ_RBRACELET ']'
#define LEX_OTHERWISE 'n'
#define LEX_STDF 'a'
#define LEX_CREATE 'q'
#define LEX_SEP 'w'
#include<iostream>
namespace LT {
	enum operations {
		ONOT = -1,
		OPLUS,
		OMINUS,
		OMUL,
		ODIV,
		OMORE,
		OLESS,
		OAND,
		ONO,
		OOR
	};
		struct Entry {
			char lexema;
			int sn;
			int idxTI;
			operations op;
			Entry();
			Entry(char lexema, int sn);
			Entry(char lexema);
		};
		struct LexTable {
			int maxsize;
			int size;
			Entry* table;
		};
		LexTable Create(int size);
		void Add(LexTable& lextable, Entry entry);
		Entry GetEntry(LexTable& lextable, int n);
		void Delete(LexTable& lextable);
		void WriteIn(LexTable& lextable, std::ostream* streamline);
		void PrintIt(LexTable& lextable, std::ostream* streamline);
		Entry WriteEntry(Entry& entry, char lexema, int indx, int line);
}