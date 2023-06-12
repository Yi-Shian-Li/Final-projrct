/**********************************************************
delete_record: 根據key word刪除資料，可以用在大量刪除類似的資料
add_to_deleted_records: 暫時把刪除的資料放進linked list，以便列印
free_deleted_records: 刪除暫時的資料
 **********************************************************/
void delete_record();
void add_to_deleted_records(Record* record);
void free_deleted_records();