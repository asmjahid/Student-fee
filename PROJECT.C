/*
Name : Student fee management
Created by : MD JAHIDUL ALAM MOJUMDER
ID- 1202310200419
Premier Univeristy, Chittagong
Language: C

*/
#include<stdio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
struct subscriber
{
    char stdnumber[15];
    char name[50];
    float amount;
} s;
void addrecords();
void listrecords();
void modifyrecords();
void deleterecords();
void searchrecords();
void payment();
char get;
int main()
{
    int password;
    int stdnumber;
    char choice;
    system("cls");
    system("color 57");
    printf("\n\t\tWELCOME TO THE STUDENT FEE MANAGEMENT SYSTEM");
    printf("\n\n\n\t\t\t\tPLEASE WAIT..........");
    Sleep(4000);
    system("cls");
    while (1)
    {
        system("cls");
        printf("\n \t\t\tENTER ANY OF BELOW\n\n\n \t\t\tA : for adding new records.\n \t\t\tL : for list of records");
        printf("\n \t\t\tM : for modifying records.\n \t\t\tP : for payment");
        printf("\n \t\t\tS : for searching records.");
        printf("\n \t\t\tD : for deleting records.\n \t\t\tE : for exit\n");
        printf("\n\t\t\t");
        choice=getchar();
        choice=toupper(choice);
        switch(choice)
        {
        case 'P':
            payment();
            break;
        case 'A':
            addrecords();
            break;
        case 'L':
            listrecords();
            break;
        case 'M':
            modifyrecords();
            break;
        case 'S':
            searchrecords();
            break;
        case 'D':
            deleterecords();
            break;
        case 'E':
            system("cls");
            Sleep(200);
            exit(0);
        default:
            system("cls");
            printf("Incorrect Input");
            printf("\nAny key to continue");
        }
    }
}
void addrecords()
{
    FILE *f;
    char test;
    f=fopen("manage.txt","ab+");
    if(f==0)
    {
        f=fopen("manage.txt","wb+");
        system("cls");
        printf("please wait while we configure your computer");
        printf("/npress any key to continue");
    }
    while(1)
    {
        system("cls");
        printf("\n Enter your student number:");
        scanf("%s",&s.stdnumber);
        printf("\n Enter name:");
        fflush(stdin);
        scanf("%[^\n]",&s.name);
        printf("\n Enter amount:");
        scanf("%s",&s.amount);
        fwrite(&s,sizeof(s),1,f);
        fflush(stdin);
        system("cls");
        printf("1 record successfully added");
        printf("\n\n\nPress 1 key to exit, any other key to add other record:");
        test=getchar();
        if(test == 1)
        exit(0);
    }
    fclose(f);
}
void listrecords()
{
    FILE *f;
    int i;
    if((f=fopen("manage.txt","rb"))==NULL)
        exit(0);
    system("cls");
    printf("Student Number\t\tName\t\t\tAmount\n");
    for(i=0; i<79; i++)
        printf("-");
    while(fread(&s,sizeof(s),1,f)==1)
    {
        printf("\n%-10s\t\t%-20s\t\tRs. %.2f /-",s.stdnumber,s.name,s.amount);
    }
    printf("\n");
    for(i=0; i<79; i++)
        printf("-");
    fclose(f);
}
void deleterecords()
{
    FILE *f,*t;
    int i=1;
    char stdnumber[20];
    if((t=fopen("manage.txt","w+"))==NULL)
        exit(0);
    if((f=fopen("manage.txt","rb"))==NULL)
        exit(0);
    system("cls");
    printf("Enter the student number to be deleted from the Database");
    fflush(stdin);
    scanf("%[^\n]",stdnumber);
    while(fread(&s,sizeof(s),1,f)==1)
    {
        if(strcmp(s.stdnumber,stdnumber)==0)
        {
            i=0;
            continue;
        }
        else
            fwrite(&s,sizeof(s),1,t);
    }
    if(i==1)
    {
        system("cls");
        printf("Student number \"%s\" not found",stdnumber);
        remove("manage.txt");
        rename("manage.txt","manage.txt");
        fclose(f);
        fclose(t);
        main();
    }
    remove("manage.txt");
    rename("manage.txt","manage.txt");
    system("cls");
    printf("The Number %s Successfully Deleted!!!!",stdnumber);
    fclose(f);
    fclose(t);
}
void searchrecords()
{
    FILE *f;
    char stdnumber[20];
    int flag=1;
    f=fopen("manage.txt","rb+");
    if(f==0)
        exit(0);
    fflush(stdin);
    system("cls");
    printf("Enter Student Number to search in our database");
    scanf("%s", stdnumber);
    while(fread(&s,sizeof(s),1,f)==1)
    {
        if(strcmp(s.stdnumber,stdnumber)==0)
        {
            system("cls");
            printf(" Record Found ");
            printf("\n\nStudent number: %s\nName: %s\nAmount: Rs.%0.2f\n",s.stdnumber,s.name,s.amount);
            flag=0;
            break;
        }
        else if(flag==1)
        {
            system("cls");
            printf("Requested Student Number Not found in our database");
        }
    }
    fclose(f);
}
void modifyrecords()
{
    FILE *f;
    char stdnumber[20];
    long int size=sizeof(s);
    if((f=fopen("manage.txt","rb+"))==NULL)
        exit(0);
    system("cls");
    printf("Enter student number of the subscriber to modify:");
    scanf("%[^\n]",stdnumber);
    fflush(stdin);
    while(fread(&s,sizeof(s),1,f)==1)
    {
        if(strcmp(s.stdnumber,stdnumber)==0)
        {
            system("cls");
            printf("\n Enter student number:");
            scanf("%s",&s.stdnumber);
            printf("\n Enter name: ");
            fflush(stdin);
            scanf("%[^\n]",&s.name);
            printf("\n Enter amount: ");
            scanf("%s",&s.amount);
            fseek(f,-size,SEEK_CUR);
            fwrite(&s,sizeof(s),1,f);
            break;
        }
    }
    fclose(f);
}
void payment()
{
    FILE *f;
    char stdnumber[20];
    long int size=sizeof(s);
    float amt;
    int i;
    if((f=fopen("manage.txt","rb+"))==NULL)
        exit(0);
    system("cls");
    printf("Enter student number for payment");
    scanf("%[^\n]",stdnumber);
    fflush(stdin);
    while(fread(&s,sizeof(s),1,f)==1)
    {
        if(strcmp(s.stdnumber,stdnumber)==0)
        {
            system("cls");
            printf("\n Phone No.: %s",s.stdnumber);
            printf("\n Name: %s",s.name);
            printf("\n Current amount: %s",s.amount);
            printf("\n");
            for(i=0; i<79; i++)
            printf("-");
            printf("\n\nEnter amount of payment :");
            fflush(stdin);
            scanf("%f",&amt);
            s.amount=s.amount-amt;
            fseek(f,-size,SEEK_CUR);
            fwrite(&s,sizeof(s),1,f);
            break;
        }
    }
    system("cls");
    printf("THANK YOU %s FOR YOUR TIMELY PAYMENTS",s.name);
    fclose(f);
}
