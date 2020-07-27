

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

//last->first traversal
//reverse

struct Node{
    int val;
    int color; // traver or not :: 0 : white, 1 : gray, 2 : black;
    int numNext;
    struct Node** Next;//arr (1->0)1 next has 0, must take 0 first then 1// last->first
    //struct Node* head;//for free()
    
    int numLast;
    struct Node** Last;//arr inverse of Next
};


struct queue{
    int head;
    int tail;
    int size;
    struct Node** arr;
};


int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize){
    
    *returnSize = numCourses;
    
        
    int* result = (int*)malloc(numCourses * sizeof(int));
    for(int i = 0; i < numCourses; i++){
        result[i] = i;//any ordering at first
    }
    
    int *mark = (int*)malloc(numCourses * sizeof(int));
    for(int i = 0; i < numCourses; i++){
        mark[i] = 0;//mark the courses have been recorded
    }
    
    if(prerequisitesSize == 0){
        return result;//no ordering just return normal sequence
    }
    
    struct Node** Courses = (struct Node**)malloc(numCourses * sizeof(struct Node*));
    for(int i = 0; i < numCourses; i++){
        Courses[i] = NULL;
    }
        
    
    //create graph
    for(int i = 0; i < prerequisitesSize; i++){
        int original = 0;
        if(Courses[prerequisites[i][0]] == NULL){
            Courses[prerequisites[i][0]] = (struct Node*)malloc(sizeof(struct Node));
            Courses[prerequisites[i][0]]->val = prerequisites[i][0];
            Courses[prerequisites[i][0]]->color = 0;
            Courses[prerequisites[i][0]]->Next = NULL;
            Courses[prerequisites[i][0]]->Last = NULL;
            Courses[prerequisites[i][0]]->numLast = 0;
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
                Courses[prerequisites[i][j + 1]]->numLast = 1;
                Courses[prerequisites[i][j + 1]]->Last = (struct Node**)malloc(sizeof(struct Node*));
                Courses[prerequisites[i][j + 1]]->Last[0] = Courses[prerequisites[i][0]];
                Courses[prerequisites[i][0]]->Next[j + original] = Courses[prerequisites[i][j + 1]];
            }else{
                Courses[prerequisites[i][0]]->Next[j + original] = Courses[prerequisites[i][j + 1]];
                if(Courses[prerequisites[i][j + 1]]->Last == NULL){
                    Courses[prerequisites[i][j + 1]]->numLast = 1;
                    Courses[prerequisites[i][j + 1]]->Last = (struct Node**)malloc(sizeof(struct Node*));
                    Courses[prerequisites[i][j + 1]]->Last[0] = Courses[prerequisites[i][0]];
                }else{
                    Courses[prerequisites[i][j + 1]]->numLast += 1;
                    Courses[prerequisites[i][j + 1]]->Last = (struct Node**)realloc(Courses[prerequisites[i][j + 1]]->Last, Courses[prerequisites[i][j + 1]]->numLast * sizeof(struct Node*));
                    Courses[prerequisites[i][j + 1]]->Last[Courses[prerequisites[i][j + 1]]->numLast - 1] = Courses[prerequisites[i][0]];
                }
            }
        }
    }
    
    //rebuild the ordering
    int Count = 0;
    struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    q->head = -1;
    q->tail = -1;
    q->size = numCourses;
    q->arr = (struct Node**)malloc(q->size * sizeof(struct Node*));
    for(int i = 0; i < q->size; i++){
        q->arr[i] = 0;
    }
    
    struct Node* Cur;
    while(Count < numCourses){
        //find the last
        int check = 0;
        if(q->head == q->tail){
            for(int i = 0; i < numCourses; i++){
                if(Courses[i] != NULL){
                    check = 1;
                    if(Courses[i]->numNext == 0){
                        q->arr[++q->tail] = Courses[i];
                        break;
                    }
                }
                if(i == numCourses - 1){
                    if(check){//there is no way
                        *returnSize = 0;
                        return NULL;
                    }else{//remains can be any ordering
                        for(int j = 0; j < numCourses; j++){
                            if(mark[j] == 0){
                                result[Count++] = j;
                                mark[j] = 1;
                            }
                        }
                        return result;
                    }
                }
            }
        }
        
        Cur = q->arr[++q->head];
        mark[Cur->val] = 1;
        result[Count++] = Cur->val;
        for(int i = 0; i < Cur->numLast; i++){
            Cur->Last[i]->numNext--;
            if(Cur->Last[i]->numNext == 0){
                q->arr[++q->tail] = Cur->Last[i];
            }
        }
        Courses[Cur->val] = NULL;
    }
    
    
    return result;
}
