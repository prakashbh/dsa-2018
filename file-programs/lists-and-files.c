#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int id;
    char data[20];
    struct node *next;
};
typedef struct node NODE;


NODE * insert_at_end(NODE * start, int id, char *data)
{
    NODE * newnode, * nextnode;
    newnode = (NODE *)malloc(sizeof(NODE));
    if(newnode == NULL) {
        printf("Memory Allocation Failed\n");
        return start;
    }

    newnode->id = id;
	strcpy(newnode->data, data);
	newnode->next = NULL;

    if(start == NULL)
        start = newnode;
    else {
        nextnode = start;
        while(nextnode->next != NULL)
            nextnode = nextnode->next;

        nextnode->next = newnode;
    }
    return start;
}

void display(NODE * start)
{
    while(start!=NULL) {
        printf("%d\t%s\n", start->id, start->data);
        start = start->next;
    }
}

NODE * read_from_file(NODE * start)
{
    FILE *fp;
    int id;
	char data[20];

    fp = fopen("program-data.txt", "r");
    if(fp == NULL) {
        printf("Unable to open file\n");
        return 0;
    }

    // Until we reach the end of the file,
    // Read the numbers from one by one and
    // Insert at the end of the list
    while(1) {
        if(feof(fp))
            break;

        fscanf(fp, "%d %s\n", &id, data);
        start = insert_at_end(start, id, data);

    }
    fclose(fp);
    printf("\nThe list read from file is...\n");
    display(start);
    printf("\nYou will be now operating on above list.\n");
    return start;
}

void dump_data(NODE * start)
{
    FILE *fp;
    fp = fopen("program-data.txt", "w");
    if(fp == NULL) {
        printf("Unable to open file\n");
        return;
    }

    // Dump the list data back to file
     while(start!=NULL) {
        fprintf(fp, "%d %s\n", start->id, start->data);
        start = start->next;
    }
    fclose(fp);
}

int main()
{
    NODE *start = NULL;
    int choice;
    int id;
    char data[20];

    // Before we start with any operations,
    // We read existing file details into list
    start = read_from_file(start);

    while(1)
    {
        // You have menu to perform required list operations
        printf("\n** MENU **\n");
        printf("1-Display List\n");
        printf("2-Add to list(list end)\n");
        printf("3-Exit\n");

        printf("Enter your choice\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: display(start);
                    break;

            case 2: printf("Enter data you want to insert to list\n");
                    printf("Enter id(int) and data(string)\n");
                    scanf("%d %s", &id, data);
                    start = insert_at_end(start, id, data);
                    break;

            case 3: printf("Program Terminating\n");
                    // Before we terminate, we dump the existing
                    // list data to file
                    dump_data(start);
                    exit(1);
        }
    }
    return 0;
}
