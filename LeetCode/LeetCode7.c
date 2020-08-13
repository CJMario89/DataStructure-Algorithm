int reverse(int x) {
    int sign = 1;
    
    int P_limit = 2;
    for(int i = 0; i < 30; i++){
        if(i != 29){
            P_limit *= 2;
        }else{
            int temp = P_limit - 1;
            P_limit += temp;
        }
    }
    
    if(x < 0){
        sign = 0;
        int y = x;
        x -= y;// negative to 0
        if(y <= -P_limit){
            return 0;
        }
        x -= y;// 0 to positive
    }
    
    int result = 0;
    int i = 0;
    while(x > 0){
        if(i > 7){
            if(sign){
                if(result > P_limit / 10){
                    return 0;
                }
            }else{
                if(result > P_limit / 10){
                    return 0;
                }
            }
        }
        if(i != 0){
            result *= 10;
        }
        
        if(i > 7){
            if(sign){
                if(result > P_limit - (x % 10)){
                    return 0;
                }
            }else{
                if(x % 10 != 0){
                    if(result > P_limit - (x % 10) + 1){
                        return 0;
                    }
                }
            }
        }
        
        result += x % 10;
        x /= 10;
        i++;
    }
    
    if(!sign){
        int y = result;
        result -= y;
        result -= y;
    }
    return result;
}
