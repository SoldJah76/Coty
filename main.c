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

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s));
}

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

void writeSqlQuery(struct produitStruct myArray[], int compteur) {
    /*for(int k = 0; k < 10; k++) {
        printf("Mon tableau : %s\n", myArray[k].pr_desi);
        printf("pr_cd_pr : %d\n", myArray[k].pr_cd_pr);
    }*/

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

    char sqlValues[1000] = {'\0'};

    //strcat(sqlValues, "toto");
    strcat(sqlValues, "(");

    /*strcat(sqlValues, (char*)myArray[0].pr_cd_pr);
    strcat(sqlValues, ", ");*/
    strcat(sqlValues, myArray[0].pr_desi);
    strcat(sqlValues, ", ");
    strcat(sqlValues, "0");
    strcat(sqlValues, ", ");
    strcat(sqlValues, "0");
    strcat(sqlValues, ", ");
    strcat(sqlValues, myArray[0].pr_prac);
    strcat(sqlValues, ", ");
    strcat(sqlValues, "0");
    strcat(sqlValues, ", ");
    strcat(sqlValues, "0");
    strcat(sqlValues, ", ");
    strcat(sqlValues, "0");
    strcat(sqlValues, ", ");
    strcat(sqlValues, "0");
    strcat(sqlValues, ", ");
    strcat(sqlValues, myArray[0].pr_refour);
    strcat(sqlValues, ", ");
    strcat(sqlValues, myArray[0].pr_codebarre);
    strcat(sqlValues, ", ");
    strcat(sqlValues, myArray[0].pr_marque);
    strcat(sqlValues, ", ");
    strcat(sqlValues, myArray[0].pr_prix);
    strcat(sqlValues, ", ");
    strcat(sqlValues, myArray[0].pr_pack);

    strcat(sqlValues, ")");

    if (compteur > 1) {
        for(int i = 1; i < compteur; i++) {
            printf("Valeur de i : %d\n", i);
            printf("Valeur de compteur : %d\n", compteur);
            printf("pr_desi : %s\n", myArray[i].pr_desi);


            strcat(sqlValues, ",\n (");

            /*//strcat(sqlValues, (char*)myArray[0].pr_cd_pr);
            //strcat(sqlValues, ", ");
           // strcat(sqlValues, myArray[i].pr_desi);
            //strcat(sqlValues, ", ");
            strcat(sqlValues, "0");
            strcat(sqlValues, ", ");
            strcat(sqlValues, "0");
            strcat(sqlValues, ", ");
            //strcat(sqlValues, myArray[i].pr_prac);
            //strcat(sqlValues, ", ");
            strcat(sqlValues, "0");
            strcat(sqlValues, ", ");
            strcat(sqlValues, "0");
            strcat(sqlValues, ", ");
            strcat(sqlValues, "0");
            strcat(sqlValues, ", ");
            strcat(sqlValues, "0");
            strcat(sqlValues, ", ");
            /*strcat(sqlValues, myArray[i].pr_refour);
            strcat(sqlValues, ", ");
            strcat(sqlValues, myArray[i].pr_codebarre);
            strcat(sqlValues, ", ");
            strcat(sqlValues, myArray[i].pr_marque);
            strcat(sqlValues, ", ");
            strcat(sqlValues, myArray[i].pr_prix);
            strcat(sqlValues, ", ");
            strcat(sqlValues, myArray[i].pr_pack);*/

            strcat(sqlValues, ", )");
        }
    }

    fprintf(sqlFile, sqlQuery, sqlValues);
    fclose(sqlFile);
}

int main()
{
    FILE* file = fopen("coty.csv", "r");

    char line[1024];

    char champ[100] = {'\0'};
    char marque[100] = {'\0'};

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
                strcpy(marque, champ);

            } else if(getMyCol(tmp, 1, champ) > 0) {
                               strcpy(produitArray[i].pr_refour, rtrim(champ));
                memset(&champ[0], 0, 99);

                getMyCol(tmp, 3, champ);
                strcpy(produitArray[i].pr_desi, rtrim(champ));
                memset(&champ[0], 0, 99);
                getMyCol(tmp, 4, champ);
                strcat(produitArray[i].pr_desi, rtrim(champ));
                strcat(produitArray[i].pr_desi, " ML");
                memset(&champ[0], 0, 99);

                getMyCol(tmp, 5, champ);
                strcpy(produitArray[i].pr_pack, rtrim(champ));
                memset(&champ[0], 0, 99);

                getMyCol(tmp, 6, champ);
                strcpy(produitArray[i].pr_prac, rtrim(champ));
                memset(&champ[0], 0, 99);

                getMyCol(tmp, 7, champ);
                strcpy(produitArray[i].pr_prix, rtrim(champ));
                memset(&champ[0], 0, 99);

                getMyCol(tmp, 8, champ);
                strcpy(produitArray[i].pr_codebarre, rtrim(champ));
                memset(&champ[0], 0, 99);

                strcpy(produitArray[i].pr_marque, marque);

                produitArray[i].pr_cd_pr = 1000000 + i;

                i++;
            }
        }
    }

    writeSqlQuery(produitArray, i);

    return 0;
}
