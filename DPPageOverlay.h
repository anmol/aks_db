/* 
 * File:   DPPageOverlay.h
 * Author: anmol
 *
 * Created on 19 November, 2010, 11:49 AM
 */

#ifndef DPPAGEOVERLAY_H
#define	DPPAGEOVERLAY_H
#include "db.h"

class DPPageOverlay {
public:
    genpage *dpPage;
    DPPageOverlay();
    DPPageOverlay(genpage* pg);


    int CreateDPPage(genpage *newDPPage);
    long getDPHeaderDECount();
    long getMaxTFSwithinDE();
    int setDPHeaderDECount();
    int setMaxTFSwithinDE();
    de_struct* FindFreeDE();
    de_struct* DE_Search_by_TFS(long TFS);
    int DE_Update();
    de_struct* GetLastUsedDE();
    int DE_Add(de_struct *de, long DBPageNumber, long TFS);
    int DE_Delete(de_struct *de);
    int ShowError();


~DPPageOverlay();

};

#endif	/* DPPAGEOVERLAY_H */

