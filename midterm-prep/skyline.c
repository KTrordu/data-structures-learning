#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Building structure
typedef struct {
    int left;
    int right; 
    int height;
} Building;

// Skyline point structure
typedef struct {
    int x;
    int height;
} SkylinePoint;

// Dynamic array for skyline points
typedef struct {
    SkylinePoint* points;
    int size;
    int capacity;
} Skyline;

// Initialize skyline
Skyline* createSkyline() {
    Skyline* skyline = (Skyline*)malloc(sizeof(Skyline));
    skyline->capacity = 10;
    skyline->size = 0;
    skyline->points = (SkylinePoint*)malloc(sizeof(SkylinePoint) * skyline->capacity);
    return skyline;
}

// Add point to skyline
void addPoint(Skyline* skyline, int x, int height) {
    if (skyline->size >= skyline->capacity) {
        skyline->capacity *= 2;
        skyline->points = (SkylinePoint*)realloc(skyline->points, 
                                               sizeof(SkylinePoint) * skyline->capacity);
    }
    skyline->points[skyline->size].x = x;
    skyline->points[skyline->size].height = height;
    skyline->size++;
}

// Get maximum of two integers
int maxInt(int a, int b) {
    return (a > b) ? a : b;
}

// Merge two skylines - CORE ALGORITHM
Skyline* mergeSkylines(Skyline* left, Skyline* right) {
    Skyline* result = createSkyline();
    
    int i = 0, j = 0;
    int leftHeight = 0, rightHeight = 0;
    int currentMaxHeight = 0;
    
    // Merge process using two pointers
    while (i < left->size && j < right->size) {
        int x;
        
        // Determine next x coordinate to process
        if (left->points[i].x < right->points[j].x) {
            x = left->points[i].x;
            leftHeight = left->points[i].height;
            i++;
        } else if (left->points[i].x > right->points[j].x) {
            x = right->points[j].x;
            rightHeight = right->points[j].height;
            j++;
        } else {
            // Same x coordinate in both skylines
            x = left->points[i].x;
            leftHeight = left->points[i].height;
            rightHeight = right->points[j].height;
            i++;
            j++;
        }
        
        // Calculate new max height
        int newMaxHeight = maxInt(leftHeight, rightHeight);
        
        // Add point only if height changes
        if (newMaxHeight != currentMaxHeight) {
            addPoint(result, x, newMaxHeight);
            currentMaxHeight = newMaxHeight;
        }
    }
    
    // Process remaining points from left skyline
    while (i < left->size) {
        if (left->points[i].height != currentMaxHeight) {
            addPoint(result, left->points[i].x, maxInt(left->points[i].height, rightHeight));
            currentMaxHeight = maxInt(left->points[i].height, rightHeight);
        }
        i++;
    }
    
    // Process remaining points from right skyline  
    while (j < right->size) {
        if (right->points[j].height != currentMaxHeight) {
            addPoint(result, right->points[j].x, maxInt(right->points[j].height, leftHeight));
            currentMaxHeight = maxInt(right->points[j].height, leftHeight);
        }
        j++;
    }
    
    return result;
}

// Convert single building to skyline
Skyline* buildingToSkyline(Building building) {
    Skyline* skyline = createSkyline();
    
    // Add start point (rising edge)
    addPoint(skyline, building.left, building.height);
    
    // Add end point (falling edge)
    addPoint(skyline, building.right, 0);
    
    return skyline;
}

// Recursive divide and conquer solution
Skyline* getSkylineRecursive(Building buildings[], int start, int end) {
    // Base case: single building
    if (start == end) {
        return buildingToSkyline(buildings[start]);
    }
    
    // Divide
    int mid = start + (end - start) / 2;
    
    // Conquer
    Skyline* leftSkyline = getSkylineRecursive(buildings, start, mid);
    Skyline* rightSkyline = getSkylineRecursive(buildings, mid + 1, end);
    
    // Combine
    Skyline* mergedSkyline = mergeSkylines(leftSkyline, rightSkyline);
    
    // Clean up memory
    free(leftSkyline->points);
    free(leftSkyline);
    free(rightSkyline->points);
    free(rightSkyline);
    
    return mergedSkyline;
}

// Main skyline function
Skyline* getSkyline(Building buildings[], int n) {
    if (n == 0) return createSkyline();
    return getSkylineRecursive(buildings, 0, n - 1);
}

// Print skyline for visualization
void printSkyline(Skyline* skyline) {
    printf("Skyline Points:\n");
    for (int i = 0; i < skyline->size; i++) {
        printf("(%d, %d) ", skyline->points[i].x, skyline->points[i].height);
    }
    printf("\n\n");
}

// Visualize skyline in ASCII art
void visualizeSkyline(Skyline* skyline) {
    if (skyline->size == 0) return;
    
    // Find max height for visualization
    int maxHeight = 0;
    int maxX = 0;
    for (int i = 0; i < skyline->size; i++) {
        if (skyline->points[i].height > maxHeight) {
            maxHeight = skyline->points[i].height;
        }
        if (skyline->points[i].x > maxX) {
            maxX = skyline->points[i].x;
        }
    }
    
    printf("ASCII Visualization:\n");
    
    // Draw from top to bottom
    for (int h = maxHeight; h > 0; h--) {
        for (int x = 0; x <= maxX; x++) {
            // Find current height at position x
            int currentHeight = 0;
            for (int i = 0; i < skyline->size - 1; i++) {
                if (x >= skyline->points[i].x && x < skyline->points[i + 1].x) {
                    currentHeight = skyline->points[i].height;
                    break;
                }
            }
            
            if (currentHeight >= h) {
                printf("X");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    
    // Draw x-axis
    for (int x = 0; x <= maxX; x++) {
        printf("-");
    }
    printf("\n");
}

// Test function with example from slides
void testExample() {
    printf("=== SKYLINE PROBLEM TEST ===\n\n");
    
    // Example buildings: (left, right, height)
    Building buildings[] = {
        {1, 3, 3},   // Building 1: x1=1, x2=3, height=3
        {2, 4, 4},   // Building 2: x1=2, x2=4, height=4  
        {5, 7, 1}    // Building 3: x1=5, x2=7, height=1
    };
    
    int n = sizeof(buildings) / sizeof(buildings[0]);
    
    printf("Input Buildings:\n");
    for (int i = 0; i < n; i++) {
        printf("Building %d: [%d, %d, %d]\n", 
               i+1, buildings[i].left, buildings[i].right, buildings[i].height);
    }
    printf("\n");
    
    // Get skyline
    Skyline* result = getSkyline(buildings, n);
    
    // Print result
    printSkyline(result);
    
    // Visualize
    visualizeSkyline(result);
    
    // Clean up
    free(result->points);
    free(result);
}

// Advanced test with more complex buildings
void testComplex() {
    printf("\n=== COMPLEX EXAMPLE ===\n\n");
    
    Building buildings[] = {
        {0, 2, 3},
        {1, 4, 2}, 
        {3, 6, 1},
        {5, 8, 4},
        {7, 9, 2}
    };
    
    int n = sizeof(buildings) / sizeof(buildings[0]);
    
    printf("Complex Buildings:\n");
    for (int i = 0; i < n; i++) {
        printf("Building %d: [%d, %d, %d]\n", 
               i+1, buildings[i].left, buildings[i].right, buildings[i].height);
    }
    printf("\n");
    
    Skyline* result = getSkyline(buildings, n);
    printSkyline(result);
    visualizeSkyline(result);
    
    free(result->points);
    free(result);
}

// Step-by-step demonstration
void demonstrateSteps() {
    printf("\n=== STEP BY STEP DEMONSTRATION ===\n\n");
    
    Building buildings[] = {{1, 3, 3}, {2, 4, 4}};
    
    printf("Step 1: Convert buildings to individual skylines\n");
    Skyline* sky1 = buildingToSkyline(buildings[0]);
    Skyline* sky2 = buildingToSkyline(buildings[1]);
    
    printf("Building 1 [1,3,3] → ");
    printSkyline(sky1);
    
    printf("Building 2 [2,4,4] → ");
    printSkyline(sky2);
    
    printf("Step 2: Merge skylines\n");
    Skyline* merged = mergeSkylines(sky1, sky2);
    printf("Merged result → ");
    printSkyline(merged);
    
    printf("Step 3: Visualization\n");
    visualizeSkyline(merged);
    
    // Cleanup
    free(sky1->points); free(sky1);
    free(sky2->points); free(sky2);
    free(merged->points); free(merged);
}

int main() {
    testExample();
    testComplex();
    demonstrateSteps();
    
    return 0;
}

/*
ALGORITHM EXPLANATION:

1. DIVIDE AND CONQUER APPROACH:
   - Divide buildings into two halves
   - Recursively solve each half
   - Merge the two skylines

2. MERGE ALGORITHM:
   - Use two pointers to traverse both skylines
   - At each x-coordinate, determine max height
   - Add point only when height changes

3. TIME COMPLEXITY: O(n log n)
   - Divide: O(log n) levels
   - Merge: O(n) at each level
   - Total: O(n log n)

4. SPACE COMPLEXITY: O(n)
   - Recursion stack: O(log n)
   - Result storage: O(n)

KEY INSIGHTS:
- Only add points where height changes
- Handle overlapping buildings correctly
- Merge process is similar to merge sort
- Visualization helps understand the result

EXAMPLE TRACE:
Buildings: [(1,3,3), (2,4,4), (5,7,1)]

Individual skylines:
Sky1: (1,3) (3,0)
Sky2: (2,4) (4,0) 
Sky3: (5,1) (7,0)

Merge Sky1 + Sky2:
x=1: max(3,0) = 3 → add (1,3)
x=2: max(3,4) = 4 → add (2,4)  
x=3: max(0,4) = 4 → no change
x=4: max(0,0) = 0 → add (4,0)

Final merge with Sky3:
Result: (1,3) (2,4) (4,0) (5,1) (7,0)
*/