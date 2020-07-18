struct queue{
    int head;
    int tail;
    int* arr; 
};


bool isBipartite(int** graph, int graphSize, int* graphColSize){
    //situation 0:haven't been 1:odd 2:even
    int *situation = (int*)malloc(graphSize * sizeof(int));
    
    struct queue *Q = (struct queue*)malloc(sizeof(struct queue));
    Q->head = 0;
    Q->tail = 0;
    Q->arr = (int*)malloc(graphSize * sizeof(int));
    for(int i = 0; i < graphSize; i++){
        situation[i] = 0;
        Q->arr[i] = 0;
    }
    //BFS check
    int current = 0;
    int S = 1;
    for(int i = 0; i < graphSize; i++){
        if(situation[i] == 0){
            S = 1;
            Q->arr[Q->tail++] = i;
            situation[i] = S;
            while(Q->tail != Q->head){
                current = Q->arr[Q->head++];
                S = situation[current];
                for(int j = 0; j < graphColSize[current]; j++){
                    if(situation[graph[current][j]] == 0){
                        Q->arr[Q->tail++] = graph[current][j];
                        if(S == 1){
                            situation[graph[current][j]] = 2;
                        }else{
                            situation[graph[current][j]] = 1;
                        }
                    }else{
                        if(situation[graph[current][j]] == S){
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}
