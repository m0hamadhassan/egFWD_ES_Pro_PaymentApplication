#include<stdio.h>
#include"app.h"
void main()
{
	static char choice[1]="1";
	printf("###############################################\n");
	printf("################ W E L C O M E ################\n");
	printf("###############################################\n");
	printf("########### [1] : Make Transaction ############\n");
	printf("######### [2] : View all Transactions #########\n");
	printf("###############################################\n");
	while (1) 
	{
		printf("choice >: ");
		gets(choice);
		switch (choice[0])
		{
		case '1':
			appStart();
			break;
		case '2': 
			listSavedTransactions();
			break;
		}
	}
}