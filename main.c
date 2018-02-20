#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct produitStruct {
    int pr_cd_pr;
    char pr_desi[100];
    char pr_stre[100];
    char pr_douane[100];
    char pr_prac[100];
    char pr_deg[100];
    char pr_pdn[100];
    char pr_pdb[100];
    char pr_four[100];
    char pr_refour[100];
    char pr_codebarre[100];
    char pr_marque[100];
    char pr_prix[100];
    char pr_pack[100];
};

//struct produitStruct produitArray[1000];

int getMyCol(char table[], int index, char chaine_work[]) {
    int i = 0;
    int j = 0;
    int compt = 1;

    while (table[i] != '\0') {
        if (table[i] == ';') {
            compt++;
        }

        if (compt == index && table[i] != ';') {
            chaine_work[j] = table[i];
            j++;
        }

        i++;
    }

    return j;
}

void writeSqlQuery() {
    const char *sqlQuery = "INSERT INTO "
                            "produit (pr_cd_pr, pr_desi, pr_stre, pr_douane, pr_prac, pr_deg, pr_pdn, pr_pdb, pr_four, pr_refour, pr_codebarre, pr_marque, pr_prix, pr_pack) "
                            "VALUES %s";

    // Ouverture/création du fichier
    FILE* sqlFile = fopen("dataToInsert.sql", "w+");

    if (sqlFile == NULL)
    {
        printf("Erreur d'ouverture de fichier\n");
        return;
    }

    // TODO : faire boucle for each
    char *sqlValues = "(A1, B1, C1, D1, E1)";

    /*if (sizeof(vector) > 2) {
        for(int i = 1) {
            strcat(sqlValues, ", (A1, B1, C1, D1, E1)")
        }
    }*/

    fprintf(sqlFile, sqlQuery, sqlValues);

    fclose(sqlFile);
}

int main()
{
    FILE* file = fopen("coty.csv", "r");

    char line[1024];

    char champ[100] = {'\0'};
    char *marque;

    int minLine = 0;
    int i = 0;

    //vector<produitStruct> produitVector;
    struct produitStruct produitArray[1000];

    while (fgets(line, sizeof(line), file)) {
        minLine++;

        if(minLine > 5) {
            char* tmp = strdup(line);
            //printf(tmp);

            if(getMyCol(tmp, 1, champ) == 0) {
                memset(&champ[0], 0, 99);

                getMyCol(tmp, 3, champ);
                marque = champ;
                memset(&champ[0], 0, 99);
            } else if(getMyCol(tmp, 1, champ) > 0) {
                //printf("Mon champ : %s | Val de i : %d\n", champ, i);
                strcpy(produitArray[i].pr_refour, champ);
                memset(&champ[0], 0, 99);

                getMyCol(tmp, 3, champ);
                strcpy(produitArray[i].pr_desi, champ);
                memset(&champ[0], 0, 99);
                getMyCol(tmp, 4, champ);
                strcat(produitArray[i].pr_desi, champ);
                strcat(produitArray[i].pr_desi, " ML");
                memset(&champ[0], 0, 99);

                getMyCol(tmp, 5, champ);
                strcpy(produitArray[i].pr_pack, champ);
                memset(&champ[0], 0, 99);

                getMyCol(tmp, 6, champ);
                strcpy(produitArray[i].pr_prac, champ);
                memset(&champ[0], 0, 99);

                getMyCol(tmp, 7, champ);
                strcpy(produitArray[i].pr_prix, champ);
                memset(&champ[0], 0, 99);

                getMyCol(tmp, 8, champ);
                strcpy(produitArray[i].pr_codebarre, champ);
                memset(&champ[0], 0, 99);

                strcpy(produitArray[i].pr_marque, marque);

                produitArray[i].pr_cd_pr = 1000000 + i;

                i++;
            }

        }
    }

    for(int k = 0; k < 10; k++) {
        printf("Mon tableau : %s\n", produitArray[k].pr_desi);
        printf("pr_cd_pr : %d\n", produitArray[k].pr_cd_pr);
    }

    return 0;
}
