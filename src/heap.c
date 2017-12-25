/***************************
 * Name: Vicky Mohammad
 * ID: 0895381
 ***************************/

#include "HeapAPI.h"

/**
 * Internal functions to search for the max element between the data stored at index i
 * and the left child. This function will use compares data using the function pointer and return the index of the maximum item.
 */
size_t findMaxLeft(Heap *heap,size_t i); 

/**
 * Internal functions to search for the max element between the data stored at index current
 * and the right child. This function will use compares data using the function pointer and return the index of the maximum item.
 */
size_t findMaxRight(Heap *heap,size_t curr, size_t i); 

/**************************************************************************************************************************/

Heap *createHeap(size_t initialSize, void (*destroyDataFP)(void *data),int (*compareFP)(const void *first, const void *second)){
    Heap *heap;
    if(!(heap = malloc(sizeof(Heap)))){
        fprintf(stderr,"Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    if(!(heap->heapArray = malloc(sizeof(Node)*initialSize))){
        fprintf(stderr,"Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    heap->type = MIN_HEAP;
    heap->currentSize = 0;
    heap->maxSize = initialSize;
    heap->destroyData = destroyDataFP;
    heap->compare = compareFP;
    return heap;
}//end struct

Node *createHeapNode(void *data){
    Node *node;
    node = malloc(sizeof(Node));
    node->data = data;
    return node;
}//end struct

//TODO: For lab 11 students must recreate this function
// This function inserts data into the heap.
// It should check for the next available position in the tree.
// Then it should ensure that the heap's properties remain consistent.
void insertHeapNode(Heap *heap, void *data){

    /*init and add the node to the array*/
    Node* newNode = createHeapNode(data);
    heap->heapArray[heap->currentSize] = newNode;
    //increament and sort the heap from the root
    (heap->currentSize)++;
    heapify(heap, 0);//doesnt't work for some reason based on my debug
    
    // rearrange the array by heapifying each
    int size = currentSize(heap);
    for (int x = size / 2 - 1; x >= 0; x--){
        heapify(heap, x);
    }//end for
 
    // go trhough one by one and swap the root and heapify
    for (int x=size-1; x>=0; x--){
        // swap the root
        Node* temp = heap->heapArray[0];
        heap->heapArray[0] = heap->heapArray[x];
        heap->heapArray[x] = temp;
 
        //heapify the section
        heapify(heap, x);
    }//end for
    
}//end func

void deleteRoot(Heap *heap) {
    Node *temp;
    if(heap->currentSize>0) {
        temp = heap->heapArray[0];
        (heap->currentSize)--;
        heap->heapArray[0] = heap->heapArray[heap->currentSize];
        //printf("delete: %d\n", *(int*)(temp->data));//my debug
        heap->destroyData(temp);
        heapify(heap, 0) ;
    } else {
        fprintf(stderr,"Heap is empty.\n") ;
	}//end if
}//end func

void deleteHeap(Heap *heap){
    size_t i;
    i = heap->currentSize;
    while(i>0){
        deleteRoot(heap);
        i--;
    }//end loop
    free(heap->heapArray);
    free(heap);
}//end func

void* getRoot(Heap *heap){
    return heap->heapArray[0]->data;
}//end func

//TODO: For lab 11 students must recreate this function
// This function adjust the heap to ensure that it remains in proper order.
// The adjustment occurs with the heap contianer.
void heapify(Heap *heap, size_t i){
    size_t new = i;
    //if left child is larger/smaller than the root
    new = findMaxLeft(heap, i);
    //if right child is larger/smaller than the number being passed
    new = findMaxRight(heap, i, new);
    
    //debug
    //printf("Small: %d Large: %d\n", *(int*)heap->heapArray[new]->data, *(int*)heap->heapArray[i]->data);
    
    //if largest/smaller is not the same as the number being passed
    if(new != i){
        //debug
        //printf("SWAP\n");

        //swap the number
        Node* temp = heap->heapArray[i];
        heap->heapArray[i] = heap->heapArray[new];
        heap->heapArray[new] = temp;
        heapify(heap, new);
    }//end if
}//end func

size_t findMaxLeft(Heap *heap,size_t i){
    size_t  leftIdx = getLeftChildIndex( i );
    if( leftIdx < heap->currentSize && heap->compare(heap->heapArray[leftIdx]->data,heap->heapArray[i]->data) > 0){
        return leftIdx;
        printf("Left Happened");
    }//end if
    return i;
}//end func

size_t findMaxRight(Heap *heap,size_t curr, size_t i){
    size_t rightIdx = getRightChildIndex( curr );
    if( rightIdx < heap->currentSize && heap->compare(heap->heapArray[rightIdx]->data,heap->heapArray[i]->data) > 0){
      return rightIdx;
      printf("Right Happened");
    }//end if
    return i;
}//end func

//TODO: For lab 11 students must recreate this function
// helper to quickly calculate the left child from index ( ie index is the parent )
size_t getLeftChildIndex(size_t index){
	return (index*2)+1;
}//end func

//TODO: For lab 11 students must recreate this function
// helper to quickly calculate the right child from index ( ie index is the parent )
size_t getRightChildIndex(size_t index){
	return (index*2)+2;
}//end func

//TODO: For lab 11 students must recreate this function
// helper to quickly calculate the parent index of a child node. 
size_t getParentIndex(size_t index){
	return (index-1)/2;
}//end func

size_t currentSize(Heap* heap){
    return heap->currentSize;
}//end func

void* search(Heap* heap, void* data){       
    for(size_t i =0; i < currentSize(heap);i++) {
        if( heap->compare(data,heap->heapArray[i]->data) == 0)
            return heap->heapArray[i]->data;
    }//end for
    return NULL;
}//end func

//TODO: For lab 11 students must recreate this function
// Print a BFS version of the Heap Array
// This function should be iterative for BFS.
void printHeap(Heap* heap, void (*printFunc)(void*) ){
    for(size_t x= 0; x < currentSize(heap); x++){
        printFunc(heap->heapArray[x]->data);
    }//end for
}//end func
