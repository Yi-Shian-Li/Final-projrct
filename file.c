#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file.h"
#include "main.h"
#include "functions.h"

//全局宣告
extern Record* head;
extern char global_category[MAX_CATEGORY_NUM][MAX_CATEGORY_NAME];
extern int cur_category_num; //category的數量

void initialize_with_file() {
    FILE *fp;        // 定義一個指向 FILE 的指標
    char ch;         // 定義一個字符型變量
    fp = fopen("file.txt", "r");   // 打開一個檔案，使用 "r" 參數表示讀取模式
    // 檢查是否成功打開檔案
    if (fp == NULL) {
        printf("Failed to open file!\nYou need to have a file name \"file.txt\".\n");
        return;
    }
    //開始讀檔
    char input[150];
    fgets(input, 100, fp);//吃掉第一行 Category:
    printf("%s", input);

    fgets(input, 10, fp);//取得category數列
    cur_category_num = atoi(input);
    printf("%d\n", cur_category_num);

    for(int i =0;i<cur_category_num;i++){//取得category
        fscanf(fp,"%s", global_category[i]);
        printf("%s\n",global_category[i]);
    }
    fgets(input, 100, fp);//吃掉一行
    fgets(input, 100, fp);//吃掉第一行 Date: date, amout, category, type, note
    // 讀取檔案中的字符，並輸出到屏幕上
    while (fgets(input, 150, fp)) {

        Record* new_record = (Record*)malloc(sizeof(Record));
        printf("%s", input);
        sscanf(input, "%d %d %d %f %s %d %s ", &new_record->time.year, &new_record->time.month, &new_record->time.day, 
        &new_record->amount, new_record->category, &new_record->type, new_record->note);

        new_record->first_edge = NULL;
        new_record->next = NULL;
        Record* p = head;

        if (head == NULL) {
            head = new_record;
        }
        else {
            new_record->next = head;
            head = new_record;
        }
    }

    printf("\nLoaded successfully!\n");
    fclose(fp);// 關閉檔案
    press_any_key();
    return;

}

void initialize_no_file(){
    
    //載入默認的categories
    cur_category_num = 19;
    char default_category[MAX_CATEGORY_NUM][MAX_CATEGORY_NUM] = {"Food",
            "Transportation",
            "Clothing",
            "Housing",
            "Entertainment",
            "Travel",
            "Electronics",
            "Healthcare",
            "Sports",
            "Education",
            "Social_Activities",
            "Pets",
            "Miscellaneous_Expenses",
            "Electricity_Bill",
            "Internet_Bill",
            "Water_Bill",
            "Communication_Bill",
            "Taxes",
            "Insurance"};

    for(int i=0;i<cur_category_num;i++){
        strcpy(global_category[i],default_category[i]);
    }
}

void save(){
    FILE *fp;        // 定義一個指向 FILE 的指標
    char ch;         // 定義一個字符型變量

    fp = fopen("output.txt", "w"); //輸出output.txt

    int data_num;
    Record** arr = record_to_array(head, &data_num);

    //整理日期>時間
    sort(arr, data_num, 2, 1);
    sort(arr, data_num, 1, 1);
    
    // 寫入字符到檔案中
    fprintf(fp, "Category_num:\n");
    fprintf(fp, "%d\n", cur_category_num);
    for(int i = 0 ; i < cur_category_num ; i++ ) {
        fprintf(fp, "%s\n", global_category[i]);
    }
    
    fprintf(fp, "Date: date, amout, category, type, note");
    for (int i = 0; i < data_num; i++) {
        Record* cur = arr[i];
        fprintf(fp, "\n%04d %02d %02d %f %s %d %s",
            cur->time.year, cur->time.month, cur->time.day,
            cur->amount, cur->category, cur->type, cur->note);
    }
    // 關閉檔案
    fclose(fp);
    printf("Saved successfully!\n");
}