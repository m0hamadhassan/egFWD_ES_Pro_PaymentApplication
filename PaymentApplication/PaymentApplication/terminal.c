#include<stdio.h>
#include<string.h>
#include"terminal.h"
#include<time.h>

void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	EN_terminalError_t ErrorStatus = TERMINAL_OK;
	time_t Time;
	Time = time(NULL);
	struct tm currentTime = *localtime(&Time);

	// currentTime.tm_mday, currentTime.tm_mon + 1, currentTime.tm_year +1900
	//			18		  ,     08 +1 = 09        ,    122    +1900 =2022

	//getting integer value and assigning it as a string in termData->transactionDate
	//	D D / M M / Y Y Y Y
	//	0 1 2 3 4 5 6 7 8 9	

	termData->transactionDate[0] = (currentTime.tm_mday / 10) + 48;
	//											18 /10 = 1 +48 ='1'
	termData->transactionDate[1] = (currentTime.tm_mday % 10) + 48;
	//											18%10 = 8 +48 = '8'
	termData->transactionDate[2] = '/';
	termData->transactionDate[3] = ((currentTime.tm_mon + 1) / 10) + 48;
	//											(8 +1 ) /10 = 0 +48 ='0'
	termData->transactionDate[4] = ((currentTime.tm_mon + 1) % 10) + 48;
	//											(8+1) %10 = 9 +48 ='9'
	termData->transactionDate[5] = '/';
	//												(122  + 1990) =(2022)
	termData->transactionDate[6] = ((currentTime.tm_year + 1900) / 1000) + 48;
	//												     (2022)  /1000 = (2) + 48 = '2'

	termData->transactionDate[7] = ((currentTime.tm_year + 1900) / 100) - 10 * ((currentTime.tm_year + 1900) / 1000) + 48;
	//													   (2022)/100  -10 * (2)  
	//															20	   -10 * (2)   = 0 +48 ='0'
	termData->transactionDate[8] = ((currentTime.tm_year + 1900) / 10) - 100 * ((currentTime.tm_year + 1900) / 1000) + 48;
	//												 	  (2022) /10	- 100 * (2) 
	//															202     - 200 = 2 +48 ='2'
	termData->transactionDate[9] = ((currentTime.tm_year + 1900)) % 10 + 48;
	//														2022	%10	= 2 +48 ='2'	
	termData->transactionDate[10] = '\0';
	return ErrorStatus;
}
void getTransactionDateTest(void)
{
	ST_terminalData_t termData;
	getTransactionDate(&termData);
	printf("%s", termData.transactionDate);
}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t* termData)
{
	EN_terminalError_t ErrorStatus = TERMINAL_OK;
	//exp date format MM/YY
	//term date gormat DD/MM/YYYY
	uint8_t cardExpMonth;
	cardExpMonth = (cardData->cardExpirationDate[0] - 48) * 10 + (cardData->cardExpirationDate[1] - 48);
	uint8_t cardExpYear;
	cardExpYear = (cardData->cardExpirationDate[3] - 48) * 10 + (cardData->cardExpirationDate[4] - 48);
	uint8_t currentMonth;
	currentMonth = (termData->transactionDate[3] - 48) * 10 + (termData->transactionDate[4] - 48);
	uint8_t currentYear;
	currentYear = (termData->transactionDate[8] - 48) * 10 + (termData->transactionDate[9] - 48);


	if ((cardExpMonth< currentMonth && cardExpYear < currentYear)|| cardExpYear < currentYear)
	{
		ErrorStatus = EXPIRED_CARD;
	}
		return ErrorStatus;
}
void isCardExpriedTest(void)
{
	ST_cardData_t cardData1 = {"Mohamad Hassan Kamal","7452132574141354","02/21"};
	ST_cardData_t cardData2 = {"Mohamad Hassan Kamal","7452132574141354","10/27"};
	ST_terminalData_t termData;
	getTransactionDate(&termData);
	printf("%s\n\n", termData.transactionDate);
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: isCardExpired\n");
	printf("Test Case 1: expired card \n");
	printf("Input Data: 10/21 \n");
	printf("Expected Result:2 (EXPIRED_CARD) \n");
	printf("Actual Result: %d \n", isCardExpired(&cardData1 ,&termData));
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: isCardExpired\n");
	printf("Test Case 2: not expired card \n");
	printf("Input Data: 05/23 \n");
	printf("Expected Result:0 (TERMINAL_OK) \n");
	printf("Actual Result: %d \n", isCardExpired(&cardData2, &termData));

}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{	
	EN_terminalError_t ErrorStatus = TERMINAL_OK;
	float transactionAmount;

	
	printf("Enter transaction amount :");
	scanf("%f",&transactionAmount);
	if (transactionAmount <= 0)
	{
		ErrorStatus = INVALID_AMOUNT;
	}
	else
	{
		termData->transAmount = transactionAmount;

	}
	return ErrorStatus;
}
void getTransactionAmountTest(void)
{
	ST_terminalData_t termData;
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: getTransactionAmount\n");
	printf("Test Case 1: -ve value \n");
	printf("Input Data: -5 \n");
	printf("Expected Result:4 (INVALID_AMOUNT) \n");
	printf("Actual Result: %d \n", getTransactionAmount(&termData));
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: getTransactionAmount\n");
	printf("Test Case 2: +ve value \n");
	printf("Input Data: 5.1 \n");
	printf("Expected Result:0 (TEMINAL_OK) \n");
	printf("Actual Result: %d \n", getTransactionAmount(&termData));
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t ErrorStatus = TERMINAL_OK;

	if (termData->transAmount > termData->maxTransAmount)
	{
		ErrorStatus = EXCEED_MAX_AMOUNT;
	}
	return ErrorStatus;
}
void isBelowMaxAmountTest(void)
{
	ST_terminalData_t termData;
	//setting terminal max amount 1500
	termData.maxTransAmount = 1500;

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: isBelowMaxAmount\n");
	printf("Test Case 1: more than max amount (>1500)\n");
	printf("Input Data: 1650 \n");
	termData.transAmount = 1650;
	printf("Expected Result:5  (EXCEED_MAX_AMOUNT) \n");
	printf("Actual Result: %d \n", isBelowMaxAmount(&termData));
	printf("#######################################################\n");

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: isBelowMaxAmount\n");
	printf("Test Case 2: less than max amount (<1500)\n");
	printf("Input Data: 1250 \n");
	termData.transAmount = 1250;
	printf("Expected Result:0  (TERMINAL_OK) \n");
	printf("Actual Result: %d \n", isBelowMaxAmount(&termData));
	printf("#######################################################\n");

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: isBelowMaxAmount\n");
	printf("Test Case 3: equal to max amount (=1500)\n");
	printf("Input Data: 1500 \n");
	termData.transAmount = 1500;
	printf("Expected Result:0  (TERMINAL_OK) \n");
	printf("Actual Result: %d \n", isBelowMaxAmount(&termData));
	printf("#######################################################\n");

}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData )
{
	EN_terminalError_t ErrorStatus = TERMINAL_OK;
	float maxAmount;
	printf("Enter max amount :");
	scanf("%f", &maxAmount);
	
	if (maxAmount <= 0)
	{
		ErrorStatus = INVALID_MAX_AMOUNT;
	}
	else
	{
		termData->maxTransAmount = maxAmount;
	}
	return ErrorStatus;
}
void setMaxAmountTest(void)
{

	ST_terminalData_t termData;
	
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: setMaxAmount\n");
	printf("Test Case 1: -ve number (-150)\n");
	printf("Input Data: -150 \n");
	printf("Expected Result: 6  (INVALID_MAX_AMOUNT) \n");
	printf("Actual Result: %d \n", setMaxAmount(&termData));
	printf("#######################################################\n");

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: setMaxAmount\n");
	printf("Test Case 2: zero (0)\n");
	printf("Input Data: 0 \n");
	printf("Expected Result: 6  (INVALID_MAX_AMOUNT) \n");
	printf("Actual Result: %d \n", setMaxAmount(&termData));
	printf("#######################################################\n");

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: setMaxAmount\n");
	printf("Test Case 3: +ve number  (2300)\n");
	printf("Input Data: 2300 \n");
	printf("Expected Result: 0  (TERMINAL_OK) \n");
	printf("Actual Result: %d \n", setMaxAmount(&termData));
	printf("#######################################################\n");

}