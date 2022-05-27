#include <stdio.h>
#include <string.h>


typedef enum {                  /**//**/
    employee,                       /**/
    retired,                        /**/
    student,                        /**//*The enumerated types of customers*/
    unemployed,                     /**/
    other                           /**/
} customer_t;                   /**//**/

typedef struct {                /**//**/
    char name[20];                  /**/
    int age;                        /**//*The struct for a customer's info*/
    customer_t category;            /**/
} customer_info;                /**//**/


/*Adds new_customer to the sequence*/
void add_customer (customer_info sequence[25][16], customer_info new_customer, int max_count[5])
{
    int i, j=0, 
        counter=0;          /*counter: counts the number of times the same label repeated consecutively*/

    for(i=0; (i<15) && (sequence[j][0].age!=-1) ;i++)
    {
        if(sequence[j][i].category==new_customer.category)
            counter += 1;

        else if (counter<max_count[new_customer.category])
        {                                                                   /*The cases that require writing in the middle of the sequence:*/
            if (counter>0||                                                 /*1- The same label was found and did not repeat max times.    */
                sequence[j][i].category>new_customer.category||             /*2- The current label is bigger than the new one, and the new label is not found.*/
                sequence[j][i].age==-1)                                     /*3- The end of the line is reached and and the new label is not found.*/
                break;
        }

        else if(j<24)           /*When none of the conditions are met, proceeds to the next line when available*/
        {
            j++;
            i = -1;
            counter = 0;
        }

        else return;
    }

    memcpy(&sequence[j][i+1], &sequence[j][i], sizeof(sequence[0][0])*(15-i));      /*Pushs the labels after the new label one space forward in the line*/
    strcpy(sequence[j][i].name, new_customer.name);             /**//**/
    sequence[j][i].age = new_customer.age;                          /**//*Assigning the new label to the created space*/
    sequence[j][i].category = new_customer.category;            /**//**/
}


/*Processes the first customer in the sequence*/
void process_customer (customer_info sequence[25][16], int max_count[5])
{
    int i, j;
    customer_t temp;            /*Stores the label of the processed value temporarily*/

    printf("Proceed customer is %s", sequence[0][0].name);
    temp = sequence[0][0].category;
    memcpy(&sequence[0][0], &sequence[0][1], sizeof(sequence[0][0])*(16));      /*Pulls the labels one space toward the start in the first line*/

    /*This part reassigns the places of the customers with the same label (more like moving them one space toward the processed customer)*/
    for(j=1;j<24;j++)
        for(i=0;i<15, sequence[j][i].age!=-1;i++)
            if(temp==sequence[j][i].category)
            {
                add_customer(sequence, sequence[j][i], max_count);              
                memcpy(&sequence[j][i], &sequence[j][i+1], sizeof(sequence[0][0])*(15-i));
            }
}


/*Prints the sequence*/
void print_list (customer_info sequence[25][16])
{
    int i, j;

    printf("\nCurrent Sequence: ");

    if(sequence[0][0].age!=-1)
    {
        printf("%u", sequence[0][0].category);
    
        for(i=1;(i<15) && (sequence[0][i].age!=-1);i++)
            printf(" - %u", sequence[0][i].age);
    }

    for(j=1; (j<=24) && (sequence[j][0].age!=-1) ;j++)
    {
        for(i=0; (i<15) && (sequence[j][i].age!=-1) ;i++)
            printf(" - %u", sequence[j][i].age);
    }

    printf("\n");
}


/*Scans the parameters for a new customer and returns the number of valid inputs*/
int customer_scan (customer_info *new_customer)
{
    int status=0;

    printf("\nPlease enter the name of the customer :");
    status += scanf("%s", new_customer->name);

    printf("\nPlease enter the age of the customer :");
    status += scanf("%d", &(new_customer->age));

    printf("\nPlease enter the label of the customer :");
    status += scanf("%u", &(new_customer->category));

    return status;
}


/*The main function of the sequence manager*/
void sequence_manager ()
{
    customer_info sequence[25][16], new_customer;
    int max_count[5] = {5, 3, 3, 2, 2};         /*Stores the number of maximum times each label can be consecutively repeat*/
    int command, i;

    for(i=0;i<25;i++)
        sequence[i][0].age = -1;

    printf("\n***********Banking System***********\n");

    while(1)
    {
        print_list(sequence);             /*Prints the list*/
        printf("\n1-Add customer\n2-Process customer\n");
        scanf("%d", &command);

        if(command==1)
        {
            if(customer_scan (&new_customer)!=3)        /*Scans for the new customer*/
            {
                printf("Please enter valid values\n");
                continue;
            }

            add_customer(sequence, new_customer, max_count);       /*Adds the new customer to the sequence*/
        }

        else if(command==2)
        {
            if(sequence[0][0].age!=-1) process_customer(sequence, max_count);       /*Processes the first customer in the sequence*/
            else    printf("\nThere is not any customer in bank system sequence.\n");
            continue;
        }

        else break;             /*Exits when An input other than 1 and 2 is entered*/
    }
}


int main()
{
    sequence_manager ();
}
