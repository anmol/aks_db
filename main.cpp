/* 
 * File:   main.cpp
 * Author: anmol
 *
 * Created on 26 October, 2010, 4:03 PM
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "db.h"
using namespace std;

//int Verbose_Flag;
//buffer_manager buffer1;
Database db;

void Clear_Options()
{
	Verbose_Flag = FRSET;
}

void Process_Options(int argc,char *argv[])
{
	int i;
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			switch (toupper(argv[i][1]))
			{
				case 'V':
					Verbose_Flag = FSET;
					break;

				default:
					printf("\n Unknown Option ");
					printf("\n");
					exit(ERROR);
			}
		}
		i++;
	}
}
int Print_Gui_Options()
{
        int get_opt;

        printf("\n\n\t Buffer Manager Testing Module \n");
        printf("\t ----------------------------- \n");
        printf("\n\n");
        printf("\t List of Options: \n");
        printf("\t 1. Create DB: \n");
        printf("\t 2. Delete DB: \n");
        printf("\t 3. Increment DB: \n");
        printf("\t 4. Read Page: \n");
        printf("\t 5. Write Page: \n");
        printf("\t 6. Show Frame: \n");
        printf("\t 7. Show Frames: \n");
        printf("\t 8. Commit: \n");
        printf("\t 9. Commit All: \n");
        printf("\t 10. Release Buffer and Exit: \n");
        printf("\t 11. OpenDB: \n");
        printf("\t 12. Print DB Index: \n");
        printf("\t ----------------------------- \n");
        printf("\n\n\t Database Testing Module \n");
        printf("\t ----------------------------- \n");
        printf("\t 13. Create_DB: \n");
        printf("\t 14. Create_Table: \n");
        printf("\n\n");
        printf("Enter your option(1-13):: ");
        scanf("%d",&get_opt);
        return (get_opt);
}




	/* Main Function */

int main(int argc,char *argv[])
{
        Clear_Options();

        // Get choice option for testing GUI
        int opt,i;
        char aks_db_name[MAX_FILE_NAME];
        long numpages, status, initsize;
        // Process the command prompt options
        Process_Options(argc,argv);

        // Give opt some high value to exit
        opt=20;

        buffer1.PrintVerbose("MAIN:: The program is in verbose mode");

        printf("\n\t\tBUFFER MANAGER");
        printf("\n\t\t--------------\n");
        printf("Size for the buffer Manager(in KB): ");
        scanf("%ld",&initsize);
        Buffer_Pool::InitBuffer(initsize);
        //buffer1.InitBuffer(initsize);
        strcpy(Current_Open_DB_Name, "\0");

        do {

                opt = Print_Gui_Options();
                switch (opt){

                        // Create DB
                        case 1:
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the new database(max 16chars): ");
                                scanf("%s",aks_db_name);
                                printf("\nEnter the number of DB pages: ");
                                scanf("%ld",&numpages);
                                buffer1.CreateDB (aks_db_name, numpages, PAGESIZE);
                                break;

                        // Delete DB
                        case 2:
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the new database(max 16chars): ");
                                scanf("%s",aks_db_name);
                                buffer1.DeleteDB (aks_db_name);
                                break;

                        // Increment DB
                        case 3:
                                printf("\nEnter the number of DB pages for increamenting: ");
                                scanf("%ld",&numpages);
                                buffer1.IncrementDB (numpages, PAGESIZE);
                                break;

                        // Read Page
                        case 4:
                                // use the current DB and page num will be stored in numpages
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the database to be read: ");
                                scanf("%s",aks_db_name);
                                printf("\nEnter the page number: ");
                                scanf("%ld",&numpages);
                                buffer1.ReadPage (aks_db_name, numpages);
                                break;

                                // Write Page
                        case 5:
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the database to be read: ");
                                scanf("%s",aks_db_name);
                                printf("\nEnter the page number: ");
                                scanf("%ld",&numpages);
                                buffer1.WritePage (aks_db_name, numpages);
                                break;

                        // Show Frame
                        case 6:
                                // Here numpages takes form of frame number
                                printf("\nEnter the frame number: ");
                                scanf("%ld",&numpages);
                                buffer1.ShowFrame(numpages);
                                break;

                        // Show Frames
                        case 7:
                                buffer1.ShowFrames();
                                break;

                        // Commit
                        case 8:
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the database to commit: ");
                                scanf("%s",aks_db_name);
                                printf("\nEnter the page number: ");
                                scanf("%ld",&numpages);
                                buffer1.Commit(aks_db_name, numpages);
                                break;

                        // Commit All
                        case 9:
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the database to commit: ");
                                scanf("%s",aks_db_name);
                                buffer1.CommitAll(aks_db_name);
                                break;

						// Release Buffer and Exit
                        case 10:
                                Buffer_Pool::ReleaseBuffer();
                                break;

                        // Open the DB
                        case 11:
                                buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the database to open: ");
                                scanf("%s",aks_db_name);
                                status = buffer1.OpenDB (aks_db_name);
                                if (status==ERROR)
                                        printf("\nError has occured from OpenDB");

                                break;

                        //Print all the entries in Db Handler
                        case 12:
                                if (curDbOpen == 0)
                                        printf("\nThe DB Table Index is Empty");
                                else
                                {
                                        printf("\n----------Printing DB Handler entries--------------");
                                        for (i=0;i<curDbOpen;i++)
                                        {
                                                printf("\nIndex: %d",i+1);
                                                printf("\nDb Name: %s",db_handle[i]._dbname);
                                                printf("\nDb Index: %ld",db_handle[i]._db_index);
                                                printf("\n\n");
                                        }
                                }
                                break;

                        case 13:

								buffer1.Reset_String(aks_db_name,MAX_FILE_NAME);
                                printf("\nEnter the name for the new database(max 16chars): ");
                                scanf("%s",aks_db_name);
                                printf("\nEnter the number of DB pages: ");
                                scanf("%ld",&numpages);
                                db.Create_DB (aks_db_name, numpages, PAGESIZE);
                                break;
						
                        case 14:

				mega_struct mega;
				mega.NumTable = 1;
				char *tableName;
				printf("\nEnter the name for the database ");
                                scanf("%s",aks_db_name);
                                printf("\nEnter the name for the table ");
                                scanf("%s",tableName);
                                strcpy(mega.Table[1],tableName);
                                printf("\nEnter the column name and type for the database ");
                                scanf("%s",aks_db_name);
                                db.Create_Table(aks_db_name, &mega);

                        // Unknown Option
                        default:
                                printf("\tERROR:: Unknown Option\n");

							}
						}while(opt !=10);

	//buffer_manager buffer;

	//char name[] = "anmol";
	//buffer1.InitBuffer(40960);
	//db.Create_DB(name,10,PAGESIZE);
	//buffer1.ReleaseBuffer();
	return 0;
}


