#include <stdio.h>
#include <string.h>
#include "server.h"

ST_accountsDB_t accountsDB[255] =
{
	{23450.0, RUNNING, "5365227418449952"},
	{10871.0, RUNNING, "6216421762123284"},
	{1874.0, BLOCKED, "5494031536443382"}, // blocked
	{2010.0, RUNNING, "2946376193279905"},
	{254.0, RUNNING, "6964690405822411"},//*
	{120.0, RUNNING, "1388393921568886"},
	{29852.0, BLOCKED, "2010377165328481"}, // blocked*
	{98745.0, RUNNING, "9737628650154429"},
	{14.0, RUNNING, "4031373251867921"},
	{845.0, RUNNING, "5027705752873721"},
	{451.0, RUNNING, "5506659692130454"},
	{87451.0, BLOCKED, "8625948822271191"}, // blocked
	{564.0, RUNNING, "9768698847407065"},
	{35130.5, BLOCKED, "1532424181474690"}, // blocked
	{212.4, RUNNING, "7270910662920824"},
	{935130.9, RUNNING, "2958468509546062"},
	{654130.2, RUNNING, "9116722165124844"},
	{17132.5, RUNNING, "7857467935523357"},
	{23459478.0, BLOCKED, "8348419678890647"}, // blocked
	{17.1, RUNNING, "8254392307557717"},
};

ST_transaction_t transactionsDB[255] = { 0 };

int transactionIndex = 0;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	EN_transState_t transactionState = INTERNAL_SERVER_ERROR;
	EN_serverError_t isValidAccountE_Status;
	EN_serverError_t isAmountAvailableE_status;
	EN_serverError_t isBlockedAccountE_status;
	// pointer to pointer to an account in accounts db
	ST_accountsDB_t* accountRef;

	// checking account validity
	isValidAccountE_Status = isValidAccount(&(transData->cardHolderData), &accountRef);

	if (isValidAccountE_Status == SERVER_OK)
	{
		// the account is found in database
		isAmountAvailableE_status = isAmountAvailable(&(transData->terminalData), accountRef);
		isBlockedAccountE_status = isBlockedAccount(accountRef);
		// checking the state of account
		if (isBlockedAccountE_status == BLOCKED_ACCOUNT)
		{
			transactionState = DECLINED_STOLEN_CARD;
		}
		// checking available amount for transaction
		else if (isAmountAvailableE_status == LOW_BALANCE)
		{
			transactionState = DECLINED_INSUFFECIENT_FUND;
		}
		else
		{
			transactionState = APPROVED;
			accountRef->balance = accountRef->balance - transData->terminalData.transAmount;
		}
	}
	else
	{
		// the account is not found in database
		transactionState = FRAUD_CARD;
	}
	transData->transState = transactionState;
	saveTransaction(transData);
	return transactionState;
}
void recieveTransactionDataTest(void)
{
	ST_transaction_t transData ;
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: recieveTransactionData\n");
	printf("Test Case 1:Fraud account(WRONG PAN)\n");
	transData = (ST_transaction_t){ .cardHolderData = "Mohamed Hassan Kamal ","1254745632147452","10/26",.terminalData = {150,1500,"30/9/2022"} };
	printf("Input Data: cardHolderData = {Mohamed Hassan Kamal ,1254745632147452,10/26},\nterminalData = {150,1500,30/9/ 2022} \n");
	printf("Expected Result: 3  (FRAUD_CARD) \n");
	printf("Actual Result: %d \n", recieveTransactionData(&transData));
	printf("#######################################################\n");

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: recieveTransactionData\n");
	printf("Test Case 2: stolen card (Account blocked)\n");
	transData = (ST_transaction_t){ .cardHolderData = "Mohamed Hassan Kamal ","2010377165328481","10/26",.terminalData = {150,1500,"30/9/2022"} };
	printf("Input Data: cardHolderData = {Mohamed Hassan Kamal ,2010377165328481,10/26},\nterminalData = {150,1500,30/9/ 2022} \n");
	printf("Expected Result: 2  (DECLINED_STOLEN_CARD) \n");
	printf("Actual Result: %d \n", recieveTransactionData(&transData));
	printf("#######################################################\n");

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: recieveTransactionData\n");
	printf("Test Case 3: Insufficiend fund\n");
	transData = (ST_transaction_t){ .cardHolderData = "Mohamed Hassan Kamal ","6964690405822411","10/26",.terminalData = {900,1500,"30/9/2022"} };
	printf("Input Data: cardHolderData = {Mohamed Hassan Kamal ,2010377165328481,10/26},\nterminalData = {150,1500,30/9/ 2022} \n");
	printf("Expected Result: 1  (DECLINED_INSUFFECIENT_FUND) \n");
	printf("Actual Result: %d \n", recieveTransactionData(&transData));
	printf("#######################################################\n");

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: recieveTransactionData\n");
	printf("Test Case 4: Approved \n");
	transData = (ST_transaction_t){ .cardHolderData = "Mohamed Hassan Kamal ","6964690405822411","10/26",.terminalData = {120,1500,"30/9/2022"} };
	printf("Input Data: cardHolderData = {Mohamed Hassan Kamal ,2010377165328481,10/26},\nterminalData = {150,1500,30/9/ 2022} \n");
	printf("Expected Result: 0  (AAPROVED) \n");
	printf("Actual Result: %d \n", recieveTransactionData(&transData));
	printf("#######################################################\n");
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t** accountRefrence)
{
	EN_serverError_t ErrorStatus = SERVER_OK;
	int i;

	int foundFlag = 0;

	for (i = 0; i < 255; i++)
	{

		if (strcmp(accountsDB[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0)
		{
			*accountRefrence = &accountsDB[i];

			foundFlag++;
			break;
		}
	}
	if (foundFlag == 0)
	{
		*accountRefrence = NULL;
		ErrorStatus = ACCOUNT_NOT_FOUND;
	}

	return ErrorStatus;
}
void isValidAccountTest(void)
{
	ST_cardData_t cardData;
	ST_accountsDB_t* accountRefrence;
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: isValidAccount\n");
	printf("Test Case 1:account not found (WRONG PAN)\n");
	cardData = (ST_cardData_t){.cardHolderName="Mohamed Hassan Kamal ",.primaryAccountNumber="1236541265474145",.cardExpirationDate="10/26"};
	printf("Input Data: cardHolderName=Mohamed Hassan Kamal,primaryAccountNumber=1236541265474145,cardExpirationDate=10/26\n");
	printf("Expected Result: 3  (ACCOUNT_NOT_FOUND) \n");
	printf("Actual Result: %d \n", isValidAccount(&cardData, &accountRefrence));
	printf("#######################################################\n");

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: isValidAccount\n");
	printf("Test Case 2:account found (Correct PAN)\n");
	cardData = (ST_cardData_t){ .cardHolderName = "Mohamed Hassan Kamal ",.primaryAccountNumber = "6964690405822411",.cardExpirationDate = "10/26" };
	printf("Input Data: cardHolderName=Mohamed Hassan Kamal,primaryAccountNumber=6964690405822411,cardExpirationDate=10/26\n");
	printf("Expected Result: 0  (SERVER_OK) \n");
	printf("Actual Result: %d \n", isValidAccount(&cardData, &accountRefrence));
	printf("#######################################################\n");
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	EN_transState_t ErrorStatus = SERVER_OK;
	if (accountRefrence->state == BLOCKED)
	{
		ErrorStatus = BLOCKED_ACCOUNT;
	}
	return ErrorStatus;
}
void isBlockedAccountTest(void)
{
	ST_accountsDB_t* accountRefrence = NULL;
	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: isBlockedAccount\n");
	printf("Test Case 1: Blocked account \n");
	accountRefrence = &accountsDB[2]; //blocked
	printf("Input Data: &accountsDB[2]\n");
	printf("Expected Result: 5  (BLOCKED_ACCOUNT) \n");
	printf("Actual Result: %d \n", isBlockedAccount(accountRefrence));
	printf("#######################################################\n");

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: isBlockedAccount\n");
	printf("Test Case 2: Not Blocked account \n");
	accountRefrence = &accountsDB[3]; //not blocked
	printf("Input Data: &accountsDB[3]\n");
	printf("Expected Result: 0 (SERVER_OK) \n");
	printf("Actual Result: %d \n", isBlockedAccount(accountRefrence));
	printf("#######################################################\n");
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t ErrorStatus = SERVER_OK;
	if (accountRefrence->balance < termData->transAmount)
	{

		ErrorStatus = LOW_BALANCE;
	}
	return ErrorStatus;
}
void isAmountAvailableTest(void)
{
	ST_terminalData_t termData;
	ST_accountsDB_t* accountRefrence=NULL;

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: isAmountAvailable\n");
	printf("Test Case 1: account balance < transAmount\n");
	accountRefrence = &accountsDB[5];
	termData = (ST_terminalData_t){ .transAmount = 200,.maxTransAmount = 1500,.transactionDate = "30/09/2022" };
	printf("Input Data: Account Balance =120.0, transAmount = 200.0\n");
	printf("Expected Result: 4  (LOW_BALANCE) \n");
	printf("Actual Result: %d \n", isAmountAvailable(&termData,accountRefrence));
	printf("#######################################################\n");

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: isAmountAvailable\n");
	printf("Test Case 2: account balance > transAmount\n");
	accountRefrence = &accountsDB[0];
	termData = (ST_terminalData_t){ .transAmount = 200,.maxTransAmount = 1500,.transactionDate = "30/09/2022" };
	printf("Input Data: Account Balance =23450.0, transAmount = 200.0\n");
	printf("Expected Result: 0  (SERVER_OK) \n");
	printf("Actual Result: %d \n", isAmountAvailable(&termData, accountRefrence));
	printf("#######################################################\n");

}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	EN_transState_t ErrorStatus = SERVER_OK;
	if (&transactionsDB[transactionIndex] != NULL)
	{
		transactionsDB[transactionIndex].cardHolderData = transData->cardHolderData;
		transactionsDB[transactionIndex].terminalData = transData->terminalData;
		transactionsDB[transactionIndex].transactionSequenceNumber = transactionIndex;
		transData->transactionSequenceNumber = transactionIndex;
		transactionsDB[transactionIndex].transState = transData->transState;
		transactionIndex++;
	}
	else
	{
		ErrorStatus = SAVING_FAILED;
	}
	return ErrorStatus;
}
void saveTransactionTest(void)
{
	ST_transaction_t transData;

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: saveTransaction\n");
	printf("Test Case 1: saving ok state APPROVED \n");
	transData = (ST_transaction_t)
	{ .cardHolderData = {.cardHolderName = "Mohamad Hassan Kamal",.cardExpirationDate = "10/27",.primaryAccountNumber = "9737628650154429"}
	 ,.terminalData = {.maxTransAmount = 1500,.transactionDate = "30/9/2022",.transAmount = 150}
	 ,.transState = APPROVED
	};
	printf("Input Data: .cardHolderData = {.cardHolderName = Mohamad Hassan Kamal,.cardExpirationDate = 10 / 27,.primaryAccountNumber = 9737628650154429}\nterminalData = { maxTransAmount = 1500transactionDate = 30/9/2022transAmount = 150 }\ntransactionSequenceNumber = 0, .transState = APPROVED);\n");
	printf("Expected Result: 0  (SERVER_OK) \n");
	printf("Actual Result: %d \n", saveTransaction(&transData));
	printf("#######################################################\n");

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: saveTransaction\n");
	printf("Test Case 2: saving ok state DECLINED_INSUFFECIENT_FUND \n");
	transData = (ST_transaction_t)
	{ .cardHolderData = {.cardHolderName = "Mohamad Hassan Kamal",.cardExpirationDate = "10/27",.primaryAccountNumber = "9737628650154429"}
	 ,.terminalData = {.maxTransAmount = 1500,.transactionDate = "30/9/2022",.transAmount = 150}
	 ,.transState = DECLINED_INSUFFECIENT_FUND
	};
	printf("Input Data: .cardHolderData = {.cardHolderName = Mohamad Hassan Kamal,.cardExpirationDate = 10 / 27,.primaryAccountNumber = 9737628650154429}\nterminalData = { maxTransAmount = 1500transactionDate = 30/9/2022transAmount = 150 }\ntransactionSequenceNumber = 0, .transState = DECLINED_INSUFFECIENT_FUND);\n");
	printf("Expected Result: 0  (SERVER_OK) \n");
	printf("Actual Result: %d \n", saveTransaction(&transData));
	printf("#######################################################\n");

	printf("#######################################################\n");
	printf("Tester Name: Mohamad Hassan\n");
	printf("Function Name: saveTransaction\n");
	printf("Test Case 3: saving ok state FRAUD_CARD \n");
	transData = (ST_transaction_t)
	{ .cardHolderData = {.cardHolderName = "Mohamad Hassan Kamal",.cardExpirationDate = "10/27",.primaryAccountNumber = "9737628650154429"}
	 ,.terminalData = {.maxTransAmount = 1500,.transactionDate = "30/9/2022",.transAmount = 150}
	 ,.transState = FRAUD_CARD
	};
	printf("Input Data: .cardHolderData = {.cardHolderName = Mohamad Hassan Kamal,.cardExpirationDate = 10 / 27,.primaryAccountNumber = 9737628650154429}\nterminalData = { maxTransAmount = 1500transactionDate = 30/9/2022transAmount = 150 }\ntransactionSequenceNumber = 0, .transState = FRAUD_CARD);\n");
	printf("Expected Result: 0  (SERVER_OK) \n");
	printf("Actual Result: %d \n", saveTransaction(&transData));
	printf("#######################################################\n");
}
void listSavedTransactions(void)
{
	int i = 0;
	if (transactionIndex == 0)
	{
		printf("there is no transactions yet\n");
	}
	else
	{
		for (i = 0; i < transactionIndex; i++)
		{
			printf("#########################\n");
			printf("Transaction Sequence Number : %d\n", i);
			printf("Transaction Date: %s\n", transactionsDB[i].terminalData.transactionDate);
			printf("Transaction Amount: %.1f\n", transactionsDB[i].terminalData.transAmount);
			switch (transactionsDB[i].transState)
			{
			case APPROVED:
				printf("Transaction State : APPROVED\n");
				break;
			case DECLINED_INSUFFECIENT_FUND:
				printf("Transaction State : DECLINED_INSUFFECIENT_FUND\n");
				break;
			case DECLINED_STOLEN_CARD:
				printf("Transaction State : DECLINED_STOLEN_CARD\n");
				break;
			case FRAUD_CARD:
				printf("Transaction State : FRAUD_CARD\n");
				break;
			case INTERNAL_SERVER_ERROR:
				printf("Transaction State : INTERNAL_SERVER_ERROR\n");
				break;
			}
			printf("Terminal Max Amount : %.1f\n", transactionsDB[i].terminalData.maxTransAmount);
			printf("Cardholder Name: %s\n", transactionsDB[i].cardHolderData.cardHolderName);
			printf("PAN: %s\n", transactionsDB[i].cardHolderData.primaryAccountNumber);
			printf("Card Expiration Date: %s\n", transactionsDB[i].cardHolderData.cardExpirationDate);
			printf("#########################\n");
		}
	}
}
