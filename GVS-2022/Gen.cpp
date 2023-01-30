#include"Gen.h"
#define _CRT_SECURE_NO_WARNINGS
#include<fstream>
#include"Semantica.h"
#include"Parm.h"
#include<stack>
#include<queue>
#include <string>
namespace Gen {
	queue<string>HW;
	void GeneratorCode(LT::LexTable pLexT, IT::IdTable pIdT, wchar_t pout[]) {
		std::vector<std::pair<char*, char*>>sizesnames;
		LT::LexTable lexT = pLexT;
		IT::IdTable idT = pIdT;
		ofstream out(pout);
		out << ".586\n";
		out << ".model flat, stdcall\n";
		out << "includelib kernel32.lib\n";
		out << "includelib libucrt.lib\n";
		out << "includelib ..\\Debug\\GVS-2022Libs.lib\n";
		out << "SetConsoleTitleA PROTO : DWORD\n";
		out << "GetStdHandle PROTO:DWORD\n";
		out << "WriteConsoleA PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD\n";
		out << "printconsole PROTO : DWORD, : DWORD\n";
		out << "SetConsoleOutputCP PROTO : DWORD\n\n";
		out << "SetConsoleCP PROTO : DWORD\n\n";
		out << "ExitProcess PROTO:DWORD\n\n";
		out << "\n.stack 4096\n\n";
		out << "EXTRN module: proc\n";
		out << "EXTRN raiser: proc\n";
		out << ".const\n";
		out << "endl equ 0ah" << "\n";
		out << "str_endl byte endl,0\n";
		for (int i = 0,counterious=0; i < idT.size; i++) {
			if (idT.table[i].idtype == IT::L) {
				out << "\t" << idT.table[i].id;
				if (idT.table[i].iddatatype == IT::SYM) {
					char name[255];
					out << " BYTE \"" << idT.table[i].value.vstr.str << "\", 0\n";
					_itoa_s(counterious, name, 10);
					string ch = "HW";
					string names[255];
					names[counterious] = ch+name;
					out <<names[counterious]<< " = ($ - " << idT.table[i].id << ")\n";
					HW.push(names[counterious]);
					counterious++;
				}	
				if (idT.table[i].iddatatype == IT::INT) {
					out << " SDWORD " << idT.table[i].value.vint;
				}
				out << "\n";
			}
		}
		out << "\n.data\n";
		out << "\tbuffer BYTE 256 dup(0)\n";
		out << "\tmessageSize dword ?\n";
		out << "\tconsoleTitle BYTE \'GVS-2022\'\n";
		out << "\tresult BYTE 40 dup(0)\n";
		out << "\tfunc_work BYTE \'Working functions=\'\n";
		out << "\tstrsym_work BYTE \'Working symbol/string\'\n";
		out << "\tint_work BYTE \'Working integer=\'\n";
		out << "\tconsolehandle dword 0h\n";
		for (int i = 0; i < lexT.size; i++) {
			if (lexT.table[i].lexema == LEX_CREATE) {
				if (idT.table[lexT.table[i + 2].idxTI].idtype == IT::V) {
					out << "\t" << idT.table[lexT.table[i + 2].idxTI].id;
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype == IT::SYM)
						out << " DWORD ?\n";
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype == IT::INT)
						out << " SDWORD 0\n";
				}
			}
		}
		stack<char*> stk;
		int num_of_points = 0,
			num_of_ret = 0,
			num_of_ends = 0,
			num_of_cycles = 0,
			countParm = 0;
		string strret = string(),
			cycle_code = string(),
			func_name = string();
		bool flag_func = false,
			flag_ret = false,
			flag_body = false,
			flag_if = false,
			flag_then = false,
			flag_else = false,
			flag_proc = false,
			flag_callfunc = false,
			flag_condition = false,
			flag_cycle = false;

		int result_position;

		out << "\n.code\n\n";
		for (int i = 0; i < lexT.size; i++) {
			switch (lexT.table[i].lexema) {
			case LEX_FUNCTION:
				while (lexT.table[i].lexema != RIGHTHESIS) {
					if (lexT.table[i].lexema == LEX_ID && idT.table[lexT.table[i].idxTI].idtype == IT::F) {
						out << (func_name = string((char*)idT.table[lexT.table[i].idxTI].id)) << " PROC ";
					}
					if (lexT.table[i].lexema == LEX_ID && idT.table[lexT.table[i].idxTI].idtype == IT::P) {
						out << idT.table[lexT.table[i].idxTI].id << " : ";
						if (idT.table[lexT.table[i].idxTI].iddatatype == IT::INT)
							out << "SDWORD";
						else
							out << "BYTE";
					}
					if (lexT.table[i].lexema == LEX_COMMA)
						out << ", ";
					i++;
				}
				flag_func = true;
				out << "\n";
				break;


			case LEX_START: {
				flag_body = true;
				out << "main PROC\n";
				break;
			}

			case LEX_EQUAL: {
				result_position = i - 1;
				while (lexT.table[i].lexema != LEX_SEMICOLON) {
					switch (lexT.table[i].lexema) {
					case LEX_ID:
					case LEX_LITERAL:
						if (idT.table[lexT.table[i].idxTI].idtype == IT::F)
							flag_callfunc = true;
						if (idT.table[lexT.table[i].idxTI].iddatatype == IT::INT) {
							out << "\tpush " << idT.table[lexT.table[i].idxTI].id << "\n";
							stk.push(idT.table[lexT.table[i].idxTI].id);
							break;
						}
						if (idT.table[lexT.table[i].idxTI].iddatatype == IT::SYM) {
							char* s;
							if (idT.table[lexT.table[i].idxTI].idtype == IT::L) {
								out << "\tmov eax, offset " << idT.table[lexT.table[i].idxTI].id << "\n";
								s = new char[8]{ "offset " };
							}
							else {
								out << "\tpush " << idT.table[lexT.table[i].idxTI].id << "\n";
								s = new char[1]{ "" };
							}

							size_t len1 = strlen((char*)s);
							size_t len2 = strlen((char*)idT.table[lexT.table[i].idxTI].id);
							char* result = (char*)malloc(len1 + len2 + 1);
							memcpy(result, s, len1);
							memcpy(result + len1, (char*)idT.table[lexT.table[i].idxTI].id, len2 + 1);
							stk.push(result);
							break;
						}

					case LEX_OPERATOR:
						switch (lexT.table[i].op) {
						case LT::OMUL:
							out << "\tpop eax\n\tpop ebx\n";
							out << "\tmul ebx\n\tpush eax\n";
							break;
						case LT::OPLUS:
							out << "\tpop eax\n\tpop ebx\n";
							out << "\tadd eax, ebx\n\tpush eax\n";
							break;
						case LT::OMINUS:
							out << "\tpop ebx\n\tpop eax\n";
							out << "\tsub eax, ebx\n\tpush eax\n";
							break;
						case LT::ODIV:
							out << "\tpop ebx\n\tpop eax\n";
							out << "\tcdq\n\tidiv ebx\n\tpush eax\n";
							break;
						case LT::OAND:
							out << "\tpop ebx\n\tpop eax\n";
							out << "\tand eax, ebx\n\tpush edx\n";
							break;
						case LT::OOR:
							out << "\tpop ebx\n\tpop eax\n";
							out << "\tor eax, ebx\n\tpush edx\n";
							break;
						case LT::ONOT:
							out << "\tpop ebx\n\tpop eax\n";
							out << "\tnot eax, ebx\n\tpush edx\n";
							break;
						}
						break;

					case '@':
						countParm = (char)lexT.table[i + 1].lexema - '0';

						for (int j = 1; j <= countParm; j++)
							out << "\tpop edx\n";

						for (int j = 1; j <= countParm; j++) {
							out << "\tpush " << stk.top() << "\n";
							stk.pop();
						}
						out << "\tcall " << idT.table[lexT.table[i].idxTI].id << "\n\tpush eax\n";
						flag_callfunc = false;
						break;
					}

					i++;
				}

				out << "\tpop " << idT.table[lexT.table[result_position].idxTI].id << "\n";
				break;

			case '@':
				countParm = (char)lexT.table[i + 1].lexema - '0';
				for (int j = 1; j <= countParm; j++) {
					if (idT.table[lexT.table[i - j].idxTI].iddatatype == IT::INT)
						out << "\tpush " << idT.table[lexT.table[i - j].idxTI].id << "\n";
					else {
						if (idT.table[lexT.table[i - j].idxTI].idtype == IT::L)
							out << "\tpush offset " << idT.table[lexT.table[i - j].idxTI].id << "\n";
						else
							out << "\tpush " << idT.table[lexT.table[i - j].idxTI].id << "\n";
					}
				}

				out << "\tcall " << idT.table[lexT.table[i].idxTI].id << "\n";
				break;

			case LEX_BRING:
				out << "\tpush ";
				if (idT.table[lexT.table[i + 1].idxTI].idtype == IT::L)
					out <<"eax\n" << "\n";
				else
					out << idT.table[lexT.table[i + 1].idxTI].id << "\n";
				if (flag_func) {
					out << "\tjmp local" << num_of_ret << "\n";
					flag_ret = true;
				}
				if (flag_body) {
					out << "\t\tjmp theend\n";
					flag_ret = true;
				}
				break;

			case LEX_BRACELET:
				if (flag_body && !flag_then && !flag_else && !flag_func && !flag_cycle) {
					if (flag_ret) {
						out << "theend:\n";
						flag_ret = false;
					}
					out << "\tcall ExitProcess\nmain ENDP\n";
				}
				if (flag_func && !flag_then && !flag_else && !flag_cycle) {
					if (flag_ret) {
						out << "local" << num_of_ret++ << ":\n";
						out << "\tpop eax\n\tret\n";
						flag_ret = false;
					}
					if (flag_proc) {
						out << "\tret\n";
						flag_proc = false;
					}
					out << func_name << " ENDP\n\n";
					flag_func = false;
				}
				if (flag_then) {
					flag_then = false;
					if (flag_else) {
						out << "\tjmp e" << num_of_ends << "\n";
						flag_else = false;
					}
					out << "m" << num_of_points++ << ":\n";
				}
				if (flag_else) {
					flag_else = false;
					out << "e" << num_of_ends++ << ":\n";
				}
				if (flag_cycle) {
					out << cycle_code << "cyclenext" << num_of_cycles << ":\n";
					cycle_code.clear();
					num_of_cycles++;
					flag_cycle = false;
				}
				break;

			case LEX_IF:
				flag_if = true;
				break;

			case LEX_UNTIL:
				flag_cycle = true;
				flag_condition = true;
				break;

			case LEX_OTHERWISE:
				flag_else = true;
				break;

			case LEFTHESIS:
				if (flag_if) {
					if (lexT.table[i + 2].lexema == RIGHTHESIS) {
						out << "\tmov eax, " << idT.table[lexT.table[i + 1].idxTI].id << "\n";
						out << "\tcmp eax, 1\n";
						out << "\tjz m" << num_of_points << "\n";
						out << "\tjnz m" << num_of_points + 1 << "\n";
					}
					else {
						out << "\tmov eax, " << idT.table[lexT.table[i + 1].idxTI].id << "\n";
						out << "\tcmp eax, " << idT.table[lexT.table[i + 3].idxTI].id << "\n";

						if (lexT.table[i + 2].op == LT::OMORE) {
							out << "\tjg m" << num_of_points << "\n";
							out << "\tjl m" << num_of_points + 1 << "\n";
						}
						else if (lexT.table[i + 2].op == LT::OLESS) {
							out << "\tjl m" << num_of_points << "\n";
							out << "\tjg m" << num_of_points + 1 << "\n";
						}
					}
					out << "\tje m" << num_of_points + 1 << "\n";
					int j = i;
					while (lexT.table[j++].lexema != LEX_BRACELET) {
						if (lexT.table[j + 1].lexema == LEX_OTHERWISE) {
							flag_else = true;
							break;
						}
					}
				}

				if (flag_condition) {
					if (lexT.table[i + 2].lexema == RIGHTHESIS) {
						out << "\tmov eax, " << idT.table[lexT.table[i + 1].idxTI].id << "\n";
						out << "\tcmp eax, 1\n";
						cycle_code = "\tmov eax, " + string((char*)idT.table[lexT.table[i + 1].idxTI].id) + "\n" +
							"\tcmp eax, " + string((char*)idT.table[lexT.table[i + 1].idxTI].value.vint) + "\n";
						cycle_code += "\tjz cycle" + to_string(num_of_cycles) + "\n";
						out << "\tjz cycle" << num_of_cycles << "\n";
					}
					else {
						cycle_code = "\tmov eax, " + string((char*)idT.table[lexT.table[i + 1].idxTI].id) + "\n" +
							"\tcmp eax, " + string((char*)idT.table[lexT.table[i + 3].idxTI].id) + "\n";
						out << "\tmov eax, " << idT.table[lexT.table[i + 1].idxTI].id << "\n";
						out << "\tcmp eax, " << idT.table[lexT.table[i + 3].idxTI].id << "\n";

						if (lexT.table[i + 2].op == LT::OMORE) {
							cycle_code += "\tjg cycle" + to_string(num_of_cycles) + "\n";
							out << "\tjg cycle" << num_of_cycles << "\n";
						}
						else if (lexT.table[i + 2].op == LT::OLESS) {
							cycle_code += "\tjl cycle" + to_string(num_of_cycles) + "\n";
							out << "\tjl cycle" << num_of_cycles << "\n";
						}
					}
					out << "\tjmp cyclenext" << num_of_cycles << "\n";
				}
				break;

			case RIGHTHESIS:
				if (lexT.table[i + 1].lexema == LEX_LEFTBRACE && flag_if) {
					flag_then = true;
					out << "m" << num_of_points++ << ":\n";
					flag_if = false;
				}
				if (lexT.table[i + 1].lexema == LEX_LEFTBRACE && flag_condition) {
					out << "cycle" << num_of_cycles << ":\n";
					flag_condition = false;
				}
				break;

			case LEX_OUTPUT:
				if (idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::INT) {
					out << "\tpush " << idT.table[lexT.table[i + 1].idxTI].id << "\n\tpush offset result\n"<<
						"\tcall int_to_char\n"<<"\tinvoke printconsole,offset int_work,offset consoleTitle\n";
				}
				else {
					out << "push offset consoleTitle\n";
					out << "call SetConsoleTitleA\n";
					out << "mov messageSize, " << HW.front() << "\n";
					HW.pop();
					out << "push -11\n";
					out << "call GetStdHandle\n";
					out << "mov consolehandle,eax\n";
					out << "push 0\npush 0\npush messageSize\npush offset "<< idT.table[lexT.table[i + 1].idxTI].id <<"\npush consolehandle\ncall WriteConsoleA\n";
				}
				break;

			case LEX_JUMP:
				out << "invoke printconsole, offset str_endl, offset consoleTitle \n";
				break;
			}
			}
		}
		out << "\nprintconsole proc uses eax ebx ecx edi esi,"<< "pstr :dword,ptitle :dword";
		out << "\npush ptitle";
		out << "\ncall SetConsoleTitleA ;";
		out << "\nmov esi,pstr";
		out << "\npush -11 ; -11 - handle для стандартного вывода";
		out << "\ncall GetStdHandle ; получить handle -> в eax";
		out << "\nmov esi, pstr ; подсчет количества символов";
		out << "\nmov edi, -1 ; до 0-символа";
		out << "\ncount:";
		out << "\ninc edi ;";
		out << "\ncmp byte ptr [esi + edi], 0 ; ";
		out << "\njne count ;";
		out << "\npush 0 ; можно 0 (резерв)";
		out << "\npush 0 ; можно 0";
		out << "\npush edi ; количество байт";
		out << "\npush pstr ; адрес выводимой строки";
		out << "\npush eax ; handle для вывода (eax)";
		out << "\ncall WriteConsoleA ; вывести в консоль";
		out << "\nret ; вывести в консоль";
		out << "\nprintconsole ENDP";
		out << "; ----------------преобразование числа в строку--------------------------\n";
		out << "int_to_char PROC uses eax ebx ecx edi esi,"<< "pstr : dword,intfield : sdword\n";
		out << "mov edi, pstr\n";
		out << "mov esi, 0\n";
		out << "mov eax, intfield\n";
		out << "cdq\n";
		out << "mov ebx,10\n";
		out << "idiv ebx\n";
		out << "test eax, 80000000h\n";
		out << "jz plus\n";
		out << "neg eax\n";
		out << "neg edx\n";
		out << "mov cl,\'-\'\n";
		out << "mov[edi],cl\n";
		out << "inc edi\n";
		out << "plus:\n";
		out << "push dx\n";
		out << "inc esi\n";
		out << "test eax,eax;\n";
		out << "jz fin\n";
		out << "cdq\n";
		out << "idiv ebx\n";
		out << "jmp plus\n";
		out << "fin:\n";
		out << "mov ecx,esi\n";
		out << "write:\n";
		out << "pop bx\n";
		out << "add bl, '0'\n";
		out << "mov[edi], bl\n";
		out << "inc edi\n";
		out << "loop write\n";
		out << "ret\n";
		out << "int_to_char ENDP\n";
		out << "end main\n";
	}
}