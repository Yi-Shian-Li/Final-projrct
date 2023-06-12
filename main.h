#define MAX_RECORD_NUM 999
#define MAX_CATEGORY_NUM 30
#define MAX_CATEGORY_NAME 25
#define MAX_AMOUNT 2147483647
#define MAX_NOTE 51

//type定義
typedef struct Category{
    char name[MAX_CATEGORY_NAME];
    float total_expense;
    float total_income;
}Category;
struct Edge;

typedef struct Record {
    int type;           //支出0 收入1
    struct {
        int year;
        int month;
        int day;
    } time;
    float amount;
    char category[MAX_CATEGORY_NAME];
    char note[MAX_NOTE];
    struct Edge* first_edge;
    struct Record* next;
} Record;

typedef struct Edge {
    struct Record* dest;
    struct Edge* next_edge;
} Edge;

//functions

void help();
void setting();
void leave();

