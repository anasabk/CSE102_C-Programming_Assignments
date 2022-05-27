/*
**
**                     Homework 7
** Done with the bonus task merged in the same algorithm
** Bonus part explanation at line 56
**
**
*/



#include <stdio.h>
#include <string.h>


/*--------------------------------------------------------------------------------------------------------------------*/
/*           Finds the value in an array that matches the target value and returns it's place in the array            */
/*--------------------------------------------------------------------------------------------------------------------*/
int char_arr_matcher(char target, char arr[], int length)
{
    int i;
    for(i=0;i<length;i++)
        if(target == arr[i])    return i;

    return -1;
}


/*--------------------------------------------------------------------------------------------------------------------*/
/*              Checks if the word has any punctuation marks and does actions based on which mark it is               */
/*--------------------------------------------------------------------------------------------------------------------*/
int punct_checker(char word[], FILE * text){
    int i, extraC=1;

    for(i=0;i<strlen(word);i++)
        if((!(word[i]>64&&word[i]<91)&&!(word[i]>96&&word[i]<123)&&word[i]!='&'))
        {
            printf("%d %ld\n", i, i-strlen(word));
            fseek(text, i-strlen(word), SEEK_CUR);              /*move sthe file pointer back to before the puntuation part*/
            if(word[i]==39&&strlen(word)-i-1<3) extraC = strlen(word)-i;        /*Skips the letters after the apostrophe*/
            word[i] = 0;                 /*Deletes the punctuation point to easily compare the word*/
            break;
        }

    return extraC;          /*returns the number of characters to move the pointer over*/
}


/*--------------------------------------------------------------------------------------------------------------------*/
/*                     Finds the correct form of the given word in the dictionary and returns it                      */
/*--------------------------------------------------------------------------------------------------------------------*/
int find_best_correction(FILE * dictionary, char word[], char correction[], int current_miss_max)
{
    int missed=0, i, j=0, k=0, t=0, vowelFlag, capsFlag;
    
    int max_miss = 2;               /*max_miss decides how many mistakes are accepted in the words, which is the times the function recalls itself. Can be 0, 1 or 2, used in line 111*/      /* <<---- BONUS PART <<---- */

    char similars[3][20], vowels[] = {'a', 'e', 'i', 'o', 'u'};

    rewind(dictionary);                             /*Sends the file pointer of the dictionary file to the beginning of the file*/

    while(fgets(correction, 19, dictionary)!=NULL&&k<3)
    {
        vowelFlag = 0;
        missed = 0;
        correction[char_arr_matcher('\n', correction, strlen(correction))-1] = 0;       /*Removes the '\n' character from the word in the dictionary to match the given word*/
        if(strlen(word)!=strlen(correction)) continue;                                  /*Skips words with length not equal to the length of the given word*/

        for(i=0;i<strlen(word);i++)                                                     /*Matches the words letter by letter*/
            if(word[i] != correction[i]&&word[i]+32 != correction[i])                   /*Accepts any letter not equal to the given one, nor it's capital*/
            {
                ++missed;                       /*Increases the counter of the non-match letters by one*/
                if (char_arr_matcher(word[i], vowels, sizeof(vowels)/sizeof(vowels[0]))==-1&&
                    char_arr_matcher(correction[i], vowels, sizeof(vowels)/sizeof(vowels[0]))!=-1)    ++vowelFlag;  /*Increases the counter of constant-to-vowel*/
            }

        if(missed==current_miss_max)                /*accepts evey word that has a number differences with the target word equal to the current_max_miss value*/
        {
            if(vowelFlag==current_miss_max){                        /*Gives the priority for the words with the number of constant-to-vowel changes equal to current_max_miss*/
                strcpy(similars[k++] ,correction);
                ++j;
                ++t;
                if(strcmp(word, correction)==0) break;
            }

            else if(current_miss_max==2&&vowelFlag==current_miss_max-1&&t<3)    /*In the case of 2 different characters, 1 constant-to-vowel case has the priority in case the first doesn't apply*/
            {
                strcpy(similars[t++] ,correction);
                ++j;
                if(strcmp(word, correction)==0) break;
            }

            else if(j<3){                                           /*This is for non-constant-to-vowel cases*/
                strcpy(similars[j] ,correction);
                ++j;
            }
        }
    }

    if(j>0)
    {
        if(k==1||j==1||t==1) strcpy(correction, similars[0]);       /*If only one similar word with the highest priority is found, it's chosen as the correct one*/
        else strcpy(correction, similars[1]);                       /*In case of multiple choices, The second one is always chosen, returns the correction and '1' which means a success*/
        printf("%s\n", correction);
        if(word[0]>64&&word[0]<91) correction[0] -= 32;
        return 1;
    }

    else                                            /*If no similar words are found, the function recalls itself*/
    {
        if(current_miss_max<max_miss) return find_best_correction(dictionary, word, correction, ++current_miss_max);    /*Recalls the function accepting a higher number of mistakes*/
        else return 0;                  /*returns 0 which means no similar words where found*/
    }
}


/*--------------------------------------------------------------------------------------------------------------------*/
/*  Scans every word in the target file and replaces it by it's correction found by (find_best_correction) function   */
/*--------------------------------------------------------------------------------------------------------------------*/
void fix_spelling_error2(FILE * textFile, FILE * dictionary)
{
    char word[20], correction[20];
    int extraC;

    while(fscanf(textFile," %s", word)==1)                  /*keeps scanning until not getting a valid value*/
    {
        extraC = punct_checker(word, textFile);             /*Stores the number of characters to skip after printing*/
        printf("%d %s\n", extraC, word);
        if(find_best_correction(dictionary, word, correction, 0)==1)
        {
            fseek(textFile, -strlen(correction), SEEK_CUR);             /*Moves the file pointer back to the beginning of the scanned word*/
            strcpy(word, correction);                                   
            fprintf(textFile, "%s", word);                              /*Overwrites the word with it's correction*/
        }

        fseek(textFile, +extraC, SEEK_CUR);             /*Skips characters based on the punctuation marks*/
    }
}


/*--------------------------------------------------------------------------------------------------------------------*/
/*                                                  The main function                                                 */
/*--------------------------------------------------------------------------------------------------------------------*/
int main(){
    FILE * textf, * dictionary;

    if((textf = fopen("text.txt","r+"))==NULL||(dictionary = fopen("dictionary.txt","r")) ==NULL)
    {
        printf("Error! opening files");
    }

    else
    {
        fix_spelling_error2(textf, dictionary);
    }

    fclose(textf);
    fclose(dictionary);
    return 0;
}