//DPPageOverlay.cpp

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>

using namespace std;

#include "globals.h"
#include "db.h"
#include "buffer_manager.h"
#include "DPPageOverlay.h"

void DPPageOverlay::DPPageOverlay(genpage* pg){
    if(pg->_priority == DP_PRIORITY){
        dpPage = pg;
    }
    else
        CreateDPPage(pg);

}

int DPPageOverlay::CreateDPPage(genpage *newDPPage){
    dpPage = newDPPage;
    dpPage->_priority = DP_PRIORITY;
    dp_page *dp;
    de_struct *de;
    dp = (dp_page *)dpPage->_data;
    dp->DE_number = 0;
    dp->max_TFS_withinTheDP = PG_DATASIZE;
    de = (de_struct *)((dpPage->_data) + sizeof(dp_page));

    for(long i=(PG_DATASIZE - sizeof(dp_page)/sizeof(de_struct)) ; i > 0 ; i--)
    {
        de->page_TFS = PG_DATASIZE;
        de->page_num = -1;
        de++;
    }

    return 0;

}
long DPPageOverlay::getDPHeaderDECount(){
    de_struct *de;
    long count;
    de = (de_struct *)((dpPage->_data) + sizeof(dp_page));
    for(long i=(PG_DATASIZE - sizeof(dp_page)/sizeof(de_struct)) ; i > 0 ; i--)
    {
        if(de->page_num != -1){
            count++;
        }
    }
    return count;

}
long DPPageOverlay::getMaxTFSwithinDE(){
    de_struct *de;
    de = (de_struct *)((dpPage->_data) + sizeof(dp_page));
    long max_tfs = de->page_TFS;
    for(long i=(PG_DATASIZE - sizeof(dp_page)/sizeof(de_struct)) ; i > 0 ; i--)
    {
        de++;
        if(de->page_TFS > max_tfs){
            max_tfs = de->page_TFS;
        }
        
    }
    return max_tfs;

}
void DPPageOverlay::setDPHeaderDECount(long count){

    dp_page *dp;
    dp = dpPage->_data;
    dp->DE_number = count;

}
void DPPageOverlay::setMaxTFSwithinDE(long max_tfs){

    dp_page *dp;
    dp = dpPage->_data;
    dp->max_TFS_withinTheDP = max_tfs;

}
de_struct* DPPageOverlay::DE_Search_by_TFS(long TFS){
    de_struct* de;
    while(1){
        de = (de_struct *)((dpPage->_data) + sizeof(dp_page));
        for(long i=(PG_DATASIZE - sizeof(dp_page)/sizeof(de_struct)) ; i > 0 ; i--)
        {
            if(de->page_TFS >= TFS){
                return de;
            }
        de++;

        }
        if(dpPage->_next_page == -1){
            break;
        }
        else{
            dpPage = dpPage->_next_page;
        }
    }
    if(dpPage->_next_page == -1){
        //allocate new dpPage and return first de
        genpage *dp_Pg;
        buffer_manager buffer1 = new buffer_manager();
        dp_Pg = buffer1.GetFreePage(Current_Open_DB_Name);
        CreateDPPage(dp_Pg);
        de = (de_struct *)((dpPage->_data) + sizeof(dp_page));
        return de;

    }


    
}
de_struct* DPPageOverlay::FindFreeDE(){
    de_struct *de;
    //dp_page *dp;
    long maxNumberofDE;
    int i;
    while(1){
        de = (de_struct *)((dpPage->_data) + sizeof(dp_page));
        for(i = 0 ; i< maxNumberofDE ; i++){
            if(de->page_num = -1){
                return de;
            }
            de++;
        }
        if (dpPage->_next_page == -1){
            break;
            

        }
        else{
            dpPage = dpPage->_next_page;
        }
    }
    
    //request for a new DPPage
            buffer_manager bm = new buffer_manager();
            genpage *pg;
            pg = bm.GetFreePage(Current_Open_DB_Name);
            CreateDPPage(pg);
            dpPage = pg;


}
int DPPageOverlay::DE_Add(de_struct *de, long DBPageNumber, long TFS){
    //de_struct *de;
    de->page_TFS = TFS;
    de->page_num = DBPageNumber;

}
de_struct* DPPageOverlay::GetLastUsedDE(){

}

int DPPageOverlay::DE_Delete(de_struct* de){

    de_struct* last_used_DE;
    //GET last DP Page from systable
    genpage *pg;
    DPPageOverlay lastDP = new DPPageOverlay(pg);
    
    
    last_used_DE=lastDP.GetLastUsedDE();

    de->page_num = last_used_DE->page_num;
    de->page_TFS = last_used_DE->page_TFS;

    //free last used de

    last_used_DE->page_num = -1;
    last_used_DE->page_TFS = PG_DATASIZE;

    return 0;

    
}


void DPPageOverlay::ShowError(){
    if(dpPage == NULL){
        printf("\n error: dpPage not set !! stop !!\n");
    }

}
