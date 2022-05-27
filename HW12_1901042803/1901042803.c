#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct word_list_t word_list_t1;

/*Linked list to store the synonyms of a word*/
typedef struct syn_seq {
    struct word_list_t *node;        /*Pointer to the synonym*/
    struct syn_seq *next;
} syn_seq;

/*Linked list to store the antonyms of a word*/
typedef struct ant_seq {
    struct word_list_t *node;        /*Pointer to the antonym*/
    struct ant_seq *next;
} ant_seq;

/*Linked list to store every word in the given files*/
typedef struct word_list_t {
    syn_seq *synonyms;  /*Linked list to store the pointers to the synonyms of the word*/
    ant_seq *antonyms;  /*Linked list to store the pointers to the antonyms of the word*/

    int syn_asked,  /*How many times the word was asked in a synonym question*/
        ant_asked,  /*How many times the word was asked in an antonym question*/
        score;  /*The total score of the answers, +1 for correct, -1 for wrong answers*/

    char word[18];
    struct word_list_t * next;
} word_list_t;

/*Linked list tp store the record of a user*/
typedef struct user_rec_t {
    int qtype,      /*Question type, 0 for synonym and 1 for antonym*/ 
        result;     /*1 for correct and -1 for wrong answer*/

    char main_word[18], answer[18]; /*stores the main words and the answers*/
    struct user_rec_t *next;
} user_rec_t;

/*Multi-purpose variable type for input*/
typedef union {
    int integer;
    char string[60];
} int_str_t;


/*Scans for integer avoiding wrong input, return 0 on fail, 1 on success*/
int intScan (int *input)
{
    if(scanf("%d", input)!=1)
    {
        while(getchar()!='\n'); /*deletes the junk in stdin*/
        printf("\nInvalid input...\n\n");
        return 0;
    }

    else return 1;
}


/*Removes end-of-line non-alphabetic characters from the line*/
void remove_line_adds (char *line)
{
    if( *line != 0 &&
        !(line[strlen(line)-1] >= 'a' && line[strlen(line)-1] <= 'z') && 
        !(line[strlen(line)-1] >= 'A' && line[strlen(line)-1] <= 'Z') &&
        !(line[strlen(line)-1] >= '0' && line[strlen(line)-1] <= '9'))
    {
        line[strlen(line)-1] = 0;   /*Replace the character with a NULL*/
        remove_line_adds (line);    /*Recall the function with the new string*/
    }

    else return; 
}


/*Search the word list for target*/
word_list_t ** search_list (word_list_t **list_head, char * target)
{
    for (; (*list_head != NULL) && (strcmp((*list_head)->word, target) != 0) ; list_head = &((*list_head)->next));
    
    return list_head;   /*Return the target node if found, will return NULL on fail*/
}


/*Search the synonyms of word for target, return target's address*/
word_list_t * search_syn (word_list_t *word, char * target)
{
    syn_seq *sequence = word->synonyms; /*The head of the synonym list*/

    for (; (sequence != NULL) && (strcmp(sequence->node->word, target) != 0) ; sequence = sequence->next);

    if (sequence == NULL)   /*return NULL when not found*/
        return NULL;

    else return sequence->node; /*return the target node's address when found*/
}


/*Search the antonyms of word for target, return target's address*/
word_list_t * search_ant (word_list_t *word, char * target)
{
    ant_seq *sequence = word->antonyms; /*The head of the antonym list*/

    for (; (sequence != NULL) && (strcmp(sequence->node->word, target) != 0) ; sequence = sequence->next);

    if (sequence == NULL)   /*return NULL when not found*/
        return NULL;

    else return sequence->node; /*return the target node's address when found*/
}


/*Give a word by it's order in the list*/
word_list_t ** search_by_order (word_list_t **list_head, int order)
{
    for (; (order > 0) && (*list_head != NULL) ; (list_head = &((*list_head)->next)) && (order--));

    return list_head;   /*Return the target node's address if found, will return NULL on fail*/
}


/*Add a new word to the list*/
word_list_t ** add_new_word (word_list_t **list_head,   /*word List's head*/
                           char *new_word, /*New word to be added*/
                           int *word_num)  /*Total number of words in the list*/
{
    word_list_t **new_node; /*New_word's node*/

    new_node = search_list(list_head, new_word); /*Be sure the word isn't in the list, if it was there, return it's address*/

    /*Create the word's node if it wasn't found*/
    if(*new_node == NULL)
    {
        *new_node = (word_list_t *)calloc(1, sizeof(word_list_t));
        strcpy((*new_node)->word, new_word);    /*Copy the new word to the node*/
        (*word_num)++;      /*Increase the total number of words*/
    }

    return new_node;    /*Return the address of the new word's node*/
}


/*Add child_word to the synonym list of main_node*/
void add_new_syn (word_list_t **list, /*word List's head*/
                  word_list_t ** main_word, /*The main_word where child_word will be added to*/
                  char *child_word,   /*The word to be added to main_word's synonyms*/
                  int *word_num)    /*Total number of words in word list*/
{
    syn_seq *temp;  /*Temporariy address variable*/
    word_list_t ** child_node;  /*child_word's node*/

    child_node = add_new_word (list, child_word, word_num); /*take the child_word's address from the list if it existed, insert it in case it's totally new*/

    if (search_syn(*main_word, child_word) == NULL) /*Scan the synonym list of node */
    {
        /*Inserting child_word to the synonym list of main_word*/
        temp = (*main_word)->synonyms;
        (*main_word)->synonyms = (syn_seq *)calloc(1, sizeof(syn_seq));
        (*main_word)->synonyms->next = temp;
        (*main_word)->synonyms->node = *child_node;

        /*Inserting main_word to the synonym list of child_word*/
        temp = (*child_node)->synonyms;
        (*child_node)->synonyms = (syn_seq *)calloc(1, sizeof(syn_seq));
        (*child_node)->synonyms->next = temp;
        (*child_node)->synonyms->node = *main_word;
    }
}


/*Add target_word to the antonym list of node*/
void add_new_ant (word_list_t **list, /*word List's head*/
                  word_list_t ** main_word, /*The main_word where child_word will be added to*/
                  char *child_word,   /*The word to be added to main_word's antonyms*/
                  int *word_num)    /*Total number of words in word list*/
{
    ant_seq *temp;  /*Temporariy address variable*/
    word_list_t ** child_node; /*child_word's node*/

    child_node = add_new_word (list, child_word, word_num); /*take the child_word's address from the list if it existed, insert it in case it's totally new*/

    if (search_ant(*main_word, child_word) == NULL) /*Scan the antonym list of node */
    {
        /*Inserting child_word to the antonym list of main_word*/
        temp = (*main_word)->antonyms;
        (*main_word)->antonyms = (ant_seq *)calloc(1, sizeof(ant_seq));
        (*main_word)->antonyms->next = temp;
        (*main_word)->antonyms->node = *child_node;

        /*Inserting main_word to the antonym list of child_word*/
        temp = (*child_node)->antonyms;
        (*child_node)->antonyms = (ant_seq *)calloc(1, sizeof(ant_seq));
        (*child_node)->antonyms->next = temp;
        (*child_node)->antonyms->node = *main_word;
    }
}


/*Update the files in syn_path and ant_path with the new lists*/
void update_files (word_list_t * list, char *syn_path, char *ant_path)
{
    word_list_t *head = list; /*head of the word list*/
    syn_seq *temps;
    ant_seq *tempa;
    FILE *out;      /*pointer to the target file*/
    int i;

    out = fopen(syn_path, "w");   /*Open the synonyms file*/

    /*Over-write the files*/
    for(; (list!=NULL) ; list = list->next)
    {
        /*Check that the word has more than one synonym*/
        for ((temps = list->synonyms) && (i=0); (temps != NULL) && (i < 1) ; (temps = temps->next) && (i++));

        /*If the word had one or no synonyms, it will be skipped*/
        if (temps != NULL)
        {
            fprintf(out, "%s =", list->word);    /*Print the main word*/

            /*Print the synonyms*/
            for((temps = list->synonyms) ; temps != NULL ; temps = temps->next)
                fprintf(out, " %s", temps->node->word);

            fprintf(out, "\n");
        }
    }

    fclose(out);  /*Close the synonyms file*/

    out = fopen(ant_path, "w");  /*Open the antonyms file*/

    /*Over-write the files*/
    for(list = head ; (list!=NULL) ; list = list->next)
    {
        /*Check that the word has more than one antonym*/
        for ((tempa = list->antonyms) && (i=0); (tempa != NULL) && (i < 1) ; (tempa = tempa->next) && (i++));

        /*If the word had one or no antonyms, it will be skipped*/
        if (tempa != NULL)
        {
            fprintf(out, "%s =", list->word);    /*Print the main word*/

            /*Print the antonyms*/
            for((tempa = list->antonyms) ; tempa != NULL ; tempa = tempa->next)
                fprintf(out, " %s", tempa->node->word);

            fprintf(out, "\n");
        }
    }

    fclose(out);    /*Close the antonyms file*/
}


/*Import the words from the files to word_list*/
size_t import_words (word_list_t ** word_list, char *syn_file, char *ant_file, int *word_num)
{
    char buffer[1024], * token;
    FILE * antonym_file, * synonym_file;
    word_list_t **temp_node;
    size_t total_size;   /*The size of both files in bytes*/

    *word_num = 0;      /*Initialize the total number of words by 0*/

    if ((synonym_file = fopen(syn_file, "r")) == NULL)    /*Open synonyms' file*/
    {
        printf("\n%s does not exist.\n", syn_file);
        return 0;
    }

    /*Scan the file line by line*/
    while(fgets(buffer, 1024, synonym_file) != NULL)
    {
        total_size += strlen(buffer);    /*Increase total size by the number of charachters in the line*/
        remove_line_adds (buffer);  /*Clean the line's end from fgets's extra characters*/

        /*Get the main word*/
        token = strtok(buffer, " ");
        if (strlen(token) >= 17) continue;  /*skip the main word if it was too long*/

        temp_node = add_new_word (word_list, token, word_num); /*Add the new word to the list*/

        /*Add the rest of the line as child words to main word's synonym list*/
        strtok(NULL, " ");
        while((token = strtok(NULL, " ")) != NULL)
        {
            if (strlen(token) >= 17) /*skip the word if it was too long*/
                continue;

            /*Add the word to the synonym list*/
            add_new_syn(word_list, temp_node, token, word_num);
        }
    }

    /*close the synonyms' file*/
    fclose(synonym_file);

    /*Open the antonyms' file*/
    if ((antonym_file = fopen(ant_file, "r")) == NULL)
    {
        printf("\n%s does not exist.\n", ant_file);
        return 0;
    }

    /*Scan the file line by line*/
    while(fgets(buffer, 1024, antonym_file) != NULL)
    {
        total_size += strlen(buffer);    /*Increase total size by the number of charachters in the line*/
        remove_line_adds (buffer);  /*Clean the line's end from fgets's extra characters*/
        
        /*Get the main word*/
        token = strtok(buffer, " ");
        if (strlen(token) >= 17) continue;  /*skip the main word if it was too long*/

        temp_node = add_new_word (word_list, token, word_num); /*Add the new word to the list*/

        /*Add the rest of the line as child words to main word's antonym list*/
        strtok(NULL, " ");
        while((token = strtok(NULL, " ")) != NULL)
        {
            if (strlen(token) >= 17) /*skip the word if it was too long*/
                continue;

            /*Add the word to the antonym list*/
            add_new_ant(word_list, temp_node, token, word_num);
        }
    }

    fclose(antonym_file);    /*Close the antonyms' file*/

    return total_size;  /*Return the total size of the files*/
}


/*Literally, a question engine. Chooses words from word_list for questions based on each word's ask times*/
void question_engine (word_list_t ** word_list, /*List of words*/
                      int *word_num, /*Total_number of words in word_list*/
                      user_rec_t **user_record) /*The up-to-date user record*/

/*The chances in this system are as follow:
    For example: the word was asked 7 times, a random number is chosen beyween 1 and 7, if the chosen number is 7, then the word is accepted.
    The chosen number is chosen from 7 different numbers, so the chance for the number to match the times the word is asked (which is 7) is 1 over 7.

    The same applys for the question type (Antonym or synonym), but add that the times a question is asked is devided by the times the other question was asked.*/
{
    int rand_num;
    word_list_t **target;
    int_str_t command;

    for (; (*user_record != NULL) ; (user_record = &((*user_record)->next)));   /*Go to the end of user_record*/


/*Ask the first question randomly*/
    rand_num = rand() % *word_num;  /*Create a random number to find it in the word_list's order*/
    target = search_by_order (word_list, rand_num); /*Find the word in the requested order*/
    rand_num = rand() % 2;

    if (rand_num == 0)
    {
        /*Increase the syn_asked counter by 1*/
        (*target)->syn_asked++;

        printf("\nGive a synonym of the word \"%s\":\n", (*target)->word);
        scanf("%s", command.string);

        /*Insert a new user_record node and assign the values of the session to it*/
        *user_record = (user_rec_t *)calloc(1 ,sizeof(user_rec_t)); /*Dynamically allocate the node*/
        (*user_record)->qtype = 0;  /*Record the question type*/
        strcpy((*user_record)->main_word, (*target)->word);   /*store the main word*/
        strncpy((*user_record)->answer, command.string, 17);   /*store the answer*/

        /*If the answer was one of the synonyms of the word, then it's correct*/
        if (search_syn(*target, command.string) != NULL)
        {
            (*user_record)->result = 1; /*Record the result as 1*/
            (*target)->score += 1;  /*Increase the score of the word by 1*/

            printf("\nYour answer is correct\n");
        }

        /*The answer is wrong*/
        else
        {
            (*user_record)->result = 0; /*Record the result as 0*/
            (*target)->score += -1; /*Reduce the score of the word by 1*/

            /*Take the choice to store the wrong answer as a correct one in word_list*/
            printf("\nYour answer is wrong, do you want to add your answer as a correct one?\n(Yes = 1    No = 0)\n");
            intScan (&command.integer);

            if (command.integer == 1)
                add_new_syn (word_list, target, (*user_record)->answer, word_num);  /*Add the answer as a synonym of the asked word*/
        }

        /*Change the end of user_record to the current node*/
        user_record = &((*user_record)->next);
    }

    /*The question is an antonym question*/
    else if (rand_num == 1)
    {
        /*Increase the ant_asked counter by 1*/
        (*target)->ant_asked++;

        printf("\nGive an antonym of the word \"%s\":\n", (*target)->word);
        scanf("%s", command.string);

        /*Insert a new user_record node and assign the values of the session to it*/
        *user_record = (user_rec_t *)calloc(1 ,sizeof(user_rec_t)); /*Dynamically allocate the node*/
        (*user_record)->qtype = 1;  /*Record the question type*/
        strcpy((*user_record)->main_word, (*target)->word);   /*store the main word*/
        strncpy((*user_record)->answer, command.string, 17);   /*store the answer*/

        /*If the answer was one of the antonyms of the word, then it's correct*/
        if (search_ant(*target, command.string) != NULL)
        {
            (*user_record)->result = 1; /*Record the result as 1*/
            (*target)->score += 1;  /*Increase the score of the word by 1*/

            printf("\nYour answer is correct\n");
        }
        
        /*The answer is wrong*/
        else
        {
            (*user_record)->result = 0; /*Record the result as 0*/
            (*target)->score += -1; /*Reduce the score of the word by 1*/

            /*Take the choice to store the wrong answer as a correct one in word_list*/
            printf("\nYour answer is wrong, do you want to add your answer as a correct one?\n(Yes = 1    No = 0)\n");
            intScan (&command.integer);

            if (command.integer == 1)
                add_new_ant (word_list, target, (*user_record)->answer, word_num);  /*Add the answer as a antonym of the asked word*/
        }

        /*Change the end of user_record to the current node*/
        user_record = &((*user_record)->next);
    }


/*Create questions by examining the words' chances*/
    /*Keep asking until being prompted to leave*/
    while (1)
    {  
        rand_num = rand() % *word_num;  /*Create a random number to find it in the word_list's order*/
        target = search_by_order (word_list, rand_num); /*Find the word in the requested order*/
        
        /*When the word was asked before*/
        if ((*target)->ant_asked + (*target)->syn_asked != 0)
        {
        /*Selection by total times a word is asked*/
            /*Pick a random number in the range of syn_asked + ant_asked*/
            rand_num = (rand() % ((*target)->syn_asked + (*target)->ant_asked)) + 1;

            /*if the picked number matched the total times the word was asked, then it's accepted, or it will search again for another word*/
            if (rand_num != ((*target)->syn_asked + (*target)->ant_asked))  continue;


        /*Selection by total score*/
            /*if the word recieved too many wrong answers, it will be chosen, or it will be tested by it's score*/
            if ((*target)->score > 0)
            {
                /*Pick a random number in the range of the score of the chosen word*/
                rand_num = rand() % ((*target)->score) + 1;

                /*If the picked number matched the score of the word, then it's accepted, or it will search again for another word*/
                if(rand_num != ((*target)->score))  continue;
            }


        /*Selectoin of question type using syn_asked and ant_asked*/
            /*If the word wasn't asked in a synonym question, then pick a synonym question*/
            if ((*target)->syn_asked == 0)  command.integer = 0;

            /*If the word wasn't asked in an antonym question, then pick an antonym question*/
            else if ((*target)->ant_asked == 0)  command.integer = 1;
            
            /*If the syn_asked was larger than ant_asked, then ant_asked would be like 0*/
            else if ((*target)->ant_asked / (*target)->syn_asked == 0)  command.integer = 1;

            /*If the syn_asked was larger than ant_asked, then ant_asked would be like 0*/
            else if ((*target)->syn_asked / (*target)->ant_asked == 0)  command.integer = 0;

            /*In this case, syn_asked and ant_asked are probably the same*/
            else command.integer = rand() % 2;
        }

        /*If the word wasn't asked before, pick it and pick a random question type for it*/
        else command.integer = rand() % 2;

        /*The question is a synonym question*/
        if (command.integer == 0)
        {
            /*Increase the syn_asked counter by 1*/
            (*target)->syn_asked++;

            printf("\nGive a synonym of the word \"%s\":\n", (*target)->word);
            scanf("%s", command.string);

            /*Insert a new user_record node and assign the values of the session to it*/
            *user_record = (user_rec_t *)calloc(1 ,sizeof(user_rec_t)); /*Dynamically allocate the node*/
            (*user_record)->qtype = 0;  /*Record the question type*/
            strcpy((*user_record)->main_word, (*target)->word);   /*store the main word*/
            strncpy((*user_record)->answer, command.string, 17);   /*store the answer*/

            /*If the answer was one of the synonyms of the word, then it's correct*/
            if (search_syn(*target, command.string) != NULL)
            {
                (*user_record)->result = 1; /*Record the result as 1*/
                (*target)->score += 1;  /*Increase the score of the word by 1*/
            
                printf("\nYour answer is correct\n");
            }

            /*The answer is wrong*/
            else
            {
                (*user_record)->result = 0; /*Record the result as 0*/
                (*target)->score += -1; /*Reduce the score of the word by 1*/

                /*Take the choice to store the wrong answer as a correct one in word_list*/
                printf("\nYour answer is wrong, do you want to add your answer as a correct one?\n(Yes = 1    No = 0)\n");
                intScan (&command.integer);

                if (command.integer == 1)
                    add_new_syn (word_list, target, (*user_record)->answer, word_num);
            }

            /*Change the end of user_record to the current node*/
            user_record = &((*user_record)->next);
        }

        /*The question is an antonym question*/
        else if (command.integer == 1)
        {
            /*Increase the ant_asked counter by 1*/
            (*target)->ant_asked++;

            printf("\nGive an antonym of the word \"%s\":\n", (*target)->word);
            scanf("%s", command.string);

            /*Insert a new user_record node and assign the values of the session to it*/
            *user_record = (user_rec_t *)calloc(1 ,sizeof(user_rec_t)); /*Dynamically allocate the node*/
            (*user_record)->qtype = 1;  /*Record the question type*/
            strcpy((*user_record)->main_word, (*target)->word);   /*store the main word*/
            strncpy((*user_record)->answer, command.string, 17);   /*store the answer*/

            /*If the answer was one of the antonyms of the word, then it's correct*/
            if (search_ant(*target, command.string) != NULL)
            {
                (*user_record)->result = 1; /*Record the result as 1*/
                (*target)->score += 1;  /*Increase the score of the word by 1*/

                printf("\nYour answer is correct\n");
            }
            
            /*The answer is wrong*/
            else
            {
                (*user_record)->result = 0; /*Record the result as 0*/
                (*target)->score += -1; /*Reduce the score of the word by 1*/

                /*Take the choice to store the wrong answer as a correct one in word_list*/
                printf("\nYour answer is wrong, do you want to add your answer as a correct one?\n(Yes = 1    No = 0)\n");
                intScan (&command.integer);

                if (command.integer == 1)
                    add_new_ant (word_list, target, (*user_record)->answer, word_num);
            }

            /*Change the end of user_record to the current node*/
            user_record = &((*user_record)->next);
        }

        /*Ask to continue to the next question*/
        printf("\nContinue to the next question? (Yes = 1     No = 0)\n");
        intScan(&command.integer);

        if (command.integer == 0)   return;
    }
}


/*Read a single line from bfile*/
int fread_frag (FILE *bfile, char *input)
{
    int i;

    for (i = 0 ; (i < 43) ; i++)
        if (fread (&input[i], sizeof(char), 1, bfile) == 0 || input[i] == '\n')  
            break;

    input[i] = 0;

    remove_line_adds(input);

    return i;
}


/*Import user_record from the file with name "username.worddat"*/
void import_session (word_list_t *word_list, char *username, user_rec_t **user_record)
{
    word_list_t *temp;
    char buffer[60], *token;
    FILE * user_record_file;

    /*Create the file name*/
    strcpy(buffer, username);
    strcat(buffer, ".worddat\0");

    /*Reset all the user_based values in word_list*/
    for(temp = word_list ; (temp != NULL) ; temp = temp->next)
    {
        temp->syn_asked = 0;
        temp->ant_asked = 0;
        temp->score = 0;
    }

    /*Open the file*/
    if((user_record_file = fopen(buffer, "rb")) == NULL)    return;

    /*Read the file line by line till reaching file end*/
    while (fread_frag (user_record_file, buffer))
    {
        /*Create a new user_record node*/
        *user_record = (user_rec_t *)calloc(1, sizeof(user_rec_t));

        /*Store the question type*/
        token = strtok(buffer, " ");
        (*user_record)->qtype = token[0] - '0';

        /*Store the question result*/
        token = strtok(NULL, " ");
        (*user_record)->result = token[0] - '0';

        /*Store the main word*/
        token = strtok(NULL, " ");
        strcpy((*user_record)->main_word, token);

        /*Search for main_word in word_list and update the times asked and score values in it*/
        temp = *search_list(&word_list, token);
        if (temp != NULL)
        {
            if ((*user_record)->result == 0) temp->score += -1;
            else temp->score += 1;

            if((*user_record)->qtype == 0)  temp->syn_asked++;
            else  temp->ant_asked++;
        }

        /*Store the answer*/
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        strcpy((*user_record)->answer, token);

        /*Change the end of user_record to the curent node*/
        user_record = &((*user_record)->next);
    }

    /*Close the file*/
    fclose(user_record_file);
}


/*Return the size of user_record in bytes*/
size_t list_size (user_rec_t *user_record)
{
    size_t total_size;

    for (total_size = 0 ; user_record != NULL ; (user_record = user_record->next) && (total_size += 43));

    return total_size;
}


/*Export user_record to a file with the name "username.worddat*/
void export_session (user_rec_t *user_record, char *username, size_t size_limit)
{
    int i, size_overflow;
    char buffer[44];
    FILE * user_record_file;

    /*Create the file name*/
    strcpy(buffer, username);
    strcat(buffer, ".worddat\0");
    
    /*Open the file*/
    if((user_record_file = fopen(buffer, "wb")) == NULL) return;

    /*Calculate the difference between user_record and the size_limit in bytes*/
    size_overflow = list_size (user_record)*3/2 - size_limit;

    /*if user_record was larger, skip the leading nodes of user_record till reaching the size_limit*/
    if (size_overflow > 0)
        for(; (user_record != NULL) && (size_overflow > 0) ; (user_record != user_record->next) && (size_overflow -= 43));

    /*Print the records*/
    for (; user_record != NULL ; user_record = user_record->next)
    {
    /*Create the line*/
        /*question type*/
        buffer[0] = user_record->qtype + '0';
        buffer[1] = ' ';

        /*result*/
        buffer[2] = user_record->result + '0';
        buffer[3] = ' ';
        buffer[4] = 0;

        /*the word asked*/
        strcat(buffer, user_record->main_word);

        strcat(buffer, " -> ");

        /*The answer*/
        strcat(buffer, user_record->answer);

        strcat(buffer, "\n");

    /*Print the line*/
        fwrite(buffer, strlen(buffer), 1, user_record_file);
    }
}


/*Free the user record*/
void free_user_rec (user_rec_t * record)
{
    if (record != NULL) free_user_rec (record->next);
    else return;
    free (record);
}


/*Manage the session of a user*/
void session_manager (word_list_t **word_list, char *username, int *word_num, size_t total_size)
{
    int_str_t command, command2;
    word_list_t **temp_node;
    user_rec_t *user_record;
    int commandi;

    /*Import the user record*/
    import_session (*word_list, username, &user_record);

    /*Keep asking till being prompted to leave*/
    while (1)
    {
        printf("\n1. Get a question\n2. Add a word as a synonym or an antonym (new primary words can be added here)\n3. End session\n\nChoose an operation: ");
        if (intScan (&command.integer) != 1)    continue;

        switch (command.integer)
        {
            /*Go to the question engine*/
            case 1: question_engine (word_list, word_num, &user_record);
                    break;

            /*Add the given word to word_list*/
            case 2: printf("\nPlease enter the word: ");
                    scanf("%s", command.string);

                    printf("\nTo which word does it relate? (new words can be added here in case they had multiple relations)\n");
                    scanf("%s", command2.string);

                    printf("\nIs it a synonym (1) or an antonym (2) to \"%s\"?\n", command2.string);
                    if (intScan (&commandi) != 1)    continue;

                    /*Add the word as a synonym*/
                    if(commandi == 1)
                    {
                        temp_node = add_new_word (word_list, command2.string, word_num);  /*Add the the main word to word_list if it didn't exist*/
                        add_new_syn (word_list, temp_node, command.string, word_num);   /*Add the new child word to the main word's synonym list*/
                    }

                    /*Add the word as an antonym*/
                    if(commandi == 2)
                    {
                        temp_node = add_new_word (word_list, command2.string, word_num);  /*Add the new child word to the main word's synonym list*/
                        add_new_ant (word_list, temp_node, command.string, word_num);   /*Add the new child word to the main word's synonym list*/
                    }

                    break;

            /*export the current user record, free it and exit the session*/
            case 3: export_session (user_record, username, total_size);
                    free_user_rec (user_record);
                    return; 
        }
    }
}


/*Add username to user_list*/
void add_user (char **(*user_list), char *username, int *user_num)
{
    char **temp_list, *temp;
    int i;

    /*If the user existed before, the function is aborted*/
    for (i = 0 ; (*user_num > i) && (*user_list != NULL) && (strcmp((*user_list)[i], username) != 0) ; i++);

    if (i != *user_num) return;

    /*Create a new string and copy the user name to it*/
    temp = (char *)calloc(26, sizeof(char));
    strcpy(temp, username);
    username = temp;
    
    /*allocate a temporary user_list with one more place*/
    temp_list = (char **)calloc(++(*user_num), sizeof(char *)); /*Increase user_num by 1*/

    /*copy the old user_list to the temporary one*/
    for (i = 0 ; i < *user_num-1 ; i++)
        temp_list[i] = (*user_list)[i];
    
    /*Free the old list and update it's address to the new one*/
    free(*user_list);
    (*user_list) = temp_list;

    /*place the new name in the list*/
    (*user_list)[*user_num-1] = username;
}


/*Import users list from file and return an array*/
char ** import_users (FILE *file, int *name_num)
{
    int counter;
    char *name, **name_list = NULL, buffer[26];

    /*Keep scanning till reaching file end*/
    while (fgets(buffer, 25, file) != NULL)
    {
        name = (char*)calloc(26, sizeof(char)); /*Create a space for the name*/

        remove_line_adds(buffer);   /*Clean the string's end from non-letter characters*/

        strcpy (name, buffer);  /*Copy the buffer to the name string*/

        /*Create the list if it didn't exist*/
        if (name_list == NULL)
        {
            name_list = (char **)calloc(++(*name_num), sizeof(char *));
            name_list[(*name_num) - 1] = name;
        }

        /*Call the function to add the new user*/
        else    add_user (&name_list, name, name_num);
    }

    return name_list;
}


/*Free a word's synonym list*/
void free_syn_seq (syn_seq *node)
{
    if (node != NULL) free_syn_seq (node->next);
    else return;
    free (node);
}


/*Free a word's synonym list*/
void free_ant_seq (ant_seq *node)
{
    if (node != NULL) free_ant_seq (node->next);
    else return;
    free (node);
}


/*Heap doesn't free itself automatically, guess i'll do it myself*/
/*recursively free word_list*/
void fine_i_will_do_it_myself (word_list_t * word_list)
{
    if (word_list != NULL) fine_i_will_do_it_myself(word_list->next);
    else return;

    free_syn_seq (word_list->synonyms);
    free_ant_seq (word_list->antonyms);
    free(word_list);
}


/*Main functiion of the program*/
void ant_syn_manager (char *syn_file_path, char *ant_file_path, char *user_list_path)
{
    int word_num = 0, user_num = 0, i, *rand_seed;
    char **user_list;
    word_list_t * word_list = 0;
    int_str_t command;
    FILE *user_list_p;
    size_t total_size;

    /*Open the user_list file and import the users, then close the file*/
    if((user_list_p = fopen(user_list_path, "r+")) != NULL)
    {
        user_list = import_users (user_list_p, &user_num);
        fclose(user_list_p);
    }

    /*Keep the user_list as NULL if no file is detected*/
    else user_list = NULL;

    /*Create the seed for the random numbers using malloc*/
    rand_seed = malloc(1);
    srand((long)rand_seed / 100);
    free(rand_seed);

    /*Store the total size of both synonyms and antonyms files*/
    total_size = import_words (&word_list, syn_file_path, ant_file_path, &word_num);

    /*choosing a user*/
    while (1)
    {
        printf ("\nPlease choose the name of the user to start the session:\n\n0. Exit\n\n");

        /*Print the users*/
        for (i = 1 ; i <= user_num ; i++)
            printf("%d. %s\n", i, user_list[i-1]);

        printf("%d. New user\n", i);

        printf("\nEnter an operation: ");
        if (intScan (&command.integer) != 1)    continue;

        /*open a session for the given user*/
        if (command.integer > 0 && command.integer <= user_num) 
            session_manager (&word_list, user_list[command.integer-1], &word_num, total_size);

        /*Add a new user*/
        else if (command.integer == i)
        {
            printf("Please enter the new user's name:\n");
            scanf("%25s", command.string);

            add_user (&user_list, command.string, &user_num);
        }

        /*Close all the open files, free the used blocks and end the program*/
        else if (command.integer == 0)
        {
            user_list_p = fopen(user_list_path, "w");

            for (i = 0 ; (i < user_num) ; i++)
                fprintf(user_list_p, "%s\n", user_list[i]);

            fclose(user_list_p);

            update_files (word_list, syn_file_path, ant_file_path);

            for (; user_num > 0 ; user_num--)
                free(user_list[user_num-1]);

            free(user_list);

            fine_i_will_do_it_myself (word_list);
            return;
        }

        else    printf("\nInvalid input...\n\n");
    }
}


int main ()
{
    char antonym_file_path[] = "antonyms_list.txt", /*The adress of the list of synonyms*/
         synonym_file_path[] = "synonyms_list.txt", /*The adress of the list of synonyms*/
         user_list_path[] = "users_list.txt";   /*The adress of the list of users*/
    
    ant_syn_manager (synonym_file_path, antonym_file_path, user_list_path);
}