//QuickSort
//p i-->   <--j
//0 9 4 8 2 5 1
void quicksort(char *word, int front, int back){
	if(back <= front){
		return;
	}
	char pivot = word[front];
	int mid = front;
	int f = front + 1 - 1;
	int b = back + 1;
	while(f < b){
		while(b >= front + 1){
			b--;
			if(word[b] <= pivot){
				break;
			}
		}
		while(f <= back){
			f++;
			if(word[f] >= pivot){
				break;
			}
		}
		if(f < b){
			char temp = word[f];
			word[f] = word[b];
			word[b] = temp;
		}
		if(f >= b){
			if(word[b] <= pivot){
				mid = b;
				char temp = word[b];
				word[b] = word[front];
				word[front] = temp;
				break;
			}
		}
		
	}
	quicksort(word, front, mid - 1);
	
	quicksort(word, mid + 1, back);
}



bool isAnagram(char * s, char * t){
    
    int length;
    
    int s_l = 0;
	while(s[s_l] != '\0'){
		s_l++;
	}
	int t_l = 0;
	while(t[t_l] != '\0'){
		t_l++;
	}
    
    if(s_l == t_l){
        length = t_l;
    }else{
        return false;
    }
	
	quicksort(s, 0, s_l - 1);
	quicksort(t, 0, t_l - 1);
    
    
    
    bool flag = true;
    for(int i = 0; i < length; i++){
        if(s[i] != t[i]){
            flag = false;
        }
    }
    
    return flag;
}
