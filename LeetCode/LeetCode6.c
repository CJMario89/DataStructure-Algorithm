

char * convert(char * s, int numRows){
    int s_length = strlen(s);
    int numSet = (numRows * 2) - 2;
    
    char *result = (char*)malloc((s_length + 1) * sizeof(char));
    if(numRows == 1){
        return s;
    }
    
    int j = 0;
    int k = 0;
    int r = 0;
    for(int i = 0; i < numRows; i++){
        if(i != 0 && i != numRows - 1){
            j = i;
            k = numSet - i;
            while(j < s_length){
                result[r++] = s[j];
                
                if(k >= s_length){
                    break;
                }
                result[r++] = s[k];
                j += numSet;
                k += numSet;
            }
        }else{
            j = i;
            while(j < s_length){
                result[r++] = s[j];
                j += numSet;
            }
        }
    }
    result[r] = '\0';
    return result;
}
