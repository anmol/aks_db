/* 
 * File:   SysTableOverlay.h
 * Author: anmol
 *
 * Created on 19 November, 2010, 3:04 AM
 */

#ifndef SYSTABLEOVERLAY_H
#define	SYSTABLEOVERLAY_H
#include "db.h"

class SysTableOverlay {
public:
    genpage *systabPage;
    SysTableOverlay();
    SysTableOverlay(genpage *pg);
    ~SysTableOverlay();
    long CreateSystablePage(genpage *newSysTablePage);
    long getTableIndex();
    long getNumberofTables();
    long setTableIndex();
    long setNumberofTables();
    long AddSysTableEntry(char *table_name);
    long FindSysTableEntry(char *table_name);
    long DeleteSysTableEntry(char *table_name);
    long GetFirstDPPageNumber(char *table_name);
    long GetLastDPPageNumber(char *table_name);
    void FillmegaStruct(mega_struct *mega);
    sys_table_entry* SearchTablebyName(char *table_name);
    void ShowError();




};

#endif	/* SYSTABLEOVERLAY_H */

