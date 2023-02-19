#include<algorithm>
#include <Windows.h>
#include<stdio.h>
extern "C"{
	int raiser(int a, int b) {
		return pow(a, b);
	}
	int module(int a) {
		return abs(a);
	}
	/*void outputint(int a) {
		int iout = a;
		printf("%d", iout);
	}
	void outputsym(char a) {
		char chout = a;
		printf("%c", chout);
	}
	void outputstr(char* a) {
		if (a == nullptr) {
			printf("%c",'\n');
			return;
		}
		char strout[255];
		for (int i = 0; a[i] != '\0'; i++) {
			strout[i] = a[i];
		}
		printf("%s", strout);
	}*/
}