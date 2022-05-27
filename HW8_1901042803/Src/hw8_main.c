/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/


#include <stdio.h>
#include "hw8_lib.h"


void test_clean_file () 
{
	char a[WORDSIZE] = "hi", b[WORDSIZE] = "one", c[WORDSIZE] = "man", d[WORDSIZE] = "Hello";	/*An example*/
	char *str[4];

	printf("\n------------------------------------------\n");
	printf("-------------- FILE CLEANER --------------\n");
	printf("------------------------------------------\n");

	str[0] = a;
	str[1] = b;
	str[2] = c;
	str[3] = d;

	clean_file("in.txt", "out.txt", str, 4);		/*Fourth argument is for the number of words to delete, size of str*/
}


void test_maze_move ()
{
	int stat, i, j, k;
	move_type move;
	cell_type player;
	cell_type maze[8][8] = {cell_wall, cell_wall, cell_wall,   cell_wall, cell_wall, cell_wall, cell_wall, cell_wall,		/**//**/
							cell_wall, cell_wall, cell_wall, cell_target, cell_wall, cell_wall, cell_wall, cell_wall,			/**/
							cell_wall, cell_wall, cell_wall,   cell_free, cell_wall, cell_wall, cell_wall, cell_wall,			/**/
							cell_wall, cell_wall, cell_wall,   cell_free, cell_wall, cell_wall, cell_wall, cell_wall,			/**//*An example maze*/
							cell_wall, cell_wall, cell_wall,   cell_free, cell_wall, cell_wall, cell_wall, cell_wall,			/**/
							cell_wall, cell_wall, cell_wall,   cell_free, cell_free, cell_free, cell_wall, cell_wall,			/**/
							cell_wall, cell_wall, cell_wall,   cell_wall, cell_wall, cell_free, cell_free, cell_wall,			/**/
							cell_wall, cell_wall, cell_wall,   cell_wall, cell_wall, cell_wall,   cell_p1, cell_wall};		/**//**/

	printf("\n\n-----------------------------------------\n");
	printf("-------------- MAZE RUNNER --------------\n");
	printf("-----------------------------------------\n");

/*Printing the maze*/
	printf("**************************\n");
	for(j=0;j<8;j++)
	{
		for(k=0;k<2;k++)
		{
			printf("*");
			for(i=0;i<8;i++)
			{
				switch(maze[j][i])
				{
					case cell_wall: printf("***");
									break;
									
					case cell_free: printf("   ");
									break;

					case cell_p1: 	printf("111");
									break;

					case cell_p2: 	printf("222");
									break;

					case cell_target: 	printf("^^^");
										break;
				}
			}
			printf("*\n");
		}
	}
	printf("**************************\n");

	printf("Enter the movement and the player number as follows:\n");
	printf("direction codes: left=0, right=1, up=2, down=3\n");
	printf("player number: player 1 = 1, player 2 = 2\n");
	printf("(Enter the direction as -1 to surrender)\n");
	printf("player number, direction code\n");
	
	while(scanf("%u, %u", &player, &move)==2&&move!=-1)
	{
		stat = maze_move(maze, player, move);

		/*Printing the current maze*/
		printf("\n**************************\n");
		for(j=0;j<8;j++)
		{
			for(k=0;k<2;k++)
			{
				printf("*");
				for(i=0;i<8;i++)
				{
					switch(maze[j][i])
					{
						case cell_wall: printf("***");
										break;
										
						case cell_free: printf("   ");
										break;

						case cell_p1: 	printf("111");
										break;

						case cell_p2: 	printf("222");
										break;

						case cell_target: 	printf("^^^");
											break;
					}
				}
				printf("*\n");
			}
		}
		printf("**************************\n");

		printf("Enter the movement and the player number as follows:\n");
		printf("direction codes: left=0, right=1, up=2, down=3\n");
		printf("player number: player 1 = 1, player 2 = 2\n");
		printf("(Enter the direction as -1 to surrender)\n");
		printf("player number, direction code\n");

		if (stat == 1)	break;			/*Breaks when the maze is solved*/

		else if (stat==-1)	printf("Invalid movement.\n");
	}
}


void test_towers_of_hanoi ()
{
	printf("NOT IMPLEMENTED\n");
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_clean_file ();
	test_maze_move ();
	test_towers_of_hanoi ();
	return (0);
} /* end main */
