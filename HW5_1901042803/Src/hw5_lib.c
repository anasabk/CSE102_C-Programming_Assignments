/*
** hw5_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/

#include <stdio.h>
#include <math.h>
#include "hw5_lib.h"

void ratio_max_finder (double x1, double y1, double x2, double y2, double x3, double y3, double * xm, double * ym, double * a, double * b, double * c);

void order_2d_ratio_calc (double x, double y, double * ratio);

void max_finder_op (double * a, double * b, double * c, double * d, double * e, int * sa, int * sb, int * sc, int * sd, int * se);

void polynomial_scanner(int d, double t, double * a3, double * a2, double * a1, double * a0){
    switch(d){  case 3: *a3 = t;    break;
                case 2: *a2 = t;    break;
                case 1: *a1 = t;    break;
                case 0: *a0 = t;    break;
    }
}


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------Polynomial Calculator-------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void operate_polynomials  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0, char op)
{
	double c6, c5, c4, c3, c2, c1, c0;

	switch(op){								/*This switch statement simply calls the right operation based on the 'op' variable.*/
		case '+':	*b3 += *a3;
					*b2 += *a2;
					*b1 += *a1;
					*b0 += *a0;
					break;

		case '-':	*b3 = *a3 - *b3;
					*b2 = *a2 - *b2;
					*b1 = *a1 - *b1;
					*b0 = *a0 - *b0;
					break;

		case '*':	c4 = (*a3)*(*b1) + (*a2)*(*b2) + (*a1)*(*b3);
					c3 = (*a3)*(*b0) + (*a2)*(*b1) + (*a1)*(*b2) + (*a0)*(*b3);
					c2 = (*a2)*(*b0) + (*a1)*(*b1) + (*a0)*(*b2);
					*b1 = (*a1)*(*b0) + (*a0)*(*b1);
					*a1 = (*a3)*(*b2) + (*a2)*(*b3);
					*b0 = (*a0)*(*b0);
					*a2 = (*a3)*(*b3);
					*a0 = c4;
					*b3 = c3;
					*b2 = c2;
					return;
	}

	*a3 = 0;					/**//**/
	*a2 = 0;						/**//*Except in the multiplication operation, the 'a' coefficients will always be returned as 0. */
	*a1 = 0;						/**/
	*a0 = 0;					/**//**/
}


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------4D Distance Calcultor-------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void four_d_vectors (double* mean_a0, double* mean_a1, double* mean_a2, double* mean_a3, double* longest_distance, int N)
{
	double d0, d1, d2, d3, euclidian_distance, t10, t11, t12, t13, t20, t21, t22, t23, sum0, sum1, sum2, sum3;
	int i;
	
	printf("Please enter the 1. point in the form:\n x, y, z, t\n ");
	while(1){																	/**//**/
		if(scanf("%lf, %lf, %lf, %lf", &t10, &t11, &t12, &t13)==4) break;			/**//*Scans for the first 4D point.*/
		printf("Please enter numeric values only:\n ");								/**//*This loop keeps scanning until getting 4 numeric values at a time.*/
		while(getchar()!='\n');														/**/
	}																			/**//**/
	
	sum0 = t10;																	/**//**/
	sum1 = t11;																		/**//* Starts the sum value of each dimension with the first parameter of each dimension.*/
	sum2 = t12;																		/**/ 
	sum3 = t13;																	/**//**/

	if (fabs(t10+1)<0.0000001&&fabs(t11+1)<0.0000001&&							/**//**/
		fabs(t12+1)<0.0000001&&fabs(t13+1)<0.0000001)								/**/
	{																				/**//*Terminates the function when the first entered point is '-1, -1, -1, -1',*/
		longest_distance = 0;														/**//*and all returned values will be 0.*/
		return;																		/**/
	}																			/**//**/

	for(i=2;i<=N;++i){
		printf("Please enter the %d. point in the form:\n x, y, z, t\n ", i);
		while(1){																/**//**/	
			if(scanf("%lf, %lf, %lf, %lf", &t20, &t21, &t22, &t23)==4) break;		/**//*Scans for the rest of the 4D points.*/
			printf("Please enter numeric values only:\n ");							/**//*This loop keeps scanning until getting 4 numeric values at a time.*/
			while(getchar()!='\n');												/**//**/
		}
	
		if (fabs(t20+1)<0.0000001&&fabs(t21+1)<0.0000001&&						/**//*Stops reading anymore points and breaks the loop*/ 
			fabs(t22+1)<0.0000001&&fabs(t23+1)<0.0000001)	break;				/**//*when the last entered point is '-1, -1, -1, -1' */

		sum0 += t20;															/**//**/
		sum1 += t21;																/**//*Adds the scanned point parameters to the sum.*/
		sum2 += t22;																/**/
		sum3 += t23;															/**//**/

		distance_between_4d_points (t20-t10, t21-t11, t22-t12, t23-t13, &euclidian_distance);		/*Calculates the euclidian distance between the last two scanned points.*/
		if(i==2||*longest_distance<euclidian_distance)	*longest_distance = euclidian_distance;		/*Assigns the longest distance.*/
		
		t10 = t20;
		t11 = t21;
		t12 = t22;
		t13 = t23;
	}

	*mean_a0 = sum0/(i-1);														/**//**/
	*mean_a1 = sum1/(i-1);															/**//*Finds the average of each dimension.*/
	*mean_a2 = sum2/(i-1);															/**/
	*mean_a3 = sum3/(i-1);														/**//**/
}

/*--------------------------This function calculates the euclidian distance---------------------------*/
void distance_between_4d_points (double d0, double d1, double d2, double d3, double* euclidian_distance)
{
    *euclidian_distance = sqrt(d0*d0 + d1*d1 + d2*d2 + d3*d3);
}


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------D'Hont Method calculator------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void dhondt_method (int* partyA, int* partyB, int* partyC, int* partyD, int* partyE, int numberOfSeats)
{
	int seatA = 0, seatB = 0, seatC = 0, seatD = 0, seatE = 0, maxvote, i, * max_seat;
	double	dpartyA = *partyA,					/**//**/
			dpartyB = *partyB,						/**/
			dpartyC = *partyC,						/**//*Converts the party vote numbers to double for max precision.*/
			dpartyD = *partyD,						/**/
			dpartyE = *partyE,					/**//**/
			* max  = &dpartyA;

	while(seatA + seatB + seatC + seatD + seatE <numberOfSeats)				/**//**/
	{																			/**/
		max_finder_op	(&dpartyA, &dpartyB, &dpartyC, &dpartyD, &dpartyE,		/**//*Keeps the comparison running till reaching the maximum number of seats.*/
						 &seatA, &seatB, &seatC, &seatD, &seatE);				/**/
	}																		/**//**/
	
	*partyA = seatA;														
	*partyB = seatB;
	*partyC = seatC;
	*partyD = seatD;
	*partyE = seatE;
}

/*This function applies the D'Hont method as an operation to the party vote numbers, and returns the new*/
/*value of the vote number and the new seat number of the party with the max votes. 					*/
void max_finder_op (double * a, double * b, double * c, double * d, double * e,
					int * sa, int * sb, int * sc, int * sd, int * se)
{
	double * maxv = a;
	int * vseat = sa;

	if(*maxv<*b){ 
		maxv = b;
		vseat = sb;
	}

	if(*maxv<*c){ 
		maxv = c;
		vseat = sc;
	}

	if(*maxv<*d){ 
		maxv = d;
		vseat = sd;
	}

	if(*maxv<*e){
		maxv = e;
		vseat = se;
	}

	*maxv = ((*maxv)/(*vseat+2)) * (*vseat+1);
	(*vseat) += 1;
}


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------2D Points Counter-Clockwise Orderer------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void order_2d_points_cc (double* x1, double* y1, double* x2, double* y2, double* x3, double* y3)
{
	int ratioConst;
	double	ratio1, ratio2, ratio3, xm1=0, ym1=0, xm2=0, ym2=0;

	order_2d_ratio_calc(*x1, *y1, &ratio1);							/**//**//*Calculates the position of each point as a ratio in the shape:	*/
	order_2d_ratio_calc(*x2, *y2, &ratio2);								/**//*			(x/y) + region constant = for regions 1 and 3 			*/
	order_2d_ratio_calc(*x3, *y3, &ratio3);							/**//**//* 			(y/x) + region constant = for regions 2 and 4 			*/

	ratio_max_finder(*x1, *y1, *x2, *y2, *x3, *y3, &xm1, &ym1, &ratio1, &ratio2, &ratio3);		/**//**/
	ratio_max_finder(*x1, *y1, *x2, *y2, *x3, *y3, &xm2, &ym2, &ratio1, &ratio2, &ratio3);			/**/
	ratio_max_finder(*x1, *y1, *x2, *y2, *x3, *y3, x3, y3, &ratio1, &ratio2, &ratio3);				/**/
	*x1 = xm1;																						/**//*Orders the ratios from the largest to the smallest.*/
	*y1 = ym1;																						/**/
	*x2 = xm2;																						/**/
	*y2 = ym2;																					/**//**/
}

/*This function finds the max ratio, returns it and replaces it by -1 to ignore it in the next comparison.*/
void ratio_max_finder (double x1, double y1, double x2, double y2, double x3, double y3,
					double * xm, double * ym, double * a, double * b, double * c)
{
	double * max = a;
	*xm = x1;
	*ym = y1;

	if(*max<*b){
		max = b;
		*xm = x2;
		*ym = y2;
	}

	if(*max<*c){
		max = c;
		*xm = x3;
		*ym = y3;
	}

	*max = -1;
}

/*This function decides which region is the point in, assigns it's region constant and calculates it's ratio.*/
void order_2d_ratio_calc(double x, double y, double * ratio){
	int ratioConst;

	if(x>0&&y>0) ratioConst = 4;
	else if(x<0&&y>0) ratioConst = 2;
	else if(x<0&&y<0) ratioConst = 1;
	else if(x>0&&y<0) ratioConst = 0;

	if(fabs(y)<0.0000001||fabs(x)<0.0000001) *ratio = ratioConst;
	else if(x*y>0)	*ratio = fabs(x/y) + ratioConst;
	else if(x*y<0)	*ratio = fabs(y/x) + ratioConst;
}


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------4D Distance Calcultor-------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void number_encrypt (unsigned char* number)
{
	char b7='-', b6='-', b5='-', b4='-', b3='-', b2='-', b1='-', b0='-';
	get_number_components (*number, &b7, &b6, &b5, &b4, &b3, &b2, &b1, &b0);
	reconstruct_components (number, b7, b6, b5, b4, b3, b2, b1, b0);
}

/*This function changes the number's numeral system to 2 and takes every digit as a bit.*/
void get_number_components (unsigned char number, char* b7, char* b6, char* b5, char* b4, char* b3, char* b2, char* b1, char* b0)
{
	int num = (int)number;
	*b0 = num%2;
	num = num/2;
	*b1 = num%2;
	num = num/2;
	*b2 = num%2;
	num = num/2;
	*b3 = num%2;
	num = num/2;
	*b4 = num%2;
	num = num/2;
	*b5 = num%2;
	num = num/2;
	*b6 = num%2;
	num = num/2;
	*b7 = num%2;
	num = num/2;
}

/*This function does the required transformation in the bits' order and returns the new encrypted number.*/
void reconstruct_components (unsigned char* number, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0)
{
	int a0, a1, a2, a3, a4, a5, a6, a7;
	char temp;
	a0 = (int)b3;
	a1 = (int)b2;
	a2 = (int)b5;
	a3 = (int)b4;
	a4 = (int)b7;
	a5 = (int)b6;
	a6 = (int)b1;
	a7 = (int)b0;
	*number = a0 + a1*2 + a2*4 + a3*8 + a4*16 + a5*32 + a6*64 + a7*128;
}
