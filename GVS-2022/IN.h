#pragma once
#define IN_MAX_LEN_TEXT 1024*1024
#define BUFFER 512
#define IN_CODE_ENDL '\n'
#define IN_CODE_TABLE {\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::P, IN::N, IN::F,  IN::F, IN::F, IN::F, IN::F,\
		IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
		IN::P, IN::S, IN::L, IN::S,  IN::T, IN::T, IN::S, IN::S,   IN::S, IN::S, IN::S, IN::S,  IN::S, IN::S, IN::T, IN::S,\
		IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::S,  IN::S, IN::S, IN::S, IN::T,\
		IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,\
		IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::S,  IN::T, IN::S, IN::T, IN::T,\
		IN::F, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,\
		IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::S,  IN::T, IN::T, IN::LL, IN::T,\
																														   \
		IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
		IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
		IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
		IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
		IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
		IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
		IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
		IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F \
}
#include<vector>
#include<fstream>
namespace In {
	struct IN {
		enum { T = 1024, F = 2048, I = 4096, L, LL,S, P,N };
		int size;
		int lines;
		int ignor;
		unsigned char* text;
		int code[256];
	};
	IN getin(wchar_t infile[]);
}