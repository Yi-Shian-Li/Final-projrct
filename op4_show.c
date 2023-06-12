#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>

#include "file.h"
#include "main.h"
#include "op4_show.h"
#include "functions.h"

extern Record* head;
extern char global_category[MAX_CATEGORY_NUM][MAX_CATEGORY_NAME];
extern int cur_category_num; //category的數量
extern int precision; //小數點顯示多少
extern int default_show_n;//一頁顯示多少筆資料

void show_all_records(){//模式 資料 資料總數

    if (head == NULL) {
        printf("There is no record!\n");
            return;//回到main
        }

    int data_num;
    Record** arr = record_to_array(head, &data_num);

    //整理日期>時間
    sort(arr, data_num, 2, 1);
    sort(arr, data_num, 1, 1);

    //列印
    int cur_page = 1;

    while(1){
        // delete後檢查無資料
        if (head == NULL||data_num ==0) {
            printf("There is no record!\n");
            return;//回到main
        }

        int max_page = ceil((double)data_num/(double)default_show_n);
        int residual = data_num % default_show_n;
        int show_num;
        if(cur_page>max_page) cur_page--;

        printf("-------------------------------------------------------------------------------\n");    
        printf(" No. |Date       |Amount       %*s|Categories               |Type      |Note\n", precision,"");
        printf("-------------------------------------------------------------------------------\n");

        if(cur_page == max_page){//最後一頁
            if(residual==0) show_num = default_show_n;
            if(residual!=0)show_num = residual;
        }else{
            show_num = default_show_n;
        }

        for (int i = 0; i < show_num; i++) {
            Record* cur = arr[ i + ((cur_page-1)*default_show_n) ];
            printf("%3d.  ", default_show_n * (cur_page-1) + (i+1));
            print_data(cur, 0);
        }

        printf("-------------------------------------------------------------------------------\n");
        printf("[S]. Sort [M]. Modify [D]. Delete\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("[P]. Previous Page [N]. Next Page [R]. Return\n");
        printf("Page: (%d/%d) Total data: %d\n", cur_page, max_page, data_num);
        printf("-------------------------------------------------------------------------------\n");
        printf("Press the key to operate\n");
        
        char op;
        int no, data;
        int sort_by, sort_order;
        Record* temp;

        op = getch();
        op= tolower(op);
        if(op=='r'||op=='p'||op=='n')system("cls"); //清屏函數

        switch (op) {
            case 's':
                //輸入整理的資料
                printf("Which one do you want to sort by?\n");
                printf("[1]Date [2]Amount\n");
                sort_by = enter_num_lim(1,2);
                //輸入整理順序
                printf("Which sort order do you want to apply?\n");
                printf("[1]Ascending [2]Descending\n");
                sort_order = enter_num_lim(1,2);
                //整理
                sort(arr, data_num, sort_by, sort_order);
                break;

            case 'm':  
                printf("Which No. do you want to modify?\n");
                no = enter_num_lim(1, data_num);
                system("cls"); //清屏函數
                temp = arr[no-1];
                printf("-------------------------------------------------------------------------------\n");
                printf(" No. |Date       |Amount       %*s|Categories               |Type      |Note\n", precision,"");
                printf("-------------------------------------------------------------------------------\n");
                printf("%3d.  ", no);
                print_data(temp, 0);
                printf("Which data do you want to modify?\n");
                printf("[1].Type [2].Date [3].Amount [4].Categories [5].Note\n");
                data = enter_num_lim(1,5);
                enter_one_of_data(data-1, temp);
                system("cls"); //清屏函數
                break;

            case 'd':
                printf("Which No. do you want to delete?\n");
                no = enter_num_lim(1, data_num);
                system("cls"); //清屏函數
                temp = arr[no-1];
                delete_from_show(temp);
                
                arr = record_to_array(head, &data_num);
                sort(arr, data_num, 2, 1);
                sort(arr, data_num, 1, 1);
                
                break;
            case 'p':
                if(cur_page != 1) cur_page -=1;
                break;
            case 'n':
                if(cur_page != max_page) cur_page +=1;
                break;
            case 'r':
                return;//回到main
            default:
                system("cls"); //清屏函數
        }
    }
}