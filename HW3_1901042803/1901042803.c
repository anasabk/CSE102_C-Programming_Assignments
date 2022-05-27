#include <stdio.h>

/*----------------------------------------------------------------------------------------------*/
/*---------------------------This function is used for scanning input---------------------------*/
float scan_float()
{
    float var;

    while(1){
        if(scanf("\n%f", &var)!=1)                                  /*This 'if' takes the value when it's a non numeric value*/
        {
            if(getchar() == '*')    return -1;

            printf("Please enter a 'numeric' value: ");
            continue;
        }

        else if(var<0)                                              /*This 'if' takes the value when it's negative and skips the return*/
        {
            printf("please enter a positive integer number: ");
            continue;
        }

        return var;                                                 /*Returns when the value is a positive integer*/
    }
}


/*----------------------------------------------------------------------------------------------*/
/*-------------------This function Calculates and prints Fibonacci's sequence-------------------*/
void calculate_fibonacci_sequence()
{
    int n_fib, i;
    long int el1, el2, el3;

    while(1){                                                       
        el1 = 0;
        el2 = 1;
        n_fib = (int)scan_float();

        if(n_fib==-1)   return;                                     /*Exits when The scanned value is '*' */
        
        for(i=0;i<n_fib;i++)                                        /*This loop prints the second element and assigns the new values to there places*/
        {
            printf("%ld\n", el2);
            el3 = el1 + el2;
            el1 = el2;
            el2 = el3;
        }
     printf("\nPlease enter The number of terms: "); 
    }
}


/*----------------------------------------------------------------------------------------------*/
/*----------------This function prints the divisors of a positive integer number----------------*/
void divisor_printer(int n){
    int div;
    printf("The number's devisors are: ");
    
    for(div=1;div<=n/2;div++)                                   /*This loop finds the divisors and prints them immediately until it reaches half the number*/
        if(n%div==0)
        {
            printf(" %d", div);
            if(div!=n/2)    printf(",");
        }
        
    printf(".\n");
}


/*----------------------------------------------------------------------------------------------*/
/*----------This function determines if the given number is a harmonic divisor number-----------*/
int harmonic_calc(int n)
{
    int div, denom=n, num_div=1;

    for(div=1;div<=n/2;div++)                                   /*This loop finds the sum of the divisors (including the number itself) and the number of the divisors*/
        if(n%div==0)
        {
            denom += div;
            num_div++;
        }

    if((num_div*n)%denom==0)    return 1;                       /*checks the remainder of the division in the form: ((number of divisors)*(the number itself)/(the sum of the divisors))*/
    return 0;                                                   /*and returns the result accordingly. (1 as Yes, 0 as No)*/
}


/*----------------------------------------------------------------------------------------------*/
/*--------------This function determines if the given number is a perfect number----------------*/
int perfect_calc(int n)
{
    int div, sum=0;
    
    for(div=1;div<=n/2;div++)                                   /*This loop finds the sum of the divisors*/
        if(n%div==0)    sum += div;

    if(sum==n)  return 1;                                       /*returns the result as: 1 as Yes, 0 as No*/

    return 0;
}

/*----------------------------------------------------------------------------------------------*/
/*This function writes the result using the returned value of the harmonic_calc and perfect_calc functions*/
void print_result(int r)
{
    if(r==1) printf("Yes.\n");
    else printf("No.\n");
}


/*----------------------------------------------------------------------------------------------*/
/*-This function determines if the given number is perfect and if its a harmonic divisor number-*/
void decide_perfect_harmonic_number()
{
    int n_in, result;

    printf("\n        Perfect and Harmonic Number        \n");
    printf("                  Finder                   \n");
    printf("\nplease enter a number: ");

    while(1)                                                    /*This loop keeps the function running until it recieves '*' input*/
    {
        n_in = (int)scan_float();
        if(n_in==-1)    break;

        divisor_printer(n_in);
        printf("Is it a perfect number? ");
        print_result(perfect_calc(n_in));

        printf("Is it a harmonic divisor number? ");
        print_result(harmonic_calc(n_in));

        printf("\nplease enter a number: ");
    }
}


/*----------------------------------------------------------------------------------------------*/
/*----------------------This function Finds the range of a group of values----------------------*/
void difference_max_min()
{
    double n, max, min;

    while(1)                                                    /*This loop keeps the function running until it recieves '*' input*/
    {
        int i;
        printf("\nPlease enter 5 numbers with spaces in between: ");

        if(scanf("%lf", &n)!=1&&getchar() == '*')   return;     

        max = n;
        min = n;

        for(i=0;i<4;i++)                                    /*This loop compares the known max and min to each recieved input*/      
        {
            scanf("%lf", &n);
            if(n>max)   max = n;
            if(n<min)   min = n;
        }

        printf("The maximum number is: %g\n", max);
        printf("The minimum number is: %g\n", min);
        printf("The range of the numbers is: %g\n", max-min);
    }
}


/*----------------------------------------------------------------------------------------------*/
/*-----------------------------This function Finds the BMI categorys----------------------------*/
void bmi_calculation()
{
    float weight, height, bmi;

    printf("\n        BMI Calculator        \n");
    printf("\nPlease enter your weight(kg): ");
    weight = scan_float();

    printf("Please enter you height(m): ");
    height = scan_float();
    
    bmi = weight/(height*height);

    printf("Your category is: ");
    if(bmi<16)  printf("Severely underweight.\n");
    if(bmi<18.5&&bmi>=16)   printf("Underweight.\n");
    if(bmi<25&&bmi>=18.5)   printf("Normal.\n");
    if(bmi<30&&bmi>=25) printf("Overweight.\n");
    if(bmi>=30) printf("Severely overweight.\n");
}


void main()
{
    int f_num;

    while(1)
    {
        printf("\nPlease choose one of the following functions:\n 1- Fibonacci Calculator.\n 2- Perfect and Harmonic Divisor Number Checker.\n 3- Max, Min and Range Finder.\n 4- BMI Calculator.\n 0- Exit.\n (Type '*' to Exit a Function.)\n");
        scanf("%d", &f_num);
        switch(f_num)
        {
            case 1: printf("       Fibonacci Calculator       \n");
                    printf("Please enter The number of terms: ");     
                    calculate_fibonacci_sequence();
                    break;
            
            case 2: decide_perfect_harmonic_number();
                    break;
            
            case 3: difference_max_min();
                    break;
            
            case 4: bmi_calculation();
                    break;
            
            case 0: break;
        }
    }
}