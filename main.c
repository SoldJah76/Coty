#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* file = fopen("Csv_test.csv", "r");

    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        char* tmp = strdup(line);
        printf(tmp);

        // Appeler la fonction de JO et Vincent
    }


    return 0;
}
