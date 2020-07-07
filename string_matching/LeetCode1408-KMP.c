

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
                // 0 1 2 3 4 5
            	// a b a b a c
            	//-1-1 0 1 2-1
           		int *failure = (int*)malloc((Wsize[M]) * sizeof(int));
            	failure[0] = -1;
                int acu = -1;
            	for(int n = 1; n < Wsize[M]; n++){
            		while(acu > -1 && S[n] != S[acu + 1]){
                        acu = failure[acu];
                    }
                    if(S[n] == S[acu + 1]){
                        acu = acu + 1;
                    }
                    failure[n] = acu;
				}
           	 
           		//matching
           		int Match = 0;
           		int m = -1;
                int n = 0;
           		while(n < l){
                    if(L[n] == S[m + 1]){
                        m++;
                        n++;
                    }
                    if(m == s - 1){
                        Match = 1;
                            break;
                    }
                    if(L[n] != S[m + 1] && n < l){
                        if(m != -1)
                            m = failure[m];
                        else
                            n++;
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
