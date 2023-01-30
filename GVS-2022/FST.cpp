#include<iostream>
#include"FST.h";
namespace FSTN {
	RELATION::RELATION(char c, short ns) {
		symbol = c;
		nnode = ns;
	}

	NODE::NODE() {
		n_relation = 0;
		relations = NULL;
	}

	NODE::NODE(short n, RELATION rel, ...) {
		n_relation = n;
		RELATION* ptr = &rel;
		relations = new RELATION[n_relation];
		for (int i = 0; i < n_relation; i++) {
			relations[i] = ptr[i];
		}
	}

	FST::FST(char* s, short ns, NODE n, ...) {
		string = s;
		nstates = ns;
		nodes = new NODE[ns];
		NODE* p = &n;
		for (int k = 0; k < ns; k++)
			nodes[k] = p[k];
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short) * nstates);
		rstates[0] = 0;
		position = -1;
	}
	bool execute(FST fst) {
		short* rstates = new short[fst.nstates];
		memset(rstates, -1, fst.nstates * (sizeof(short)));
		short length = strlen(fst.string);
		bool rc = true;
		for (short i = 0; i < length && rc; i++) {
			fst.position++;
			rc = false;
			std::swap(fst.rstates, rstates);
			for (short k = 0; k < fst.nstates; k++) {
				if (rstates[k] == fst.position) {
					for (short j = 0; j < fst.nodes[k].n_relation; j++) {
						if (fst.nodes[k].relations[j].symbol == fst.string[fst.position]) {
							fst.rstates[fst.nodes[k].relations[j].nnode] = fst.position + 1;
							rc = true;
						}
					}
				}
			}
		}
		delete[]rstates;
		return(rc ? fst.rstates[fst.nstates - 1] == length : rc);
	}
}