#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "op1_add.h"
#include "main.h"
#include "functions.h"

extern Record* head;
extern int precision; //小數點顯示多少

void add_record() {

    //初始化
    Record* new_record = (Record*)malloc(sizeof(Record));
    new_record->time.year=0,new_record->time.month=0, new_record->time.day=0,new_record->amount=0;
    strcpy(new_record->category, "NULL");
    strcpy(new_record->note, "NULL");

    for(int i=0;i<5;i++){
    //提示
        printf("-------------------------------------------------------------------------------\n");
        printf("Date       |Amount       %*s|Categories               |Type      |Note\n", precision,"");
        printf("-------------------------------------------------------------------------------\n");
        print_data(new_record, 0);
    //輸入
        enter_one_of_data(i, new_record);
        system("cls"); //清屏函數
    }
        
    new_record->first_edge = NULL;
    new_record->next = NULL;

    if (head == NULL) {
        head = new_record;
    }
    else {
        new_record->next = head;
        head = new_record;
    }

    system("cls"); //清屏函數
    printf("Added successfully!\n");
}