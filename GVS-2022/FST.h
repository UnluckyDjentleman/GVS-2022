﻿#pragma once
#pragma once
#define N_REPL 20
#define INTEGER 8,\
FSTN::NODE(1, FSTN::RELATION('i', 1)),\
FSTN::NODE(1, FSTN::RELATION('n', 2)),\
FSTN::NODE(1, FSTN::RELATION('t', 3)),\
FSTN::NODE(1, FSTN::RELATION('e', 4)),\
FSTN::NODE(1, FSTN::RELATION('g', 5)),\
FSTN::NODE(1, FSTN::RELATION('e', 6)),\
FSTN::NODE(1, FSTN::RELATION('r', 7)),\
FSTN::NODE()
#define GRAPH_INT_NEGATIVE 6,\
	FSTN::NODE(1, \
			FSTN::RELATION('-', 1)),\
	FSTN::NODE(2, \
			FSTN::RELATION('0', 2),FSTN::RELATION('0', 4)),\
	FSTN::NODE(1, \
			FSTN::RELATION('x', 3)),\
	FSTN::NODE(32,\
			FSTN::RELATION('1',3),FSTN::RELATION('0',3),		FSTN::RELATION('2',3),FSTN::RELATION('3',3),\
			FSTN::RELATION('A',3),FSTN::RELATION('B',3),		FSTN::RELATION('4',3),FSTN::RELATION('5',3),\
			FSTN::RELATION('C',3),FSTN::RELATION('D',3),		FSTN::RELATION('6',3),FSTN::RELATION('7',3),\
			FSTN::RELATION('E',3),FSTN::RELATION('F',3),		FSTN::RELATION('8',3),FSTN::RELATION('9',3),\
			FSTN::RELATION('1',5),FSTN::RELATION('0',5),		FSTN::RELATION('2',5),FSTN::RELATION('3',5),\
			FSTN::RELATION('A',5),FSTN::RELATION('B',5),		FSTN::RELATION('4',5),FSTN::RELATION('5',5),\
			FSTN::RELATION('C',5),FSTN::RELATION('D',5),		FSTN::RELATION('6',5),FSTN::RELATION('7',5),\
			FSTN::RELATION('E',5),FSTN::RELATION('F',5),		FSTN::RELATION('8',5),FSTN::RELATION('9',5)),\
	FSTN::NODE(16,\
			FSTN::RELATION('1',4),FSTN::RELATION('0',4),		FSTN::RELATION('2',2),FSTN::RELATION('3',4),\
			FSTN::RELATION('4',4),FSTN::RELATION('5',4),		FSTN::RELATION('6',2),FSTN::RELATION('7',4),\
			FSTN::RELATION('1',5),FSTN::RELATION('0',5),		FSTN::RELATION('2',5),FSTN::RELATION('3',5),\
			FSTN::RELATION('4',5),FSTN::RELATION('5',5),		FSTN::RELATION('6',5),FSTN::RELATION('7',5)),\
	FSTN::NODE()

#define GRAPH_INT_LITERAL 6, \
	FSTN::NODE(23, \
			FSTN::RELATION('-', 1),FSTN::RELATION('0', 2),FSTN::RELATION('0', 5),\
			FSTN::RELATION('1',1),FSTN::RELATION('0',3),FSTN::RELATION('1',5),\
			FSTN::RELATION('2',1),FSTN::RELATION('3',1),FSTN::RELATION('2',5),FSTN::RELATION('3',5),\
			FSTN::RELATION('6',1),FSTN::RELATION('7',1),FSTN::RELATION('4',5),FSTN::RELATION('5',5),\
			FSTN::RELATION('1',1),FSTN::RELATION('6',5),FSTN::RELATION('7',5),\
			FSTN::RELATION('4',1),FSTN::RELATION('5',1),FSTN::RELATION('8',5),FSTN::RELATION('9',5),\
			FSTN::RELATION('8',1),FSTN::RELATION('9',1)),\
	FSTN::NODE(20,\
			FSTN::RELATION('1',1),FSTN::RELATION('0',1),		FSTN::RELATION('0',5),\
			FSTN::RELATION('2',1),FSTN::RELATION('3',1),		FSTN::RELATION('4',1),FSTN::RELATION('5',1),\
			FSTN::RELATION('6',1),FSTN::RELATION('7',1),		FSTN::RELATION('8',1),FSTN::RELATION('9',1),\
			FSTN::RELATION('1',5),FSTN::RELATION('2',5),		FSTN::RELATION('3',5),FSTN::RELATION('4',5),\
			FSTN::RELATION('5',5),FSTN::RELATION('6',5),		FSTN::RELATION('7',5),FSTN::RELATION('8',5),\
			FSTN::RELATION('9',5)),\
	FSTN::NODE(16,\
			FSTN::RELATION('1',2),FSTN::RELATION('0',2),		FSTN::RELATION('2',2),FSTN::RELATION('3',2),\
			FSTN::RELATION('4',2),FSTN::RELATION('5',2),		FSTN::RELATION('6',2),FSTN::RELATION('7',2),\
			FSTN::RELATION('1',5),FSTN::RELATION('0',5),		FSTN::RELATION('2',5),FSTN::RELATION('3',5),\
			FSTN::RELATION('4',5),FSTN::RELATION('5',5),		FSTN::RELATION('6',5),FSTN::RELATION('7',5)),\
	FSTN::NODE(1,FSTN::RELATION('x',4)),\
	FSTN::NODE(32,\
			FSTN::RELATION('1',4),FSTN::RELATION('0',4),		FSTN::RELATION('2',4),FSTN::RELATION('3',4),\
			FSTN::RELATION('A',4),FSTN::RELATION('B',4),		FSTN::RELATION('4',4),FSTN::RELATION('5',4),\
			FSTN::RELATION('C',4),FSTN::RELATION('D',4),		FSTN::RELATION('6',4),FSTN::RELATION('7',4),\
			FSTN::RELATION('E',4),FSTN::RELATION('F',4),		FSTN::RELATION('8',4),FSTN::RELATION('9',4),\
			FSTN::RELATION('1',5),FSTN::RELATION('0',5),		FSTN::RELATION('2',5),FSTN::RELATION('3',5),\
			FSTN::RELATION('A',5),FSTN::RELATION('B',5),		FSTN::RELATION('4',5),FSTN::RELATION('5',5),\
			FSTN::RELATION('C',5),FSTN::RELATION('D',5),		FSTN::RELATION('6',5),FSTN::RELATION('7',5),\
			FSTN::RELATION('E',5),FSTN::RELATION('F',5),		FSTN::RELATION('8',5),FSTN::RELATION('9',5)),\
		FSTN::NODE()
#define SYMBOL 7,\
FSTN::NODE(1, FSTN::RELATION('s', 1)),\
FSTN::NODE(1, FSTN::RELATION('y', 2)),\
FSTN::NODE(1, FSTN::RELATION('m', 3)),\
FSTN::NODE(1, FSTN::RELATION('b', 4)),\
FSTN::NODE(1, FSTN::RELATION('o', 5)),\
FSTN::NODE(1, FSTN::RELATION('l', 6)),\
FSTN::NODE()
#define STRING 7,\
FSTN::NODE(1, FSTN::RELATION('s', 1)),\
FSTN::NODE(1, FSTN::RELATION('t', 2)),\
FSTN::NODE(1, FSTN::RELATION('r', 3)),\
FSTN::NODE(1, FSTN::RELATION('i', 4)),\
FSTN::NODE(1, FSTN::RELATION('n', 5)),\
FSTN::NODE(1, FSTN::RELATION('g', 6)),\
FSTN::NODE()
#define FUNC 5,\
FSTN::NODE(1, FSTN::RELATION('f', 1)),\
FSTN::NODE(1, FSTN::RELATION('u', 2)),\
FSTN::NODE(1, FSTN::RELATION('n', 3)),\
FSTN::NODE(1, FSTN::RELATION('c', 4)),\
FSTN::NODE()
#define JUMP  5,\
FSTN::NODE(1, FSTN::RELATION('j', 1)),\
FSTN::NODE(1, FSTN::RELATION('u', 2)),\
FSTN::NODE(1, FSTN::RELATION('m', 3)),\
FSTN::NODE(1, FSTN::RELATION('p', 4)),\
FSTN::NODE()
#define BRING 6,\
FSTN::NODE(1, FSTN::RELATION('b', 1)),\
FSTN::NODE(1, FSTN::RELATION('r', 2)),\
FSTN::NODE(1, FSTN::RELATION('i', 3)),\
FSTN::NODE(1, FSTN::RELATION('n', 4)),\
FSTN::NODE(1, FSTN::RELATION('g', 5)),\
FSTN::NODE()
#define OUTPUT 7,\
FSTN::NODE(1, FSTN::RELATION('o', 1)),\
FSTN::NODE(1, FSTN::RELATION('u', 2)),\
FSTN::NODE(1, FSTN::RELATION('t', 3)),\
FSTN::NODE(1, FSTN::RELATION('p', 4)),\
FSTN::NODE(1, FSTN::RELATION('u', 5)),\
FSTN::NODE(1, FSTN::RELATION('t', 6)),\
FSTN::NODE()
#define STR_LIT 3,\
	FSTN::NODE(1, FSTN::RELATION('\"', 1)),\
	FSTN::NODE(87, \
			FSTN::RELATION('a', 1), FSTN::RELATION('b', 1), FSTN::RELATION('c', 1), FSTN::RELATION('d', 1),\
			FSTN::RELATION('e', 1), FSTN::RELATION('f', 1), FSTN::RELATION('g', 1), FSTN::RELATION('h', 1),\
			FSTN::RELATION('i', 1), FSTN::RELATION('j', 1), FSTN::RELATION('k', 1), FSTN::RELATION('l', 1),\
			FSTN::RELATION('m', 1), FSTN::RELATION('n', 1), FSTN::RELATION('o', 1), FSTN::RELATION('p', 1),\
			FSTN::RELATION('q', 1), FSTN::RELATION('r', 1), FSTN::RELATION('s', 1), FSTN::RELATION('t', 1),\
			FSTN::RELATION('u', 1), FSTN::RELATION('v', 1), FSTN::RELATION('w', 1), FSTN::RELATION('x', 1),\
			FSTN::RELATION('y', 1), FSTN::RELATION('z', 1),\
			FSTN::RELATION('A', 1), FSTN::RELATION('B', 1), FSTN::RELATION('C', 1), FSTN::RELATION('D', 1),\
			FSTN::RELATION('E', 1), FSTN::RELATION('F', 1), FSTN::RELATION('G', 1), FSTN::RELATION('H', 1),\
			FSTN::RELATION('I', 1), FSTN::RELATION('J', 1), FSTN::RELATION('K', 1), FSTN::RELATION('L', 1),\
			FSTN::RELATION('M', 1), FSTN::RELATION('N', 1), FSTN::RELATION('O', 1), FSTN::RELATION('P', 1),\
			FSTN::RELATION('Q', 1), FSTN::RELATION('R', 1), FSTN::RELATION('S', 1), FSTN::RELATION('T', 1),\
			FSTN::RELATION('U', 1), FSTN::RELATION('V', 1), FSTN::RELATION('W', 1), FSTN::RELATION('X', 1),\
			FSTN::RELATION('Y', 1), FSTN::RELATION('Z', 1),\
			FSTN::RELATION('0', 1), FSTN::RELATION('1', 1), FSTN::RELATION('2', 1), FSTN::RELATION('3', 1),\
			FSTN::RELATION('4', 1), FSTN::RELATION('5', 1), FSTN::RELATION('6', 1), FSTN::RELATION('7', 1),\
			FSTN::RELATION('8', 1), FSTN::RELATION('9', 1),\
			FSTN::RELATION(' ', 1), FSTN::RELATION(',', 1), FSTN::RELATION('.', 1), FSTN::RELATION(';', 1),\
			FSTN::RELATION('-', 1), FSTN::RELATION('+', 1), FSTN::RELATION('*', 1), FSTN::RELATION('/', 1),\
			FSTN::RELATION('=', 1), FSTN::RELATION(':', 1), FSTN::RELATION(')', 1), FSTN::RELATION('(', 1),\
			FSTN::RELATION('}', 1), FSTN::RELATION('{', 1), FSTN::RELATION(']', 1), FSTN::RELATION('[', 1),\
			FSTN::RELATION('!', 1), FSTN::RELATION('?', 1), FSTN::RELATION('#', 1), FSTN::RELATION('&', 1),\
			FSTN::RELATION('>', 1), FSTN::RELATION('<', 1), FSTN::RELATION('[', 1), FSTN::RELATION(']', 1),\
			FSTN::RELATION('\"', 2)),\
	FSTN::NODE()
#define IF 3,\
	FSTN::NODE(1,FSTN::RELATION('i',1)),\
	FSTN::NODE(1,FSTN::RELATION('f',2)),\
	FSTN::NODE()
#define OTHERWISE 10, \
	FSTN::NODE(1, FSTN::RELATION('o',1)),\
	FSTN::NODE(1, FSTN::RELATION('t',2)),\
	FSTN::NODE(1, FSTN::RELATION('h',3)),\
	FSTN::NODE(1, FSTN::RELATION('e',4)),\
	FSTN::NODE(1, FSTN::RELATION('r',5)),\
	FSTN::NODE(1, FSTN::RELATION('w',6)),\
	FSTN::NODE(1, FSTN::RELATION('i',7)),\
	FSTN::NODE(1, FSTN::RELATION('s',8)),\
	FSTN::NODE(1, FSTN::RELATION('e',9)),\
	FSTN::NODE()
#define STD_MODULE 7, \
	FSTN::NODE(1, FSTN::RELATION('m',1)),\
	FSTN::NODE(1, FSTN::RELATION('o',2)),\
	FSTN::NODE(1, FSTN::RELATION('d',3)),\
	FSTN::NODE(1, FSTN::RELATION('u',4)),\
	FSTN::NODE(1, FSTN::RELATION('l',5)),\
	FSTN::NODE(1, FSTN::RELATION('e',6)),\
	FSTN::NODE()
#define STD_RAISE 7, \
	FSTN::NODE(1, FSTN::RELATION('r',1)),\
	FSTN::NODE(1, FSTN::RELATION('a',2)),\
	FSTN::NODE(1, FSTN::RELATION('i',3)),\
	FSTN::NODE(1, FSTN::RELATION('s',4)),\
	FSTN::NODE(1, FSTN::RELATION('e',5)),\
	FSTN::NODE(1, FSTN::RELATION('r',6)),\
	FSTN::NODE()
#define UNTIL 6, \
	FSTN::NODE(1, FSTN::RELATION('u',1)),\
	FSTN::NODE(1, FSTN::RELATION('n',2)),\
	FSTN::NODE(1, FSTN::RELATION('t',3)),\
	FSTN::NODE(1, FSTN::RELATION('i',4)),\
	FSTN::NODE(1, FSTN::RELATION('l',5)),\
	FSTN::NODE()
#define START 6, \
	FSTN::NODE(1, FSTN::RELATION('S',1)),\
	FSTN::NODE(1, FSTN::RELATION('t',2)),\
	FSTN::NODE(1, FSTN::RELATION('a',3)),\
	FSTN::NODE(1, FSTN::RELATION('r',4)),\
	FSTN::NODE(1, FSTN::RELATION('t',5)),\
	FSTN::NODE()
#define CREATE 7, \
	FSTN::NODE(1, FSTN::RELATION('c',1)),\
	FSTN::NODE(1, FSTN::RELATION('r',2)),\
	FSTN::NODE(1, FSTN::RELATION('e',3)),\
	FSTN::NODE(1, FSTN::RELATION('a',4)),\
	FSTN::NODE(1, FSTN::RELATION('t',5)),\
	FSTN::NODE(1, FSTN::RELATION('e',6)),\
	FSTN::NODE()
#define PLUS 2,	\
	FSTN::NODE(1, FSTN::RELATION('+', 1)),\
	FSTN::NODE()

#define MINUS 2,	\
	FSTN::NODE(1, FSTN::RELATION('-', 1)),\
	FSTN::NODE()

#define STAR 2,	\
	FSTN::NODE(1, FSTN::RELATION('*', 1)),\
	FSTN::NODE()

#define DIRSLASH 2,	\
	FSTN::NODE(1, FSTN::RELATION('/', 1)),\
	FSTN::NODE()
#define AND 2,	\
	FSTN::NODE(1, FSTN::RELATION('&', 1)),\
	FSTN::NODE()
#define OR 2,	\
	FSTN::NODE(1, FSTN::RELATION('|', 1)),\
	FSTN::NODE()
#define NO 2,	\
	FSTN::NODE(1, FSTN::RELATION('?', 1)),\
	FSTN::NODE()
#define LESS 2,	\
	FSTN::NODE(1, FSTN::RELATION('<', 1)),\
	FSTN::NODE()
#define MORE 2,	\
	FSTN::NODE(1, FSTN::RELATION('>', 1)),\
	FSTN::NODE()

#define SEMICOLON 2,	\
	FSTN::NODE(1, FSTN::RELATION(';', 1)),\
	FSTN::NODE()

#define COMMA 2,	\
	FSTN::NODE(1, FSTN::RELATION(',', 1)),\
	FSTN::NODE()

#define LEFTBRACE 2,	\
	FSTN::NODE(1, FSTN::RELATION('{', 1)),\
	FSTN::NODE()

#define BRACELET 2,	\
	FSTN::NODE(1, FSTN::RELATION('}', 1)),\
	FSTN::NODE()

#define LEFTTHESIS 2,	\
	FSTN::NODE(1, FSTN::RELATION('(', 1)),\
	FSTN::NODE()

#define RIGHTTHESIS 2,	\
	FSTN::NODE(1, FSTN::RELATION(')', 1)),\
	FSTN::NODE()

#define EQUALS 2,	\
	FSTN::NODE(1, FSTN::RELATION('=', 1)),\
	FSTN::NODE()
#define NEXTLINE 2,	\
	FSTN::NODE(1, FSTN::RELATION('\n', 1)),\
	FSTN::NODE()
#define IDENTIFICATOR 1,	\
			FSTN::NODE(54,	FSTN::RELATION('a', 0),	\
							FSTN::RELATION('b', 0),	\
							FSTN::RELATION('c', 0),	\
							FSTN::RELATION('d', 0),	\
							FSTN::RELATION('e', 0),	\
							FSTN::RELATION('f', 0),	\
							FSTN::RELATION('g', 0),	\
							FSTN::RELATION('h', 0),	\
							FSTN::RELATION('i', 0),	\
							FSTN::RELATION('j', 0),	\
							FSTN::RELATION('k', 0),	\
							FSTN::RELATION('l', 0),	\
							FSTN::RELATION('m', 0),	\
							FSTN::RELATION('n', 0),	\
							FSTN::RELATION('o', 0),	\
							FSTN::RELATION('p', 0),	\
							FSTN::RELATION('q', 0),	\
							FSTN::RELATION('r', 0),	\
							FSTN::RELATION('s', 0),	\
							FSTN::RELATION('t', 0),	\
							FSTN::RELATION('u', 0),	\
							FSTN::RELATION('v', 0),	\
							FSTN::RELATION('w', 0),	\
							FSTN::RELATION('x', 0),	\
							FSTN::RELATION('y', 0),	\
							FSTN::RELATION('z', 0),	\
							FSTN::RELATION('_', 0)),\
							FSTN::RELATION('A', 0),	\
							FSTN::RELATION('B', 0),	\
							FSTN::RELATION('C', 0),	\
							FSTN::RELATION('D', 0),	\
							FSTN::RELATION('E', 0),	\
							FSTN::RELATION('F', 0),	\
							FSTN::RELATION('G', 0),	\
							FSTN::RELATION('H', 0),	\
							FSTN::RELATION('I', 0),	\
							FSTN::RELATION('J', 0),	\
							FSTN::RELATION('K', 0),	\
							FSTN::RELATION('L', 0),	\
							FSTN::RELATION('M', 0),	\
							FSTN::RELATION('N', 0),	\
							FSTN::RELATION('O', 0),	\
							FSTN::RELATION('P', 0),	\
							FSTN::RELATION('Q', 0),	\
							FSTN::RELATION('R', 0),	\
							FSTN::RELATION('S', 0),	\
							FSTN::RELATION('T', 0),	\
							FSTN::RELATION('U', 0),	\
							FSTN::RELATION('V', 0),	\
							FSTN::RELATION('W', 0),	\
							FSTN::RELATION('X', 0),	\
							FSTN::RELATION('Y', 0),	\
							FSTN::RELATION('Z', 0),	\
			FSTN::NODE()
namespace FSTN {
	struct RELATION {
		char symbol;
		short nnode;
		RELATION(char c = 0x00, short ns = NULL);
	};
	struct NODE {
		short n_relation;
		RELATION* relations;
		NODE();
		NODE(short n, RELATION rel, ...);
	};
	struct FST {
		char* string;
		short position;
		short nstates;
		NODE* nodes;
		short* rstates;
		FST(char* s, short ns, NODE n, ...);
	};
	bool execute(FST fst);
}