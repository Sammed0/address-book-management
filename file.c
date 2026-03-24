//file.c handles file input and output operations for the address book allowing contact details to be saved to and loaded from a file.

#include <stdio.h> // Standard input-output functions
#include "file.h"  // Function declarations and AddressBook structure

//Saves all contacts from the address book into a CSV file.
void saveContactsToFile(AddressBook *addressBook) 
{
    
    FILE *fp;  // File pointer

    // Open file in write mode
    if((fp = fopen("contact.csv","w")) == NULL)
    {
        printf("File Not Found\n");
        return;
    }

     // Write each contact in CSV format
    for(int i = 0; i < addressBook -> contactCount; i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(fp); // Close file
    printf("\n*************************************************************************************\n");
    printf("|                            SAVED SUCCESSFULY                                      |\n");
    printf("*************************************************************************************\n");
}

//Loads contact details from the CSV file into the address book.
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp;  // File pointer
    
    // Open file in read mode
    if((fp = fopen("contact.csv","r")) == NULL)
    {
        printf("File Not Found\n");
        return;
    }
    
     // Read contact details until end of file
    while((fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[addressBook -> contactCount].name,
                                addressBook->contacts[addressBook -> contactCount].phone,
                                addressBook->contacts[addressBook -> contactCount].email)) == 3)
        {
            addressBook->contactCount++; // Increment contact count
        }
        fclose(fp);  // Close file
}
