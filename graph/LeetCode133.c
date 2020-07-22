/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numNeighbors;
 *     struct Node** neighbors;
 * };
 */


struct queue{
    int head;
    int tail;
    struct Node** arr;
};

struct Node *cloneGraph(struct Node *s) {
    if(s == NULL){
        return NULL;
    }
    
    //BFS traversal
    
    //s queue
    struct queue *Q = (struct queue*)malloc(sizeof(struct queue));
    Q->head = -1;
    Q->tail = -1;
    Q->arr = (struct Node**)malloc(101 * sizeof(struct Node*));
    
    //result queue
    struct queue *QR = (struct queue*)malloc(sizeof(struct queue));
    QR->head = -1;
    QR->tail = -1;
    QR->arr = (struct Node**)malloc(101 * sizeof(struct Node*));
    
    
   
    struct Node **Mark = (struct Node**)malloc(101 * sizeof(struct Node*));//which node has been reached
    for(int i = 0; i < 101; i++){
        Mark[i] = NULL;
        Q->arr[i] = NULL;
        QR->arr[i] = NULL;
    }
    
     //result clone
    struct Node *R = (struct Node*)malloc(sizeof(struct Node));
    struct Node *result = R;
    QR->arr[++QR->tail] = R;
    
    //add first node
    Q->arr[++Q->tail] = s;
    Mark[s->val] = R;
    
    R->val = s->val;
    R->numNeighbors = s->numNeighbors;
    
    while(Q->head < Q->tail){
        QR->head++;
        Q->head++;

        QR->arr[QR->head]->neighbors = (struct Node**)malloc(QR->arr[QR->head]->numNeighbors * sizeof(struct Node*));
        
        for(int i = 0; i < QR->arr[QR->head]->numNeighbors; i++){
            if(Mark[Q->arr[Q->head]->neighbors[i]->val] == NULL){
                QR->arr[QR->head]->neighbors[i] = (struct Node*)malloc(sizeof(struct Node));
                QR->arr[QR->head]->neighbors[i]->val = Q->arr[Q->head]->neighbors[i]->val;
                QR->arr[QR->head]->neighbors[i]->numNeighbors = Q->arr[Q->head]->neighbors[i]->numNeighbors;
                QR->arr[QR->head]->neighbors[i]->neighbors = NULL;
                
                QR->arr[++QR->tail] = QR->arr[QR->head]->neighbors[i];
                Q->arr[++Q->tail] = Q->arr[Q->head]->neighbors[i];
                Mark[Q->arr[Q->head]->neighbors[i]->val] = QR->arr[QR->head]->neighbors[i];
            }else{
                QR->arr[QR->head]->neighbors[i] = Mark[Q->arr[Q->head]->neighbors[i]->val];
            }
        }
    }
    return result;
}
