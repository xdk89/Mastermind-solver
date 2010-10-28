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
	int whitePins= 0; int blackPins=0;
	int white, black;

/*	for(int i=0; i <= historypointer; i++){
		whitePins = countWhitePins(hs,i);
		blackPins = countBlackPins(hs,i);
		white = 0;
		black = 0;
	
		Code bckCode;
		bckCode[0] = hs[i].code[0];
		bckCode[1] = hs[i].code[1];
		bckCode[2] = hs[i].code[2];
		bckCode[3] = hs[i].code[3];
	
		Code bckCode2;
		bckCode2[0] = cd[0];
		bckCode2[1] = cd[1];
		bckCode2[2] = cd[2];
		bckCode2[3] = cd[3];
	
		for(int k=0; k<4; k++){
			if(bckCode[k] == bckCode2[k]){
				black++;
				bckCode2[k] = empty;	
				bckCode[k] = empty;
			}
		}
		for(int l=0; l<4; l++){
			if(bckCode[l] == bckCode2[0] && bckCode[l] != empty){
				white++;	
				bckCode2[0] = empty;
				bckCode[l] = empty;
			} else if(bckCode[l] == bckCode2[1] && bckCode[l] != empty){
				white++;
				bckCode2[1] = empty;
				bckCode[l] = empty;
			} else if(bckCode[l] == bckCode2[2] && bckCode[l] != empty){
				white++;
				bckCode2[2] = empty;
				bckCode[l] = empty;
			} else if(bckCode[l] == bckCode2[3] && bckCode[l] != empty){
				white++;
				bckCode2[3] = empty;
				bckCode[l] = empty;
			}	
		}
		if(white != whitePins || black != blackPins){
			return false;
		}
	}*/



	for(int i=0 ; i<=historypointer; i++){
		bool codeCan[4] = { true, true, true, true };
		bool  hisCan[4] = { true, true, true, true };
		whitePins = countWhitePins(hs,i);
		blackPins = countBlackPins(hs,i);
		white=0; black=0;
		for(int k=0; k<4; k++){
			if(cd[k] == hs[i].code[k]){
				black++;
				codeCan[k] = false;
				hisCan[k]  = false;
			}
		}
		for(int k=0; k<4; k++){
//			if(codeCan[k] == true){
				for(int l=0; l<4; l++){
					if(cd[k] == hs[i].code[l] && hisCan[l] == true && codeCan[k] == true){
						white++;
						hisCan[l] = false;
					}
				}
//			}

		} 
		if(white != whitePins || black != blackPins){
			return false;
		}
	}		
	return true;
}
