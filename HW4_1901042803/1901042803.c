#include <stdio.h>
#include <math.h>

/*--------------------------------------------------------------------------------------------*/
/*-------------------This function scans and returns only a positive integer------------------*/
/*--------------------------------------------------------------------------------------------*/
void positive_int_scanner(int * num){
    while(1){
        if(scanf("%d", num)!=1){
            getchar();
            printf("Please enter a numeric value: ");
        }
        else if(*num<0) printf("Please enter a positive integer: ");
        else break;
    }
}


/*--------------------------------------------------------------------------------------------*/
/*--------------------This function writes a polynomial in a pretty format--------------------*/
/*--------------------------------------------------------------------------------------------*/
void write_polynomial()
{
    double a;
    int size, i = 0, flag = 0;

    printf("\n----------------------------------------------------------");
    printf("\nPlease enter the polynomial coefficients in the shape: \n[degree a_n a_n-1 a_n-2 ... a_0]: \n");

    positive_int_scanner(&size);  

    while(i<=size)                                                  /*This loop's number of cycles is based on the degree of the polinomial + 1*/
    {
        while(scanf("%lf", &a)!=1){                                 /*This loop keeps running until getting a valid value for the degree*/
            getchar();
            printf("\nNon numeric value was entered.\nPlease enter the values again: ");
            i = 0;
            while(getchar()!='\n');
            positive_int_scanner(&size);
        }

        a -= 0.0000000000001;

        if(i==0)    printf("P(x)= ");

        if(a>0.05&&flag!=i)    printf("+");                         /*Prints the '+' sign whenever the current coefficient is not the first to write, and when it's greater than 0*/
        
        if(fabs(a)>0.05)                                            /*Activates when the current coefficient is not 0*/
        {
            if(i==size)   printf("%.1f", a);                        /*Prints the constant of the polynomial when the counter is at it's max*/
            else
            {
                if(fabs(a)-1>0.05) printf("%.1fx", a);              /*The general format of a part in a polynomial*/
                else if(a+1>-0.05&&a+1<0)  printf("-x");            /*When the coefficient is '-1', only it's sign is written*/
                else    printf("x");                                /*Does the same as the '-1', but without a sign (The '+' is already managed in the start of the loop)*/
            }

            if(i!=size-1&&i!=size)    printf("^%d", size-i);        /*Prints the power sign always except at the last two coefficients*/
        }
        else flag++;                                                /*This flag increases each time the coefficient is 0. It keeps track of which parts are 0 to decide weither to write '+' sign or not*/
                                                                    /*(When the flag is equal to the 'i' counter, this means that every coefficient so far is 0, thus doesn't print the '+' sign)*/
        i++;                                                        /*This counter tells how many coefficients are passed (which is at max when i=size)*/
    }
    printf("\n----------------------------------------------------------\n");
}


/*--------------------------------------------------------------------------------------------*/
/*---------This function Checks if the number is a Palindrome and an Armstrong number---------*/
/*--------------------------------------------------------------------------------------------*/
void palindrome_armstrong_check()
{
    int num=0, num1, num2, sum=0, tempn, arm_st, palin_st, i, dig=0, flag=0;
    printf("\n----------------------------------------------------------");
    printf("\n            Palindrome and Armstrong Number Checker            ");
    printf("\nPlease enter a number: ");

    positive_int_scanner(&num); 
    
    num1 = num; 
    num2 = num;
    tempn = num;

    while(tempn!=0)                                             /*This loop counts the number of digits in the number*/
    {
        tempn = tempn/10;                                       
        dig++;
    }

    if((sum = pow(num/100, dig) + pow((num%100)/10, dig) + pow((num%10), dig))!=num||dig>3||dig==2)    arm_st = 0;    /*This passes in case the number is not an Armstrong number*/
    else arm_st = 1;                                            /*Decides that the number is an Armstrong number*/

    for(i=0;i<dig/2;i++)
    {
        num1 = (num%(int)pow(10, dig-i))/pow(10, dig-i-1);      /*Finds the left most digit of the number*/
        num2 = (num%(int)pow(10, i+1))/pow(10, i);              /*Finds the right most digit of the number*/

        if(num1==num2)  flag++;                                 /*This flag keeps track of how many times the two known digits match*/
    }

    if(flag==dig/2)  palin_st = 1;                              /*When the flag value is equal to the number of matching attempts, The number is a Palindrome number*/
    else palin_st = 0;

    if(arm_st==1&&palin_st==1)   printf("The number %d is both an Armstrong and a Palindrome number.", num);
    else if(arm_st==1) printf("The number %d is only an Armstrong number.", num);
    else if(palin_st==1) printf("The number %d is only a Palindrome number.", num);
    else printf("The number %d is neither an Armstrong nor a Palindrome\nnumber.", num);
    printf("\n----------------------------------------------------------\n");
}


/*--------------------------------------------------------------------------------------------*/
/*-------------This function finds the sum of the prime numbers in a given range--------------*/
/*--------------------------------------------------------------------------------------------*/
void prime_sum_finder()
{
    int div, sum=0, n, n1, n2, flag;
    printf("\n----------------------------------------------------------");
    printf("\n                Prime Numbers Calculater                  ");
    printf("\nPlease enter the start point: ");
    while(scanf("%d", &n1)!=1)
    {
        getchar();
        printf("Please enter a numeric value:");
    }

    printf("Please enter the end point: ");
    while(scanf("%d", &n2)!=1)
    {
        getchar();
        printf("Please enter a numeric value:");
    }

    n = n1 + 1;

    for(;n<=n2;n++)                                                   /*This loop finds the prime numbers and calculates their sum*/
    {
        flag=0;
        for(div=2;div<=fabs(n/2);div++)                               /*This loop checks weither the current number is prime or not*/
            if(n%div==0){flag = 1;                                    /*The flag assigns the number as a non prime number*/
                         break;  }

        if(flag==0&&fabs(n)!=1) sum += n;                             /*Adds every prime number the total sum (excluding 1 since it passes as a prime number in this program)*/
    }

    printf("The sum of the prime numbers between %d and %d is %d.", n1, n2, sum);
    printf("\n----------------------------------------------------------\n");
}


void main()
{
    int choice;
    while(1)
    {
        printf("\n----------------------------------------------------------");
        printf("\nPlease choose a function from the following: ");
        printf("\n 1-Polynomial Writer. \n 2-Sum of Prime Numbers in a Range. \n 3-Palindrome and Armstrong Number Checker. \n 0-Exit.\n");
        while(scanf("%d", &choice)!=1){
            getchar();
            printf("Please enter a numeric value: ");
        }

        printf("----------------------------------------------------------\n");
        switch(choice){
            case 1: write_polynomial();
                    break;
            
            case 2: prime_sum_finder();
                    break;
            
            case 3: palindrome_armstrong_check();
                    break;

            case 0: return;

            default: printf("Please enter a valid choice.");
        }
    }
}