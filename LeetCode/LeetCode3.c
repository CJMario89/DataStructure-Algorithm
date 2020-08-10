

int lengthOfLongestSubstring(char * s){
    if(s[0] == ' '){
        return 1;
    }
    printf("%s", s);
    
    int s_length = strlen(s);
    
    
    int *hashTable = (int*)malloc(128 * sizeof(int));
    for(int i = 0; i < 128; i++){
        hashTable[i] = -1;
    }

    int val = 0;
    int count = 0;
    int Max = 0;
    int position = 0;
    
    int i = 0;
    position = 0;
    while(i < s_length){
        val = s[i];
        if(hashTable[val] == -1){
            hashTable[val] = i;
            count++;
            i++;
        }else{
            count -= (hashTable[val] + 1 - position);
            position = hashTable[val] + 1;
            for(int j = 0; j < 128; j++){
                if(hashTable[j] < position){
                    hashTable[j] = -1;
                }
            }
        }
        if(count > Max){
            Max = count;
        }
    }
    
    return Max;
}
