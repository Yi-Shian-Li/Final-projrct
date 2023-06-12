#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "op3_search.h"
#include "functions.h"

extern Record* head;


void bfs(Record* r, int* visited, int size) {
    // Initialize queue
    Record** queue = (Record**)malloc(size * sizeof(Record*));
    int front = 0, rear = 0;
    queue[rear++] = r;

    // Mark the starting node as visited
    visited[r - head] = 1;

    // Start BFS traversal
    while (front != rear) {
        Record* cur = queue[front++];

        // Output current node information
        printf("date: %d-%d-%d, amount: %f, category: %s, note: %s\n",
               cur->time.year, cur->time.month, cur->time.day,
               cur->amount, cur->category, cur->note);

        // Traverse all adjacent nodes
        Edge* e = cur->first_edge;
        while (e != NULL) {
            Record* dest = e->dest;

            // If the adjacent node is not visited, mark it as visited and enqueue
            if (!visited[dest - head]) {
                visited[dest - head] = 1;
                // Resize the queue array if necessary
                if (rear == size) {
                    size *= 2;
                    queue = (Record**)realloc(queue, size * sizeof(Record*));
                }
                queue[rear++] = dest;
            }

            e = e->next_edge;
        }
    }
    press_any_key();
    free(queue);
}

void search_record() {
    if (head == NULL) {
        printf("There is no record!\n");
        return;
    }

    printf("Please input the record you want to search (yyyy mm dd amount):\n");
    int year, month, day;
    float amount;
    scanf("%d %d %d %f", &year, &month, &day, &amount);

    // Dynamically allocate memory for the visited array
    int* visited = (int*)malloc(sizeof(int));
    memset(visited, 0, sizeof(int));

    Record* p = head;
    while (p != NULL) {
        if (p->time.year == year && p->time.month == month && p->time.day == day && p->amount == amount) {
            // Output the found record
            printf("date: %04d-%02d-%02d, amount: %f, category: %s, note: %s\n",
                   p->time.year, p->time.month, p->time.day,
                   p->amount, p->category, p->note);
            press_any_key();
            // Perform BFS traversal on the found record
            bfs(p, visited, 1);

            free(visited);
            return;
        }
        p = p->next;
    }

    free(visited);
    printf("Can't find the record!\n");
}
