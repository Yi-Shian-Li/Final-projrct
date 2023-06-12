//gcc main.c file.c op1_add.c op2_delete.c op3_search.c op4_show.c op5_search_category.c op6_count.c functions.c -o program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>

#include "main.h"
#include "op2_delete.h"
#include "functions.h"

extern Record* head;
extern char global_category[MAX_CATEGORY_NUM][MAX_CATEGORY_NAME];
extern int cur_category_num; //category的數量
extern int precision; //小數點顯示多少
extern int default_show_n;//一頁顯示多少筆資料

Record* deleted_records_head = NULL;

// 刪除記錄並將其添加到新鍊錶
void add_to_deleted_records(Record* record) {
    Record* deleted_record = (Record*)malloc(sizeof(Record));
    *deleted_record = *record;
    deleted_record->next = NULL;

    if (deleted_records_head == NULL) {
        deleted_records_head = deleted_record;
    } else {
        Record* last_deleted_record = deleted_records_head;
        while (last_deleted_record->next != NULL) {
            last_deleted_record = last_deleted_record->next;
        }
        last_deleted_record->next = deleted_record;
    }
}

void delete_record() {
    if (head == NULL) {
        printf("There is no record!\n");
        return;
    }

    
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

    system("cls"); //清屏函數

    Record* p = head;
    Record* pre = NULL;

    while (p != NULL) {
        if (data == 1) {
            if (p->type == temp->type) {
                // 將刪除的記錄添加到新的鍊錶中
                add_to_deleted_records(p);

                // 刪除記錄的代碼
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
                // 將刪除的記錄添加到新的鍊錶中
                add_to_deleted_records(p);

                // 刪除記錄的代碼
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
                // 將刪除的記錄添加到新的鍊錶中
                add_to_deleted_records(p);

                // 刪除記錄的代碼
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
                // 將刪除的記錄添加到新的鍊錶中
                add_to_deleted_records(p);

                // 刪除記錄的代碼
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
                // 將刪除的記錄添加到新的鍊錶中
                add_to_deleted_records(p);

                // 刪除記錄的代碼
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
    } 
    
    Record** arr = record_to_array(deleted_records_head, &count);

    int cur_page = 1;
    while(1){
        int max_page = ceil((double)count/(double)default_show_n);
        int residual = count % default_show_n;
        int show_num;
        if(cur_page>max_page) cur_page--;
        printf("-------------------------------------------------------------------------------\n");
        if (count == 1) {
            printf(" %d record has been deleted.\n", count);
        } else {
            printf(" %d records have been deleted.\n", count);
        }
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
        printf("[S]. Sort\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("[P]. Previous Page [N]. Next Page [R]. Return\n");
        printf("Page: (%d/%d) Deleted data: %d\n", cur_page, max_page, count);
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
                sort(arr, count, sort_by, sort_order);
                break;

            case 'p':
                if(cur_page != 1) cur_page -=1;
                break;
            case 'n':
                if(cur_page != max_page) cur_page +=1;
                break;
            case 'r':
                free_deleted_records();
                return;//回到main
            default:
                system("cls"); //清屏函數
        }
    }
    return;
}

void free_deleted_records() {
    Record* p = deleted_records_head;
    while (p != NULL) {
        Record* temp = p;
        p = p->next;
        free(temp);
    }
    deleted_records_head = NULL;
}
