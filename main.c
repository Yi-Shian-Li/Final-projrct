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

int main() {
    int init = 1;
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
        printf("3. Search record\n");
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
            search_record();
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