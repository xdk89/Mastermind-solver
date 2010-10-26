#include <stdio.h>


#ifndef __COMMON
#define __COMMON

//--------------------------------------------------------------------------------------------------------------definitions

enum eColor { empty, a, b, c, d, e, f };
enum ePin   { none, white, black      };

typedef eColor Code [4];
typedef ePin   Pins [4];

struct History { Code code; Pins pins; };
History m_history[50];
int historypointer = -1;

void printCode(Code);
void printPins(Pins);
void printLine();
void printTab();
void printHistory();

void addRecordToHistory(Code, Pins);
void addRecordToHistory(eColor, eColor, eColor, eColor, ePin, ePin, ePin, ePin);



//--------------------------------------------------------------------------------------------------------------functions


int countBlackPins(History *hs, int index){
	int count = 0;
	for(int i=0; i<4; i++){
		if(hs[index].pins[i] == black){
			count++;
		}
	}
	return count;
}

int countWhitePins(History *hs, int index){
	int count = 0;
	for(int i=0; i<4; i++){
		if(hs[index].pins[i] == white){
			count++;
		}
	}
	return count;
}

void printCode(Code cd){
	for( int i=0; i<4; i++){
		switch(cd[i]){
			case empty:
				printf("-");
			break;
			case a:
				printf("a");
			break;
			case b:
				printf("b");
			break;
			case c:
				printf("c");
			break;
			case d:
				printf("d");
			break;
			case e:
				printf("e");
			break;
			case f:
				printf("f");
			break;			
		}
	}	
}

void printPins(Pins pn){
	for( int i=0; i<4; i++ ){
		switch(pn[i]){
			case none:
				printf("-");
			break;
			case white:
				printf("w");
			break;
			case black:
				printf("b");
			break;
		}
	}
}

void printLine(){
	printf("\n");
}

void printTab(){
	printf("\t");
}

void printHistory(){
	for(int i=0; i <= historypointer ; i++){
		printCode(m_history[i].code);
		printTab();
		printPins(m_history[i].pins);
		printLine();
	}
}

void addRecordToHistory(Code cd, Pins pn){
	int index = ++historypointer;
	m_history[index].code[0] = cd[0];
	m_history[index].code[1] = cd[1];
	m_history[index].code[2] = cd[2];
	m_history[index].code[3] = cd[3];
	m_history[index].pins[0] = pn[0];
	m_history[index].pins[1] = pn[1];
	m_history[index].pins[2] = pn[2];
	m_history[index].pins[3] = pn[3];	
}

void addRecordToHistory(eColor e1, eColor e2, eColor e3, eColor e4, ePin p1, ePin p2, ePin p3, ePin p4){
	int index = ++historypointer;
	m_history[index].code[0] = e1;
	m_history[index].code[1] = e2;
	m_history[index].code[2] = e3;
	m_history[index].code[3] = e4;
	m_history[index].pins[0] = p1;
	m_history[index].pins[1] = p2;
	m_history[index].pins[2] = p3;
	m_history[index].pins[3] = p4;
}
#endif
