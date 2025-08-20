#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int* data;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->data = (int*)malloc((capacity + 1) * sizeof(int)); // 1-indexed
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Parent-Child relationships
int parent(int i) { return i / 2; }
int leftChild(int i) { return 2 * i; }
int rightChild(int i) { return 2 * i + 1; }

void maxHeapify(MaxHeap* heap, int i) {
    int left = leftChild(i);
    int right = rightChild(i);
    int largest = i;

    // Find largest among i, left child, right child
    if (left <= heap->size && heap->data[left] > heap->data[largest])
        largest = left;
    
    if (right <= heap->size && heap->data[right] > heap->data[largest])
        largest = right;

    // If largest is not current node, swap and recursively heapify
    if (largest != i) {
        swap(&heap->data[i], &heap->data[largest]);
        maxHeapify(heap, largest);
    }
}

void buildMaxHeap(MaxHeap* heap, int arr[], int n) {
    heap->size = n;
    
    // Copy array to heap (1-indexed)
    for(int i = 0; i < n; i++) {
        heap->data[i + 1] = arr[i];
    }
    
    // Heapify from last non-leaf to root
    for(int i = heap->size / 2; i >= 1; i--) {
        maxHeapify(heap, i);
    }
}

void heapSort(int arr[], int n) {
    MaxHeap* heap = createHeap(n);
    buildMaxHeap(heap, arr, n);
    
    printf("Max Heap: ");
    for(int i = 1; i <= heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
    
    // Extract max elements one by one
    for(int i = heap->size; i >= 2; i--) {
        // Move current root to end
        swap(&heap->data[1], &heap->data[i]);
        heap->size--; // Reduce heap size
        maxHeapify(heap, 1); // Heapify root
        
        printf("After extracting %d: ", heap->data[i]);
        for(int j = 1; j <= heap->size; j++) {
            printf("%d ", heap->data[j]);
        }
        printf("| Sorted: ");
        for(int j = heap->size + 1; j <= n; j++) {
            printf("%d ", heap->data[j]);
        }
        printf("\n");
    }
    
    // Copy back to original array
    for(int i = 0; i < n; i++) {
        arr[i] = heap->data[i + 1];
    }
    
    free(heap->data);
    free(heap);
}

void printArray(int arr[], int size, const char* title) {
    printf("%s: ", title);
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    printf("\n=== HEAP AND HEAPSORT DEMONSTRATION ===\n");
    
    // Example array for heap operations
    int arr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int heapSize = sizeof(arr) / sizeof(arr[0]);
    
    printArray(arr, heapSize, "Original Array");
    
    // Create and demonstrate max heap
    MaxHeap* demoHeap = createHeap(heapSize);
    buildMaxHeap(demoHeap, arr, heapSize);
    
    printf("Max Heap (array representation): ");
    for(int i = 1; i <= demoHeap->size; i++) {
        printf("%d ", demoHeap->data[i]);
    }
    printf("\n");
    
    printf("Heap structure visualization:\n");
    printf("       %d\n", demoHeap->data[1]);
    printf("      / \\\n");
    printf("    %d   %d\n", demoHeap->data[2], demoHeap->data[3]);
    printf("   / \\   / \\\n");
    printf("  %d   %d %d  %d\n", demoHeap->data[4], demoHeap->data[5], 
           demoHeap->data[6], demoHeap->data[7]);
    printf(" / \\   /\n");
    printf("%d   %d %d\n", demoHeap->data[8], demoHeap->data[9], demoHeap->data[10]);
    
    printf("\n=== HEAPSORT STEP BY STEP ===\n");
    
    // Reset array and perform heapsort
    int sortArr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    heapSort(sortArr, heapSize);
    
    printArray(sortArr, heapSize, "Final Sorted Array");
    
    // Cleanup
    free(demoHeap->data);
    free(demoHeap);
    
    printf("\n=== COMPLEXITY ANALYSIS ===\n");
    printf("Huffman Coding:\n");
    printf("  - Build tree: O(n^2) with array, O(n log n) with heap\n");
    printf("  - Generate codes: O(n)\n");
    printf("  - Encoding: O(message_length)\n\n");
    
    printf("Heap Operations:\n");
    printf("  - MAX-HEAPIFY: O(log n)\n");
    printf("  - BUILD-MAX-HEAP: O(n)\n");
    printf("  - HEAPSORT: O(n log n)\n");
    printf("  - Extract Max: O(log n)\n");
    printf("  - Insert: O(log n)\n");

    return EXIT_SUCCESS;
}