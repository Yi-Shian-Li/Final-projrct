//gcc main.c functions.c  file.c op1_add.c op2_delete.c op3_search.c op4_show.c op5_search_category.c op6_count.c -o program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "file.h"
#include "main.h"
#include "op1_add.h"
#include "op2_delete.h"
#include "op3_search.h"
#include "op4_show.h"
#include "op5_search_category.h"
#include "op6_count.h"
#include "functions.h"

//全局宣告
Record* head = NULL; 
char global_category[MAX_CATEGORY_NUM][MAX_CATEGORY_NAME];
int cur_category_num; //category的數量
int precision = 2; //小數點顯示多少
int default_show_n = 15;//一頁顯示多少筆資料


typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct Graph {
    int nodeNum;
    Node** aList;
} Graph;

Graph* createGraph(int nodeNum) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->nodeNum = nodeNum;
    graph->aList = (Node**)malloc(nodeNum * sizeof(Node*));

    for (int i = 0; i < nodeNum; ++i) {
        graph->aList[i] = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = dest;
    newNode->next = NULL;

    newNode->next = graph->aList[src];
    graph->aList[src] = newNode;
}

Graph* readGraph() {
    int numNodes;
    scanf("%d", &numNodes);
    getchar();

    Graph* graph = createGraph(numNodes);

    for (int i = 0; i < numNodes; ++i) {
        char line[100];
        fgets(line, sizeof(line), stdin);

        char* token = strtok(line, " \n");
        int srcNode = atoi(token);

        token = strtok(NULL, " \n");
        while (token != NULL) {
            int adjNode = atoi(token);
            addEdge(graph, srcNode, adjNode);
            token = strtok(NULL, " \n");
        }
    }

    return graph;
}

int DFS(Graph* graph, int* visited, int* inPath, int currNode) {
    if (inPath[currNode]) return 1;
    if (visited[currNode]) return 0;

    visited[currNode] = 1;
    inPath[currNode] = 1;

    Node** aList = graph->aList;
    Node* curr = aList[currNode];

    while (curr != NULL) {
        if (DFS(graph, visited, inPath, curr->value)) {
            return 1;
        }
        curr = curr->next;
    }

    inPath[currNode] = 0;
    return 0;
}

int hasCycle(Graph* graph) {
    int numNode = graph->nodeNum;
    int visited[100] = { 0 };
    int inPath[100] = { 0 };

    for (int i = 0; i < numNode; ++i) {
        if (DFS(graph, visited, inPath, i)) {
            return 1;
        }
    }

    return 0;
}
int main() {
    int init = 1;
    Graph* graph;
    int op;
        printf("Hello! Welcome to the accounting database.\n");
        while (init) {
            printf("Do you want to load file?\n");
            printf("1. Yes\n");
            printf("2. No\n");
            op = enter_num();

            system("cls"); //清屏函數
            switch (op) {
            case 1:
                initialize_with_file();
                init = 0;
                break;
            case 2:
                initialize_no_file();
                init = 0;
                break;
            default:
                printf("Invalid input! Please enter 1 or 2.\n");
        }
        
    }
    
    while (1) {

        printf("Please enter the operation you want to take.\n");
        printf("-----------------------------------------------------------\n");
        printf("0. Help\n");
        printf("1. Add record\n");
        printf("2. Delete record\n");
        printf("3. dfs game\n");
        printf("4. Show all records\n");
        printf("5. Search category\n");
     printf("6. Calculate total expense in each category\n");
        printf("7. Save file\n");
        printf("8. Setting\n");
        printf("9. Exit\n");
        printf("-----------------------------------------------------------\n");
        op = enter_num();

        system("cls"); //清屏函數
        switch (op) {
         case 0:
            help();
            break;
        case 1:
            add_record();
            break;
        case 2:
            delete_record();
            break;
        case 3:
            graph = readGraph();
            if (hasCycle(graph)) {
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }
            break;
        case 4:
            show_all_records();
            break;
        case 5:
            search_category();
            break;
     case 6:
         calculate_total_expense();
         break;
        case 7:
            save();
            break;
        case 8:
            setting();
            break;
        case 9:
            leave();
            break;
        default:
            printf("Invalid input! Please enter between 0 ~ 9.\n");
        }
    }
    
    return 0;
    
}

void help(){//程式的限制都可以寫在這裡
    printf("Some limitations:\n");
    printf("The maximun length of a category's name is %d.\n", MAX_CATEGORY_NAME);
    printf("The maximun quantity of categories is %d.\n", MAX_CATEGORY_NUM);
    printf("The maximun amount is %d.\n", MAX_AMOUNT);
    printf("-----------------------------------------------\n");
    press_any_key();
    return;
}

void setting(){//設定
    while(1){
        printf("Please enter the setting you want to change.\n");
        printf("-----------------------------------------------------------\n");
        printf("0. Return\n");
        printf("1. Decimal points\n");
        printf("2. Number of data showed\n");
        printf("-----------------------------------------------------------\n");
        int op;
        op = enter_num();
        system("cls"); //清屏函數
        int num;
        switch (op) {
            case 0:
                return;
            case 1:
                printf("How many decimal points do you want to display?\n");
                precision = enter_num_lim(0,15);
                system("cls"); //清屏函數
                printf("Change successfully! Now the precision is %d.\n", precision);
                break;
            case 2:
                printf("In operation 4, how many data do you want to display at once?\n");
                default_show_n = enter_num_lim(1, 99);
                system("cls"); //清屏函數
                printf("Change successfully! Now the number of data displayed is %d.\n", default_show_n);
                break;
            default:
                printf("Invalid input! Please enter between 0 ~ 2.\n");
        }
    }
}

void leave(){//離開程式

    while(1){
    printf("Do you want to save the file before leaving?\n");
    printf("0. Return.\n");
    printf("1. Save.\n");
    printf("2. Don't save.\n");
    
    int op;
    scanf("%d", &op);
    system("cls"); //清屏函數

        switch (op) {
            case 0:
                return;
            case 1:
                save();
                exit(0);
                break;
            case 2:
                exit(0);
                break;
            default:
                printf("Invalid input! Please enter between 0 ~ 2.\n");
        }
    }
}