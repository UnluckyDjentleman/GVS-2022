#pragma once
#define ID_MAXSIZE 16
#define SCOPE_NAME_MAX (ID_MAXSIZE*2-1)
#define TI_MAXSIZE 4096
#define TI_INT_DEFAULT 0x00000000
#define TI_INT_MAXVAL 65535
#define TI_INT_MINVAL -65536
#define TI_STR_DEFAULT 0x00
#define TI_NULLIDX 0xffffffff
#define TI_STR_MAXSIZE 255										
namespace IT {
	enum IDDATATYPE {INT = 1, SYM=2};
	enum IDTYPE {V = 1, F = 2, P = 3, L = 4, OP = 5};
	struct Entry {
		int idxfirstLE;
		char scope[ID_MAXSIZE];
		char* id = new char[2 * ID_MAXSIZE];
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		union {
			int vint;
			struct {
				int len;
				char str[TI_STR_MAXSIZE - 1];
			} vstr;
			struct {
				int CountOfPar;
				IDDATATYPE* types;
			} parameters;
		}value;
	};
	struct IdTable {
		int maxsize;
		int size;
		Entry* table;
	};
	IdTable Create(int size);
	void Add(IdTable& idtable, Entry entry);
	Entry GetEntry(IdTable& idtable, int n);
	Entry GetEntry(char id, IdTable& idtable);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]);
	void Delete(IdTable& idtable);
	void Write(IdTable& idtable, std::ostream* streamline);
}
