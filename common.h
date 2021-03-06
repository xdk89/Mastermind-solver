#include <stdio.h>
#include <fstream>


#ifndef __COMMON
#define __COMMON

//--------------------------------------------------------------------------------------------------------------definitions

enum eColor { empty, a=1, b=2, c=3, d=4, e=5, f=6 };
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

void generateTable(); 

Code m_table [1300];
int tablepointer = 0; 

std::ofstream myfile;
void printFileCode(Code cd);

//--------------------------------------------------------------------------------------------------------------functions

void generateTable(){
	int counter= 0;
	for(int i=0; i<6; i++){
		for(int k=0; k<6; k++){
			for(int l=0; l<6; l++){
				for(int m=0; m<6; m++){
					m_table[counter][0] =  (eColor) (i+1);
					m_table[counter][1] =  (eColor) (k+1);
					m_table[counter][2] =  (eColor) (l+1);
					m_table[counter++][3] = (eColor) (m+1);
				}
			}
		}
	}
	tablepointer = counter;
}

void printTable(){
	for(int i=0; i< tablepointer; i++){
		printCode(m_table[i]);
		printLine();
	}
}

void printFileTable(){
    myfile.open("mastermind.log");
	for(int i=0; i< tablepointer; i++){
		printFileCode(m_table[i]);
	    myfile << "\n";	
	}
    myfile.close();
}

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

void printFileCode(Code cd){
	for( int i=0; i<4; i++){
		switch(cd[i]){
			case empty:
				myfile << "-";
			break;
			case a:
				myfile << "a";
			break;
			case b:
				myfile << "b";
			break;
			case c:
				myfile << "c";
			break;
			case d:
				myfile << "d";
			break;
			case e:
				myfile << "e";
			break;
			case f:
				myfile << "f";
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
#endif
