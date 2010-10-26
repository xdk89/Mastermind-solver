#include <stdio.h>
#include "common.h"

#ifndef __VALIDATOR
#define __VALIDATOR

//--------------------------------------------------------------------------------------------------------definitions



//helpers
eColor ColorsCertainlyInCode[] =    { empty, empty,empty, empty };	  	//contains colors that are certainly in the code (minimum 1 and maximum 4 colors in a code).
eColor ColorsCertainlyNotInCode[] = { empty, empty, empty, empty, empty };	//contains colors that are certainly not in the code (minimum 2 and maximum 5 in colors not in a code).

int ColorAShouldOnPos= -1; 
int ColorBShouldOnPos= -1;
int ColorCShouldOnPos= -1;
int ColorDShouldOnPos= -1;
int ColorEShouldOnPos= -1;
int ColorFShouldOnPos= -1;
int ColorAShouldNotOnPos[] = { -1,-1,-1,-1 };
int ColorBShouldNotOnPos[] = { -1,-1,-1,-1 };
int ColorCShouldNotOnPos[] = { -1,-1,-1,-1 };
int ColorDShouldNotOnPos[] = { -1,-1,-1,-1 };
int ColorEShouldNotOnPos[] = { -1,-1,-1,-1 };
int ColorFShouldNotOnPos[] = { -1,-1,-1,-1 };

int ShouldNotNumberOfColors[] = { -1,-1,-1,-1 };

void addNewPosToShouldNotOnPos(int[], int);

void printColorsCertainlyInCode();
void printColorsCertainlyNotInCode();

bool checkPins(Code, History*);
bool checkColorsCertainlyInCode(Code);
bool checkColorsCertainlyNotInCode(Code);
bool checkColorShouldOnPos(Code);
bool checkColorShouldNotOnPos(Code);
bool checkNumberOfColors(Code);


//-------------------------------------------------------------------------------------------------------functions



void addNewPosToShouldNotOnPos(int shouldNot[], int newPos){
	for(int i=0; i<4; i++){	
		if(shouldNot[i] == newPos) return;
	}	
	for(int k=0; k<4; k++){
		if(shouldNot[k] == -1){
			shouldNot[k] = newPos;
			return;
		}
	}
}


void printShouldNotOnPos(int shouldNot[]){
	for(int i=0; i<4; i++){
		printf("%d ", shouldNot[i]);
	}
	printf("\n");
}

void printColorsCertainlyInCode(){
	for(int i=0; i<4; i++){
		if(ColorsCertainlyInCode[i] == a){
			printf("a");
		}	
		if(ColorsCertainlyInCode[i] == b){
			printf("b");
		}	
		if(ColorsCertainlyInCode[i] == c){
			printf("c");
		}
		if(ColorsCertainlyInCode[i] == d){
			printf("d");
		}
		if(ColorsCertainlyInCode[i] == e){
			printf("e");
		}
		if(ColorsCertainlyInCode[i] == f){
			printf("f");
		}
		if(ColorsCertainlyInCode[i] == empty){
			printf("-");
		}
	}	
	printLine();
}	

void printColorsCertainlyNotInCode(){
	for(int i=0; i<5; i++){
		if(ColorsCertainlyNotInCode[i] == a){
			printf("a");
		}
		if(ColorsCertainlyNotInCode[i] == b){
			printf("b");
		}
		if(ColorsCertainlyNotInCode[i] == c){
			printf("c");
		}
		if(ColorsCertainlyNotInCode[i] == d){
			printf("d");
		}
		if(ColorsCertainlyNotInCode[i] == e){
			printf("e");
		}
		if(ColorsCertainlyNotInCode[i] == f){
			printf("f");
		}
		if(ColorsCertainlyNotInCode[i] == empty){
			printf("-");
		}
	}
	printLine();
}


/**
 * important note:
 *
 * returns false if code is definetly not valid due to the heuristics. 
 * True means that the validator cannot detect if the code is valid or not. 
 * In other words, there can occur parodox situations which it's possible that a code is invalid but
 * this function returns a true either.
 *
 * */
bool validateCode(Code cd, History *hs){
	if(!checkPins(cd, hs))		       { printf("err 0");	return false; }
	if(!checkColorsCertainlyInCode(cd))    { printf("err 1"); 	return false; }
	if(!checkColorsCertainlyNotInCode(cd)) { printf("err 2");	return false; }	
	if(!checkColorShouldOnPos(cd))	       { printf("err 3");	return false; }
	if(!checkColorShouldNotOnPos(cd))      { printf("err 4");	return false; }
	if(!checkNumberOfColors(cd))	       { printf("err 5");	return false; }
	return true;
}

bool checkPins(Code cd, History *hs){
	int whitePins=0, blackPins= 0;
	int white, black;
	for(int i=0; i <= historypointer; i++){
		Code cd2;
		cd2[0] = cd[0];
		cd2[1] = cd[1];
		cd2[2] = cd[2];
		cd2[3] = cd[3];

		blackPins = countBlackPins(hs, i);
		whitePins = countWhitePins(hs, i);
		black= 0;
		white= 0;
		for(int k=0; k<4; k++){
			if(hs[i].code[k] == cd2[k]){
				black++;
				cd2[k] == empty;
			} else if(hs[i].code[k] == cd2[0] || hs[i].code[k] == cd2[1] || hs[i].code[k] == cd2[2] || hs[i].code[k] == cd2[3]){
				white++;
			}
			
		}
		if(white != whitePins || black != blackPins){
			printf("%d", i);
			printLine();
			printCode(cd2);
			printLine();
			printf("%d - %d ", blackPins, black);
			printLine();
			printf("%d - %d", whitePins, white);
			printLine();
			printLine();
			return false;
		}
	}
	return true;
}

bool checkColorsCertainlyInCode(Code cd){
	int count = 0;
	for(int k=0; k<4; k++){
		if(ColorsCertainlyInCode[k] != empty){
			count--;
			for(int i=0; i<4; i++){
				if(cd[i] == ColorsCertainlyInCode[k]){
					count++;
					break;				
				}
			}
		}
	}
	if(count == 0)
		return true;
	printf("false due to colors certainly in code");
	return false;
}

bool checkColorsCertainlyNotInCode(Code cd){
	for(int k=0; k<4; k++){
		if(ColorsCertainlyNotInCode[k] != empty){
			for(int i=0; i<4; i++){
				if(cd[i] == ColorsCertainlyNotInCode[k]){
					printf("false due to colors certainly not in code");
					return false;
				}
			}
		}
	}
	return true;
}

bool checkColorShouldOnPos(Code cd){
	if(ColorAShouldOnPos >= 0){
		if(cd[ColorAShouldOnPos] != a){
			return false;
		}

	}
	if(ColorBShouldOnPos >= 0){
		if(cd[ColorBShouldOnPos] != b){
			return false;
		}
	}
	if(ColorCShouldOnPos >= 0){
		if(cd[ColorCShouldOnPos] != c){
			return false;
		}
	}
	if(ColorDShouldOnPos >= 0){
		if(cd[ColorDShouldOnPos] != d){
			return false;
		}		
	}
	if(ColorEShouldOnPos >= 0){
		if(cd[ColorEShouldOnPos] != e){
			return false;
		}	
	}
	if(ColorFShouldOnPos >= 0){
		if(cd[ColorFShouldOnPos] != f){
			return false;
		}	
	}
	return true;
}

bool checkColorShouldNotOnPos(Code cd){
	for(int i=0; i<4; i++){
		if(ColorAShouldNotOnPos[i] >= 0){
			if(cd[ColorAShouldNotOnPos[i]] == a){
				return false;
			}
		}
	}
	for(int i=0; i<4; i++){
		if(ColorBShouldNotOnPos[i] >= 0){
			if(cd[ColorBShouldNotOnPos[i]] == b){
				return false;
			}
		}
	}
	for(int i=0; i<4; i++){
		if(ColorCShouldNotOnPos[i] >= 0){
			if(cd[ColorCShouldNotOnPos[i]] == c){
				return false;
			}
		}
	}	
	for(int i=0; i<4; i++){
		if(ColorDShouldNotOnPos[i] >= 0){
			if(cd[ColorDShouldNotOnPos[i]] == d){
				return false;
			}
		}
	}
	for(int i=0; i<4; i++){
		if(ColorEShouldNotOnPos[i] >= 0){
			if(cd[ColorEShouldNotOnPos[i]] == e){
				return false;
			}	
		}
	}	
	for(int i=0; i<4; i++){
		if(ColorFShouldNotOnPos[i] >= 0){
			if(cd[ColorFShouldNotOnPos[i]] == f){
				return false;
			}
		}
		
	}
	return true;
}

bool checkNumberOfColors(Code cd){
	int countA=0, countB=0, countC=0, countD=0, countE=0, countF=0;
	for(int i=0; i<4; i++){
		if(cd[i] == a){
			countA++;
		}
		if(cd[i] == b){
			countB++;
		}
		if(cd[i] == c){
			countC++;
		}
		if(cd[i] == d){
			countD++;
		}
		if(cd[i] == e){
			countE++;
		}
		if(cd[i] == f){
			countF++;
		}
	}
	int number = 4;
	if(countA == 4 || countB == 4 || countC == 4 || countD == 4 || countE == 4 || countF == 4){
		number = 1;
	}
	if(countA == 3 || countB == 3 || countC == 3 || countD == 3 || countE == 3 || countF == 3){
		number = 2;
	}
	if(countA == 2 || countB == 2 || countC == 2 || countD == 2 || countE == 2 || countF == 2){
		number = 3;
	}
	for(int i = 0; i < 4 ; i++){
		if(ShouldNotNumberOfColors[i] == number){
			return false;
		}
	} 
	return true;	
}

#endif
