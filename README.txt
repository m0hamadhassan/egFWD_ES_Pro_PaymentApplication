# egFWD_ES_Pro_PaymentApplication
First project on egFWD Embedded Systems Professional Nano degree
This repo contains modules implementation and test functions 
Videos and screenshots 
https://drive.google.com/drive/folders/1jBxxbTNHgWVbYEnraTMaRnU5HqQ09oFi?usp=sharing

Project Requirements : 
- Development environment preparation
- Implement the card module
- Implement the terminal module
- Implement the server module
- Implement the application
- Testing the application

Development environment preparation : 
- Create modules folders
- Create .c and .h file for each module
- Add header file guard
- Create the main.c file
- Implement the card module
Fill in card.h file with functions' prototypes and typedefs :
- Implement getCardHolderName function
- Implement getCardExpiryDate function
- Implement getCardPAN function
- Implement the terminal module
Fill in terminal.h file with functions' prototypes and typedefs : 
- Implement getTransactionDate function
- Implement isCardExpried function
- Implement gatTransactionAmount function
- Implement isBelowMaxAmount function
- Implement setMaxAmount function
- Implement the server module
Fill in server.h file with functions' prototypes and typedefs : 
- Implement server-side accounts' database
- Implement server-side transactions' database
- Implement recieveTransactionData function
- Implement isValidAccount function
- Implement isAmountAvailable function
- Implement saveTransaction function
- Implement the application
Fill in application.h file with functions' prototypes : 
- Implement appStart function
- Testing the application
- Transaction approved user story
- Exceed the maximum amount user story
- Insufficient fund user story
- Expired card user story
- Invalid card user story
