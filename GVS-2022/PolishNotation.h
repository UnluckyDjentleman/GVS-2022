#pragma once
#define _CRT_NO_SECURE_WARNINGS
#include<iostream>
#include<ostream>
#include<stack>
#include"IT.h"
#include"LT.h"
#include"IN.h"
#include"Lexica.h"
#include<map>
namespace PN {
	void startPolish(LexAn::LEX& lex);
	bool polishNotation(int i, LexAn::LEX& lex);
}