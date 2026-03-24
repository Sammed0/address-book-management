/*
Name:Sammed kuranagi
Date:31-12-2025
Description: implementation of core address book operations such as  creating, listing, searching, editing, and deleting contact records.
*/

#include <stdio.h>  // Standard input-output functions
#include <stdlib.h> // For exit(), EXIT_SUCCESS
#include <string.h> // For string handling functions
#include "contact.h" // Structure declarations for AddressBook & Contact
#include "file.h"  // File handling functions (save/load)
#include "populate.h" //// Populate address book (if used)

   //Sorts the contacts alphabetically by name and displays them in a tabular format.
 

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Bubble sort logic to sort contacts based on name
    for(int i = 1; i < addressBook->contactCount; i++)
    {
        for(int j = 0; j < addressBook->contactCount - i; j++)
        {
            // Compare adjacent contact names
            if((strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)) > 0)
            {
                // Swap contacts if out of order
                Contact temp = addressBook -> contacts[j];
                addressBook -> contacts[j] = addressBook -> contacts[j+1];
                addressBook -> contacts[j+1] = temp;
            }
        }
    }
    printf("\n");
    printf("===================================================================================\n");
    printf("|                            ENTERED INTO CONTACT LIST                            |\n");
    printf("===================================================================================\n");

    printf("| %-5s | %-20s | %-15s | %-30s |\n","S.NO", "NAME", "CONTACT", "EMAIL");
    printf("-----------------------------------------------------------------------------------\n");
    // Print all contacts
    for(int i = 0; i < addressBook -> contactCount; i++)
    {
        printf("| %-5d | %-20s | %-15s | %-30s |\n",i+1,addressBook-> contacts[i].name,addressBook-> contacts[i].phone,addressBook-> contacts[i].email);
    }
    printf("-----------------------------------------------------------------------------------\n");
}

 //Initializes the address book and loads existing contacts from file.

void initialize(AddressBook *addressBook) 
{

    // Set initial contact count to zero
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
 //Saves contacts to file and exits the program.
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

 //Checks if name contains only alphabets, spaces, or dot.
int validatename(char *name)
{
    int i = 0;
    while(name[i] != '\0')
    {
        if((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || name[i] == ' ' || name[i] == '.')
            i++;

        else
            return 0; // Invalid character found
    }
    return 1; // Valid name
}
 // Checks Validates phone number Must be 10 digits and Must contain only digits Must be unique
int validatephone(AddressBook *addressBook, char *phone)
{
    if((strlen(phone)) != 10)
        return 0;

    int i = 0;
    while(phone[i] != '\0')
    {
        // Check digits only
        if(phone[i] < '0' || phone[i] > '9')
            return 0;
        i++;
    }
    for(i = 0; i < addressBook->contactCount; i++)
    {
        // Check for duplicate phone numbers
        if((strcmp(addressBook->contacts[i].phone,phone)) == 0)
            return 0;
    }
    return 1; // valid phone number
}

//In this functions it checks the email existing or not and checks whether it contains the @ and .
int validateemail(AddressBook *addressBook, char *email)
{
    int i = 0,atfound = 0,dotfound = 0;
    while(email[i] != '\0')
    {
        //checks the it contains alphabets or number and . and @ 
        if((email[i] >= 'a' && email[i] <= 'z') || (email[i] >= '0' && email[i] <= '9') || email[i] == '.' || email[i] == '_' || email[i]  == '@')
        {
            //checks for @
            if(email[i] == '@')
                atfound = 1;
            //checks for .
            if(email[i] == '.')
                dotfound = 1;

            i++;
        }
        else
            return 0;
    }
    //checks for @ present or not
    if(atfound == 0)
        return 0; //if not then return 0
    
    //checks for the . present or not
    if(dotfound == 0) 
        return 0;

    for(i = 0; i < addressBook->contactCount; i++)
    {
        //checks whether email is already existing
        if((strcmp(addressBook->contacts[i].email,email)) == 0)
            return 0;
    }
    return 1; // valid email
}

 //Adds a new contact after validating name, phone number, and email.
void createContact(AddressBook *addressBook)
{
	// Check if address book is full
    if(addressBook -> contactCount >= MAX_CONTACTS)
    {
        printf("AddresBook is full\n");
        return;
    }

    char name1[50],phone1[20],email1[50];
    // Input and validate name
    do
    {
    printf("\nEnter name : ");
    scanf(" %[^\n]",name1);

    if(validatename(name1) == 0)
        printf("\nInvalid name\n");
    }while(validatename(name1) == 0);
    
    // Input and validate phone number
    do
    {
    printf("\nEnter phone number : ");
    scanf(" %[^\n]",phone1);
    

    if(validatephone(addressBook,phone1) == 0)
     printf("\nInvalid phone number\n");

    }while(validatephone(addressBook,phone1) == 0);

    // Input and validate email
    do
    {
    printf("\nEnter email id : ");
    scanf(" %[^\n]",email1);

    if(validateemail(addressBook,email1) == 0)
        printf("\nInvalid email id\n");
    }while(validateemail(addressBook,email1) == 0);

    // Store validated contact
    strcpy(addressBook->contacts[addressBook->contactCount].name,name1);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone1);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email1);
    addressBook->contactCount++;

    printf("\n*************************************************************************************\n");
    printf("|                           CONTACT CREATED SUCCESSFULY                             |\n");
    printf("*************************************************************************************\n");

}

// This functions search details by name and phone and email
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice,flag = 0,dup_index[50],count = 0;
    char new_str[100];

    printf("===================================================================================\n");
    printf("|                            ENTERED INTO SEARCH LIST                            |\n");
    printf("===================================================================================\n");
    printf("\nSearch By \n1.Name\n2.Phone\n3.Email\n");
    printf("\n");
    // Clear input buffer
    getchar();
    // Read user choice
    printf("Enter your choice : ");
    scanf("%d",&choice);
    printf("\n");

    // Perform search based on user choice
    switch(choice)
    {
        case 1: // Search by name (partial match)
            printf("Enter name : ");
            scanf(" %[^\n]",new_str);

        for(int i = 0; i < addressBook->contactCount; i++)
        {
            // Case-insensitive substring search
            char *sub_string = strcasestr(addressBook->contacts[i].name,new_str);

            if(sub_string != NULL)
            {
                dup_index[count++] = i; // Store matched index
                flag = 1;
            }
        
        }
        break;
        
        case 2:// Search by phone (exact match)

            printf("Enter phone number : ");
            scanf(" %[^\n]",new_str);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                int res = strcmp(new_str,addressBook->contacts[i].phone);

                if(res == 0)
                {
                    dup_index[count++] = i;
                    flag = 1;
                }
            }
            break;

            case 3: // Search by email (exact match)
                printf("Enter email id : ");
                scanf(" %[^\n]",new_str);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                int res = strcmp(new_str,addressBook->contacts[i].email);

                if(res == 0)
                {
                    dup_index[count++] = i;
                    flag = 1;
                }
            }
            break;

            default:
            {
                printf("Invalid Choice\n");
                return ;
            }
    }
    // If no contact found
    if(flag == 0 )
        {
            printf("\n*************************************************************************************\n");
            printf("|                           CONTACT NOT FOUND!                                      |\n");
            printf("*************************************************************************************\n");
            return ;
        }
         // Display matched contacts   
        if(flag == 1)
        {
            printf("\n-----------------------------------------------------------------------------------\n");
            printf("| %-5s | %-20s | %-15s | %-30s |\n","S.NO", "NAME", "CONTACT", "EMAIL");
            printf("-----------------------------------------------------------------------------------\n");
            for(int i = 0; i < count; i++)
                {
                    printf("| %-5d | %-20s | %-15s | %-30s |\n",i+1,addressBook->contacts[dup_index[i]].name,
                                                                addressBook->contacts[dup_index[i]].phone,
                                                                addressBook->contacts[dup_index[i]].email);
                    printf("-----------------------------------------------------------------------------------\n");
                }
        }
}

// here we are editing the contacts by name and email and phone
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice,flag = 0,dup_index[50],count = 0;
    char new_str[50];

    printf("===================================================================================\n");
    printf("|                            ENTERED INTO EDIT LIST                            |\n");
    printf("===================================================================================\n");
    printf("Search By \n1.Name\n2.Phone\n3.Email\n");
    printf("\n");
    printf("Enter your choice : ");
    scanf("%d",&choice);
    printf("\n");

    // Search contact (same logic as searchContact)
    switch(choice)
    {
        case 1: // search by name
            printf("\nEnter name : ");
            scanf(" %[^\n]",new_str);

        for(int i = 0; i < addressBook->contactCount; i++)
        {
            char *sub_string = strcasestr(addressBook->contacts[i].name,new_str); // using the inbuilt function 

            if(sub_string != NULL)
            {
                dup_index[count++] = i;
                flag = 1;
            }
        
        }
        break;
        
        case 2: // search by phone number
            printf("Enter phone number : ");
            scanf(" %[^\n]",new_str);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                int res = strcmp(new_str,addressBook->contacts[i].phone); // comparing

                if(res == 0)
                {
                    dup_index[count++] = i;
                    flag = 1;
                }
            }
            break;

            case 3: // search by email id
                printf("Enter email id : ");
                scanf(" %[^\n]",new_str);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                int res = strcmp(new_str,addressBook->contacts[i].email); //comparing

                if(res == 0)
                {
                    dup_index[count++] = i;
                    flag = 1;
                }
            }
            break;

            default:
            {
                printf("Invalid Choice\n");
                return ;
            }
    }
    // No contact found
    if(flag == 0 )
        {
            printf("\n*************************************************************************************\n");
            printf("|                           CONTACT NOT FOUND!                                      |\n");
            printf("*************************************************************************************\n");
            return ;
        }   
        if(flag == 1) // Contact found
        {
            printf("\n-----------------------------------------------------------------------------------\n");
            printf("| %-5s | %-20s | %-15s | %-30s |\n","S.NO", "NAME", "CONTACT", "EMAIL");
            printf("-----------------------------------------------------------------------------------\n");
            for(int i = 0; i < count; i++)
                {
                    printf("| %-5d | %-20s | %-15s | %-30s |\n",i+1,addressBook->contacts[dup_index[i]].name,
                                                                addressBook->contacts[dup_index[i]].phone,
                                                                addressBook->contacts[dup_index[i]].email);
                    printf("-----------------------------------------------------------------------------------\n");
                }
        }
     // Choose which contact to edit
    int choice1,choice2;
    char new_str1[50];
    printf("\nWhich one you want edit? (1 - %d) : ",count);
    scanf("%d",&choice1);
    
    if(choice1 < 1 || choice1 > count)
    {
        printf("\nInvalid Choice\n");
        return;
    }

    choice1--;// Convert to index
    // Edit options
    printf("\nWhat you want to edit\n1.Name\n2.Phone\n3.Email\n");
    printf("\nEnter your choice : ");
    scanf("%d",&choice2);

    // Perform edit
    switch(choice2)
    {
        case 1: //Asking the user for new name
            printf("\nEnter New Name : ");
            scanf(" %[^\n]",new_str1);
            if((validatename(new_str1)) == 0)
            {
                printf("\nInvalid Name\n");
                return;
            }
            strcpy(addressBook->contacts[dup_index[choice1]].name,new_str1);
            break;

        case 2: // Asking the user for new phone number
            printf("\nEnter New Number : ");
            scanf(" %[^\n]",new_str1);
            if((validatephone(addressBook,new_str1)) == 0)
            {
                printf("\nInvalid Phone Number\n");
                return;
            }
            strcpy(addressBook->contacts[dup_index[choice1]].phone,new_str1);
            break;
        
        case 3: // asking user for name email id
            printf("\nEnter New Email : ");
            scanf(" %[^\n]",new_str1);
            if((validateemail(addressBook,new_str1)) == 0)
            {
                printf("\nInvalid Email Id\n");
                return;
            }
            strcpy(addressBook->contacts[dup_index[choice1]].email,new_str1);
            break;

        default:
            printf("Invalid Choice\n");
            return;
    }

    printf("\n*************************************************************************************\n");
    printf("|                           CONTACT UPDATED SUCCESSFULY                             |\n");
    printf("*************************************************************************************\n");
}

// In this function we are deleting contacts by giving the menu

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int choice,flag = 0,dup_index[50],count = 0;
    char new_str[50];

    printf("===================================================================================\n");
    printf("|                            ENTERED INTO DELETE LIST                             |\n");
    printf("===================================================================================\n");
    // Search options
    printf("\nSearch By \n1.Name\n2.Phone\n3.Email\n");
    printf("\n");
    printf("Enter your choice : ");
    scanf("%d",&choice);
    printf("\n");

    // Search contact to delete
    switch(choice)
    {
        case 1: // search by name
            printf("Enter name : ");
            scanf(" %[^\n]",new_str);

        for(int i = 0; i < addressBook->contactCount; i++)
        {
            char *sub_string = strcasestr(addressBook->contacts[i].name,new_str);

            if(sub_string != NULL)
            {
                dup_index[count++] = i;
                flag = 1;
            }
        
        }
        break;
        
        case 2: // search by phone number
            printf("Enter phone number : ");
            scanf(" %[^\n]",new_str);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                int res = strcmp(new_str,addressBook->contacts[i].phone); // comparing both strings

                if(res == 0)
                {
                    dup_index[count++] = i;
                    flag = 1;
                }
            }
            break;

            case 3: // search by email id
                printf("Enter email id : ");
                scanf(" %[^\n]",new_str);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                int res = strcmp(new_str,addressBook->contacts[i].email);  // comparing both strings

                if(res == 0)
                {
                    dup_index[count++] = i;
                    flag = 1;
                }
            }
            break;

            default: 
            {
                printf("Invalid Choice\n");
                return ;
            }

    }
    if(flag == 0 ) // No contact found
        {
            printf("\n*************************************************************************************\n");
            printf("|                           CONTACT NOT FOUND!                                      |\n");
            printf("*************************************************************************************\n");
            return ;
        }
        if(flag == 1) // If contact found
        {
            printf("\n-----------------------------------------------------------------------------------\n");
            printf("| %-5s | %-20s | %-15s | %-30s |\n","S.NO", "NAME", "CONTACT", "EMAIL");
            printf("-----------------------------------------------------------------------------------\n");
            for(int i = 0; i < count; i++)
                {
                    printf("| %-5d | %-20s | %-15s | %-30s |\n",i+1,addressBook->contacts[dup_index[i]].name,
                                                                addressBook->contacts[dup_index[i]].phone,
                                                                addressBook->contacts[dup_index[i]].email);
                    printf("-----------------------------------------------------------------------------------\n");
                }
        }
        
    int choice1;
    char new_str1[50];
    printf("\nWhich one you want delete? (1 - %d) : ",count); // Asking user to delete which one.
    scanf("%d",&choice1);
    
    if(choice1 < 1 || choice1 > count)
    {
        printf("\nInvalid Choice\n");
        return;
    }

    choice1--;
    char ch;
    printf("\nif you want to delete?(y/Y) : "); // asking permission from the user for delete
    scanf(" %c",&ch);

     // Delete by shifting contacts
    int pos = dup_index[choice1];
    if(ch == 'y' || ch == 'Y')
    {
        for(int i =  pos; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i+1];
        }
        addressBook->contactCount--;
    }

    printf("\n*************************************************************************************\n");
    printf("|                           CONTACT DELETED SUCCESSFULY                             |\n");
    printf("*************************************************************************************\n");
}