#include<stdio.h>
#include<stdlib.h>

#define MAX	80

struct HeapTree
{
    int data[MAX];
    int count;
    
    // Constructor
    HeapTree(const char* filename);
    
    // Methods
    void InsertData(int);
    void Show();
    void ShowSpace(int);
    int MyPower(int);
    int GetLevel();
    void ShowTree();
    void HeapSort();
    void AdjustHeap();
};

int main()
{
    // Create HeapTree from file
    HeapTree heap("a.txt");
    
    // Show original heap contents
    printf("Original Heap:\n");
    heap.Show();
    
    // Show tree structure
    printf("\nHeap Tree Structure:\n");
    heap.ShowTree();
    
    // Perform heap sort
    heap.HeapSort();
    
    // Show sorted heap
    printf("\nSorted Heap:\n");
    heap.Show();

    //heap insertion
    heap.InsertData(21);
    heap.Show();
    
    return 0;
}

//======================================
HeapTree::HeapTree(const char* filename)
{
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Error opening file %s\n", filename);
        count = 0;
        return;
    }
    
    count = 0;
    int num;
    
    // Read numbers from file and insert into heap
    while(fscanf(fptr, "%d", &num) != EOF && count < MAX)
    {
        InsertData(num);
    }
    
    fclose(fptr);
}

//======================================
void HeapTree::InsertData(int num)
{
    if (count < MAX) {
        // Insert the new number at the end of the array
        data[count] = num;
        count++; // Increment the count of elements
        
        // Bubble up to maintain heap property
        int index = count - 1;
        printf("Inserting %d\n", num);  // Debug print
        
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            
            // If current node is greater than parent, swap
            if (data[index] > data[parentIndex]) {
                // Swap
                int temp = data[index];
                data[index] = data[parentIndex];
                data[parentIndex] = temp;
                
                printf("Swapped %d with %d\n", data[index], data[parentIndex]);  // Debug print
                
                // Move up to parent
                index = parentIndex;
            } else {
                // Heap property satisfied
                break;
            }
        }
        
        // Show the tree after insertion
        printf("\nTree after inserting %d:\n", num);
        ShowTree();
    } else {
        printf("Heap is full, cannot insert %d\n", num);
    }
}

//======================================
void HeapTree::Show()
{
    printf("Heap contents (%d elements):\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

//======================================
void HeapTree::ShowSpace(int num)
{
    // Print a specified number of spaces
    for (int i = 0; i < num; i++) {
        printf(" ");
    }
}

//======================================
int HeapTree::MyPower(int num)
{
    // Calculate 2^num (power of 2)
    int result = 1;
    for (int i = 0; i < num; i++) {
        result *= 2;
    }
    return result;
}

//======================================
int HeapTree::GetLevel()
{
    // Calculate the number of levels in the heap
    int levels = 0;
    int totalNodes = count;
    
    while (totalNodes > 0) {
        totalNodes >>= 1;  // Divide by 2
        levels++;
    }
    
    return levels;
}

//======================================
void HeapTree::ShowTree()
{
    if (count == 0) {
        printf("Empty heap\n");
        return;
    }

    int levels = GetLevel();
    int index = 0;

    for (int level = 0; level < levels; level++) {
        int nodesAtThisLevel = 1 << level;
        int spaceBetween = (1 << (levels - level)) - 1;

        // Print leading spaces
        ShowSpace(spaceBetween);

        // Print nodes at this level
        for (int j = 0; j < nodesAtThisLevel && index < count; j++) {
            printf("%d", data[index]);
            index++;

            // Print spaces between nodes
            if (j < nodesAtThisLevel - 1 && index < count) {
                ShowSpace(spaceBetween * 2 + 1);
            }
        }
        printf("\n");
    }
}

//======================================
void HeapTree::HeapSort()
{
    // Heap sort implementation
    // First, create a max heap (which is already done during insertion)
    
    // Save the original count
    int originalCount = count;
    
    // Extract elements from the heap one by one
    for (int i = count - 1; i > 0; i--) {
        // Move current root to end
        int temp = data[0];
        data[0] = data[i];
        data[i] = temp;
        
        // Reduce heap size
        count--;
        
        // Heapify the reduced heap
        int index = 0;
        while (true) {
            int largest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            
            // If left child is larger than root
            if (left < count && data[left] > data[largest])
                largest = left;
            
            // If right child is larger than largest so far
            if (right < count && data[right] > data[largest])
                largest = right;
            
            // If largest is not root
            if (largest != index) {
                // Swap
                temp = data[index];
                data[index] = data[largest];
                data[largest] = temp;
                
                index = largest;
            }
            else {
                break;
            }
        }
    }
    //restore the original count 
    count = originalCount;
}

//======================================
void HeapTree::AdjustHeap()
{
    // Rebuild the heap to ensure heap property
    for (int i = count / 2 - 1; i >= 0; i--) {
        int index = i;
        while (true) {
            int largest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            
            // If left child is larger than root
            if (left < count && data[left] > data[largest])
                largest = left;
            
            // If right child is larger than largest so far
            if (right < count && data[right] > data[largest])
                largest = right;
            
            // If largest is not root
            if (largest != index) {
                // Swap
                int temp = data[index];
                data[index] = data[largest];
                data[largest] = temp;
                
                // Continue heapifying
                index = largest;
            } else {
                break;
            }
        }
    }
}
