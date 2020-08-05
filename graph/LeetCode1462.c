

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct Node{
    int val;
    int numNext;
    struct Node** NextNodes;
};

struct queue{
    int head;
    int tail;
    int size;
    struct Node** arr;
};

void initialNode(struct Node* N, int val, int numNext){
    N->val = val;
    N->numNext = numNext;
    N->NextNodes = NULL;
    return;
}

bool BFS(struct Node** Mark, int start, int target, int n){
    struct queue *Q = (struct queue*)malloc(sizeof(struct queue));
    Q->head = -1;
    Q->tail = -1;
    Q->size = n;
    Q->arr = (struct Node**)malloc(Q->size * sizeof(struct Node*));
    int* mark = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        Q->arr[i] = NULL;
        mark[i] = 0;
    }
    Q->arr[++Q->tail] = Mark[start];
    
    struct Node* Cur;
    while(Q->head != Q->tail){
        
        Cur = Q->arr[++Q->head];
        
        if(Cur->val == target){
            return true;
        }
        
        for(int i = 0; i < Cur->numNext; i++){
            if(mark[Cur->NextNodes[i]->val] == 0){
                Q->arr[++Q->tail] = Cur->NextNodes[i];
                mark[Cur->NextNodes[i]->val] = 1;
            }
        }
        
    }
    
    return false;
}

bool* checkIfPrerequisite(int n, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize){
    *returnSize = queriesSize;
    
    bool* result = (bool*)malloc(queriesSize * sizeof(bool));
    for(int i = 0 ; i < queriesSize; i++){
        result[i] = false;
    }
    
    if(prerequisitesSize == 0){
        return result;
    }
    
    struct Node** Mark = (struct Node**)malloc(n * sizeof(struct Node*));
    for(int i = 0; i < n; i++){
        Mark[i] = NULL;
    }
    
    
    for(int i = 0; i < prerequisitesSize; i++){
        if(Mark[prerequisites[i][0]] == NULL){
            Mark[prerequisites[i][0]] = (struct Node*)malloc(sizeof(struct Node));
            initialNode(Mark[prerequisites[i][0]], prerequisites[i][0], 1);
            Mark[prerequisites[i][0]]->NextNodes = (struct Node**)malloc(sizeof(struct Node*));
            
            if(Mark[prerequisites[i][1]] == NULL){
                Mark[prerequisites[i][1]] = (struct Node*)malloc(sizeof(struct Node));
                initialNode(Mark[prerequisites[i][1]], prerequisites[i][1], 0);
                Mark[prerequisites[i][0]]->NextNodes[0] = Mark[prerequisites[i][1]];
            }else{
                Mark[prerequisites[i][0]]->NextNodes[0] = Mark[prerequisites[i][1]];
            }
        }else{
            Mark[prerequisites[i][0]]->numNext++;
            if(Mark[prerequisites[i][0]]->NextNodes == NULL){
                Mark[prerequisites[i][0]]->NextNodes = (struct Node**)malloc(Mark[prerequisites[i][0]]->numNext * sizeof(struct Node*));
            }else{
                Mark[prerequisites[i][0]]->NextNodes = (struct Node**)realloc(Mark[prerequisites[i][0]]->NextNodes, Mark[prerequisites[i][0]]->numNext * sizeof(struct Node*));
            }
            
            if(Mark[prerequisites[i][1]] == NULL){
                Mark[prerequisites[i][1]] = (struct Node*)malloc(sizeof(struct Node));
                initialNode(Mark[prerequisites[i][1]], prerequisites[i][1], 0);
                Mark[prerequisites[i][0]]->NextNodes[Mark[prerequisites[i][0]]->numNext - 1] = Mark[prerequisites[i][1]];
            }else{
                Mark[prerequisites[i][0]]->NextNodes[Mark[prerequisites[i][0]]->numNext - 1] = Mark[prerequisites[i][1]];
            }
        }
    }
    
    //queries may be larger than n
    bool R = true;
    
    for(int i = 0; i < queriesSize; i++){
        R = BFS(Mark, queries[i][0], queries[i][1], n);
        result[i] = R;
    }
    
    return result;
}
