#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Movie_Budget{
    int budget, year;
    char *name;
    struct Movie_Budget *next;
} Movie_Budget;


typedef struct Movie_Name{
    char *genre, *name;
    double score;
    struct Movie_Name *next;
} Movie_Name;


typedef union {
    int integer;
    double dob;
    char text[50];
} commands;


int intScan (int *input)
{
    if(scanf("%d", input)!=1)
    {
        while(getchar()!='\n');
        printf("\nTRY AGAIN...\n");
        return 0;
    }

    else return 1;
}


int dobScan (double *input)
{
    if(scanf("%lf", input)!=1)
    {
        while(getchar()!='\n');
        printf("\nTRY AGAIN...\n");
        return 0;
    }

    else return 1;
}


/*   Searches for a string in an array of strings   */
int strInArr_check (char target[], char **sarr, int arr_size)
{
	int i;
    for(i=0;i<arr_size;i++)
        if(strcmp(target, *(sarr+i))==0) 
            return i+1;
    
    return -1;
}


int check_strInList (Movie_Budget ***headB, Movie_Name ***headN, char *name)
{
    Movie_Budget **tempB = *headB;
    Movie_Name **tempN = *headN;

    for (;*tempB!=NULL; (tempB = &((*tempB)->next)) && (tempN = &((*tempN)->next)))
        if (strcmp((*tempB)->name, name)==0)
        {
            *headB = tempB;
            *headN = tempN;
            return 1;
        }

    return 0;
}


void sorted_insert (Movie_Budget **headBudget, Movie_Name **headName, Movie_Budget *new_movieB, Movie_Name *new_movieN)
{
    int i;
    Movie_Budget **tempheadB, **tempB;
    Movie_Name **tempheadN, ** tempN;

    tempheadB = headBudget;
    tempheadN = headName;

    while(1)
    {
        if (*headBudget == NULL) 
        {
            new_movieB->next = NULL;
            new_movieN->next = NULL;
            *headBudget = new_movieB;
            *headName = new_movieN;
            break;
        }

        else if (strcmp((*headBudget)->name, new_movieB->name)==0)
        {
            free((*headBudget)->name);
            free(*headBudget);
            tempB = &((*headBudget)->next);
            tempN = &((*headName)->next);
            *headBudget = (*headBudget)->next;
            *headName = (*headName)->next;
            sorted_insert (tempheadB, tempheadN, new_movieB, new_movieN);
            break;
        }

        else if ((*headBudget)->year < new_movieB->year)
        {
            if (check_strInList (&headBudget, &headName, new_movieB->name)==1)
            {
                free((*headBudget)->name);
                free(*headBudget);
                tempB = &((*headBudget)->next);
                tempN = &((*headName)->next);
                *headBudget = (*headBudget)->next;
                *headName = (*headName)->next;
                sorted_insert (tempheadB, tempheadN, new_movieB, new_movieN);
                break;
            }

            new_movieB->next = *headBudget;
            new_movieN->next = *headName;
            *headBudget = new_movieB;
            *headName = new_movieN;
            break;
        }

        else if ((*headBudget)->year == new_movieB->year)
        {
            if (check_strInList (&headBudget, &headName, new_movieB->name)==1)
            {
                free((*headBudget)->name);
                free(*headBudget);
                tempB = &((*headBudget)->next);
                tempN = &((*headName)->next);
                *headBudget = (*headBudget)->next;
                *headName = (*headName)->next;
                sorted_insert (tempheadB, tempheadN, new_movieB, new_movieN);
                break;
            }

            while(*headBudget != NULL && (*headBudget)->year == new_movieB->year && (*headBudget)->budget > new_movieB->budget) 
            {
                headBudget = &((*headBudget)->next);
                headName = &((*headName)->next);
            }

            new_movieB->next = *headBudget;
            new_movieN->next = *headName;
            *headBudget = new_movieB;
            *headName = new_movieN;
            break;
        }

        headBudget = &((*headBudget)->next);
        headName = &((*headName)->next);
    }
}


void list_to_arr (char *listName, char ***genre_list, int *genre_num, Movie_Name **headName, Movie_Budget **headBudget)
{
    char line[1024], *token, **temparr, *new_genre, *newName;
    int i, j;
    FILE *file;
    Movie_Budget *new_movieB;
    Movie_Name *new_movieN;

    if((file = fopen("Movies.txt", "r")) == NULL)
    {
        printf("\nUNABLE TO OPEN FILE\n\n");
        return;
    }

    *(genre_list) = (char **)calloc(1, sizeof(char *));

    fgets(line, 1024, file);

    while (fgets(line, 1024, file)!=NULL)
    {
        new_movieB = (Movie_Budget*)malloc(sizeof(Movie_Budget));
        new_movieN = (Movie_Name*)malloc(sizeof(Movie_Name));

        token = strtok(line, ",");
        if(strcmp(token, "unknown")!=0) new_movieB->budget = atoi(token);
        else    new_movieB->budget = -1;

        token = strtok(NULL, ",");
        new_genre = (char*)calloc(strlen(token)+1, sizeof(char));
        strcpy(new_genre, token);
        new_movieN->genre = new_genre;

        if (strInArr_check (token, *genre_list, *genre_num) == -1)
        {
            temparr = (char **)calloc(++*genre_num, sizeof(char *));

            for(j=0;j<*genre_num;j++)
                temparr[j] = (*genre_list)[j];

            free(*genre_list);
            *genre_list = temparr;
            *(*genre_list + (*genre_num)-1) = new_genre;
        }

        token = strtok(NULL, ",");
        newName = (char *)calloc(strlen(token)+1, sizeof(char));
        strcpy(newName, token);
        new_movieN->name = newName;
        new_movieB->name = newName;

        new_movieN->score = strtod(strtok(NULL, ","), NULL);

        new_movieB->year = atoi(strtok(NULL, ","));

        sorted_insert (headBudget, headName, new_movieB, new_movieN);
    }

    fclose(file);
}


void print_list(Movie_Budget * listB, Movie_Name * listN)
{
    FILE *out;
    out = fopen("list.txt", "w");
    for(; (listB!=NULL) ; (listB = listB->next) && (listN = listN->next))
        fprintf(out, "%d,%s,%s,%.1f,%d\n", listB->budget, listB->name, listN->genre, listN->score, listB->year);

    fclose(out);
}


double avg_score(Movie_Name * listN)
{
    double sum = 0;
    int counter = 0;

    for(; (listN!=NULL) ; (listN = listN->next) && (counter++))
        sum += listN->score;

    return sum/counter;
}


void print_list_genre(char ** list, int entry_num)
{
    int i;

    for(i=0;i<entry_num;i++)
        printf("%s\n", *(list+i));
}


void list_by_year (Movie_Budget *head, int target_year, int direction)
{
    if (direction == 0)
    {
        for (; (head != NULL) && (head->year >= target_year) ; (head = head->next));

        if (head == NULL)
        {
            printf("Cannot find movies in the requested range.\n");
            return;
        }

        for (; (head != NULL) ; (head = head->next))
            printf("%s\n", head->name);
    }

    if (direction == 1)
    {
        if (head->year < target_year)
        {
            printf("Cannot find movies in the requested range.\n");
            return;
        }

        for (; (head != NULL) && (head->year >= target_year) ; (head = head->next))
            printf("%s\n", head->name);
    }
}


void list_by_score (Movie_Name *head, double target_score, int direction)
{
    if (direction == 0)
        for (; (head != NULL) ; (head = head->next))
            if(head->score < target_score)
                printf("%s\n", head->name);

    if (direction == 1)
        for (; (head != NULL) ; (head = head->next))
            if(head->score >= target_score)
                printf("%s\n", head->name);
}


void movie_manager (char *fileName)
{
    int command2, field, error, entryNum=0, genre_num=0;
    commands command;
    char **genrelist;
    Movie_Budget *Budget_list = 0, **tempB;
    Movie_Name *Name_list = 0, **tempN;

    list_to_arr (fileName, &genrelist, &genre_num, &Name_list, &Budget_list);
    print_list(Budget_list, Name_list);

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

        if(intScan(&(command.integer))!=1)    continue;

        switch (command.integer)
        {
            case 1: printf("\n\n1. Budget\n2. Genre\n3. Name\n4. Score\n5. Year");
                    printf("\n\nSelect an Operation: ");
            
                    if(intScan(&field)!=1||field<1||field>5)   
                    {
                        error = 1;
                        break;
                    }

                    printf("\n1. Single Selection");
                    printf("\n2. Multiple Selection");
            
                    printf("Select an Operation: ");
            
                    if(intScan(&command.integer)!=1||command.integer<1||command.integer>2)
                    {
                        error = 1;
                        break;
                    }

                    if(command.integer==2)
                    {
                        printf("Enter start value: ");
                        if(intScan(&command.integer)!=1)
                        {
                            error = 1;
                            break;
                        }

                        printf("Enter end value: ");
                        if(intScan(&command2)!=1)
                        {
                            error = 1;
                            break;
                        }
                    }

                    else{
                        printf("Enter value: ");
                        if(intScan(&command.integer)!=1)
                        {
                            error = 1;
                            break;
                        }

                        command2 = command.integer;
                    }
                    break;


            case 2: print_list_genre(genrelist, genre_num);
                    break;


            case 3: printf("Enter a year:\n");
                    if(intScan(&command.integer)!=1)
                    {
                        error = 1;
                        break;
                    }

                    printf("until that year (0) or since that year (1)?\n");
                    if(intScan(&command2)!=1 || (command2!=0 && command2!=1))
                    {
                        error = 1;
                        break;
                    }

                    list_by_year (Budget_list, command.integer, command2);
                    break;

            case 4: printf("Enter a score:\n");
                    if(dobScan(&command.dob)!=1||command.dob>10||command.dob<0)
                    {
                        error = 1;
                        break;
                    }

                    printf("Less than that score (0) or greater than that score (1)?\n");
                    if(intScan(&command2)!=1 || (command2!=0 && command2!=1))
                    {
                        error = 1;
                        break;
                    }

                    list_by_score (Name_list, command.dob, command2);
                    break;

            case 5: printf("Please enter the name of the movie: ");
                    while(getchar()!='\n');
                    fgets (command.text, 50, stdin);
                    command.text[strlen(command.text)-1] = 0;
                    tempB = &Budget_list;
                    tempN = &Name_list;
                    
                    if (check_strInList (&tempB, &tempN, command.text) == 0)
                    {
                        printf("No such movie is found.\n");
                        break;
                    }

                    if ((*tempB)->budget == -1) printf("Budget: Unknown");
                    else printf("Budget: %d", (*tempB)->budget);

                    printf("\nGenre: %s\nName: %s\nScore: %.1f\nYear: %d\n", (*tempN)->genre, (*tempB)->name, (*tempN)->score, (*tempB)->year);
                    break;

            case 6: command.dob = avg_score(Name_list);
                    printf("Average: %.3f\n", command.dob);
                    break;

        }

        if(error == 1)
        {
            error = 0;
            printf("Invalid input...");
        }
    }
}


int main ()
{
    char listname[] = "Movies.txt";
    
    movie_manager (listname);
}