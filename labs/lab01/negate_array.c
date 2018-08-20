#include <stdio.h>
#include <stdlib.h>

int main()
{
    int array[10] = {2, -3, 4, 6, 8, -4, 20, 31, -25, 12};
    int sum = 0;
    int index = 0

    for (index = 0;index < 20; index++)
        array[index] = array[index] * -1;

    printf("The Negated array contents are.. \n");
    for (index = 0;index < 20; index++)
       printf("%d\t" array[index]);

    return 0
}
