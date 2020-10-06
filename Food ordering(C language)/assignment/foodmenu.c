#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>
#pragma warning(disable:4996)

typedef struct
{
	char menuID[10];
	char name[50];
	char description[200];
	double price;
}menu;

void addRecord();
void displayRecord();
void searchRecord();
void deleteRecord();
void modifyRecord();

void modifyRecord()
{
	system("cls");
	char ans, cont, code[10], updateName[30], updateDescription[200];
	int i = 0, pcount, modiCount = 0, found = 0;
	double updatePrice;
	menu p[20];
	FILE *fp;
	fp = fopen("menu.dat", "rb");

	while (fread(&p[i], sizeof(menu), 1, fp))
	{
		i++;
	}
	pcount = i;
	fclose(fp);

	do {
		printf("Enter product code of the product to be modified : ");
		rewind(stdin);
		scanf("%s", &code);
		found = 0;
		for (i = 0; i < pcount; i++)
		{
			if (strcmp(code, p[i].menuID) == 0)
			{
				
				printf("Before update details\n");
				printf("FoodID\t    Name\t price\t\tdescription\n");
				printf("================================================================================");
				found = 1;
				printf("%-10s%-15s%-10.2lf%15s\n", p[i].menuID, p[i].name, p[i].price, p[i].description);

				printf("Enter new name : ");
				rewind(stdin);
				scanf("%[^\n]", &updateName);
				printf("Enter new price : ");
				rewind(stdin);
				scanf("%lf", &updatePrice);
				printf("Enter new description : ");
				rewind(stdin);
				scanf("%[^\n]", &updateDescription);


				printf("\nConfirm to update?(Y/N)");
				rewind(stdin);
				scanf("%c", &ans);

				if (toupper(ans) == 'Y')
				{
					p[i].price = updatePrice;
					strcpy(p[i].name, updateName);
					strcpy(p[i].description, updateDescription);
					modiCount++;
				}

				printf("Any more records to modify?(Y/N)");
				rewind(stdin);
				scanf("%c", &cont);
			}
		}
		if (found == 0)
		{
			printf("No record found with code %s!!!\n", code);
		}

	} while (toupper(cont) == 'Y');

	fp = fopen("menu.dat", "wb");

	for (i = 0; i < pcount; i++)
	{
		fwrite(&p[i], sizeof(menu), 1, fp);
	}
	fclose(fp);
	printf("\n%d records modified.\n", modiCount);
}



void deleteRecord()
{
	char ans, ID[10];
	int  found;
	menu prod;
	FILE *fp, *save;
	system("cls");
	fp = fopen("menu.dat", "rb");
	save = fopen("save.dat", "wb");

	printf("Please enter the ID of the food to delete : ");
	rewind(stdin);
	scanf("%[^\n]", &ID);

	printf("FoodID\t    Name\t price\t\tdescription\n");
	printf("================================================================================");
	while (fread(&prod, sizeof(menu), 1, fp))
	{
		if (strcmp(ID, prod.menuID) == 0)
		{
			printf("%-10s%-15s%-10.2lf%15s\n", prod.menuID, prod.name, prod.price, prod.description);
			found = 1;
		}
		else
		{
			fwrite(&prod, sizeof(menu), 1, save);
		}
	}
	fclose(fp);
	fclose(save);
	if (found == 1)
	{
		printf("\nAre you confirm you want to delete? (Y/N) :");
		rewind(stdin);
		scanf("%c", &ans);
		if (toupper(ans) == 'Y')
		{
			system("del menu.dat");
			system("rename save.dat menu.dat");
			printf("deletion success!\n");
		}
		if (toupper(ans) != 'Y')
		{
			system("del save.dat");
		}
	}
	if (found != 1)
	{
		printf("no such record found!!!\n\n");
	}
}

void searchRecord()
{
	char ans, cont, searchID[10];
	int i = 0, count, found;
	menu p[20];
	FILE *fp;
	fp = fopen("menu.dat", "rb");

	system("cls");
	while (fread(&p[i], sizeof(menu), 1, fp))
	{
		i++;
	}
	count = i;
	fclose(fp);

	do {
		printf("Enter the Food ID to search : ");
		rewind(stdin);
		scanf("%s", &searchID);
		found = 0;
		for (i = 0; i < count; i++)
		{
			if (strcmp(searchID, p[i].menuID) == 0)
			{
				found = 1;
				printf("FoodID\t  Name\t\t price\t\tdescription\n");
				printf("================================================================================");
				printf("%-10s%-15s%-10.2lf%15s\n", p[i].menuID, p[i].name, p[i].price, p[i].description);
			}
		}
		if (found != 1)
		{
			printf("\nNo record found with code %s\n", searchID);
		}
		printf("\ndo you want to search anymore ID?(Y/N)");
		rewind(stdin);
		scanf("%c", &cont);
	} while (toupper(cont) == 'Y');
}

void addRecord()
{
	system("cls");
	menu prod;
	FILE *fp;
	fp = fopen("menu.dat", "ab");
	char choice;
	do
	{
		printf("Enter Food Menu ID : ");
		scanf("%s", &prod.menuID);
		printf("\nEnter the name of the Food : ");
		rewind(stdin);
		scanf("%[^\n]", &prod.name);
		printf("\nEnter the description for the food : ");
		rewind(stdin);
		scanf("%[^\n]", &prod.description);
		printf("\nEnter the price for the food : ");
		rewind(stdin);
		scanf("%lf", &prod.price);
		fwrite(&prod, sizeof(menu), 1, fp);
		printf("\nDo you have anymore to add?(Y/N)");
		rewind(stdin);
		scanf("%c", &choice);
	} while (toupper(choice) == 'Y');
	fclose(fp);
}

void displayRecord()
{
	menu prod;
	FILE *fp;
	fp = fopen("menu.dat", "rb");
	printf("FoodID\t    Name\t price\t\tdescription\n");
	printf("================================================================================");

	while (fread(&prod, sizeof(menu), 1, fp))
	{
		printf("%-10s%-15s%-10.2lf%15s\n\n", prod.menuID, prod.name, prod.price, prod.description);
	}
	fclose(fp);
}

void main()
{
	int option;
	system("color F0");
	do {
		printf("\n================================");
		printf("\n              Menu\n");
		printf("================================\n");
		printf("1.Add Record\n");
		printf("2.Display Record\n");
		printf("3.Search Record\n");
		printf("4.Delete Record\n");
		printf("5.Modify Record\n");
		printf("6.Exit\n");
		printf("\nEnter your option: ");
		scanf("%d", &option);
		
		choice(option);

	} while (option != 6);
	system("pause");
}

choice(char option)
{
	switch (option)
	{
	case 1:addRecord();
		break;
	case 2:displayRecord();
		break;
	case 3:searchRecord();
		break;
	case 4:deleteRecord();
		break;
	case 5:modifyRecord();
		break;
	case 6:exit(-1);
	default:
		printf("Invalid option!\n");
		printf("Please key in a valid option\n");
	}
}