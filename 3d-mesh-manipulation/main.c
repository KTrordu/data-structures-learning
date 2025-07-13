#include <stdio.h>
#include <stdlib.h>

typedef struct positions
{
    int x;
    int y;
    int z;
} Positions;

typedef struct triangle
{
    Positions vertices[3];
    int is_active;
} Triangle;

typedef struct triangle_list
{
    Triangle *triangles;
    int capacity;
    int count;
} TriangleList;

TriangleList* create_triangle_list(int capacity);
void free_triangle_list(TriangleList *list);
void add_triangle(TriangleList *list, Triangle triangle);

void x_limit(TriangleList *list, int limit);
void y_limit(TriangleList *list, int limit);
void z_limit(TriangleList *list, int limit);

void print_active_triangles(TriangleList *list);

int main()
{
    TriangleList *triangle_list = create_triangle_list(10);

    Triangle t1 = {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 1};
    Triangle t2 = {{{10, 15, 20}, {25, 30, 35}, {40, 45, 50}}, 1};
    Triangle t3 = {{{2, 3, 4}, {5, 6, 7}, {8, 9, 10}}, 1};

    add_triangle(triangle_list, t1);
    add_triangle(triangle_list, t2);
    add_triangle(triangle_list, t3);

    printf("Before x_limit(10):\n");
    print_active_triangles(triangle_list);

    x_limit(triangle_list, 10);

    printf("After x_limit(10):\n");
    print_active_triangles(triangle_list);

    free_triangle_list(triangle_list);
    return EXIT_SUCCESS;
}

TriangleList* create_triangle_list(int capacity)
{
    TriangleList *list = malloc(sizeof(TriangleList));
    if(!list) return NULL;

    list->triangles = malloc(sizeof(Triangle) * capacity);
    if(!list)
    {
        free(list);
        return NULL;
    }

    list->capacity = capacity;
    list->count = 0;
    return list;
}

void free_triangle_list(TriangleList *list)
{
    if(list)
    {
        free(list->triangles);
        free(list);
    }
}

void add_triangle(TriangleList *list, Triangle triangle)
{
    if(list && list->count < list->capacity)
    {
        list->triangles[list->count] = triangle;
        list->count++;
    }
}

void x_limit(TriangleList *list, int limit)
{
    if(!list) return;

    for(int i = 0; i < list->count; i++)
    {
        if(list->triangles[i].is_active)
        {
            for(int j = 0; j < 3; j++)
            {
                if(list->triangles[i].vertices[j].x > limit)
                {
                    list->triangles[i].is_active = 0;
                    break;
                }
            }
        }
    }
}

void y_limit(TriangleList *list, int limit)
{
    if(!list) return;

    for(int i = 0; i < list->count; i++)
    {
        if(list->triangles[i].is_active)
        {
            for(int j = 0; j < 3; j++)
            {
                if(list->triangles[i].vertices[j].y > limit)
                {
                    list->triangles[i].is_active = 0;
                    break;
                }
            }
        }
    }
}

void z_limit(TriangleList *list, int limit)
{
    if(!list) return;

    for(int i = 0; i < list->count; i++)
    {
        if(list->triangles[i].is_active)
        {
            for(int j = 0; j < 3; j++)
            {
                if(list->triangles[i].vertices[j].z > limit)
                {
                    list->triangles[i].is_active = 0;
                    break;
                }
            }
        }
    }
}

void print_active_triangles(TriangleList *list)
{
    if(!list) return;

    printf("Active Triangles:\n");
    for(int i = 0; i < list->count; i++)
    {
        if(list->triangles[i].is_active)
        {
            printf("Triangle %d: ", i);
            for(int j = 0; j < 3; j++)
            {
                printf("(%d, %d, %d) ", list->triangles[i].vertices[j].x, list->triangles[i].vertices[j].y, list->triangles[i].vertices[j].z);
            }
            printf("\n");
        }
    }
}