struct set{
	int value;
	int key;
	struct set *next;
};





int* twoSum(int* nums, int numsSize, int target, int* returnSize){
	int *TN = (int*)malloc(2 * sizeof(int));
	TN[0] = 0;
	TN[1] = 0;
	struct set *head = (struct set*)malloc(sizeof(*head));
	head->value = 0;
	head->key = -1;
	head->next = NULL;
	struct set *current = head;
	int match = 0;
	
	
    for(int i = 0; i < numsSize; i++){
    	current = head;
    	while(current->next != NULL){
    		if(current->next->value == nums[i]){
    			TN[0] = current->next->key;
    			TN[1] = i;
    			match = 1;
    			break;
			}
			current = current->next;
		}
		if(match == 1){
			break;
		}
    	
    	current->next = (struct set*)malloc(sizeof(struct set));
    	current->next->key = i;
    	current->next->value = target - nums[i];
    	current->next->next = NULL;
    	
    	
	}
	return TN;
}
