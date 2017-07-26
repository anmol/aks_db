/* 
 * File:   db.h
 * Author: anmol
 *
 * Created on 26 October, 2010, 4:04 PM
 */

#ifndef DB_H
#define	DB_H

#include "buffer_manager.h"
#include <time.h>
#include <vector>
#include <string>

#define TYPE_LENGTH 50
#define NAME_LENGTH 50
char Current_Open_DB_Name[50];

enum PagePriority {
    DB_HEADER_PRIORITY = 0,
    SYS_TABLE_PRIORITY,
    SYS_COLUMN_PRIORITY,
    SYS_INDEX_PRIORITY,
    DP_PRIORITY,
    DB_PAGE_PRIORITY,
    INDEX_PAGE_PRIORITY
};

typedef std::vector<std::string> Strings;

typedef struct Attribute
{
    char attr_name[NAME_LENGTH];
    int length;
    char type[TYPE_LENGTH];
    long ppos;
    void *value;
    long IsPrimary;
}Attribute;

typedef std::vector<Attribute> Vattribute;
typedef struct DatabaseHeaderPage
{
    char dbName[50];
    //int tableID;
    long Systable_Page_Number;
    long Filled_Page;
    long Partial_Filled_Page;
    long First_Free_Page;
    long First_DP_Page;

}db_header;

typedef struct TableHeaderPage
{
    long Table_ID;
    long DP_Page_Number;
    

}table_header;

//structure for the DP page
//will have the DE entries

typedef struct DP_structure{
    long next_DP;
    long DE_number;
    long max_TFS_withinTheDP;


}dp_page;

typedef struct dbPage_header
{
    
    long _TFS;
}dbPage_header;

//stored at the bottom of the db page
typedef struct SlotDirectory
{
    long SlotID;
    long SlotSize;

}SlotDirectory;

typedef struct SlotTail
{
    long CFS;
    long no_of_slots;
    
}slot_tail;

typedef struct DE_struct{
    long page_num;
    long page_TFS;

}de_struct;

typedef struct MegaStructure{
    int NumTable;
    //Strings Table;
    char *Table;
    long NumPattr;
    Vattribute Pattr;
    //Attribute *Pattr;
    long NumSattr;
    Vattribute Sattr;
    //Attribute *Sattr;
    char *Condition;
    char Relation[NAME_LENGTH];

}mega_struct;

typedef struct SysTableHeader{
    long tableindex;
    long numberofTables;
}SysTableHeader;

typedef struct SystemTableEntry{
    char tablename[NAME_LENGTH];
    long TID;
    //long table_index;
    //long tableHeader;
    long first_DP_Page_Number;
    long last_DP_Page_Number;
    int is_deleted; //1 for yes 0 for no

}sys_table_entry;

typedef struct SystemColumnHeader{
    long columnindex;
    long numberofColumns;

}SysColumnHeader;

typedef struct SystemColumnEntry{
    char column_name[NAME_LENGTH];
    long TID;
    long CID;
    //char *type;
    long length;
    long num_columns;
    char *column_type;
    long ppos;
    bool isNULL;
    char *DefaultValue;
    int is_deleted;

 }sys_column_entry;

typedef struct SystemIndex{

}sys_index;

class Database {
//private:

public:
    static long current_table_id;
    //sql functions
    int Use_DB(char *_db_Name);
    int Create_DB(char *_db_Name, long _db_pages, long _page_Size);
    int Create_Table(char *_db_Name, mega_struct *mega);
    int WriteTo_DB_Page(genpage *page);
    int Insert_Into_Table(mega_struct *mega);
    
    //page templates
    int Create_TableHeader_Page(genpage *page);
    int Create_DP_Page(genpage *page);
    int Create_DB_Page(genpage *page);



    //view functions
    int ShowDBPage();
    int ShowHeaderPage();
    int ShowSysTable();
    int ShowSysColumn();
    int ShowSysIndex();
    int ShowDPPage();
    
    

    //int Delete_DB(char *_db_Name);

};

long Database::current_table_id = 0;

class SysIndexOverlay {
public:
    genpage *systabPage;

};


class DBPageOverlay {

};



#endif	/* DB_H */

