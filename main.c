/*
Name:Sammed kuranagi
Date:31-12-2025
Description: This controls the overall flow of the address book application by calling appropriate functions based on user input
*/

#include <stdio.h>  // Standard input-output functions
#include "contact.h"  // AddressBook structure and function declarations

int main() {
    int choice,sortChoice; // Variables for menu selection
    AddressBook addressBook; // Address book instance
    initialize(&addressBook); // Initialize the address book

    printf("\n********************************************************************************\n");
    printf("*                         WELCOME TO ADDRESS BOOK                              *\n");
    printf("********************************************************************************\n");
    
     // Menu-driven loop
    do 
    {
        printf("\nAddress Book Menu:\n");
        printf("\n1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");

        // Read user choice
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        
       // Perform operation based on user choice
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving...\n");
                saveContactsToFile(&addressBook);
                break;   
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);  // Repeat until user chooses Exit
    
       return 0;  // Program termination
}
