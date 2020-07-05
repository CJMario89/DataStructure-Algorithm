

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** stringMatching(char ** words, int wordsSize, int* returnSize){
    
    char **MatchedString = (char**)malloc(wordsSize * sizeof(char*));//return
    
    int *Wsize = (int*)malloc(wordsSize * sizeof(int));// size of each word
    
    int *Matched = (int*)malloc(wordsSize * sizeof(int));// whether the word is matched
    
    (*returnSize) = 0;
    Matched[0] = 0;
    Wsize[0] = 0;
    int j = 0;
    int count = 0;
    while(words[0][j] != '\0'){
        count++;
        j++;
    }
    Wsize[0] = count;
    for(int i = 1; i < wordsSize; i++){
        
        Matched[i] = 0;
        
        //count current i Word length
        j = 0;
        count = 0;
        while(words[i][j] != '\0'){
            count++;
            j++;
        }
        Wsize[i] = count;
        
        
        //figure out which is bigger
        int s;
        int l;
        char *S;
        char *L;
        int M;
        
        for(int k = 0; k < i; k++){
            if(Wsize[k] <= Wsize[i]){
                S = words[k];
                L = words[i];
                s = Wsize[k];
                l = Wsize[i];
                M = k;
            }else{
                S = words[i];
                L = words[k];
                s = Wsize[i];
                l = Wsize[k];
                M = i;
            }
            if(Matched[M] == 0){
            	
            	//failure function
            	//   a b a b a
            	//-1-1-1 0 1 2
           		int *failure = (int*)malloc((Wsize[M] + 1) * sizeof(int));
            	int acu = -1;
            	failure[0] = acu;
            	failure[1] = acu;
            	int Cur = 0;
            	for(int n = 1; n < Wsize[M]; n++){
            		if(S[n] == S[Cur]){
            			Cur++;
            			acu++;
					}else{
						Cur = 0;
						if(S[n] == S[Cur]){
							acu = 0;
						}else{
							acu = -1;
						}
					}
					failure[n + 1] = acu;
				}
           	 
           		//matching
           		int Match = 0;
           		int m = 0;
           		int Cur_Pos;
           		for(int n = 0; n < l - s + 1; n++){
           		    m = 0;
           		    while(S[m] == L[n] && m < Wsize[M]){
           		    	m++;
           		    	n++;
           		    	
           		    	if(S[m] != L[n]){
           		    		m = failure[m] + 1;
						}
           		    	
           		    	if(m == Wsize[M] - 1){
           		    		Match = 1;
						}
					}
          		}
           	 	if(Match){
          	   	  	Matched[M] = 1;
          	   		MatchedString[(*returnSize)] = (char*)malloc((s + 1) * sizeof(char));
               		for(int m = 0; m < s; m++){
       	        	   	MatchedString[(*returnSize)][m] = S[m];
           	    	}
           	       	MatchedString[(*returnSize)][s] = '\0';
           	   		(*returnSize)++; 
           	   	}
			}
        }
    }
    free(Matched);
    free(Wsize);
    return MatchedString;
}
