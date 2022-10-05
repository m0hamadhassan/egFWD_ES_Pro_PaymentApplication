#include<stdio.h>
#include<string.h>
#include"card.h"
void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	int i;
	
	EN_cardError_t ErrorStatus = CARD_OK;

	char buffer[30];

	printf("Enter cardholder's name : ");

	gets(buffer);

	if ((buffer==NULL) || (strlen(buffer) < 20) || (strlen(buffer) > 24) )
	{
		ErrorStatus = WRONG_NAME;
	}
	else
	{
		for (i = 0; i <= strlen(buffer) ; i++)
		{
			cardData->cardHolderName[i] = buffer[i];
		}
	}
	return ErrorStatus;
}
void getCardHolderNameTest(void)
{
	ST_cardData_t cardData;
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: getCardHolderName\n");
	printf("Test Case 1: less than 20 characters \n");
	printf("Input Data: mohamad \n");
	printf("Expected Result: 1 (WRONG_NAME) \n");
	printf("Actual Result: %d \n", getCardHolderName(&cardData) );
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: getCardHolderName\n");
	printf("Test Case 2: more than 20 characters \n");
	printf("Input Data: mohamad hassan kamal mohamad \n");
	printf("Expected Result: 1 (WRONG_NAME) \n");
	printf("Actual Result: %d \n", getCardHolderName(&cardData));
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: getCardHolderName\n");
	printf("Test Case 3: not less than 20 characters or more than 24 characters \n");
	printf("Input Data: mohamad hassan kamal \n");
	printf("Expected Result: 0 (CARD_OK) \n");
	printf("Actual Result: %d \n", getCardHolderName(&cardData));

}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	char buffer[10];
	int i;
	EN_cardError_t ErrorStatus = CARD_OK;
	printf("Enter card expiry date : ");
	gets(buffer);
	fflush(stdin);

	//the correct format is  MM/YY
	int month = (buffer[0]-48) * 10 + (buffer[1] - 48);

	if ((buffer == NULL) || (strlen(buffer)< 5) || (strlen(buffer) > 5)
		|| month >12|| month<0|| (buffer[2] != '/'))
	{
		ErrorStatus = WRONG_EXP_DATE;
	}
	else
	{
		for (i = 0; i <= strlen(buffer); i++)
		{
			cardData->cardExpirationDate[i] = buffer[i];
		}
	}
	return ErrorStatus;
}
void getCardExpiryDateTest(void)
{
	ST_cardData_t cardData;
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: getCardExpiryDate\n");
	printf("Test Case 1: bad format yy/mm \n");
	printf("Input Data: 22/10 \n");
	printf("Expected Result: 2 (WRONG_EXP_DATE) \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: getCardExpiryDate\n");
	printf("Test Case 2: good format but month bigger than 12 \n");
	printf("Input Data: 15/24 \n");
	printf("Expected Result: 2 (WRONG_EXP_DATE) \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: getCardExpiryDate\n");
	printf("Test Case 3: good format and good input \n");
	printf("Input Data: 10/23 \n");
	printf("Expected Result: 0 (CARD_OK) \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));
	/*After review*/
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: getCardExpiryDate\n");
	printf("Test Case 4: string more than 5  \n");
	printf("Input Data: 10/2022 \n");
	printf("Expected Result: 2 (WRONG_EXP_DATE) \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: getCardExpiryDate\n");
	printf("Test Case 5: non numric string \n");
	printf("Input Data: abcd \n");
	printf("Expected Result: 2 (WRONG_EXP_DATE) \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: getCardExpiryDate\n");
	printf("Test Case 6:changing slash  \n");
	printf("Input Data: 10-23\n");
	printf("Expected Result: 2 (WRONG_EXP_DATE) \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));

}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint8_t buffer[25];
	int8_t	i;
	EN_cardError_t ErrorStatus = CARD_OK;
	printf("Enter card PAN : ");
	fflush(stdin);
	gets(buffer);

	if ( strlen(buffer)< 16 || strlen(buffer)>20 )
	{
		ErrorStatus = WRONG_PAN;
	}
	else
	{
		for (i = 0; i < strlen(buffer); i++)
		{
			cardData->primaryAccountNumber[i] = buffer[i];
		}
		cardData->primaryAccountNumber[strlen(buffer)] = '\0';
	}
	return ErrorStatus;
	
}	
void getCardPANTest(void)
{
	ST_cardData_t cardData;
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: getCardPAN\n");
	printf("Test Case 1: less than 16 (eg. 14 numbers) \n");
	printf("Input Data: 15423652301747 \n");
	printf("Expected Result: 3 (WRONG_PAN) \n");
	printf("Actual Result: %d \n", getCardPAN(&cardData));
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: getCardPAN\n");
	printf("Test Case 2: more than 20 (eg. 22 numbers)\n");
	printf("Input Data: 5417912032741589632014 \n");
	printf("Expected Result: 3 (WRONG_PAN) \n");
	printf("Actual Result: %d \n", getCardPAN(&cardData));
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: getCardPAN\n");
	printf("Test Case 3: not more than 20 nor less than 16\n");
	printf("Input Data: 1745963210878996325 \n");
	printf("Expected Result: 0 (CARD_OK) \n");
	printf("Actual Result: %d \n", getCardPAN(&cardData));
}