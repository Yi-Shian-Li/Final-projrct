#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "op3_search.h"
#include "functions.h"

extern Record* head;

void bfs(Record* r, int* visited) {
    // 初始化列隊
    Record* queue[MAX_RECORD_NUM];
    int front = 0, rear = 0;
    queue[rear++] = r;

    // 標示起始節點已訪問
    visited[r - head] = 1;

    // 開始 BFS 遍歷
    while (front != rear) {
        Record* cur = queue[front++];

        // 输出當前節點訊息
    /*    printf("date: %d-%d-%d，amount: %f，category: %s，note: %s\n",
            cur->time.year, cur->time.month, cur->time.day,
            cur->amount, cur->category, cur->note);
    */
        // 遍歷所有鄰接節點
        Edge* e = cur->first_edge;
        while (e != NULL) {
            Record* dest = e->dest;

            // 如果邻接节点未访问，则标记已访问，并入队
            if (!visited[dest - head]) {
                visited[dest - head] = 1;
                queue[rear++] = dest;
            }

            e = e->next_edge;
        }
    }
}

void search_record() {
    if (head == NULL) {
        printf("There is no record! \n");
        return;
    }

    printf("please input the record you want to search? (yyyy mm dd amount) : \n");
    int year, month, day;
    float amount;
    scanf("%d %d %d %f", &year, &month, &day, &amount);

    // 初始化 visited 數组
    int visited[MAX_RECORD_NUM];
    memset(visited, 0, sizeof(visited));

    Record* p = head;
    while (p != NULL) {
        if (p->time.year == year && p->time.month == month && p->time.day == day && p->amount == amount) {
            // 输出查找到的记录
            printf("date: %04d-%02d-%02d, amount: %f, category: %s, note: %s\n",
                p->time.year, p->time.month, p->time.day,
                p->amount, p->category, p->note);

            // 对查找到的记录进行 BFS 遍历
            bfs(p, visited);
            return;
        }
        p = p->next;
    }

    printf("can't find the record!\n");
}