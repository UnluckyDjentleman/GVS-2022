#pragma once
#include<iostream>
#include"LT.h"
#include"IT.h"
#include"Log.h"
#include"Parm.h"
#include<wchar.h>
using namespace std;
namespace Gen {
	void GeneratorCode(LT::LexTable pLexT,IT::IdTable pIdT,wchar_t pout[]);
}