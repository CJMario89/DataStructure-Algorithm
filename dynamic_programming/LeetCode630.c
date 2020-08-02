//sort by deadline
//maxheap record the largest numbers
//if a new course can be fitted in, then fitted in.
//if it can not be fitted in, then comparing with the largest number, which total time is bigger
//course number > total time (priority)

struct heap{
    int *arr;
    int tail;
    //index
    //    0
    //  1   2
    // 3 4 5 6(tail)
};

void Heapify(struct heap* H, int index){
    int temp = 0;
    if((index * 2) + 1 > H->tail){
        return;
    }else if((index * 2) + 1 == H->tail){
        if(H->arr[(index * 2) + 1] > H->arr[index]){
            temp = H->arr[(index * 2) + 1];
            H->arr[(index * 2) + 1] = H->arr[index];
            H->arr[index] = temp;
        }
        return;
    }
    if(H->arr[(index * 2) + 1] > H->arr[(index * 2) + 2]){
        if(H->arr[(index * 2) + 1] > H->arr[index]){
            temp = H->arr[(index * 2) + 1];
            H->arr[(index * 2) + 1] = H->arr[index];
            H->arr[index] = temp;
            Heapify(H, (index * 2) + 1);
        }
    }else{
        if(H->arr[(index * 2) + 2] > H->arr[index]){
            temp = H->arr[(index * 2) + 2];
            H->arr[(index * 2) + 2] = H->arr[index];
            H->arr[index] = temp;
            Heapify(H, (index * 2) + 2);
        }
    }
    
    return;
}

void Heap_insert(struct heap *H, int val){
    H->arr[++H->tail] = val;
    int index = H->tail;
    int temp = 0;
    int flag = 1;
    while(index != 0){
        flag = 1;
        if(H->arr[index] > H->arr[(index - 1) / 2]){
            temp = H->arr[index];
            H->arr[index] = H->arr[(index - 1) / 2];
            H->arr[(index - 1) / 2] = temp;
            flag = 0;
            index = (index - 1) / 2;
        }
        if(flag){
            break;
        }
    }
    
    return;
}

void quickSort(int** courses, int first, int last){
    // i j 0 1 2 3 4 p
    //     4 0 1 5 9 2
    if(last <= first){
        return;
    }
    int pivot = last;
    int i = first - 1;
    int j = first - 1;
    int temp = 0;
    while(j + 1 != pivot){
        if(courses[++j][1] < courses[pivot][1]){
            temp = courses[j][1];
            courses[j][1] = courses[++i][1];
            courses[i][1] = temp;
            
            temp = courses[j][0];
            courses[j][0] = courses[i][0];
            courses[i][0] = temp;
        }
    }
    temp = courses[pivot][1];
    courses[pivot][1] = courses[i + 1][1];
    courses[i + 1][1] = temp;
    
    temp = courses[pivot][0];
    courses[pivot][0] = courses[i + 1][0];
    courses[i + 1][0] = temp;
    quickSort(courses, first, i);
    quickSort(courses, i + 2, last);
    return;
}

int scheduleCourse(int** courses, int coursesSize, int* coursesColSize){
    //sort by deadline
    quickSort(courses, 0, coursesSize - 1);
    
    
    struct heap *maxHeap = (struct heap*)malloc(sizeof(struct heap));
    maxHeap->arr = (int*)malloc(coursesSize * sizeof(int));
    maxHeap->tail = -1;
    for(int i = 0; i < coursesSize; i++){
        maxHeap->arr[i] = 0;
    }
    
    int totalTime = 0;
    int coursesNum = 0;
    
    for(int i = 0; i < coursesSize; i++){
        totalTime += courses[i][0];
        if(totalTime <= courses[i][1]){
            coursesNum++;
            Heap_insert(maxHeap, courses[i][0]);
        }else{
            if(maxHeap->arr[0] > courses[i][0]){
                totalTime -= maxHeap->arr[0];
                maxHeap->arr[0] = maxHeap->arr[maxHeap->tail--];
                Heapify(maxHeap, 0);
                Heap_insert(maxHeap, courses[i][0]);
            }else{
                totalTime -= courses[i][0];
            }
        }
    }
    return coursesNum;
}
