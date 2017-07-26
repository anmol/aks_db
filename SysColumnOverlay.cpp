#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>

using namespace std;

#include "globals.h"
#include "db.h"
#include "buffer_manager.h"
#include "SysColumnOverlay.h"
#include "DPPageOverlay.h"
#define COL_DP 2


//this will add a new dbpage to the syscolumn DPs
long SysColumnOverlay::CreateSyscolumnPage(genpage *newSysColumnPage){
    //this is actually a DB Page which is created by DBPage Overlay
    
    sysColumnPage = newSysColumnPage;
    sysColumnPage->_priority = SYS_COLUMN_PRIORITY;
    //get syscolumn DPPAGE i.e, page#2
    buffer_manager bm = new buffer_manager();
    genpage *pg = bm.WritePage(Current_Open_DB_Name, COL_DP);
    DPPageOverlay dp = new DPPageOverlay();
    dp.dpPage = pg;
    de_struct *de = dp.FindFreeDE();


    
    //add DBPAGE details to DE
    long DBPageNumber = sysColumnPage->_page_number;
    long TFS = sysColumnPage->_TFS;




    //adding DE to the DP page
    dp.DE_Add(de, DBPageNumber, TFS);
     
    
}



long SysColumnOverlay::AddSysColumnEntry(){
    if(sysColumnPage == 0){
        ShowError();
        return -1;
    }
    SysColumnHeader *col;
    col = (SysColumnHeader *)sysColumnPage->_data;
    if(col->numberofColumns == ){
        //goto next syscolumn page
        //create new column if it doesnt exist
        

    }

    


}


long SysColumnOverlay::DeleteSysColumnEntry(){
    if(sysColumnPage == 0){
        ShowError();
        return -1;
    }
    
}

void ShowError(){
    printf("\n the syscolumn page is not initialized..stop!!\n");
}
