

int repeatedStringMatch(char * A, char * B){
    
    int a = 0;//A.length
    while(A[a] != '\0'){
        a++;
    }
    
    
    int b = 0;// B.length
    while(B[b] != '\0'){
        b++;
    }
    
    //failure function // a space of zero, easy to compute
    int *Pi = (int*)malloc((b * sizeof(int)));
    // 0 1 2 3 4 5
    // a a a a b a
    //-1 0 1 2-1 0
    Pi[0] = -1;         
    int Val = -1;
    for(int i = 1; i < b; i++){
        while(B[i] != B[Val + 1] && Val > -1){
            Val = Pi[Val];
        }
        if(B[i] == B[Val + 1]){
            Val = Val + 1;
        }
        Pi[i] = Val;
    }
    
    //repeat times
    int times = 0;
    int text_L = 0;
    if(b > a){
        if(b % a == 0){
            times = b / a;
        }else{
            times = (b / a) + 1;
        }
    }else{
        times = 1;
    }
    
    text_L = times * a;
    
    //repeat the string
    char *text = (char*)malloc(text_L * sizeof(char));
    for(int i = 0; i < text_L; i++){
        text[i] = A[i % a];
    }
    
    int BCur = -1;
    int match = 0;
    int i = 0;
    while (i < text_L){ 
        if(B[BCur + 1] == text[i]){ 
            BCur++; 
            i++; 
        }
        if(BCur == b - 1){ 
            match = 1;
            break; 
        }
  
        if(i < text_L && B[BCur + 1] != text[i]){ 
            if(BCur != -1){
                BCur = Pi[BCur];
            }else{
                i++;
            }
        } 
    } 
    if(match){
        return times;
    }
    
    //repeat more once
    
    times += 1;
    text_L = times * a;
    text = (char*)realloc(text, text_L * sizeof(char));
    for(int i = (times - 1) * a; i < text_L; i++){
        text[i] = A[i % a];
    }
    
    i = 0;
    BCur = -1;
    while(i < text_L){
        if(B[BCur + 1] == text[i]){
            BCur++;
            i++;
        }
        if(BCur == b - 1){
            match = -1;
            break;
        }
        if(i < text_L && B[BCur + 1] != text[i]){
            if(BCur != -1){
                BCur = Pi[BCur];
            }else{
                i++;
            }
        }
    }
    
    if(match){
        return times;
    }
    
    return -1;
}
