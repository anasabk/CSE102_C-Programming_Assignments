/*
** hw2_lib.c:
**
** The source file implementing library functions.
**
*/

#include <stdio.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include "hw2_lib.h"

/*
	Function for finding the day of the week in any given 
*/
int find_weekday_of_data(int day, int month, int year)
{
/*---------------------------------------------Based on The Gregorian Calendar---------------------------------------------*/

	int result, century_code = 0;
	int month_code[12] = {1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};

/*------------------------------------------------Finding The Century Code-------------------------------------------------*/

	if(year>=2000&&year<2100||year>=1600&&year<1700)
		century_code = 6;

	else if(year>=1800&&year<1900)
		century_code = 2;

	else if(year>=1700&&year<1800)
		century_code = 4;

	else {
		printf("Unsupported Year.");
		return 0;
	}

/*--------------------------------------------------Calculating Procedure--------------------------------------------------*/
/*-- This formula is for the Gregorian calendar, which is in the folowing shape:                                           */
/*-- day of the week number = (day + month code + (first 2 digits of the year)*5/4 + century code) % 7                     */
/*-- The days given by the formula are in the following order: 															   */
/*-- Saturday = 0, Sunday = 1, Monday = 2, Tuesday = 3, Wednesday = 4, Thursday = 5, Friday = 6.						   */

	result = (day + month_code[month-1] + ((year)%100)*5/4 + century_code) % 7;
	
	if(result<2)				/* <- */
		return result + 6;			  /**//*This part was added to change the first day of the week					*/ 
									  /**//*from Sunday which is the default in the Gregorian calendar to Monday.	*/
	return result - 1;			/* <- */	
}


int count_day_between_dates(int start_day, int start_month, int start_year, int end_day, int end_month, int end_year)
{
/*---------------------------------------------Based on The Gregorian Calendar---------------------------------------------*/
/*In this code, the number of days is going to be calculated in 3 steps:												   */
/*1- Calculating the days based on the years only, and adding an extra day for each leap year.							   */
/*2- Calculating the difference in days of the start and end month.														   */
/*(which can be less than zero if the end month was smaller than the start month)										   */
/*3- Subtracting the start date from the end date and adding the 3 results together.									   */

    int total=0;

	for(;start_year<end_year;start_year++){								/* <- */
		if(start_year%4==0 && start_year%100!=0 || start_year%400==0)		/**/
			total++;														/**//*The First Step*/
																			/**/
		total = total + 365;												/**/
	}																	/* <- */

	for(;start_month<end_month;start_month++){							/* <- */
		switch (start_month){												/**/
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:		/**/
				total = total + 31;											/**/
				break;														/**/
																			/**/
			case 2:															/**/
				total = total + 28;											/**/
				break;														/**/
																			/**/
			default:														/**/
				total = total + 30;											/**/
				break;														/**/
		}																	/**/
	}																		/**/
																			/**//*The Second Step*/
	for(;start_month>end_month;start_month--){								/**/
		switch (start_month){												/**/
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:		/**/
				total = total - 31;											/**/
				break;														/**/
																			/**/
			case 2:															/**/
				total = total - 28;											/**/
				break;														/**/
																			/**/
			default:														/**/
				total = total - 30;											/**/
				break;														/**/
		}																	/**/
	}																	/* <- */

	return total + (end_day - start_day);								/* <- *//*The Third Step*/
}


double find_angle(double a, double b, double c)
{
/*-----------------------------------------Calculating The Lengths of the Medians----------------------------------------*/
/*Using the rules: cos(A) = (b^2 + c^2 - a^2) / 2*b*c 	and    median(a) = (2*b^2 + 2*c^2 - a^2)/2						 */
    double median_b, median_c;

	median_b = sqrt(2*c*c + 2*a*a - b*b)/2;
	median_c = sqrt(2*a*a + 2*b*b - c*c)/2;

	return acos((pow(median_b*2/3, 2) + pow(median_c*2/3, 2) - a*a) / (2*median_b*median_c*4/9));	
}


/*---------------------------------------This Function is for center aligning text---------------------------------------*/
void print_tabulated_center(char text[23])
{
	int align_space = (23 - strlen(text))/2, i; /* The space before and after the text*/
	for(i=0;i<align_space;i++)
		printf(" ");
	printf("%s", text);
	for(i=0;i<align_space+(strlen(text)+1)%2;i++)
		printf(" ");
}


/*------------------------------------------This Function is for printing a row------------------------------------------*/
void print_tabulated_row(unsigned int r1, double r2, int r3, char vert_border)
{
	char text[23];
	printf("%c", vert_border);
	sprintf(text, "%d", r1);
	print_tabulated_center(text);
	printf("%c", vert_border);
	printf("%-23.3g", r2);
	printf("%c", vert_border);
	printf("%-23d", r3);
	printf("%c\n", vert_border);
}


/*--------------------------------This Function is for printing the borders between rows---------------------------------*/
void print_tabulated_row_border(wchar_t border1, wchar_t border2, wchar_t border3, wchar_t border4)
{
	int i, j;
	printf("%lc", border1);
	for(j=0;j<3;j++){
	 	for(i=0;i<23;i++)
			printf("%lc", border4);

		if(j==2) break;
		printf("%lc", border3);
	}
	printf("%lc\n", border2);
}


void print_tabulated(unsigned int r11, double r12, int r13, 
                     unsigned int r21, double r22, int r23, 
                     unsigned int r31, double r32, int r33, char border)
{
    char vert_border, text[23], align_space;
	int i, j;
	wchar_t corners[4], mids[5], horizon_border;

	setlocale(LC_CTYPE, "");					/*To let the locale be set by the enviroment*/

/*-----------------------------Assigning borders and corners based on the "border" variable------------------------------*/

	if(border=='-'){
		horizon_border = 9472;
		vert_border = '|';
		corners[0] = 9484;
		corners[1] = 9488;
		corners[2] = 9492;
		corners[3] = 9496;
		mids[0] = 9516;
		mids[1] = 9500;
		mids[2] = 9532;
		mids[3] = 9508;
		mids[4] = 9524;
	}

	else{
		horizon_border = border;
		vert_border = border;
		corners[0] = border;
		corners[1] = border;
		corners[2] = border;
		corners[3] = border;
		mids[0] = border;
		mids[1] = border;
		mids[2] = border;
		mids[3] = border;
		mids[4] = border;
	}

/*---------------------------------------------------Printing Procdure---------------------------------------------------*/

	print_tabulated_row_border(corners[0], corners[1], mids[0], horizon_border);

	printf("%c", vert_border);
	sprintf(text, "Raw 101");
	print_tabulated_center(text);
	printf("%c", vert_border);
	sprintf(text, "Row ABCDEFG");
	print_tabulated_center(text);
	printf("%c", vert_border);
	sprintf(text, "Row XYZ123");
	print_tabulated_center(text);
	printf("%c\n", vert_border);

	print_tabulated_row_border(mids[1], mids[3], mids[2], horizon_border);

	print_tabulated_row(r11, r12, r13, vert_border);

	print_tabulated_row_border(mids[1], mids[3], mids[2], horizon_border);

	print_tabulated_row(r21, r22, r23, vert_border);

	print_tabulated_row_border(mids[1], mids[3], mids[2], horizon_border);

	print_tabulated_row(r31, r32, r33, vert_border);

	print_tabulated_row_border(corners[2], corners[3], mids[4], horizon_border);
}

