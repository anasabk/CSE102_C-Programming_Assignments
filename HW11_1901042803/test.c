#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
    FILE *list, *movie;
    char in1[1000], in2[1000], *token1, *token2;
    int i=0;
    list = fopen("/media/anas/Data/projects/C and C++/Homeworks/Homework 11/list.txt", "r");
    movie = fopen("/media/anas/Data/projects/C and C++/Homeworks/Homework 11/Movies.txt", "r");
    
    while(fgets(in1, 1000, movie)!=NULL)
    {
        i=0;
        strtok(in1, ",");
        strtok(NULL, ",");
        token1 = strtok(NULL, ",");
        
        rewind(list);
        while(fgets(in2, 1000, list)!=NULL)
        {
            strtok(in2, ",");
            token2 = strtok(NULL, ",");
            if(strcmp(token1,token2)==0)
                break;
        }

        if(strcmp(token1,token2)!=0) printf("%s\n", token1);
    }
}