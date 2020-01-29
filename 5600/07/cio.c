#include <stdio.h>

int
main(int _ac, char* _av[])
{
    FILE* thing1 = fopen("/tmp/thing1.txt", "w");
    fprintf(thing1, "Hello, Thing\n");
    fclose(thing1);

    char temp[80];
    FILE* thing2 = fopen("/tmp/thing1.txt", "r");
    fgets(temp, 80, thing2);
    fclose(thing1);

    printf("Message was: [%s]\n", temp);

    return 0;
}
