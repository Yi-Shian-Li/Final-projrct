//gcc main.c file.c op1_add.c op2_delete.c op3_search.c op4_show.c op5_search_category.c op6_count.c functions.c -o program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "op2_delete.h"
#include "main.h"
#include "functions.h"

extern Record* head;
extern char global_category[MAX_CATEGORY_NUM][MAX_CATEGORY_NAME];
extern int cur_category_num; //category的數量
extern int precision; //小數點顯示多少
extern int default_show_n;//一頁顯示多少筆資料

void delete_record() {
    if (head == NULL) {
        printf("There is no record!\n");
        return;
    }

// 用一個指針數組記錄所有的節點地址
    Record** arr = NULL;
    int data_num;

    Record* temp = (Record*)malloc(sizeof(Record));
    temp->time.year = 0;
    temp->time.month = 0;
    temp->time.day = 0;
    temp->amount = 0;
    strcpy(temp->category, "NULL");
    strcpy(temp->note, "NULL");

    int data;
    int count = 0;

    printf("Based on which data do you want to delete?\n");
    printf("[1].Type [2].Date [3].Amount [4].Categories [5].Note\n");
    data = enter_num_lim(1, 5);
    enter_one_of_data(data - 1, temp);

    Record* p = head;
    Record* pre = NULL;

    while (p != NULL) {
        if (data == 1) {
            if (p->type == temp->type) {
                // 動態分配更多的記憶體來存儲節點地址
                //arr = (Record**)realloc(arr, (data_num + 1) * sizeof(Record*));
                //arr = (Record**)realloc(arr, (data_num + 1) * sizeof(Record*));
                //arr[data_num++] = p;
                
                // 刪除紀錄
                if (pre == NULL) {
                    head = p->next;
                } else {
                    pre->next = p->next;
                }
                
                count++;
                free(p);
                p = (pre == NULL) ? head : pre->next;
            } else {
                pre = p;
                p = p->next;
            }
        } else if (data == 2) {
            if (p->time.year == temp->time.year && p->time.month == temp->time.month && p->time.day == temp->time.day) {
                //  刪除紀錄
                if (pre == NULL) {
                    head = p->next;
                } else {
                    pre->next = p->next;
                }
                count++;
                free(p);
                p = (pre == NULL) ? head : pre->next;
            } else {
                pre = p;
                p = p->next;
            }
        } else if (data == 3) {
            if (p->amount == temp->amount) {
                // 删除记录的代码
                if (pre == NULL) {
                    head = p->next;
                } else {
                    pre->next = p->next;
                }
                count++;
                free(p);
                p = (pre == NULL) ? head : pre->next;
            } else {
                pre = p;
                p = p->next;
            }
        } else if (data == 4) {
            if (strcmp(p->category, temp->category) == 0) {
                // 刪除紀錄
                if (pre == NULL) {
                    head = p->next;
                } else {
                    pre->next = p->next;
                }
                count++;
                free(p);
                p = (pre == NULL) ? head : pre->next;
            } else {
                pre = p;
                p = p->next;
            }
        } else if (data == 5) {
            if (strcmp(p->note, temp->note) == 0) {
                // 刪除紀錄
                if (pre == NULL) {
                    head = p->next;
                } else {
                    pre->next = p->next;
                }
                count++;
                free(p);
                p = (pre == NULL) ? head : pre->next;
            } else {
                pre = p;
                p = p->next;
            }
        }
    }

    free(temp);

    if (count == 0) {
        printf("Can't find the record!\n");
        return;
    } else if (count == 1) {
        printf("%d record has been deleted.\n", count);
    } else {
        printf("%d records have been deleted.\n", count);
    }
    press_any_key();
/*
    int cur_page = 1;
    int max_page = ceil((double)count/(double)default_show_n);
    int residual = count % default_show_n;
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
    printf("Page: (%d/%d) Total data: %d\n", cur_page, max_page, count);
    printf("-------------------------------------------------------------------------------\n");
    printf("Press the key to operate\n");
*/
    
    return;
}
