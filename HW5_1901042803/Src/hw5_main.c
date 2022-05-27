/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/


#include <stdio.h>
#include <math.h>
#include "hw5_lib.h"


void test_operate_polynomials () 
{
	double a3=0, a2=0, a1=0, a0=0, b3=0, b2=0, b1=0, b0=0, t3=0, t2=0, t1=0, t0=0;
	char op;
	int flag=0, i=0, d3=0, d2=0, d1=0, d0=0;

	printf("\nPlease enter the polynomial coefficients in the following form: ");
	printf("\nFirst polynomial: \n (degree, coef), (degree, coef), (degree, coef), (degree, coef)\n ");
	while(1){
        if(scanf(" (%d, %lf), (%d, %lf), (%d, %lf), (%d, %lf)", &d3, &t3, &d2, &t2, &d1, &t1, &d0, &t0)==8){
            if(d3<0||d3>3||d2<0||d2>3||d1<0||d1>3||d0<0||d0>3){
                printf("Please don't enter degrees smaller than 0 or bigger than 3: \n");
                continue;
            }
            break;
        }

        while(getchar()!='\n');
        printf("Please enter numeric values only and in the right format:\n ");
    }

    polynomial_scanner(d3, t3, &a3, &a2, &a1, &a0);
    polynomial_scanner(d2, t2, &a3, &a2, &a1, &a0);
    polynomial_scanner(d1, t1, &a3, &a2, &a1, &a0);
    polynomial_scanner(d0, t0, &a3, &a2, &a1, &a0);

	printf("\nSecond polynomial: \n ");
	while(1){
        if(scanf(" (%d, %lf), (%d, %lf), (%d, %lf), (%d, %lf)", &d3, &t3, &d2, &t2, &d1, &t1, &d0, &t0)==8){
            if(d3<0||d3>3||d2<0||d2>3||d1<0||d1>3||d0<0||d0>3){
                printf("Please don't enter degrees smaller than 0 or bigger than 3: \n");
                continue;
            }
            break;
        }

        while(getchar()!='\n');
        printf("Please enter numeric values only and in the right format:\n ");
    }

    polynomial_scanner(d3, t3, &b3, &b2, &b1, &b0);
    polynomial_scanner(d2, t2, &b3, &b2, &b1, &b0);
    polynomial_scanner(d1, t1, &b3, &b2, &b1, &b0);
    polynomial_scanner(d0, t0, &b3, &b2, &b1, &b0);

	printf("\nOperation sign: ");
    while(1){
	    scanf(" %c", &op);
        if(op=='*'||op=='-'||op=='+') break;
        printf("Please enter a valid operator");
    }

	operate_polynomials(&a3, &a2, &a1, &a0, &b3, &b2, &b1, &b0, op);

    printf("      x^6 = %.1f\n      x^5 = %.1f\n      x^4 = %.1f\n      x^3 = %.1f\n      x^2 = %.1f\n        x = %.1f\n constant = %.1f\n ", a2, a1, a0, b3, b2, b1, b0);
    printf("\n\n");
}


void test_four_d_vectors ()
{
	double mean_a0=0.0, mean_a1=0.0, mean_a2=0.0, mean_a3=0.0, longest_distance=0.0;
	int N=5;
	four_d_vectors (&mean_a0, &mean_a1, &mean_a2, &mean_a3, &longest_distance, N);
	printf("Mean a0: %f\nMean a1: %f\nMean a2: %f\nMean a3: %f\nThe longest distance between two points: %f\n\n\n", mean_a0, mean_a1, mean_a2, mean_a3, longest_distance);
}


void test_dhondt_method ()
{
	int partyA=0, partyB=0, partyC=0, partyD=0, partyE=0, numberOfSeats=0;
	dhondt_method (&partyA, &partyB, &partyC, &partyD, &partyE, numberOfSeats);
	printf("Party A: %d seat(s).\nParty B: %d seat(s).\nParty C: %d seat(s).\nParty D: %d seat(s).\nParty E: %d seat(s).\n\n\n", partyA, partyB, partyC, partyD, partyE);
}


void test_order_2d_points_cc ()
{
	double x1=0.0, y1=0.0, x2=0.0, y2=0.0, x3=0.0, y3=0.0;
	order_2d_points_cc (&x1, &y1, &x2, &y2, &x3, &y3);
	printf("Counter-Clockwise Order: (%f,%f) - (%f,%f) - (%f,%f)\n\n\n", x1, y1, x2, y2, x3, y3);
}


void test_number_encrypt ()
{
	unsigned char number=0;
	number_encrypt (&number);
	printf("Encrypted number: %d\n\n\n", number);
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_operate_polynomials ();
	test_four_d_vectors ();
	test_dhondt_method ();
	test_order_2d_points_cc ();
	test_number_encrypt ();
	return (0);
} /* end main */
