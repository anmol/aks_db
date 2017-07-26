//      db.cpp

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>

using namespace std;

#include "globals.h"
#include "db.h"
#include "buffer_manager.h"
#include "SysTableOverlay.h"
#include "SysColumnOverlay.h"
#define DB_HEADER_PAGE 1
#define SYS_TABLE_PAGE 2
#define SYS_COLUMN_PAGE 3
#define SYS_INDEX_PAGE 4
#define DB_HEADER_ID 0

//extern buffer_manager buffer1;



//buffer_manager buffer1;
/*
int Database::Create_DP_Page(){
    
}
*/

int Database::Create_DB(char *_db_Name,long _db_pages,long _page_size){

    buffer_manager buffer1 = new buffer_manager();
    int SuccessDB, SuccessReadPage;
    SuccessDB = buffer1.CreateDB (_db_Name, _db_pages, _page_size);
    printf("\nsuccessDB = %d\n",SuccessDB);
    genpage *pg;
    db_header *db;
    //sys_table *tb;
    //sys_column *cm;
   // sys_index *ix;


    if(!SuccessDB)
    {
         /*request next page for PAGE*/
        pg = buffer1.BufferWrite(_db_Name,DB_HEADER_PAGE);
        pg->_priority = DB_HEADER_PRIORITY;
        pg->_TFS= PG_DATASIZE - sizeof(db_header);
        db = (db_header *)pg->_data;
        strcpy(db->dbName, _db_Name);
        //db->tableID = DB_HEADER_ID;
        db->Filled_Page = -1;
        db->Partial_Filled_Page = -1;
        db->First_DP_Page = 5;
        db->First_Free_Page = 6;

	buffer1.Commit(_db_Name, DB_HEADER_PAGE);


        printf("\nsize of dbheader = %d\n",sizeof(db_header));
	printf("\nsize of systable = %d\n",sizeof(sys_table_entry));
	printf("\nsize of long = %d\n",sizeof(long));
	printf("\nI m here\n");

        /*request next page for SYS_TABLES*/
        pg = buffer1.BufferWrite(_db_Name, SYS_TABLE_PAGE);
        SysTableOverlay sysTableOverlayNavigator = new SysTableOverlay();
        sysTableOverlayNavigator.CreateSystablePage(pg);
/*
        pg->_priority = SYS_TABLE_PRIORITY;
       // pg->_TFS= PG_DATASIZE - sizeof(sys_table);
        //adding the tableindex

        tableindex = (long *)pg->_data;
        *tableindex = 0;
        //tableindex++;
        //sprintf(pg->_data, "%ld", *tableindex);
         pg->_TFS = PG_DATASIZE - sizeof(long);

        //adding the systable table to the systable
        tb  = (sys_table *)(tableindex+1);
        //tb = (sys_table *)pg->_data;
        strcpy(tb->tablename,"systable");
        tb->TID = 1;
        tb->DP_Page_Number = -1;
        tb++;
        (*tableindex)++;
        pg->_TFS = pg->_TFS - sizeof (sys_table);

        //adding sys_column table to the sys_table
        strcpy(tb->tablename,"syscolumn");
        tb->TID = 2;
        tb->DP_Page_Number = -1;
        tb++;
        (*tableindex)++;
        pg->_TFS = pg->_TFS - sizeof(sys_table);

        //adding sys_index table to the sys_table
        strcpy(tb->tablename,"sysindex");
        tb->TID = 3;
        tb->DP_Page_Number = -1;
        tb++;
        (*tableindex)++;
        pg->_TFS = pg->_TFS - sizeof(sys_table);
*/

        //commit systablepage
        buffer1.Commit(_db_Name, SYS_TABLE_PAGE);
	printf("\nI m here\n");



        /*request next page for SYS_COLUMN*/
        /* make entries for the columns of systable,sysindex and syscolumns */
        pg = buffer1.BufferWrite(_db_Name,SYS_COLUMN_PAGE);
        //pg->_priority = SYS_COLUMN_PRIORITY;

        buffer1.Commit(_db_Name, SYS_COLUMN_PAGE);

        /*request next page for SYS_TABLES*/


        pg = buffer1.BufferWrite(_db_Name,SYS_INDEX_PAGE);
        //pg->_priority = SYS_INDEX_PRIORITY;

	buffer1.Commit(_db_Name, SYS_INDEX_PAGE);





    }
    else
		printf("\n u r unlucky...some error occured");
}

/* printing functions */

int Database::ShowDBPage(){
}
int Database::ShowHeaderPage(){
}
int Database::ShowSysTable(){
}
int Database::ShowSysColumn(){
}
int Database::ShowSysIndex(){
}
int Database::ShowDPPage(){
}

/*
int Database::Create_TableHeader_Page(genpage *page, long table_id, long pageNumber){
    table_header *th;
    //th = (table_header *)(page + (PAGESIZE - PG_DATASIZE));
    th = (table_header *)(page->_data);
    th->DP_Page_Number = pageNumber;
    th->Table_ID = table_id;

}

*/
/*
int Database::Create_DP_Page(genpage *page){
dp_page *dp;
de_struct *de;
dp = (dp_page *)(page->_data);
dp->DE_number = 0;
//dp->max_TFS_withinTheDP = PG_DATASIZE - sizeof(dbPage_header) - sizeof(long) - sizeof(long);
dp->max_TFS_withinTheDP = PG_DATASIZE;
de = (de_struct *)((page->_data) + sizeof(dp_page));
for(long i=(PG_DATASIZE - sizeof(dp_page)/sizeof(de_struct));i>0;i--)
    {
        //de->page_TFS = PG_DATASIZE - sizeof(dbPage_header) - sizeof(long) - sizeof(long);
        de->page_TFS = PG_DATASIZE;
        de->page_num = -1;
        de++;
    }
}

int Database::Create_DB_Page(genpage *page){
    char *c;
    //dbPage_header *db;
    c = (char *)page;
    // go to the end of the page
    c = c + PAGESIZE;
    c = c - sizeof(slot_tail);
    slot_tail *l;
    l = (slot_tail *)c;
    l->no_of_slots = 0;//initially there are no slots
    l->CFS = PG_DATASIZE - (2*sizeof(long));
    //db = (dbPage_header *)page;

    // total - dbpage header - long to store no of slots - long to store CFS - slot entries for each slot
    //db->_TFS = PG_DATASIZE - sizeof(dbPage_header) - sizeof(long) - sizeof(long) - (2 * no_of_slots * sizeof(long));
    page->_TFS = PG_DATASIZE - (2 * sizeof(long));

}

int Database::WriteTo_DB_Page(genpage *page){

    //dummy
    char *c;
    slot_tail *t;
    t = (slot_tail)(c + PAGESIZE - sizeof(slot_tail));
    long r = rand(t->CFS);
    c = (char *)page->_data;
    for (int i = 0;i< r;i++){
        *c = 'a';
    }

}

*/
long Database::Use_DB(char *_db_Name){
    buffer_manager buffer1 = new buffer_manager();

    int i = buffer1.OpenDB(_db_Name);
    if(i != ERROR)
    {
        strcpy(Current_Open_DB_Name, _db_Name);
    }
    return i;
}
/*
int Database::Insert_Into_Table(mega_struct *mega){
    genpage *dbh_pg, *sys_header_pg, *DP_Page;
    db_header *dbh;
    table_header *tbh;
    dp_page *dph;
    de_struct *de;
    //search in systable for tablename
    //get dbheader

    dbh_pg = buffer1.ReadPage(Current_Open_DB_Name,DB_HEADER_PAGE);
    dbh = dbh_pg->_data;
    long Systable_Page_Number = dbh->Systable_Page_Number;

    //get tableheader ofsystable
    sys_header_pg = buffer1.ReadPage(Current_Open_DB_Name, Systable_Page_Number);

    tbh = sys_header_pg->_data;

    //getting dppage of the systable
    DP_Page = buffer1.ReadPage(Current_Open_DB_Name, tbh->DP_Page_Number);
    while(DP_Page->_next_page != -1){
        
        dph = DP_Page->_data;
        
        de =(de_struct *)(dph + 1);
    }
    char *tablename;
    strcpy(tablename);

}
 */



int Database::Create_Table(char *_db_Name, mega_struct *mega){
    char *is_null = "\0";

    buffer_manager bm = new buffer_manager();

    if(!strcmp(Current_Open_DB_Name, is_null))
     {
        printf("\nNo Database is currently in use\n");
        return ERROR;
     }
     else
     {
     //request Page#1 i.e., systable page from buffer
        genpage *pg_sys = bm.BufferWrite(_db_Name,1);
        SysTableOverlay systab = new SysTableOverlay(pg_sys);
        systab.AddSysTableEntry();

        //request Page#2 i.e., syscolumn page from buffer
        genpage *pg_col = bm.BufferWrite(_db_Name,2);
        SysColumnOverlay syscol = new SysColumnOverlay();
        syscol.AddSysColumnEntry();
        //systab.GetLastDPPageNumber(char *table_name);

     }

     }