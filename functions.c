#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>

#include "main.h"
#include "functions.h"

extern Record* head;
extern char global_category[MAX_CATEGORY_NUM][MAX_CATEGORY_NAME];
extern int cur_category_num; //category的數量
extern int precision; //小數點顯示多少
extern int default_show_n;//一頁顯示多少筆資料

//防呆輸入機制
int enter_num(){
    int num;
    char c;
    printf("Enter a number: ");
    while (scanf("%d", &num) != 1) {
        // 如果讀取失敗，清空輸入緩衝區
        while ((c = getchar()) != '\n' && c != EOF) {}
        printf("Invalid input. Please enter a number: ");
    }
    return num;
}

//限制檢查輸入機制
int enter_num_lim(int min, int max){
    int num;
    while(1){
        num = enter_num();
        if (num >= min && num <= max){
            return num;
        }
        printf("Invalid input. Please enter between %d ~ %d.\n", min, max);
    }
}

//查看畫面
void press_any_key(){
    printf("PRESS any key to continue.\n");
    getch();
    system("cls"); //清屏函數
}



int enter_spending_type(){
    printf("Please enter expense (0) or income (1):\n");
    return enter_num_lim(0,1);
}

void enter_date(Record* new_record){
    int yyyy, mm, dd;
    char c;
    while(1){
        printf("Please enter the date. (yyyy mm dd)\n");
        printf("Enter three numbers: ");
        
        //防呆機制，如果輸入到char要重新輸入三個數字
        while ((scanf("%d", &yyyy) != 1) || (scanf("%d", &mm) != 1) ||(scanf("%d", &dd) != 1)) {
            // 如果讀取失敗，清空輸入緩衝區
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid input. Please enter three numbers. (yyyy mm dd)\n");
            printf("Enter three numbers: ");
        }

        //先把結果貼上，再檢查有沒有在對的範圍內
        new_record->time.year = yyyy;
        new_record->time.month = mm;
        new_record->time.day = dd;

        while(1){//檢查年
            if(yyyy >= 0 && yyyy <=9999){
                new_record->time.year = yyyy;
                break;
            }else{
                printf("Invalid year! Please enter between 0 ~ 9999.\n");
                yyyy = enter_num();
            }
        }
        while(1){//檢查月
            if(mm >= 1 && mm <=12){
                new_record->time.month = mm;
                break;
            }else{
                printf("Invalid month! Please enter between 1 ~ 12.\n");
                mm = enter_num();
            }
        }
        const char month[13][10] = {"NULL", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
        while(1){//檢查日
            if( mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12 ){//大月
                if( dd >= 1 && dd <=31){
                    new_record->time.day = dd; 
                    break;
                }else{
                    printf("Invalid date in %s! Please enter between 1 ~ 31.\n", month[new_record->time.month]);
                    dd = enter_num();
                }
            }else if( mm == 4 || mm == 6 || mm == 9 || mm == 11 ){//小月
                if( dd >= 1 && dd <=30){
                    new_record->time.day = dd;
                    break;
                }else{
                    printf("Invalid date in %s! Please enter between 1 ~ 30.\n", month[new_record->time.month]);
                    dd = enter_num();
                }
            }else if( mm == 2){//2月
                if (( yyyy % 4 == 0 && yyyy % 100 != 0) || yyyy % 400 == 0) {//閏年
                    if( dd >= 1 && dd <=29){
                        new_record->time.day = dd;
                        break;
                    }else{
                        printf("Invalid date in %s!\nIt's a leap year. Please enter between 1 ~ 29.\n", month[new_record->time.month]);
                        dd = enter_num();
                    }
                } else {//平年
                    if( dd >= 1 && dd <=28){
                        new_record->time.day = dd;
                        break;
                    }else{
                        printf("Invalid date in %s!\nIt's not a leap year. Please enter between 1 ~ 28.\n", month[new_record->time.month]);
                        dd = enter_num();
                    }
                }
            }
        }
        break;
    }
}

float enter_amount(){
    while(1){
        printf("Please enter the amount. (You can enter decimals.)\n");
        printf("Enter a number: ");
        int c;
        float num;
        while (scanf("%f", &num) != 1) {
            // 如果讀取失敗，清空輸入緩衝區
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid input. Please enter a number: ");
        }
        if(num >= 0 && num <= MAX_AMOUNT) return num;
        printf("Invalid input! Please enter between 1 ~ MAX_AMOUNT.\n");
    }
}

int enter_categories(){
    int print_times;
    print_times = ceil((double)cur_category_num / 4) * 4;
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    for(int i=0; i<print_times; i++){
        int categories_space = MAX_CATEGORY_NAME - strlen(global_category[i]) +1; //空白的長度
        if(i >= 9) categories_space -= 1; //排版

        if(i<cur_category_num){
            printf("%d. ", i+1);
        }else{
            printf("    ");
        }
        printf("%s%*s", global_category[i], categories_space, "");
        if(i % 4 ==3) printf("|\n");
    }
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    printf("Please enter the category.\n");
    return enter_num_lim(1, cur_category_num);
}

void enter_note(Record* new_record){
    char input[MAX_NOTE];
    printf("Please enter the note. (if there's no note, please enter no) : \n");
    fgets(input, sizeof(input), stdin);//吃掉換行
    fgets(input, sizeof(input), stdin);
    // 移除換行符號
    if (input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }
    int length = strlen(input);
    for (int i = 0; i < length; i++) {
        if (input[i] == ' ') {
            input[i] = '_';
        }
    }
    strcpy(new_record->note, input);
}

void enter_one_of_data(int i, Record* new_record){
    if(i==0) new_record->type = enter_spending_type();//輸入收支
    if(i==1) enter_date(new_record);//輸入日期
    if(i==2) new_record->amount = enter_amount();//輸入金額
    if(i==3){//輸入類別
        int cat = enter_categories();
        strcpy(new_record->category, global_category[cat-1]);
    }//輸入筆記
    if(i==4){
        enter_note(new_record);
    }
}

void print_data(Record* cur, int mode){
    //mode 0  
    //mode 其他 

    if(cur->amount>MAX_AMOUNT) cur->amount = MAX_AMOUNT;
    int amount_space = 10 -count_digits(cur->amount);
    int categories_space = MAX_CATEGORY_NAME - strlen(cur->category);
    
    printf("%04d-%02d-%02d  ", cur->time.year, cur->time.month, cur->time.day);
    printf("$%.*f%*s  ",  precision, cur->amount,amount_space,"");
    if(mode == 0) printf("%s%*s ", cur->category, categories_space, "");
    printf("%s    ",(cur->type == 0 ? "expense":"income "));
    print_white_instead_of_(cur->note);

}

//把_取代
void print_white_instead_of_(char* originalData) {
    char printData[MAX_NOTE];
    strcpy(printData, originalData);
    int length = strlen(originalData);
    for (int i = 0; i < length; i++) {
        if (printData[i] == '_') {
            printData[i] = ' ';
        }
    }
    printf("%s\n",printData);
}

//計算位數
int count_digits(int num){
    if(num == 0) return 1;
    int count = 0;
    while(num != 0){
        num /= 10;
        count++;
    }
    return count;
}

//比較
int compare(Record* a, Record* b, int sort_by, int sort_order) {
    int result = 0;

    // 根據排序方式進行比較
    switch (sort_by) {
        case 1:  // 按日期排序
            
            if (a->time.year != b->time.year){
                result = a->time.year - b->time.year;
            }else if(a->time.month != b->time.month){ 
                result = a->time.month - b->time.month;
            }else if(a->time.day != b->time.day){
                result = a->time.day - b->time.day;
            }     
            break;
        case 2:  // 按金額排序
            if (a->amount != b->amount) result = (a->amount > b->amount) ? 1 : -1;
            break;
    }
    
    // 根據排序順序進行調整
    if (sort_order == 2) {
        result = -result;
    }
    return result;
}

// 按照日期先後順序排序
void sort(Record** arr, int n, int sort_by, int sort_order){
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            Record* a = arr[i];
            Record* b = arr[j];
            if (compare(arr[i], arr[j], sort_by, sort_order) > 0){
                arr[i] = b;
                arr[j] = a;
            }
        }
    }
}

Record** record_to_array(Record* head, int* data_num) {
    // 無資料
    if (head == NULL) {
        return NULL;
    }

    Record** arr = NULL;
    Record* p = head;
    *data_num = 0;

    while (p != NULL) {
        // 動態分配更多的記憶體來存儲節點地址
        arr = (Record**)realloc(arr, (*data_num + 1) * sizeof(Record*));
        arr[*data_num] = p;
        p = p->next;
        (*data_num)++;
    }

    return arr;
}

void delete_from_show(Record* target){
    Record* p = head;
    Record* pre = NULL;
    while (p != NULL) {
        if (p == target){
            if (pre == NULL) {
                head = p->next;
            }
            else {
                pre->next = p->next;
            }

            Edge* e = p->first_edge;
            while (e != NULL) {
                Edge* tmp = e;
                e = e->next_edge;
                free(tmp);
            }

            free(p);
            printf("The record has been deleted!\n");
            return;
        }
        pre = p;
        p = p->next;
    }
}