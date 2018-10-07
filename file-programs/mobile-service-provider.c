/*
Question:
Mobile Service Provider – Service Directory
======================================================

A mobile service provider maintains a minimum data service file with following details:
- Registration number
- Name
- Age
- City
Of a customer for some quick information retrieval

The file is named as "service.txt".

The console for this is provided with following options:
    - Display all the entries in the file
    - Add a new customer to the file
    - Delete a customer entry from the file

The 3 functions available are:
    - add_customer()
    - delete_customer()
    - display_details()

Function Description:
----------------------
add_customer()
    - Will accept the input from the user and append it to the file
    - The file is opened in the "a" mode for this operation
    - Add a delimiter at the end of every data added

delete_customer()
    - Will accept the registration number from the user and
      will mark the beginning of the file entry with -1
    - First open the file in "r" mode and search for the entry
    - If found, then open the file in "r+" mode and rewrite registration data with -1

display_details()
    - Will display all the valid entries present in the file
    - The file will be opened in "r" mode.
*/

#include <stdio.h>
#include <stdlib.h>

void add_customer()
{

    FILE * fp;
    char filename[30] = "service.txt";
    int registration_number;
    char name[20];
    int age;
    char city[20];
    char delimiter = '|';

    // Open the file in read mode
    fp = fopen(filename, "a");

    // Check if the fp is not NULL
    if(fp == NULL)
    {
        printf("Cannot open the file\n");
        exit(0);
    }

    // Get the data form the user
    printf("Enter the following details: Reg Num, name, Age, City\n\n");
    scanf("%d", &registration_number);
    scanf("%s", name);
    scanf("%d", &age);
    scanf("%s", city);

    // Write the data into the file
    fprintf(fp, "%d %s %d %s %c ", registration_number, name, age,city, delimiter);

    // Close the file
    fclose(fp);

}

void delete_customer()
{
    FILE * fp1;
    FILE * fp4;
    char filename[30] = "service.txt";
    int temp_reg;
    int flag =0;
    int registration_number;
    char name[20];
    int age;
    char city[20];
    char delimiter;
    int curpos = 0;

    fp1 = fopen(filename, "r");
    if(fp1 == NULL)
    {
        printf("Cannot open the file\n");
        exit(0);
    }

    // Get the registration number to be deleted form the user
    printf("Enter the REG Num to be deleted\n");
    scanf("%d", &temp_reg);

    while(1)
    {
        // record the position of entry
        curpos = ftell(fp1);

        // Is it end of the file
        if(feof(fp1))
            break;

        fscanf(fp1, "%d %s %d %s %c ", &registration_number, name, &age,city, &delimiter);

        // is there a required registration number avail in file?
        if(registration_number == temp_reg) {
            printf("found at position %d\n", curpos);
            flag =1;
            break;
        }
    }

    // Entry not found
    if(flag ==0)
    {
        printf("No such matching record was found\n");
        return;
    }
    fclose(fp1);


    // Mark as deleted if there is a entry found
    if(flag ==1)
    {

        fp4 = fopen(filename, "r+");
        if(fp4 == NULL)
        {
            printf("Cannot open the file\n");
            exit(0);
        }

        fseek(fp4, curpos,0);
        fprintf(fp4, "%d ", -1);
        fclose(fp4);
    }

}

// Function to display the file data
void display()
{
    FILE * fp2;
    char filename[30] = "service.txt";

    int registration_number;
    char name[20];
    int age;
    char city[20];
    char delimiter;

    // Open the file in read mode
    fp2 = fopen(filename, "r");

    if(fp2 == NULL)
    {
        printf("Cannot open the file\n");
        exit(0);
    }

   while(1)
   {
       if(feof(fp2))
        break;

       fscanf(fp2, "%d %s %d %s %c ", &registration_number, name, &age,city, &delimiter);

        // Don't display if the record is already deleted
        if(registration_number != -1)
            printf("%d %s %d %s\n", registration_number, name, age,city);
   }

    fclose(fp2);
}


int main()
{
    int choice = 0;

    while(1)
    {
        printf("Menu\n");
        printf("1-Register a new customer\n2-Delete a customer\n3-Display All customers\n4-Exit\n\n");

        printf("Enter your choice\n");
        scanf("%d", &choice);


        switch(choice)
        {
            case 1: printf("New customer will be added to file\n");
                    add_customer();
                    printf("Customer added successfully\n");
                    break;

            case 2: printf("Customer will be deleted from file if found\n");
                    delete_customer();
                    break;

            case 3: display();
                    break;

            case 4: exit(0);
        }
    }

    return 0;
}
