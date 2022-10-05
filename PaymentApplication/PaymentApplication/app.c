#include"app.h"
void appStart(void)
{
	//card data
	ST_cardData_t cardData;
	//terminal data
	ST_terminalData_t termData;
	//transaction data
	ST_transaction_t transData;
	//transaction state
	EN_transState_t transState;
	//reference to account in database
	ST_accountsDB_t accountRef;

	EN_cardError_t cardNameError= CARD_OK;

	//get card data from user and verify it

	while (getCardHolderName(&cardData)== WRONG_NAME)
	{
		printf("Unvalid name, Try again \n");
	}
	while (getCardExpiryDate(&cardData) == WRONG_EXP_DATE)
	{
		printf("Unvalid expiry date, Try again \n");
	}
	while (getCardPAN(&cardData) == WRONG_PAN)
	{
		printf("Unvalid PAN, Try again \n");
	}
	
	//set transaction max amount manual in code
	termData.maxTransAmount = 1950.0;

	//getting transaction date
	getTransactionDate(&termData);
	
	//saving Card Data Into Transaction Data
	transData.cardHolderData = cardData;
	

	if (isCardExpired(&cardData, &termData) == EXPIRED_CARD)
	{
		printf("Declined Expired Card\n");
	}
	else
	{
		getTransactionAmount(&termData);
		
		if (isBelowMaxAmount(&termData)== EXCEED_MAX_AMOUNT)
		{
			printf("Declined Amount Excedding Limit\n");
		}
		else
		{
			
			//before checking on transaction 
			// Saving Terminal Data Into Transaction Data
			transData.terminalData = termData;
			switch(recieveTransactionData(&transData))
			{

			case APPROVED:
				printf("Transaction Approved\n");
				break; 
			case DECLINED_INSUFFECIENT_FUND:
				printf("Transaction DECLINED\tInsuffecient Fund\n");
				break;
			case DECLINED_STOLEN_CARD:
				printf("Transaction DECLINED\tStolent Card\n");
				break;
			case FRAUD_CARD:
				printf("Transaction DECLINED\tFraud Card\n");
				break;
			case INTERNAL_SERVER_ERROR:
				printf("Internal server error\n");
				break;
			}

		}

	}
}