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
/*                                                  The main function                                                 */
/*--------------------------------------------------------------------------------------------------------------------*/
int main(){
    FILE * textf1, * textf2;
    char word1[20], word2[20];

    if((textf1 = fopen("text.txt","r"))==NULL||(textf2 = fopen("textSolved.txt","r")) ==NULL)
    {
        printf("Error! opening files");
    }

    else
    {
        while(fscanf(textf1, " %s", word1)==1&&fscanf(textf2, " %s", word2)==1)
            if(strcmp(word1, word2)!=0) printf("\n1");
        
        printf("\n");
    }

    fclose(textf1);
    fclose(textf2);
    return 0;
}