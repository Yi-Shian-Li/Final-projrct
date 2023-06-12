#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#include "op6_count.h"
#include "main.h"
#include "functions.h"

extern Record* head;
extern char global_category[MAX_CATEGORY_NUM][MAX_CATEGORY_NAME];
extern int cur_category_num; //category的數量
extern int precision; //小數點顯示多少

void calculate_total_expense() {
    
    Category *category_exp = (Category*) malloc(sizeof(Category) * cur_category_num);

    for(int i = 0; i < cur_category_num ; i++){
        strcpy(category_exp[i].name, global_category[i]);
        category_exp[i].total_expense = 0;
        category_exp[i].total_income = 0;
    }

    Record* p = head;
    while (p != NULL) {
        for (int i = 0; i < cur_category_num; i++) {
            if (strcmp(category_exp[i].name, p->category) == 0) {
                category_exp[i].total_expense += (p->type == 0) ? p->amount : 0;
                category_exp[i].total_income += (p->type == 1) ? p->amount : 0;
            }
        }
        p = p->next;
    }

    int cur_page = 1;
    int max_page = 3;

    while(1){
        printf("----------------------------------------------\n");
        if(cur_page==1) printf("Total expense in each category:\n");
        if(cur_page==2) printf("Total income in each category:\n");
        if(cur_page==3) printf("Total revenue in each category:\n");
        printf("----------------------------------------------\n");
        for (int i = 0; i < cur_category_num; i++) {
            printf("%d. ",i+1);
            printf("%s", category_exp[i].name);
            int len = strlen(global_category[i]); 
            len = MAX_CATEGORY_NAME - len + 1;//空白的長度
            if(i >= 9) len -= 1; //排版
            for(int j=0; j<len; j++) printf(" ");
            if(cur_page==1) printf("$%.*f\n",precision, category_exp[i].total_expense);
            if(cur_page==2) printf("$%.*f\n",precision, category_exp[i].total_income);
            if(cur_page==3) printf("$%.*f\n",precision, category_exp[i].total_income -category_exp[i].total_expense);
        }

        printf("----------------------------------------------\n");
        printf("[P]. Previous Page [N]. Next Page [R]. Return\n");
        printf("Page: (%d/%d)\n", cur_page, max_page);
        printf("----------------------------------------------\n");
        printf("Press the key to operate\n");
        
        char op;
        op = getch();
        op= tolower(op);
        system("cls"); //清屏函數

        switch (op) {
            case 'p':
                if(cur_page != 1) cur_page -=1;
                break;
            case 'n':
                if(cur_page != max_page) cur_page +=1;
                break;
            case 'r':
                return;
        }
    }
}