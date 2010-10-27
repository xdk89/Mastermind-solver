#include "common.h"
#include "validator.h"

int fourColorList[][3] = {    	{ 2,2,2 }, { 2,2,3 }, { 2,3,3 }, 
			 	{ 2,3,4 }, { 3,2,2 }, { 3,2,3 },
			 	{ 3,3,2 }, { 3,3,3 }, { 3,3,4 },
			 	{ 4,3,2 } 
		     	 }; 

int threeColorList[][3] = {	{ 1,1,2 }, { 1,2,2 }, { 1,2,3 },
				{ 2,1,1 }, { 2,1,2 }, { 2,2,1 },
				{ 2,2,2 }, { 2,2,3 }, { 3,2,1 },
				{ 3,2,2 }, { 3,3,2 }
			  };

int twoColorList[][3] = {	{ 0,1,2 }, { 1,0,1 }, { 1,1,1 },
				{ 1,1,2 }, { 1,2,2 }, { 2,1,0 },
				{ 2,2,1 }, { 2,2,2 } 
			};

int oneColorList[][3] = {	{ 0,0,1 }, { 0,1,1 }, { 1,1,1 }
			};

 
void calculateIntroAndOutroducer(History);
void calculate(History);
void calculateNumberOfColors(History);
void calculateIf4MaxPins(History);
void calculateIfAllPinsAreWhite(History);



void calculateIfAllPinsAreWhite(History *hs){
	for(int i=0; i <= historypointer; i++){
		int count = 0;
		for(int k=0; k<4; k++){
			if(hs[i].pins[k] == black){
				count = 0;
			} else if(hs[i].pins[k] == white) {
				count++;
			}
		}
		if(count != 0){
			for(int l=0; l<4; l++){
				for(int m = 0; m<5; m++){
					if(hs[i].code[l] == a){
						addNewPosToShouldNotOnPos(ColorAShouldNotOnPos, l);
					}
					if(hs[i].code[l] == b){
						addNewPosToShouldNotOnPos(ColorBShouldNotOnPos, l); 
					}
					if(hs[i].code[l] == c){
						addNewPosToShouldNotOnPos(ColorCShouldNotOnPos, l);
					}
					if(hs[i].code[l] == d){
						addNewPosToShouldNotOnPos(ColorDShouldNotOnPos, l);
					}	
					if(hs[i].code[l] == e){
						addNewPosToShouldNotOnPos(ColorEShouldNotOnPos, l);
					}
					if(hs[i].code[l] == f){
						addNewPosToShouldNotOnPos(ColorFShouldNotOnPos, l);
					}
				} 
			}

		}

	}
}

void calculateIntroAndOutroducer(History *hs){
	for(int i=0; i < 2; i++){
		if((countWhitePins(hs, i) + countBlackPins(hs, i)) > (countWhitePins(hs, (i+1)) + countBlackPins(hs, (i+1)))) {
			for(int k=0; k<4; k++){
				if(ColorsCertainlyInCode[k] == empty){
					ColorsCertainlyInCode[k] = hs[i].code[0];
					break;
				}
			}	
		} else if((countWhitePins(hs, i) + countBlackPins(hs, i)) < countWhitePins(hs, (i+1)) + countBlackPins(hs, (i+1))){
			for(int k=0; k<4; k++){
				if(ColorsCertainlyInCode[k] == empty){
					ColorsCertainlyInCode[k] = hs[i+1].code[3];
					break;
				}	
			}
			for(int k=0; k<5; k++){
				if(ColorsCertainlyNotInCode[k] == empty){
					ColorsCertainlyNotInCode[k] = hs[i].code[0];
					break;
				}	
			}
			
		}

	}
}


void calculateIf4MaxPins(History *hs){
	for(int i=0; i<=historypointer; i++){
		int count=0;
		for(int k=0; k<4; k++){
			if(m_history[i].pins[k] != none){
				count++;
			}
		}
		if(count == 4 && ShouldNotNumberOfColors[0] != 4){
			ColorsCertainlyInCode[0] = m_history[i].code[0];
			ColorsCertainlyInCode[1] = m_history[i].code[1];
			ColorsCertainlyInCode[2] = m_history[i].code[2];
			ColorsCertainlyInCode[3] = m_history[i].code[3];
			return;			
		}
	}
}
	
void calculateNumberOfColors(History *hs){
	int code1= 0, code2= 0, code3=0;
	for(int i=0; i<4; i++){
		if(m_history[0].pins[i] != none){
			code1++;
		}
		if(m_history[1].pins[i] != none){
			code2++;
		}
		if(m_history[2].pins[i] != none){
			code3++;
		}
	}
	bool isIn = false;
	for(int i= 0; i<10; i++){
		if(code1 == fourColorList[i][0] && code2 == fourColorList[i][1] &&
		   code3 == fourColorList[i][2] ){
			isIn = true;
		}
	}	
	if(!isIn){
		ShouldNotNumberOfColors[0] = 4;
	}
	isIn = false;
	for(int i=0; i<11; i++){
		if(code1 == threeColorList[i][0] && code2 == threeColorList[i][1] &&
		   code3 == threeColorList[i][2] ){
			isIn = true;
		}
	}
	if(!isIn){
		ShouldNotNumberOfColors[1] = 3;
	}
	isIn = false;
	for(int i=0; i<8; i++){
		if(code1 == twoColorList[i][0] && code2 == twoColorList[i][1] &&
		   code3 == twoColorList[i][2] ){
			isIn = true;
		}
	}
	if(!isIn){
		ShouldNotNumberOfColors[2] = 2;
	}
	isIn = false;
	for(int i=0; i<3; i++){
		if(code1 == oneColorList[i][0] && code2 == oneColorList[i][1] &&
		   code3 == oneColorList[i][2] ){
			isIn = true;
		}
	}
	if(!isIn){
		ShouldNotNumberOfColors[3] = 1;
	}
}




void calculate(History *hs){
//	calculateNumberOfColors(hs);
//	calculateIf4MaxPins(hs);
//	calculateIntroAndOutroducer(hs);
//	calculateIfAllPinsAreWhite(hs);
}
