//SysTableOverlay.cpp
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>

using namespace std;

#include "globals.h"
#include "db.h"
#include "buffer_manager.h"
#include "SysTableOverlay.h"
SysTableOverlay::SysTableOverlay(genpage* pg){
    if(pg->_priority = SYS_TABLE_PRIORITY){
    systabPage = pg;
    }
    else
        CreateSystablePage(pg);
}
long SysTableOverlay::CreateSystablePage(genpage* newSysTablePage){
    //buffer_manager bm = new buffer_manager();

    //genpage *newSysTablePage = bm.GetFreePage(Current_Open_DB_Name);

    SysTableHeader *sth;
    //sys_table_entry *st;
    systabPage = newSysTablePage;
    systabPage->_priority = SYS_TABLE_PRIORITY;
    
    sth = systabPage->_data;
    sth->numberofTables = 0;
    sth->tableindex = 0;
    /*st = (sys_table_entry *)(sth + 1);
    strcpy(st->tablename,"sys_table");
    st->TID = 1;
    st->DP_Page_Number = -1;
    st->is_deleted = 1;
    systabPage->_TFS = PG_DATASIZE - sizeof(SysTableHeader) - sizeof(sys_table_entry);
    st++;

    //adding syscolumn to systable
    strcpy(st->tablename,"sys_column");
    st->TID = 2;
    st->DP_Page_Number = -1;
    st->is_deleted = 1;
    systabPage->_TFS = systabPage->_TFS - sizeof(sys_table_entry);
    st++;

    //adding sysindex to systable
    strcpy(st->tablename,"sys_index");
    st->TID = 3;
    st->DP_Page_Number = -1;
    st->is_deleted = 1;
    systabPage->_TFS = systabPage->_TFS - sizeof(sys_table_entry);
    st++;

*/


}
long SysTableOverlay::getNumberofTables(){

}
long SysTableOverlay::getTableIndex(){

}
long SysTableOverlay::setNumberofTables(){

}
long SysTableOverlay::setTableIndex(){
    
}
long SysTableOverlay::AddSysTableEntry(char *table_name){


    //add systable entry to the systable dbpage
    /*
    SysTableHeader *sth;
    sys_table_entry *st;

    sth = systabPage->_data;
    sth->numberofTables = sth->numberofTables + 1;
    sth->tableindex = sth->tableindex + 1;
    st = (sys_table_entry *)(sth + 1);
    strcpy(st->tablename,"sys_table");
    st->TID = sth->tableindex;
    st->first_DP_Page_Number = -1;
    st->last_DP_Page_Number = -1;

*/
    
}
long SysTableOverlay::FindSysTableEntry(char *table_name){

}
long SysTableOverlay::DeleteSysTableEntry(char *table_name){


}
sys_table_entry* SysTableOverlay::SearchTablebyName(char *tableName){
    sys_table_entry *se;
    while(1){
    se = (sys_table_entry *)(systabPage->_data + sizeof(SysTableHeader));
    
    }

}
void SysTableOverlay::FillmegaStruct(mega_struct *mega){

}
