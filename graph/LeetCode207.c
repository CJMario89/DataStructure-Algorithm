//last->first traversal
//reverse

struct Node{
    int val;
    int color; // traver or not :: 0 : white, 1 : gray, 2 : black;
    int numNext;
    struct Node** Next;//arr
    //struct Node* head;//for free()
};

struct stack{
    int top;
    int size;
    struct Node** arr;
};

bool DFS(struct Node* N, int numCourses){
    struct stack* S = (struct stack*)malloc(sizeof(struct stack));
    S->top = -1;
    S->size = numCourses;
    S->arr = (struct Node**)malloc(S->size * sizeof(struct Node*));
    S->arr[++S->top] = N;
    struct Node* Cur;
    bool finished = true;
    
    while(S->top != -1){
        Cur = S->arr[S->top];
        Cur->color = 1;
        finished = true;
        for(int i = 0; i < Cur->numNext; i++){
            if(finished == false){
                break;
            }
            if(Cur->Next[i]->color == 0){
                finished = false;
                
                S->arr[++S->top] = Cur->Next[i];
                Cur->Next[i]->color = 1;
                
            }else if(Cur->Next[i]->color == 1){
                
                return false;
            }
        }
        if(finished){
            Cur->color = 2;
            S->top--;
        }
        
    }
    return true;
}


bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize){
    
    struct Node** Courses = (struct Node**)malloc(numCourses * sizeof(struct Node*));
    for(int i = 0; i < numCourses; i++){
        Courses[i] = NULL;
    }
        
    for(int i = 0; i < prerequisitesSize; i++){
        int original = 0;
        if(Courses[prerequisites[i][0]] == NULL){
            Courses[prerequisites[i][0]] = (struct Node*)malloc(sizeof(struct Node));
            Courses[prerequisites[i][0]]->val = prerequisites[i][0];
            Courses[prerequisites[i][0]]->color = 0;
            Courses[prerequisites[i][0]]->Next = NULL;
        }
        if(Courses[prerequisites[i][0]]->Next == NULL){
            Courses[prerequisites[i][0]]->numNext = prerequisitesColSize[i] - 1;
            Courses[prerequisites[i][0]]->Next = (struct Node**)malloc((prerequisitesColSize[i] - 1) * sizeof(struct Node*));
        }else{
            original = Courses[prerequisites[i][0]]->numNext;
            Courses[prerequisites[i][0]]->numNext += prerequisitesColSize[i] - 1;
            Courses[prerequisites[i][0]]->Next = (struct Node**)realloc(Courses[prerequisites[i][0]]->Next, Courses[prerequisites[i][0]]->numNext * sizeof(struct Node*));
        }
        
        
        for(int j = 0; j < Courses[prerequisites[i][0]]->numNext - original; j++){
            
            if(Courses[prerequisites[i][j + 1]] == NULL){
                Courses[prerequisites[i][j + 1]] = (struct Node*)malloc(sizeof(struct Node));
                Courses[prerequisites[i][j + 1]]->val = prerequisites[i][j + 1];
                Courses[prerequisites[i][j + 1]]->color = 0;
                Courses[prerequisites[i][j + 1]]->numNext = 0;
                Courses[prerequisites[i][j + 1]]->Next = NULL;
                Courses[prerequisites[i][0]]->Next[j + original] = Courses[prerequisites[i][j + 1]];
            }else{
                Courses[prerequisites[i][0]]->Next[j + original] = Courses[prerequisites[i][j + 1]];
            }
        }
    }
    
    bool result = true;
    
    for(int i = 0; i < numCourses; i++){
        if(Courses[i] != NULL){
            if(Courses[i]->color == 0){
                 result = DFS(Courses[i], numCourses);
                if(!result){
                    return result;
                }
            }
        }
    }
    return result;
}

