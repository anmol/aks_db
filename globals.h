/* 
 * File:   globals.h
 * Author: anmol
 *
 * Created on 26 October, 2010, 4:58 PM
 */

#ifndef GLOBALS_H
#define	GLOBALS_H


#ifndef GLOBAL
#define EXTERN extern
#else
#define EXTERN
#endif


#define ERROR (-1)
#define KB 1024 //This will be multiplied with the page size in KB to get the actual size
#define FSET 1  // Flag Set
#define FRSET 0 // Flag Reset
#define PAGESIZE 8192 // 8 KB page size
#define PG_DATASIZE 8176// PAGESIZE - (header size of the page) = PAGESIZE - 4*4
#define MAX_FILE_NAME 16 // Maximum chars in a filename
#define MAX_FULL_PATH 30
#define MAX_DB_INDEX 10
#define HEADER_PAGE 1
#define EMPTY -1
#define DBPATH "./"

EXTERN int Verbose_Flag;


#endif	/* GLOBALS_H */

