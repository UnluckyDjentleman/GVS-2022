#include"PolishNotation.h"
#include"parm.h";
#include"Log.h"
#include"LT.h"
#include<stack>
#include<queue>
#include<map>
using namespace std;
map<char, int>Priorities = {
	{'<',0},
	{'>',0},
	{'(',0},
	{')',0},
	{',',1},
	{'+',2},
	{'-',2},
	{'*',3},
	{'/',3},
	{'&',3},
	{'|',3},
	{'?',3}
};
namespace PN {
	bool polishNotation(int i, LexAn::LEX& lex) {
		std::stack<LT::Entry> stack;
		std::queue<LT::Entry> queue;

		LT::Entry aggregate_symbol;
		aggregate_symbol.idxTI = -1;
		aggregate_symbol.lexema = '#';
		aggregate_symbol.sn = lex.lextable.table[i].sn;

		LT::Entry function_symbol;
		function_symbol.idxTI = LT_TI_NULLIDX;
		function_symbol.lexema = '@';
		function_symbol.sn = lex.lextable.table[i].sn;
		int idx;

		int lexem_counter = 0;
		int parm_counter = 0;
		int lexem_position = i;
		char* buf = new char[i];

		bool is_function = false;

		for (i; lex.lextable.table[i].lexema != LEX_SEMICOLON; i++, lexem_counter++) {
			switch (lex.lextable.table[i].lexema) {
			case LEX_ID:
			case LEX_LITERAL:
				if (lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::F) {
					is_function = true;
					idx = lex.lextable.table[i].idxTI;
				}
				else {
					if (is_function)
						parm_counter++;
					queue.push(lex.lextable.table[i]);
				}
				continue;

			case LEFTHESIS:
				stack.push(lex.lextable.table[i]);
				continue;

			case RIGHTHESIS:
				while (stack.top().lexema != LEFTHESIS) {
					queue.push(stack.top());
					stack.pop();
					if (stack.empty())
						return false;
				}

				if (!is_function)
					stack.pop();
				else {
					function_symbol.idxTI = idx;
					idx = LT_TI_NULLIDX;
					lex.lextable.table[i] = function_symbol;
					queue.push(lex.lextable.table[i]);
					_itoa_s(parm_counter, buf, 2, 10);
					stack.top().lexema = buf[0];
					stack.top().idxTI = LT_TI_NULLIDX;
					stack.top().sn = function_symbol.sn;
					queue.push(stack.top());
					stack.pop();
					parm_counter = 0;
					is_function = false;
				}
				continue;

			case LEX_OPERATOR:
				while (!stack.empty() && Priorities[lex.lextable.table[i].lexema] <= Priorities[stack.top().lexema]) {
					queue.push(stack.top());
					stack.pop();
				}
				stack.push(lex.lextable.table[i]);
				continue;
			}
		}

		while (!stack.empty()) {
			if (stack.top().lexema == LEFTHESIS || stack.top().lexema == RIGHTHESIS)
				return false;

			queue.push(stack.top());
			stack.pop();
		}

		while (lexem_counter != 0) {
			if (!queue.empty()) {
				lex.lextable.table[lexem_position++] = queue.front();
				queue.pop();
			}
			else
				lex.lextable.table[lexem_position++] = aggregate_symbol;

			lexem_counter--;
		}

		for (int i = 0; i < lexem_position; i++) {
			if (lex.lextable.table[i].lexema == LEX_OPERATOR || lex.lextable.table[i].lexema == LEX_LITERAL)
				lex.idtable.table[lex.lextable.table[i].idxTI].idxfirstLE = i;
		}

		return true;
	}

	void startPolish(LexAn::LEX& lex) {
		for (int i = 0; i < lex.lextable.size; i++) {
			if (lex.lextable.table[i].lexema == '=') {
				polishNotation(i + 1, lex);
			}
		}
	}
}