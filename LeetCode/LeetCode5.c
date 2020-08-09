char * longestPalindrome(char * s){
    //Manacher's algorithm
    
    int s_length = strlen(s);
    int R_length = s_length * 2 + 1;
    
    
    //int* Radius = (int*)malloc(R_length * sizeof(int));
    char* newS = (char*)malloc(R_length * sizeof(char));
    
    int j = 0;
    for(int i = 0; i < R_length; i++){
        //Radius[i] = 0;
        newS[i] = '#';
        if(i % 2 == 1){
            newS[i] = s[j];
            j++;
        }
    }
    
    int Max = 0;
    int position = 0;
    int offset = 0;
    int count = 0;
    int b = 0;
    int f = 0;
    for(int i = 0; i < R_length; i++){
        b = i - 1;
        f = i + 1;
        count = 0;
        while(b >= 0 && f < R_length){
            if(newS[b] == newS[f]){
                count++;
            }else{
                break;
            }
            b--;
            f++;
        }
        
        if(count > Max){
            
            Max = count;
            position = b + 1;
            offset = (f - 1) - position;
        }
    }
    

    
    char* result = (char*)malloc((((offset + 1) / 2) + 1) * sizeof(char));
    
    j = 0;
    for(int i = position; i <= position + offset; i++){
        if(i % 2 == 1){
            result[j] = newS[i];
            j++;
        }
    }
    result[j] = '\0';
    
    return result;
}
