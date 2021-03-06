/* 
 * File:   buffer_manager.h
 * Author: anmol
 *
 * Created on 26 October, 2010, 4:59 PM
 */

#ifndef BUFFER_MANAGER_H
#define	BUFFER_MANAGER_H
#include <cstdio>
#include "globals.h"
#ifndef BMGLOBAL
#define EXTERN extern
#else
#define EXTERN
#endif



/* Structures */
//page
typedef struct general_page
{
	long _page_number;
	unsigned long _priority;
	long _next_page;
	long _TFS;
	char _data[1];
}genpage;

//frame
typedef struct frame
{
	long _frameNo;
	char _dirty;
	long _pincount;
	long _db_index;
	genpage _inpage;
}frame;

//
typedef struct db_handler
{
	char _dbname[MAX_FILE_NAME];
	long _db_index;
	FILE *_db_fp;
}db_handler;


EXTERN void* bufferPool;
EXTERN long curDbOpen;

EXTERN long BUFFER_SIZE;
EXTERN long BUFF_CURSOR;
EXTERN long FRAME_SIZE;
EXTERN long FRAMES_NUM;

EXTERN FILE *fp;

EXTERN char gdbname[MAX_FILE_NAME];
EXTERN db_handler db_handle[MAX_DB_INDEX];



class Buffer_Pool{
	//Buffer related
	public:
	 static void InitBuffer(long page_size);
	 static void ReleaseBuffer();
};



class buffer_manager {
//private:

public:

/*------------- Private Prototypes----------------- */
// void Process_Options(int argc, char *argv[]);
//void Clear_Options();
 char* concat (char *str1, char*str2);
char *AddExtension (char *dbname);

// Print the string only if the verbose is on
void PrintVerbose(const char *str);
// Reseting the string by memseting the size
void Reset_String(char *str,int size);
//For Testing GUI
//int Print_Gui_Options();
// For Functions under progress, delete when done
void FuncUnderProgress();

// void Compute_Params();
/*---------------Funtionalities Prototypes--------------- */

//DB related
 int CreateDB (char *dbname, long dbpages, long page_size);
 long OpenDB (char *dbname);
 void CloseDB (char *dbname);
 void DeleteDB (char *dbname);
 void IncrementDB (long page_number, long page_size);

//Page Related
 void ReadPage (char *dbname, long page_number);
 void WritePage (char *dbname, long page_number);
 void Commit (char *dbname, long page_number);
 void CommitAll (char *dbname);

//Frame Related
frame* GetFrame(char *dbname, long page_number);
frame* LoadFrame(long dbindex, long page_number);
void FlushFrame(frame *myframe);
long ExtractPageNo(frame *curFrame);
frame* GetFreeFrame();
//FOR TESTING
 void ShowFrame (long frame_number);
 void ShowFrames ();
 void PrintFrame(frame* curFrame);
/*---------------Buffer cursor prototypes--------------- */

frame* MoveNextFrame(frame* curFrame);
frame* MovePrevFrame(frame* curFrame);
frame* MoveToFrame(long frameno);
frame* FirstFrame();
frame* LastFrame();

/*---------------DB Handler prototypes--------------- */
long SearchDbHandler(char *dbname);

/*----------------------BlockStorage APIs-------------------*/
void ReadBlock(FILE *dbfp,long page_number,genpage* wpage);
void WriteBlock(FILE *dbfp,long page_number,genpage* rpage);

/*---------------------Buffer APIs----------------------------*/
genpage* BufferRead(char* dbname, long page_number);
genpage* BufferWrite(char* dbname, long page_number);
genpage* GetFreePage(char *dbname);
void ReleasePage(char* dbname, long page_number);

/*----------------------OTHER APIs---------------------*/

//void PrintVerbose(char *str);
//void Reset_String(char *str,int size);
//char* concat(char *str1, char*str2);
//char* AddExtension(char *dbname);
//void FuncUnderProgress();

};


#endif	/* BUFFER_MANAGER_H */

