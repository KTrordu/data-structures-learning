#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct WormPart {
    int x, y;
};

struct Node {
    struct WormPart* data;
    struct Node* next;
    struct Node* previous;
};

struct DoublyList {
    struct Node* head;
    struct Node* tail;
    int elemcount;
};

void addFront(struct DoublyList* list, struct WormPart* new_element) {
    struct Node* newnode = (struct Node*) malloc(sizeof(struct Node));
    newnode->data = new_element;
    newnode->next = list->head;
    newnode->previous = NULL;

    if (list->head != NULL)
        list->head->previous = newnode;

    list->head = newnode;
    list->elemcount++;

    if (list->elemcount == 1)
        list->tail = newnode;
}

void addBack(struct DoublyList* list, struct WormPart* new_element) {
    struct Node* newnode = (struct Node*) malloc(sizeof(struct Node));
    newnode->data = new_element;
    newnode->next = NULL;
    newnode->previous = list->tail;

    if (list->tail != NULL)
        list->tail->next = newnode;

    list->tail = newnode;
    list->elemcount++;

    if (list->elemcount == 1)
        list->head = newnode;
}

void removeFront(struct DoublyList* list) {
    if (list->head != NULL) {
        struct Node* old = list->head;
        if (list->head->next != NULL)
            list->head->next->previous = NULL;
        list->head = list->head->next;
        free(old->data);
        free(old);
        list->elemcount--;
    }
}

void removeBack(struct DoublyList* list) {
    if (list->tail != NULL) {
        struct Node* old = list->tail;
        if (list->tail->previous != NULL)
            list->tail->previous->next = NULL;
        list->tail = list->tail->previous;
        free(old->data);
        free(old);
        list->elemcount--;
    }
}

void removeAt(struct DoublyList* list, int position) {
    if (position == 0) {
        removeFront(list);
        return;
    } else if (position == list->elemcount - 1) {
        removeBack(list);
        return;
    } else if (position >= list->elemcount) {
        return;
    }

    struct Node* prev_node = NULL;
    struct Node* position_pointer = list->head;

    for (int i = 0; i < position; i++) {
        prev_node = position_pointer;
        position_pointer = position_pointer->next;
    }

    struct Node* old = position_pointer;
    prev_node->next = position_pointer->next;

    if (position_pointer->next != NULL)
        position_pointer->next->previous = prev_node;

    free(old->data);
    free(old);
    list->elemcount--;
}

struct DoublyList* create_worm(char* filename) {
    struct DoublyList* worm = (struct DoublyList*) malloc(sizeof(struct DoublyList));
    worm->head = NULL;
    worm->tail = NULL;
    worm->elemcount = 0;

    FILE* infile = fopen(filename, "r");

    char line[256];
    while (fgets(line, sizeof(line), infile)) {
        int x, y;
        sscanf(line, "%d %d", &x, &y);

        struct WormPart* new_part = (struct WormPart*) malloc(sizeof(struct WormPart));
        new_part->x = x;
        new_part->y = y;

        addFront(worm, new_part);
    }

    fclose(infile);
    return worm;
}

int find_node_index(struct DoublyList* list, int x, int y);

int main() {
    struct DoublyList* wormfield[100];
    int wormcount = 4;

    char* filenames[4] = {"worms/worm1.txt", "worms/worm2.txt", "worms/worm3.txt", "worms/worm4.txt"};

    for (int i = 0; i < 4; i++) {
        struct DoublyList* new_worm = create_worm(filenames[i]);        
        wormfield[i] = new_worm;
    }

    while (1) {
        int option;
        printf("------------------------------------\n");
        printf("1- View the worms\n");
        printf("2- Attack\n");
        printf("3- Quit\n");
        printf("------------------------------------\n");
        printf("Please enter an action: ");
        scanf("%d", &option);

        if (option == 1) {

            printf("Worm List\n");

            for (int i = 0; i < wormcount; i++) {
                printf("Worm %d ", i);

                struct Node* wormnode_ptr = wormfield[i]->head;
                while (wormnode_ptr != NULL) {
                    printf("(%d,%d) ", wormnode_ptr->data->x, wormnode_ptr->data->y);
                    wormnode_ptr = wormnode_ptr->next;
                }
                printf("\n");
            }

        } else if (option == 2) {
            
            printf("Enter x y coordinates to attack\n");
            int x, y;
            scanf("%d %d", &x, &y);

            int hit_index = -1;
            int hit_worm_index = -1;

            for (int i = 0; i < wormcount; i++)
            {
                hit_index = find_node_index(wormfield[i], x, y);
                if (hit_index != -1)
                {
                    hit_worm_index = i;
                    break;
                }
            }

            if(hit_worm_index == -1)
            {
                printf("Hit missed!\n");
            }
            else
            {
                printf("Hit! Worm %d at position %d\n", hit_worm_index, hit_index);

                int length = wormfield[hit_worm_index]->elemcount;

                int remove_start = hit_index - 1;
                int remove_end = hit_index + 1;

                if(remove_start < 0) remove_start = 0;
                if(remove_end >= length) remove_end = length - 1;

                int left_remaining = remove_start;
                int right_remaining = length - (remove_end + 1);
                printf("Debug: remove_start=%d, remove_end=%d\n", remove_start, remove_end);
                printf("Debug: left_remaining=%d, right_remaining=%d\n", left_remaining, right_remaining);

                if (left_remaining == 0 && right_remaining == 0)
                {
                    // worm öldü
                    printf("Worm died completely!\n");

                    while (wormfield[hit_worm_index]->head != NULL)
                    {
                        removeFront(wormfield[hit_worm_index]);
                    }
                    free(wormfield[hit_worm_index]);
                    wormfield[hit_worm_index] = NULL;

                    for (int i = hit_worm_index; i < wormcount - 1; i++)
                    {
                        wormfield[i] = wormfield[i + 1];
                    }
                    wormfield[wormcount - 1] = NULL;
                    wormcount--;
                }
                else if(left_remaining <= 0 && right_remaining > 0)
                {
                    // worm'ün sol kısmı gitti
                    printf("Left part destroyed, right part survives\n");

                    for (int i = 0; i <= remove_end; i++)
                    {
                        removeFront(wormfield[hit_worm_index]);
                    }
                }
                else if(left_remaining > 0 && right_remaining <= 0)
                {
                    // worm'ün sağ kısmı gitti
                    printf("Right part destroyed, left part survives\n");

                    for (int i = remove_end; i >= remove_start; i--)
                    {
                        removeBack(wormfield[hit_worm_index]);
                    }
                }
                else
                {
                    // worm ikiye ayrıldı
                    printf("Worm split into two parts!\n");
                }
            }

        } else if (option == 3) {
            break;
        } else {
            printf("Wrong Input!\n");
        }
    }

    return 0;
}

int find_node_index(struct DoublyList* list, int x, int y)
{
    if(list == NULL || list->head == NULL) return -1;

    struct Node *current = list->head;
    for (int i = 0; i < list->elemcount; i++)
    {
        if (current->data->x == x && current->data->y == y) return i;

        current = current->next;
    }

    return -1;
}