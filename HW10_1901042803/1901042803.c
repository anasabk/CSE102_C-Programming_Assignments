/*
    This code is not finished completely, 
    it only stores the whole file in an array
    and prints the list and the found genres to the terminal.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    double budget;
    int genre;
    char *name;
    double score;
    int year;
} Movie;


/*int intScan (int *input)
{
    if(scanf("%d", input)!=1)
    {
        while(getchar()!='\n');
        printf("\nTRY AGAIN...\n");
        return 0;
    }

    else return 1;
}*/


/*   Finds a string's equivalent in an array of strings   */
int strInArr_check (char target[], char **sarr, int arr_size)
{
	int i;

    for(i=0;i<arr_size;i++)
        if(strcmp(target, *(sarr+i))==0) return i+1;
    
    return -1;
}


Movie *list_to_arr (char *listName, int *entryNum, char ***genre_list, int *genre_num)
{
    char line[1024], *token, **temparr, *new_genre, *newName;
    int i, j;
    FILE *list;
    Movie *movieArr;

    *genre_num = 0;

    if((list = fopen("/mnt/d/projects/C and C++/Homeworks/Homework 10/Movies.txt", "r")) == NULL)
    {
        printf("FAILED");
        return 0;
    }
    
    while(fgets(line, 1024, list)!=NULL)    (*entryNum)++;

    *(genre_list) = (char **)calloc(1, sizeof(char *));
    movieArr = (Movie *)calloc(*entryNum, sizeof(Movie));

    rewind(list);
    fgets(line, 1024, list);
    for(i=0 ; (i<*entryNum) && (fgets(line, 1024, list)!=NULL) ; i++)
    {
        token = strtok(line, ",");
        if(strcmp(token, "unknown")!=0) (movieArr+i)->budget = strtod(token, NULL);
        else (movieArr+i)->budget = -1;

        token = strtok(NULL, ",");
        if(((movieArr+i)->genre = strInArr_check (token, *genre_list, *genre_num)) == -1)
        {
            new_genre = (char *)calloc(strlen(token)+1, sizeof(char));
            temparr = (char **)calloc(++*genre_num, sizeof(char *));

            strcpy(new_genre, token);

            for(j=0;j<*genre_num;j++)
                temparr[j] = (*genre_list)[j];

            free(*genre_list);
            *genre_list = temparr;
            *(*genre_list+j-1) = new_genre;
            (movieArr+i)->genre = strInArr_check (new_genre, *genre_list, *genre_num);
        }

        token = strtok(NULL, ",");
        newName = (char *)calloc(strlen(token)+1, sizeof(char));
        strcpy(newName, token);
        (movieArr+i)->name = newName;

        (movieArr+i)->score = strtod(strtok(NULL, ","), NULL);

        (movieArr+i)->year = atoi(strtok(NULL, ","));
    }

    fclose(list);

    return  movieArr;
}


void print_list(Movie * list, int entry_num)
{
    int i;

    for(i=0;i<entry_num-1;i++)
        printf("%.2f, %d, %s, %.1f, %d\n", (list+i)->budget, (list+i)->genre, (list+i)->name, (list+i)->score, (list+i)->year);
}


void print_list_g(char ** list, int entry_num)
{
    int i;

    for(i=0;i<entry_num;i++)
        printf("%s\n", *(list+i));
}


/*void movie_manager (char *fileName)
{
    int command, endRule;
    char **genre;
    Movie *list;

    while(1)
    {
        printf("\n1. List of Sorted Data");
        printf("\n2. List of Genres");
        printf("\n3. List of Movie through the Years");
        printf("\n4. List of Movie through the Scores");
        printf("\n5. All Informations of a Single Movie");
        printf("\n6. Average of the IMDB Scores");
        printf("\n7. Frequence of the Genres");
        printf("\n8. Exit");
        printf("\n\nPlease Select an Operation: ");

        if(intScan(&command)!=1)    continue;

        switch (command)
        {
            case 1: printf("\n\n1. Budget\n2. Genre\n3. Name\n4. Score\n5. Year");
                    printf("\n\nSelect an Operation: ");
            
                    if(intScan(&command)!=1||command<1||command>5)    continue;

                    printf("\n1. Single Selection");
                    printf("\n2. Multiple Selection");
            
                    printf("Select an Operation: ");
            
                    if(intScan(&command)!=1||command<1||command>2)    continue;

                    if(command==2)
                    {
                        printf("Enter start value: ");
                        if(intScan(&command)!=1)    continue;

                        printf("Enter end value: ");
                        if(intScan(&endRule)!=1)    continue;
                    }

                    else{
                        printf("Enter value: ");
                        if(intScan(&command)!=1)    continue;

                        endRule = command;
                    }

                    findIn_sorted (list, command, endRule);

                    break;

            case 2: break;
        }
    }
}*/

int main ()
{
    Movie *listed;
    char listname[] = "Movies.txt", **genrelist;
    int entryNum=0, genre_num;

    listed = list_to_arr (listname, &entryNum, &genrelist, &genre_num);
    printf("%.2f, %d", listed->budget, listed->genre);
    print_list(listed, entryNum);
    print_list_g(genrelist, genre_num);
}