#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
  
// Structure of the system
struct client 
{
    char name[50];
    char laptop[100];
    char problem[100];
    long long int mob_no;    
};
struct client e;
  
// size of the structure
long int size = sizeof(e);
  
// In the start coordinates will be 0, 0
COORD cord = { 0, 0 };
  
// function to set the coordinates
void gotoxy(int x, int y)
{
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        cord);
}
  
FILE *fp, *ft;
  
// Function to add the records
void addrecord()
{
    system("cls");
    fseek(fp, 0, SEEK_END);
    char another = 'y';
  
    while (another == 'y') 
    {
        printf("\nEnter Name : ");
        scanf("%s",e.name);
  
        printf("\nEnter Laptop Details : ");
        scanf("%s", e.laptop);

        printf("\nEnter Defective Part : ");
        scanf("%s", e.problem);
  
        printf("\nEnter Mobile No : ");
        scanf("%lli", &e.mob_no);
  
        fwrite(&e, size, 1, fp);
  
        printf("\nWant to add another record (Y/N) : ");
        fflush(stdin);
  
        scanf("%c", &another);
    }
}
  
// Function to delete the records
void deleterecord()
{
    system("cls");
    char clientname[50];
    char another = 'y';
  
    while (another == 'y') 
    {
        printf("\nEnter client name to delete : ");
        scanf("%s", clientname);
  
        ft = fopen("temp.txt", "wb");
        rewind(fp);
  
        while (fread(&e, size,1, fp) == 1) 
        {
            if (strcmp(e.name , clientname) != 0)
                fwrite(&e, size, 1, ft);
        }
  
        fclose(fp);
        fclose(ft);
        remove("data.txt");
        rename("temp.txt", "data.txt");
        fp = fopen("data.txt", "rb+");
  
        printf("\nWant to delete another record (Y/N) :");
        fflush(stdin);
        another = getche();
    }
}
  
// Function to display the record
void displayrecord()
{
    system("cls");
  
    // sets pointer to start of the file
    rewind(fp);
  
    printf("\n========================="
           "==========================="
           "======");
    printf("\nNAME\t\tLAPTOP\t\tPROBLEM\t\tMOBILE NO\n",
            e.name, e.laptop, e.problem, e.mob_no);
    printf("==========================="
           "==========================="
           "====\n");
  
    while (fread(&e, size, 1, fp) == 1)
        printf("\n%s\t\t%s\t\t%s\t\t%lli", e.name, e.laptop, e.problem, e.mob_no);
  
    printf("\n\n\n"); 
    system("pause");
}
  
// Function to modify the record
void modifyrecord()
{
    system("cls");
    char clientname[50];
    char another = 'y';
  
    while (another == 'y') 
    {
        printf("\nEnter client name to modify : ");
        scanf("%s", clientname);
  
        rewind(fp);
  
        // While File is open
        while (fread(&e, size, 1, fp) == 1) 
        {
            // Compare the client name with ename
            if (strcmp(e.name, clientname) == 0) 
            {
                printf("\nEnter new Name : ");
                scanf("%s",e.name);
                printf("\nEnter new Laptop Details : ");
                scanf("%s", e.laptop);
                printf("\nEnter new Defective Part : ");
                scanf("%s",e.problem);
                printf("\nEnter new Mobile No : ");
                scanf("%lli", &e.mob_no);
  
                fseek(fp, -size, SEEK_CUR);
                fwrite(&e, size, 1, fp);
                break;
            }
        }
  
        // Ask for modifying another record
        printf("\nWant to modify another"
               " record (Y/N) :");
        fflush(stdin);
        scanf("%c", &another);
    }
}
  
// Driver code
int main()
{
    int choice;
  
    // opening the file
    fp = fopen("data.txt", "rb+");
  
    // showing error if file is
    // unable to open.
    if (fp == NULL) {
        fp = fopen("data.txt", "wb+");
        if (fp == NULL) {
            printf("\nCannot open file...");
            exit(1);
        }
    }
  
    system("Color 8F");
    printf("\n\n\n\n\t\t\t\t============="
           "============================="
           "===========");
    printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~");
    printf("\n\t\t\t\t==================="
           "============================="
           "=====");
    printf("\n\t\t\t\t  [|:::>:::>  "
           "CLIENT AND LAPTOP RECORD  <:::"
           "<:::|]\t");
    printf("\n\t\t\t\t==================="
           "============================="
           "=====");
    printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~");
    printf("\n\t\t\t\t====================="
           "================================\n");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t"
           "EXPERT: MISTER ABCDEFGHIJ\n\t\t\t\t\t\t\t\t\t\t\tSENIOR TECHNICIAN"
           "\n\t\t\t\t\t\t\t\t\t\tCONTACT NO. - 99999888888"
           "\n\n\t\t\t\t");
  
    system("pause");
  
    while (1) {
        // Clearing console and asking the user for input
        system("cls");
        gotoxy(30, 10);
        printf("\n1. ADD RECORD\n");
        gotoxy(30, 12);
        printf("\n2. DELETE RECORD\n");
        gotoxy(30, 14);
        printf("\n3. DISPLAY RECORDS\n");
        gotoxy(30, 16);
        printf("\n4. MODIFY RECORD\n");
        gotoxy(30, 18);
        printf("\n5. EXIT\n");
        gotoxy(30, 20);
        printf("\nENTER YOUR CHOICE...\n");
        fflush(stdin);
        scanf("%d", &choice);
  
        // Switch Case
        switch (choice) {
        case 1:
  
            // Add the records
            addrecord();
            break;
  
        case 2:
  
            // Delete the records
            deleterecord();
            break;
  
        case 3:
  
            // Display the records
            displayrecord();
            break;
  
        case 4:
  
            // Modify the records
            modifyrecord();
            break;
  
        case 5:
            fclose(fp);
            exit(0);
            break;
  
        default:
            printf("\nINVALID CHOICE...\n");
        }
    }
  
    return 0;
}