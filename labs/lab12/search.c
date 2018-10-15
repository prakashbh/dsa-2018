#include "search.h"

/**
Function Name: welcome
Input Params: NILL
Return Type: void
Description: Prints a welcome message
**/
void welcome()
{
    int  i = 0;
    for(i=0;i<80;i++)
        printf("*");

    printf("\n\n\t\t\t\tIII-D SEARCH ENGINE\n\n\n");

    for(i=0;i<80;i++)
        printf("*");

    printf("\n\n");

}

/**
Function Name: load_from_file
Input Params: NILL
Return Type: void
Description: loads all the data available with search engine into appropriate data structure
**/
void load_from_file()
{
    FILE *fp;

    /// Open the file in read mode
    fp = fopen("SearchIndex.txt", "r");

    /// Check if the file was successfully opened
    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }

    /// Until the end of the file, read all the file data
    while(!feof(fp))
    {
        fscanf(fp,"%d\t%[^\n]s", &search_list[global_count].priority, search_list[global_count].search_feed);
        printf("%d\t%s\n", search_list[global_count].priority, search_list[global_count].search_feed);
        global_count++;
    }

    fclose(fp);
}
