/*
** hw8_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/

#include <stdio.h>
#include <string.h>
#include "hw8_lib.h"


/*-------------------------------------------------------*/
/*   Finds a strings equivalent in an array of strings   */
/*-------------------------------------------------------*/
int strInArr_check (char target[], char *sarr[], int arr_size)
{
	if(strcmp(target, *sarr)==0)	return 1;	/*Returns 1 when a match is found*/

	else if(arr_size-1>0)	return strInArr_check (target, sarr+1, arr_size-1);		/*Rcalls itself to match with the next word in the array*/

	else return 0;					/*Returns 0 when no match is found*/
}


/*---------------------------------------------------------------------------------------*/
/*       Checks if the word has any punctuation marks and returns them when found        */
/*---------------------------------------------------------------------------------------*/
char punct_checker (char *word, FILE * file)
{
	char punct = 0;

	if(strlen(word)>0)
	{
        if(*word>='A'&&*word<='Z'||*word>='a'&&*word<='z')	
			return punct_checker(word+1, file);		/*Recalls itself when the current character is a letter to match the next character in the string*/

		else
		{
            fseek(file, 1-strlen(word), SEEK_CUR);              /*moves the file pointer back to after the punctuation part*/
			punct = *word;
			*word = 0;          		   /*Deletes the punctuation mark to easily compare the word*/
        }
	}

    return punct;          /*Returns the found punctuation mark*/
}


/*------------------------------*/
/*   Scans a word from a file   */
/*------------------------------*/
char wscan(FILE* file, char* input)
{
	if(fscanf(file, "%s", input)==1)
		return punct_checker (input, file);		/*Returns the punctuation mark if found in punct_checker*/ 

	else return -1;				/*Returns -1 on file end (supposedly)*/ 
}


/*------------------------------------------------------------------------------------*/
/*    Skips the words given in words_to_delete when copying to the output file        */
/*------------------------------------------------------------------------------------*/
void delete_words (FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE],  int number_of_words)		/*number_of_words is used to determine the size of words_to_delete array*/
{	
	char word[WORDSIZE];
	char scanST[2];			/*wscan status*/

	scanST[0] = wscan(infid, word);		/*Takes the returned value from wscan weither it's a char or -1*/

	if(scanST[0]!=-1)
	{
		if(strInArr_check (word, words_to_delete, number_of_words)!=1)		
			fprintf(outfid, "%s ", word);			/*Prints the given word in the output file when it's not in the words_to_delete array*/

		fseek(outfid, -1, SEEK_CUR); 			/**//*Prints the punctuation mark if found*/
		fprintf(outfid, "%.1s ", scanST);		/**/
		
		delete_words (infid, outfid, words_to_delete, number_of_words);			/*Recalls the function since file end is not reached*/
	}
}


/*-----------------------------------------------------------------------------*/
/*    Opens the input and output files and calls the delete_words function     */
/*-----------------------------------------------------------------------------*/
void clean_file (char* infile, char * outfile, char* words_to_delete[WORDSIZE], int number_of_words)
{
	FILE *infid, *outfid;

	if((infid = fopen(infile,"r"))==NULL||(outfid = fopen(outfile,"w")) ==NULL)		/*Opens the files with the names given in (infile) and (outfile)*/
    {
        printf("Error! opening files");
		return;
    }

	else
	{
		delete_words (infid, outfid, words_to_delete, number_of_words);
	}
	
	fclose(infid);			/*Closes the files*/
    fclose(outfid);
}


/*-----------------------------------------------------------------*/
/*    Finds and returns the current position of a given player     */
/*-----------------------------------------------------------------*/
int find_player(cell_type maze[][8], cell_type player, int *x_axis, int *y_axis)
{
	if (maze[*y_axis][*x_axis]==player) return 1;	/*Returns 1 when the player is found*/

	else if (*x_axis<7) {
		++*x_axis;
		return find_player(maze, player, x_axis, y_axis);		/*Recalls the function to scan the next cell in the same line*/
	}

	else if (*y_axis<7) {
		++*y_axis;
		*x_axis = 0;
		return find_player(maze, player, x_axis, y_axis);		/*Recalls the function to scan the next row from the first column*/
	}

	else return 0;			/*Returns 0 when the player is not found*/
}


/*----------------------------------------------------------------------------------------------------*/
/*      Returns weither the requested movement is possible, and does the movement if possible         */
/*----------------------------------------------------------------------------------------------------*/
int maze_move(cell_type maze[][8], cell_type player, move_type move)
{
	int direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}},		/*Tells where the to look relative to the players position based on the movement number*/
		player_x=0, player_y=0, destination_x, destination_y;

	int i, j, k;

	if(find_player(maze, player, &player_x, &player_y)==1&&player==cell_p1||player==cell_p2)
	{
		destination_x = player_x + direction[move][0];			/**//*Assigns the coordinates of the destination*/
		destination_y = player_y + direction[move][1];			/**/
		
		if(destination_x<8&&destination_y<8)		/*Gets sure no overflowed coordinates enter*/
		{
			if(maze[destination_y][destination_x]==cell_free)	
			{
				maze[destination_y][destination_x] = player;
				maze[player_y][player_x] = cell_free;
				return 0;						/*Does the movement when the destination is free and returns 0*/
			}

			else if(maze[destination_y][destination_x]==cell_target)
			{
				maze[destination_y][destination_x] = player;
				maze[player_y][player_x] = cell_free;
				return 1;						/*Does the movement when the destination is the target and returns 1*/
			}
		}
	}

	return -1;				/*Returns -1 when the movement is invalid*/
}


/*-------------------------*/
/*     NOT IMPLEMENTED     */
/*-------------------------*/
void towers_of_hanoi(char start_peg, char end_peg, char aux_peg, int n)
{
    printf("NOT IMPLEMENTED\n");
}
