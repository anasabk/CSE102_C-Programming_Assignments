/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/

/*
** Editor: Anas Abdul Khalek.
*/

#include <stdio.h>
#include "hw1_lib.h"


double integral3(double a0, double a1, double a2, double a3, double xs, double xe, double delta)
{
/*---This code is universal, it can be used for all polynomials, just by adding the right coefficients in the right order--*/
/*---in the a[] array.                                                                                                   --*/
/*---------------------------------------------------Declaring Variables---------------------------------------------------*/
    int i, j = 0;                                               
    double a[4] = {a3, a2, a1, a0};
    int size = sizeof(a)/sizeof(a[0]);
    double x[2] = {xs, xe};
    double y[2] = {0, 0};
    double result = 0;
/*--------------------------------------------------Calculating Procedure--------------------------------------------------*/
/*--Calculates the vlaue of the integral in the shape:( y = [((((a*x/4)+b/3)*x+c/2)*x+d)*x] ) at both the start and the  --*/
/*--end of the range of x, and places each y value in it's place in the y array.                                         --*/
    while(j<2){
        i = size;
        while(i>0){
            i--;
            y[j] = (y[j] + a[i]/(i+1))*x[j];
        }
        j++;
    }
/*-------------------------------------Multiplying by dx and sending the final result--------------------------------------*/
    result = (y[1] - y[0]) * delta;
    return result;
}


double integral4(double a0, double a1, double a2, double a3, double a4, double xs, double xe, double delta)
{
/*---This code is universal, it can be used for all polynomials, just by adding the right coefficients in the right order--*/
/*---in the a[] array.                                                                                                   --*/
/*---------------------------------------------------Declaring Variables---------------------------------------------------*/
    int i, j = 0;
    double a[5] = {a4, a3, a2, a1, a0};
    int size = sizeof(a)/sizeof(a[0]);
    double x[2] = {xs, xe};
    double y[2] = {0, 0};
    double result = 0;
/*--------------------------------------------------Calculating Procedure--------------------------------------------------*/
/*--Calculates the vlaue of the integral in the shape:( y = [(((((a*x/5)+b/4)*x+c/3)*x+d/2)*x+e)*x] ) at both the start  --*/
/*--and the end of the range of x, and places each y value in it's place in the y array.                                 --*/
    while(j<2){
        i = size;
        while(i>0){
            i--;
            y[j] = (y[j] + a[i]/(i+1))*x[j];
        }
        j++;
    }
/*-------------------------------------Multiplying by dx and sending the final result--------------------------------------*/
    result = (y[1] - y[0]) * delta;
    return result;
}


double root3(double a0, double a1, double a2, double a3, double xs, double xe)
{
/*---This code is universal, it can be used for all polynomials, just by adding the right coefficients in the right order--*/
/*---in the a[] array.                                                                                                   --*/
/*-------------------------------------------------Using Bisection Method--------------------------------------------------*/
/*---------------------------------------------------Declaring Variables---------------------------------------------------*/
    double a[4] = {a3, a2, a1, a0};
    int size = sizeof(a)/sizeof(a[0]);
    double x[3] = {xs, xe, (xs+xe)/2};
    double y[3];
    int i, j = 0;
/*--------------------------------------------------Calculating Procedure--------------------------------------------------*/
/*--Calculates the vlaue of the polynomial in the shape:( y = [(((a*x)+b)*x+c)*x+d] ) at the start, the end and the      --*/
/*--middle of the range of x, and places each y value in it's place in the y array, and then checks if any is equal to 0.--*/
    while(j<3){
        y[j] = 0;
        i = size;
        while(i>0){
            i--;
            y[j] = y[j]*x[j] + a[i];
        }

        if(y[j]-0<=0.0000001&&y[j]-0>=-0.0000001)
            return x[j];

        j++; 
    }
/*--------------------------------------------------Comparison Procedure---------------------------------------------------*/
/*--When no y is equal to 0, this part compares the values of y to determine which section of the graph of the polynomial--*/
/*--to inspect in the next step of the loop until it finds a value of y equal to 0.                                      --*/
    if(y[0]*y[1]<0){
        if(y[0]>y[1]){
            if(y[2]<0)
                return root3(a0, a1, a2, a3, x[0], x[2]);

            if(y[2]>0)
                return root3(a0, a1, a2, a3, x[2], x[1]);
        }

        else{
            if(y[2]<0)
                return root3(a0, a1, a2, a3, x[2], x[1]);

            if(y[2]>0)
                return root3(a0, a1, a2, a3, x[0], x[2]);
        }
    }

    else
        printf("unable to find a root in this condition.\nThere is either two or more roots or none in the current range.");
}


double root4(double a0, double a1, double a2, double a3, double a4, double xs, double xe)
{
/*---This code is universal, it can be used for all polynomials, just by adding the right coefficients in the right order--*/
/*---in the a[] array.                                                                                                   --*/
/*-------------------------------------------------Using Bisection Method--------------------------------------------------*/
/*---------------------------------------------------Declaring Variables---------------------------------------------------*/
    double a[5] = {a4, a3, a2, a1, a0};
    int size = sizeof(a)/sizeof(a[0]);
    double x[3] = {xs, xe, (xs+xe)/2};
    double y[3];
    int i, j = 0;
/*--------------------------------------------------Calculating Procedure--------------------------------------------------*/
/*--Calculates the vlaue of the polynomial in the shape:( y = [((((a*x)+b)*x+c)*x+d)*x+e] ) at the start, the end and the--*/
/*--middle of the range of x, and places each y value in it's place in the y array, and then checks if any is equal to 0.--*/
    j = 0;
    while(j<3){
        y[j] = 0;
        i = size;
        while(i>0){
            i--;
            y[j] = y[j]*x[j] + a[i];
        }

        if(y[j]-0<=0.0000001&&y[j]-0>=-0.0000001)
            return x[j];

        j++; 
    }
/*--------------------------------------------------Comparison Procedure---------------------------------------------------*/
/*--When no y is equal to 0, this part compares the values of y to determine which section of the graph of the polynomial--*/
/*--to inspect in the next step of the loop until it finds a value of y equal to 0.                                      --*/
    if(y[0]*y[1]<0){
        if(y[0]>y[1]){
            if(y[2]<0)
                return root4(a0, a1, a2, a3, a4, x[0], x[2]);

            if(y[2]>0)
                return root4(a0, a1, a2, a3, a4, x[2], x[1]);
        }

        else{
            if(y[2]<0)
                return root4(a0, a1, a2, a3, a4, x[2], x[1]);

            if(y[2]>0)
                return root4(a0, a1, a2, a3, a4, x[0], x[2]);
        }
    }

    else
        printf("unable to find a root in this condition.\nThere are either two or more roots or none in the current range.");
}
