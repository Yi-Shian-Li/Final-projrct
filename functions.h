/**********************************************************
與輸入相關的小function      
enter_num: 確保輸入的是數字，如果輸入的是字母會要求重新輸入
enter_num_lim : 輸入一個給定的範圍 (min max)，如果不在範圍內會要求重新輸入
enter_any_num : 輸入一個數字來繼程式，用來查看訊息。
 **********************************************************/
int enter_num();
int enter_num_lim(int min, int max);
void press_any_key();

/**********************************************************
與資料相關的function
enter_spending_type:收支
enter_date: 日期
enter_amount: 金額
enter_categories: 類別(回傳類別編號)
enter_note: 註解
enter_one_of_data:判斷要使用者輸入哪個資料 i=(0:收支 1:日期 2:金額 3:類別 4:註解)
print_data: 把資料列印到畫面 (mode!=0時，不列印類別)
**********************************************************/
int enter_spending_type();
void enter_date(Record* new_record);
float enter_amount();
int enter_categories();
void enter_note(Record* new_record);
void enter_one_of_data(int i, Record* new_record);
void print_data(Record* cur, int mode);

/**********************************************************
會用在列印資料的function
print_white_instead_of_: 把note的底線換成空白輸出
count_digits: 計算位數
 **********************************************************/
void print_white_instead_of_(char* originalData);
int count_digits(int num);

/**********************************************************
整理資料的funtion
compare: 比較資料
sort: 整理 (insertion sort)
 **********************************************************/
int compare(Record* a, Record* b, int sort_by, int sort_order);
void sort(Record** arr, int n, int sort_by, int sort_order);

/**********************************************************
其他
Record** record_to_array: 把linked list的資料地址放進array
delete_from_show: 從traverse中刪除資料
 **********************************************************/
Record** record_to_array(Record* head, int* data_num);
void delete_from_show(Record* target);
