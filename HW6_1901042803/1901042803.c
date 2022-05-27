#include <stdio.h>
#include <stdlib.h>


#define N 2

typedef enum{                   /*defines the directions as an enum variable*/
    up,
    down,
    left,
    right
} direction;


/*This function takes a solved table and shuffles it by applying movements N*N*N/2 times to start the games*/
void table_scrambler(int arr[][N]){
    int i, x=N-1, y=N-1, tempp , new_d[][2] = {{-1, 0}, {1, 0}, {0,-1}, {0, 1}};
    direction randMove;

    for(i=0;i<N*N*N/2;i++){                     /*The number of loop iterations might be big because some random movements deletes others, and some are invalid*/
        randMove = (rand() % (4));
        
        if(x + new_d[randMove][1]<=N-1&&x + new_d[randMove][1]>=0&&y + new_d[randMove][0]<=N-1&&y + new_d[randMove][0]>=0){     /**//**/
            tempp = arr [y + new_d[randMove][0]][x + new_d[randMove][1]];                                                           /**/
            arr [y + new_d[randMove][0]][x + new_d[randMove][1]] = arr[y][x];                                                       /**/
            arr [y][x] = tempp;                                                                                                     /**//*Switches the places of the empty cell and the next cell to the given direction*/
            y += new_d[randMove][0];                                                                                                /**/
            x += new_d[randMove][1];                                                                                                /**/
        }                                                                                                                       /**//**/
    }
}

/*Creates a solved table*/
void table_creator(int arr[][N]){
    int i, j, ele = 1, k=0, elements[N*N];

    for(j=0;j<N;j++)
        for(i=0;i<N;i++){
            arr[j][i] = ele;
            ++ele;
        }

    arr[N-1][N-1] = 0;
}

/*Prints a given table*/
void table_printer(int arr[][N]){
    int i, j;

    printf("\n   ");
    for(i=0;i<N;i++)    printf("  %2d ", i+1);      /*Prints the numbers of the columns*/
    printf("\n");

    for(j=0;j<N;j++){
        printf("   ");
        for(i=0;i<5*N+1;i++)    printf("*");

        printf("\n");
        printf("%2d ", j+1);                        /*Prints the numbers of the rows*/
        for(i=0;i<N;i++){
            if(arr[j][i]==0) printf("*    ");       /*The blank in the table is 0, this writes the blank in it*/
            else printf("* %2d ", arr[j][i]);
        }

        printf("*\n");
    }
    
    printf("   ");
    for(i=0;i<5*N+1;i++)    printf("*");
    printf("\n");
}

/*Checks if the requested movement is valid and returns a logical value*/
int movement_checker(int arr[][N], direction movement, int new_d[][2], int y, int x, int * ny, int * nx){
    int i, j;

    y += new_d[movement][0];                /*Initialy moves the indicator to the next cell in the given direction*/
    x += new_d[movement][1];                /**/

    while(x<N&&x>=0&&y<N&&y>=0){
        if(arr[y][x] == 0){             /**//**/
            *nx = x;                        /**//*When a zero is found, the function returns 1, and the coordinates of the zero*/
            *ny = y;                        /**/
            return 1;                   /**//**/
        }
        
        y += new_d[movement][0];
        x += new_d[movement][1];
    }
    
    return 0;
}

/*Takes the location and direction parameters and performs the movement*/
void movement_fun(int arr[][N], direction movement, int x, int y){
    int emptyx, emptyy, tempn, new_d[][2] = {{-1, 0}, {1, 0}, {0,-1}, {0, 1}};

    if(movement<up||movement>right){                                        /*Terminates when the given direction is not understandable*/
        printf(" Unrecognised direction, please try again:\n ");
        return;
    }

    if(movement_checker(arr, movement, new_d, y, x, &emptyy, &emptyx)==0)   /*Terminates when the requested movement is invalid*/
    {
        printf(" Unvalid movement, please enter the values again:\n ");
        return;
    }
    
    while(emptyx!=x||emptyy!=y){                    /*This loop keeps shifting values with the empty cell till reaching the cell targeted by the movement*/
        tempn = arr [emptyy - new_d[movement][0]][emptyx - new_d[movement][1]];
        arr [emptyy - new_d[movement][0]][emptyx - new_d[movement][1]] = arr[emptyy][emptyx];
        arr[emptyy][emptyx] = tempn;
        emptyy -= new_d[movement][0];               /*Updates the position of the empty cell*/
        emptyx -= new_d[movement][1];               /**/
    }
}

/*Checks the status of the table and returns a logical value*/
/*0 = not solved,   1 = solved*/
int status_checker(int arr[][N]){
    int i, j;

    if(arr[N-1][N-1]!=0) return 0;          

    for(j=0;j<N;j++)
        for(i=0;i<N;i++){
            if ((j!=N-1&&arr[j+1][0] < arr[j][i])||(j!=N-1&&i!=N-2&&arr[j][i+1] < arr[j][i]))    return 0;
        }

    return 1;
}

/*The main function*/
int main ()
{
    int i, j, x, y, direction_in, arr[N][N], *parr[N][N];

    srand(((long)&x)/1000);     /*Setting the seed for random numbers generator using a variable's address*/
    table_creator(arr);         /*Creates the table*/
    table_scrambler(arr);       /*Scrambles it*/

    while(1){
        table_printer(arr);                                                                 
        printf("\n Please enter the movement parameters:\n (Row, Column, direction )\n ");  /**//**/
        printf("up = %u, down = %u,\n left = %u, right = %u\n ", up, down, left, right);        /**/
                                                                                                /**/
       if(scanf("(%d, %d, %d)", &y, &x, &direction_in)!=3){                                     /**/
            printf(" Please enter the values in the right order and format: \n ");              /**/
            while(getchar()!='\n');                                                             /**/
            continue;                                                                           /**/
        }                                                                                       /**//*Takes the input parameters and checks if they are logicaly valid*/
                                                                                                /**/
        else if(x<0||y<0||x>N||y>N){                                                            /**/
            printf("\n The location parameters should be between 1 and %d.\n ", N);             /**/
            while(getchar()!='\n');                                                             /**/
            continue;                                                                           /**/
        }                                                                                       /**/
                                                                                                /**/
        while(getchar()!='\n');                                                             /**//**/

        x -= 1;
        y -= 1;

        movement_fun(arr, direction_in, x, y);      /*Calla the function responsible for moving*/
        if(status_checker(arr)==1) break;           /*Breaks the loop when the table is solved*/
    }

    table_printer(arr);
    printf("\n Congratulations, you solved the puzzle!\n");
}