#include "Greibach.h"
#include "string.h"
#define GRB_ERROR_SERIES 600
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)
namespace GRB
{
	Rule::Chain::Chain(short psize, GRBALPHABET s, ...) {
		size = psize;
		nt = new GRBALPHABET[psize];
		int* p = (int*)&s;
		for (short i = 0; i < psize; i++) nt[i] = (GRBALPHABET)p[i];
	};
	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...) {
		nn = pnn;
		iderror = piderror;
		chains = new Chain[size = psize];
		Chain* p = &c;
		for (int i = 0; i < size; i++) chains[i] = p[i];
	};
	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...) {
		startN = pstartN;
		stbottomT = pstbottom;
		rules = new Rule[size = psize];
		Rule* p = &r;
		for (int i = 0; i < size; i++) rules[i] = p[i];
	};
	short Greibach::getRule(GRBALPHABET pnn, Rule& prule) {
		short temp = -1;
		short k = 0;
		while (k < size && rules[k].nn != pnn) k++;
		if (k < size) prule = rules[temp = k];
		return temp;
	}
	Rule Greibach::getRule(short n) {
		Rule rc;
		if (n < size) rc = rules[n];
		return rc;
	};
	char* Rule::getCRule(char* b, short nchain) {
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn);
		b[1] = '-'; b[2] = '>'; b[3] = 0x00;
		chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	}
	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j) {
		short rc = -1;
		while (j < size && chains[j].nt[0] != t) ++j;
		rc = (j < size ? j : -1);
		if (rc >= 0) pchain = chains[rc];
		return rc;
	}
	char* Rule::Chain::getCChain(char* b) {
		for (int i = 0; i < size; i++) b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	}
	Greibach greibach(NS('S'), TS('$'),	
		13,
		Rule(
			NS('S'), GRB_ERROR_SERIES + 0,
			3,
			Rule::Chain(6, TS('t'), TS('f'), TS('i'), NS('F'), NS('B'), NS('S')),
			Rule::Chain(4, TS('s'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(5, TS('t'), TS('f'), TS('i'), NS('F'), NS('B'))
		),
		Rule(
			NS('F'), GRB_ERROR_SERIES + 1,
			2,
			Rule::Chain(3, TS('('), NS('P'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),
		Rule(
			NS('P'), GRB_ERROR_SERIES + 2,
			2,
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('P'))
		),
		Rule(
			NS('B'), GRB_ERROR_SERIES + 3,
			3,
			Rule::Chain(6, TS('{'), NS('N'), TS('b'), NS('I'), TS(';'), TS('}')),
			Rule::Chain(5, TS('{'), TS('b'), NS('I'), TS(';'), TS('}')),
			Rule::Chain(3, TS('{'), NS('N'), TS('}'))
		),
		Rule(
			NS('I'), GRB_ERROR_SERIES + 4,
			2,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l'))
		),
		Rule(
			NS('U'), GRB_ERROR_SERIES + 5,
			1,
			Rule::Chain(3, TS('{'), NS('N'), TS('}'))
		),
		Rule(
			NS('N'), GRB_ERROR_SERIES + 6,
			20,
			Rule::Chain(5, TS('q'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(7, TS('q'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(8, TS('u'), TS('('), NS('R'), TS(')'), TS('{'), NS('X'), TS('}'), NS('N')),
			Rule::Chain(8, TS('y'), TS('('), NS('R'), TS(')'), TS('{'), NS('X'), TS('}'), NS('N')),
			Rule::Chain(12, TS('y'), TS('('), NS('R'), TS(')'), TS('{'), NS('X'), TS('}'), TS('n'), TS('{'), NS('X'), TS('}'), NS('N')),
			Rule::Chain(4, TS('o'), NS('I'), TS(';'), NS('N')),
			Rule::Chain(3, TS('^'), TS(';'), NS('N')),
			Rule::Chain(4, TS('b'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), NS('K'), TS(';'), NS('N')),

			Rule::Chain(4, TS('q'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(6, TS('q'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(7, TS('u'), TS('('), NS('R'), TS(')'), TS('{'), NS('X'), TS('}')),
			Rule::Chain(7, TS('y'), TS('('), NS('R'), TS(')'), TS('{'), NS('X'), TS('}')),
			Rule::Chain(11, TS('y'), TS('('), NS('R'), TS(')'), TS('{'), NS('X'), TS('}'), TS('n'), TS('{'), NS('X'), TS('}')),
			Rule::Chain(3, TS('o'), NS('I'), TS(';')),
			Rule::Chain(2, TS('^'), TS(';')),
			Rule::Chain(3, TS('b'), NS('E'), TS(';')),
			Rule::Chain(3, TS('i'), NS('K'), TS(';'))
		),
		Rule(
			NS('R'), GRB_ERROR_SERIES + 7,
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(3, TS('i'), TS('v'), TS('i')),
			Rule::Chain(3, TS('i'), TS('v'), TS('l')),
			Rule::Chain(3, TS('l'), TS('v'), TS('i'))
		),
		Rule(
			NS('K'), GRB_ERROR_SERIES + 8,
			2,
			Rule::Chain(3, TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),
		Rule(
			NS('E'), GRB_ERROR_SERIES + 9,
			8,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(2, TS('i'), NS('K')),

			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('i'), NS('K'), NS('M'))
		),
		Rule(
			NS('W'), GRB_ERROR_SERIES + 10,
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(
			NS('M'), GRB_ERROR_SERIES + 11,
			2,
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
		),
		Rule(
			NS('X'), GRB_ERROR_SERIES + 12,
			14,
			Rule::Chain(5, TS('q'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(7, TS('q'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('o'), NS('I'), TS(';'), NS('N')),
			Rule::Chain(3, TS('^'), TS(';'), NS('N')),
			Rule::Chain(4, TS('b'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), NS('K'), TS(';'), NS('N')),

			Rule::Chain(4, TS('q'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(6, TS('q'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(3, TS('o'), NS('I'), TS(';')),
			Rule::Chain(2, TS('^'), TS(';')),
			Rule::Chain(3, TS('b'), NS('E'), TS(';')),
			Rule::Chain(3, TS('i'), NS('K'), TS(';'))
		)
	);
	Greibach getGreibach() { return greibach; }
}