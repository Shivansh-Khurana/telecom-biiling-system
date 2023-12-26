#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>
struct subscriber
{
char phonenumber[20];
char name[50];
float amount;
}s;
void addrecords();
void listrecords();
void modifyrecords();
void deleterecords();
void searchrecords();
void payment();
char get;
int main()
{	int phonenumber;
	char choice;



	system("cls");

	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t*************************************************************");
	printf("\n\t\t\t\t------WELCOME TO THE TELECOM BILLING MANAGEMENT SYSTEM------");
	printf("\n\t\t\t\t\t\tPRESS ANY KEY TO CONTINUE");
	printf("\n\t\t\t\t***************************************************************");
	Sleep(2000);
	getch();
    system("cls");
	while (1)
	{
		system("cls");
		printf("\n Enter\n A : for adding new records.\n L : for list of records");
		printf("\n M : for modifying records.\n P : for payment");
		printf("\n S : for searching records.");
		printf("\n D : for deleting records.\n E : for exit\n");
		choice=getche();
		choice=toupper(choice);
		switch(choice)
		{
			case 'P':
				payment();break;
			case 'A':
				addrecords();break;
			case 'L':
				listrecords();break;
			case 'M':
				modifyrecords();break;
			case 'S':
				searchrecords();break;
			case 'D':
				deleterecords();break;
			case 'E':
				system("cls");
				printf("\n\n\t\t\t\tTHANK YOU FOR USING OUR SERVICE");
				Sleep(2000);
				exit(0);
				break;
			default:
				system("cls");
				printf("Incorrect Input");
				printf("\nAny key to continue");
				getch();
		}
	}
}
void addrecords()
{
	FILE *f;
	char test;
	f=fopen("file.txt","ab+");
	if(f==0)
	{   f=fopen("file.txt","wb+");
		system("cls");
		printf("please wait while we configure your computer");
		printf("/npress any key to continue");
		getch();
	}
	while(1)
	{
		system("cls");
		printf("\n Enter phone number:");
		scanf("%s",&s.phonenumber);
		printf("\n Enter name:");
		fflush(stdin);
		scanf("%s",&s.name);
		printf("\n Enter amount:");
		scanf("%f",&s.amount);
		fwrite(&s,sizeof(s),1,f);
		fflush(stdin);
		system("cls");
		printf("1 record successfully added");
		printf("\n Press esc key to exit, any other key to add other record: ");
		test=getche();
		if(test==27)
			break;
	}
	fclose(f);
}
void listrecords()
{
	FILE *f;
	int i;
	if((f=fopen("file.txt","rb"))==NULL)
		exit(0);
	system("cls");
	printf("Phone Number\t\tUser Name\t\t\tAmount\n");
	for(i=0;i<79;i++)
		printf("-");
	while(fread(&s,sizeof(s),1,f)==1)
	{
		printf("\n%-10s\t\t%-20s\t\tRs. %.2f /-",s.phonenumber,s.name,s.amount);
	}
	printf("\n");
	for(i=0;i<79;i++)
		printf("-");

fclose(f);
getch();
}
void deleterecords()
{
	FILE *f,*t;
	char phonenumber[20];
	system("cls");
	f=fopen("file.txt","rb+");
	t=fopen("temp.txt","wb+");
	do{
	rewind(f);
	printf("\nEnter the phone number to be deleted from the Database: ");
	scanf("%s",phonenumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)!=0)
		{       	fwrite(&s,sizeof(s),1,t);

		}
		else
		printf("Record deleted successfully.");
	}

	fclose(f);
	fclose(t);
	remove("file.txt");
	rename("temp.txt","file.txt");

	f=fopen("file.txt","rb+");
	t=fopen("temp.txt","wb+");
    printf("\nDo you want to delete another record (y/n):");
	fflush(stdin);
	  }
    	while(getche()=='y'||getche()=='Y');
		fclose(f);
	getch();
	system("cls");
}
void searchrecords()
{
	FILE *f;
	char phonenumber[20];
	int flag=1;
	f=fopen("file.txt","rb+");
	if(f==0)
		exit(0);
	fflush(stdin);
	system("cls");
	printf("Enter Phone Number to search in our database: ");
	scanf("%s", phonenumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{	system("cls");
			printf(" Record Found ");
			printf("\n\nPhonenumber: %s\nName: %s\nAmount: Rs.%0.2f\n",s.phonenumber,s.name,s.amount);
			flag=0;
			break;
		}
		else if(flag==1)
		{	system("cls");
			printf("Requested Phone Number Not found in our database");
		}
	}
	getch();
	fclose(f);
}
void modifyrecords()
{
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	if((f=fopen("file.txt","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("Enter phone number of the subscriber to modify: ");
	scanf("%s",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			system("cls");
			printf("\n Enter phone number:");
			scanf("%s",&s.phonenumber);
			printf("\n Enter name: ");
			fflush(stdin);
			scanf("%s",&s.name);
			printf("\n Enter amount: ");
			scanf("%f",&s.amount);
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
	char phonenumber[20];
	long int size=sizeof(s);
	float amt;
	int i;
	int flag;
	if((f=fopen("file.txt","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("Enter phone number of the subscriber for payment: ");
	scanf("%s",phonenumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			system("cls");
			printf("\n Phone No.: %s",s.phonenumber);
			printf("\n Name: %s",s.name);
			printf("\n Current amount: %f",s.amount);
			printf("\n");
			for(i=0;i<79;i++)
				printf("-");
			printf("\n\nEnter amount of payment : ");
			fflush(stdin);
			scanf(" %f",&amt);
			s.amount=s.amount-amt;
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
		else if(flag==1)
		{	system("cls");
			printf("Requested Phone Number Not found in our database");
		}
	}
	system("cls");
	printf("THANK YOU %s FOR YOUR TIMELY PAYMENTS",s.name);
	getch();
	fclose(f);
}

