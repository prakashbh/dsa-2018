#include<stdio.h>
#include<stdlib.h>

int main()
{

    FILE *fp1, *fp2;
    int ch;

    if((fp1 = fopen("input-file.txt", "r")) == NULL)
    {
        printf("Error opening the file\n");
        exit(0);
    }

    fp2 = fopen("output-file.txt", "w");
    if(fp2 == NULL)
    {
        printf("Error opening the file\n");
        exit(0);
    }

    while((ch=getc(fp1)) != EOF) {
        putc(ch,fp2);
    }

    printf("File copy Successful.\n");

    fclose(fp1);
    fclose(fp2);

    return 0;

}
