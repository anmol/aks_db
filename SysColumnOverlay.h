/* 
 * File:   SysColumnOverlay.h
 * Author: anmol
 *
 * Created on 19 November, 2010, 11:35 PM
 */

#ifndef SYSCOLUMNOVERLAY_H
#define	SYSCOLUMNOVERLAY_H
#include "db.h"
class SysColumnOverlay {
public:
    genpage *sysColumnPage;


    long CreateSyscolumnPage(genpage *newSysColumnPage);
    long AddSysColumnEntry();
    long DeleteSysColumnEntry();
    void ShowError();
    


};


#endif	/* SYSCOLUMNOVERLAY_H */

