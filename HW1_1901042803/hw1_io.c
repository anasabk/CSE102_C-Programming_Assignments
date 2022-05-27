/*
** hw1_io.c:
**
** The source file implementing output functions.
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
#include "hw1_io.h"


void write_polynomial3(double a0, double a1, double a2, double a3){
/*---This code is universal, it can be used for all polynomials, just by adding the right coefficients in the right order--*/
/*---in the a[] array.                                                                                                   --*/
/*---------------------------------------------------Declaring Variables---------------------------------------------------*/
    double a[4] = {a0, a1, a2, a3};
    int size = sizeof(a)/sizeof(a[0]);
    int i = 0;
    int flag = 0;
/*--This part writes each piece of the polinomial and it's sign on it's own, and decides what to write based on the      --*/
/*--conditions of the current part and the previous ones.                                                                --*/
    while(i<size){
        if(a[i]>0&&flag!=i)
            printf("+");

        if(a[i]!=0){
            if(i==size-1)
                printf("%.1f", a[i]);

            else{
                if(a[i]!=1&&a[i]!=-1)
                    printf("%.1fx", a[i]);

                else if(a[i]==-1)
                    printf("-x");

                else
                    printf("x");
            }

            if(i!=size-2&&i!=size-1)
                printf("^%d", size-1-i);
        }

        else
            flag++;

        i++;
    }
}


void write_polynomial4(double a0, double a1, double a2, double a3, double a4){
/*---This code is universal, it can be used for all polynomials, just by adding the right coefficients in the right order--*/
/*---in the a[] array.                                                                                                   --*/
/*---------------------------------------------------Declaring Variables---------------------------------------------------*/
    double a[5] = {a0, a1, a2, a3, a4};
    int size = sizeof(a)/sizeof(a[0]);
    int i = 0;
    int flag = 0;
/*--This part writes each piece of the polinomial and it's sign on it's own, and decides what to write based on the      --*/
/*--conditions of the current part and the previous ones.                                                                --*/
    while(i<size){
        if(a[i]>0&&flag!=i)
            printf("+");
        
        if(a[i]!=0){
            if(i==size-1)
                printf("%.1f", a[i]);

            else{
                if(a[i]!=1&&a[i]!=-1)
                    printf("%.1fx", a[i]);

                else if(a[i]==-1)
                    printf("-x");

                else
                    printf("x");
            }

            if(i!=size-2&&i!=size-1)
                printf("^%d", size-1-i);
        }

        else
            flag++;

        i++;
    }
}