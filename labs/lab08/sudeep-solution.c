/**
Title: The Return of 'Lord of the Rings'
Name:Sudeep Gumaste
Roll Number:246
SRN:01FE17BCS220
**/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct prolific_potion
{
    char ingredient[30];
    int quantity;
    struct prolific_potion * prev;
    struct prolific_potion * next;
};

typedef struct prolific_potion PP;

PP * gather_ingredients(PP *,char *, int);
PP * brew(PP *);


/**
Function Name: gather_ingredients
Input Params:  The starting address of the node where collected ingredients will be added
               one by one as collected, ingredient name, quantity of the ingredient
Return Type:   Updated starting address
Description:   Collect the input one by one and add the node to the end of the list.
               You need to add a routine that will check if we have required quantity
               of desired ingredients. Till then keep collecting the input.

Changes made:  increased the number of parameters, added ingr and quant
               all the checks performed in main
               This function is dedicated just to add nodes
**/
PP * gather_ingredients(PP * process, char ingr[30], int quant)
{

    PP *newnode=(PP *)malloc(sizeof(PP));
    if(newnode == NULL){
        printf("\nMemory allocation failed");
        return process;
    }
    strcpy(newnode->ingredient, ingr);
    newnode->quantity=quant;
    newnode->next=NULL;
    if (process == NULL){
        newnode->prev=NULL;
        process=newnode;
        return process;
    }
    else if(process->next==NULL){
        newnode->prev=process;
        process->next=newnode;
        return process;
    }
    else{
        PP *temp;
        temp=process;
        while(temp->next != NULL){
            temp=temp->next;
        }
        temp->next=newnode;
        newnode->prev=temp;
        return process;
    }

}



/**
Function Name: brew
Input Params:  The starting address of the node where collected ingredients are available
Return Type:   Updated starting address
Description:   brew the materials in order as specified:
               30 cups of fluxweed
               20 bundles of knotgrass
               42 leeches
               50 Lacewing flies
               9 Bicorn horn
               The ingredients may be available in different nodes at various positions
Changes Made:  temporary pointer traverses the list and coparison against ingredient name is made
               if it matches with current ingreedient to be added necessary actions are performed
**/
PP * brew(PP * process)
{
    int quantity[5]={30,20,42,50,9};//array to keep track of number of ingredients required
    char ingr[5][30]={"fluxweed","bundles of knotgrass", "leeches", "lacewing flies", "bicorn horn"};
    PP *curr =process;
    PP *temp=NULL;
    int i;
    for( i=0;i<5;i++){
        temp=process;
        while(curr != NULL){
                if(!(strcmp(curr->ingredient,ingr[i]))){
                    //node to be deleted is at the begining
                    if(curr==process)
                    {
                        temp=curr;
                        curr=curr->next;
                        if(quantity[i]>temp->quantity){
                            curr->prev=NULL;
                            process=curr;
                            quantity[i]-=temp->quantity;
                            //deleting because quantity in the list becomes 0(Nothing left)
                            free(temp);
                            temp=NULL;
                        }
                        else{
                            //if more ingredients are present then, retaining the node
                            curr->quantity-=quantity[i];
                            quantity[i]=0;
                        }
                    }
                    //node to be deleted is at the end
                    else if(curr->next==NULL){
                        temp=curr;
                        curr=curr->next;
                        //same as above
                        if(quantity[i]>temp->quantity){
                            temp->prev->next=NULL;
                            quantity[i]-=temp->quantity;
                            free(temp);
                            temp=NULL;
                        }
                        else{
                            curr->quantity-=quantity[i];
                            quantity[i]=0;
                        }
                    }
                    //node to be deleted is in the middle
                    else{
                        temp=curr;
                        curr=curr->next;
                        //same as above
                        if(quantity[i]>temp->quantity){
                            temp->prev->next=curr;
                            curr->prev=temp->prev;
                            quantity[i]-=temp->quantity;
                            free(temp);
                            temp=NULL;
                        }
                        else{
                            curr->quantity-=quantity[i];
                            quantity[i]=0;
                        }
                    }
                }
                else
                    curr=curr->next;
            }
        }
    return process;
    //returning the header address, if
}

/**
Function Name: quant_check
Status:        temporary function to verify the working of code
return type:   NILL
Description:   prints out the the node number at which an ingreedient is present sequentially

void quant_check(PP * process)
{
    int quantity[5]={30,20,42,50,9};//array to keep track of number of ingredients required
    char ingr[5][30]={"fluxweed","bundles of knotgrass", "leeches", "lacewing flies", "bicorn horn"};
    PP *temp =process;
    int count=0;
    for(int i=0;i<5;i++){
        temp=process;
        count=0;
        while(temp != NULL){
            count++;
                if(!(strcmp(temp->ingredient,ingr[i]))){
                    printf("%d ",count);
                }
                temp=temp->next;
            }
            printf("\n");
        }

}
**/


/**
Function Name: print
Status:        temporary function, will be commented out in the later release
return type:   NILL
Description:   to print the linked list and check if everything is going fine

void print(PP *process){
    PP *temp=process;

    while(temp != NULL){
        printf("%s(%d)->",temp->ingredient, temp->quantity);
        temp=temp->next;
    }
    printf("\n");
}
**/


int main()
{
    PP *process = NULL;
    int item,x;
    /**
    array to keep track of quantity
    subtract by the quantity entered each time
    **/
    int quantity[5]={30,20,42,50,9};


    printf("\nThe preparation has begin at...\n");
    time_t start;
    start = time(NULL);
    printf(ctime(&start));
    printf("\n\n");

    while(quantity[0]>0 || quantity[1]>0 || quantity[2]>0 || quantity[3]>0 || quantity[4]>0)
    {
        /**
         * To eleminate the possibility of invalid inputs
         * displaying the inventory of the shop
        **/
        printf("\nWhat is available in the shop inventory?");
        printf("\n1. fluxweed");
        printf("\n2. bundles of knotgrass");
        printf("\n3. leeches");
        printf("\n4. lacewing flies");
        printf("\n5. bicorn horn");
        //printf("\n6. print"); //comment out later
        printf("\nSelect an option:");
        scanf("%d",&item);
        printf("\nEnter the quantity: ");
        scanf("%d",&x);
        switch(item){
            case 1: if (quantity[0]>0){
                        process = gather_ingredients(process, "fluxweed", x);
                        quantity[0]-=x;
                    }
                    else{
                        printf("\nAlready have enough of those!");
                    }
                    break;
            case 2: if (quantity[1]>0){
                        process = gather_ingredients(process, "bundles of knotgrass", x);
                        quantity[1]-=x;
                    }
                    else{
                        printf("\nAlready have enough of those!");
                    }
                    break;
            case 3: if (quantity[2]>0){
                        process = gather_ingredients(process, "leeches", x);
                        quantity[2]-=x;
                    }
                    else{
                        printf("\nAlready have enough of those!");

                    }
                    break;
            case 4: if (quantity[3]>0){
                        process = gather_ingredients(process, "lacewing flies", x);
                        quantity[3]-=x;
                    }
                    else{
                        printf("\nAlready have enough of those!");
                    }
                    break;
            case 5: if (quantity[4]>0){
                        process = gather_ingredients(process, "bicorn horn", x);
                        quantity[4]-=x;
                    }
                    else{
                        printf("\nAlready have enough of those!");
                    }
                    break;
            //case 6: print(process);
            //        break;
            default: printf("Not available in the inventory");
        }
    }

    //print(process); //comment out later

    //quant_check(process);

    process = brew(process);

    printf("\nThe POTION is ready, The dark army can now be defeated again!\n");
    printf("\n\n");

    printf("\nThe preparation ended at...\n");
    time_t end;
    end = time(NULL);
    printf(ctime(&end));
    printf("\n\n");

    return 0;
}
