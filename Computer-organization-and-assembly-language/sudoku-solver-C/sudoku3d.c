#include <stdio.h>
#include <stdlib.h>

// Declare printSudoku function
void printSudoku(int***);
// Declare solveSudoku function
int solveSudoku(int***);

//Helper functions. You can define any functions that can help your solve the problem



/*
The main program reads a text file containing the block values of the Sudoku grid.
It then saves each 3x3 block into a 2D array. The Sudoku grid is composed of 9 3x3 blocks.
DO NOT MODIFY THE MAIN FUNTION!!!
*/
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    int ***blocks = (int***)malloc(9 * sizeof(int**));

    // Open file for reading
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open File!\n");
        return 0;
    }

	// Read 9x9 blocks into 2D arrays
    for(i=0; i<9; i++)
    {
        *(blocks+i) = (int**)malloc(3 * sizeof(int*));
        printf("Reading numbers in block %d... \n", i+1);
        for(j=0; j<3; j++)
        {
            *(*(blocks+i)+j) = (int*)malloc(3 * sizeof(int));

                fscanf(fptr, "%d %d %d", *(*(blocks+i)+j), *(*(blocks+i)+j)+1, *(*(blocks+i)+j)+2);
                printf("%d %d %d\n", *(*(*(blocks+i)+j)), *(*(*(blocks+i)+j)+1), *(*(*(blocks+i)+j)+2));
        }
    }
	
	// Print out original Sudoku grid
    printf("Printing Sudoku before being solved:\n");
    printSudoku(blocks);

	// Call solveSudoku and print out result
    
    printf("\nSolving Sudoku...\n\n");
    //printf("Error");
    
    
    if(solveSudoku(blocks)){
        printf("Sudoku solved!\n");
        printSudoku(blocks);
    }
    else
        printf("This Sudoku cannot be solved!\n");

    return 0;
}





int checkrow(int*** arr, int row)
{
    int i = 0;
    int* tracker = malloc(sizeof(int)*9);
    for(i=0; i<9; i++)
    {
        if(*(*(*(arr+3*(row/3)+(i/3)) + row%3)+ i%3) !=0)
        {
        
            if(   *(tracker+ (*(*(*(arr+3*(row/3)+(i/3)) + row%3)+ i%3)-1)) == 0)
            {
                *(tracker+ (*(*(*(arr+3*(row/3)+(i/3)) + row%3)+ i%3)-1)) =1;
            }
            else
            return 0;
        }
    }
    return 1;
    
}

int checkcol(int*** arr, int col)
{
    int i = 0;
    int* tracker = malloc(sizeof(int)*9);
    for(i=0; i<9; i++)
    {
        if(*(*(*(arr+3*(i/3)+(col/3)) + i%3)+ col%3) !=0)
        {
            
            if(   *(tracker+ (*(*(*(arr+3*(i/3)+(col/3)) + i%3)+ col%3)-1) ) == 0)
            {
                *(tracker+ (*(*(*(arr+3*(i/3)+(col/3)) + i%3)+ col%3)-1) ) =1;
            }
            else
            return 0;
        }
    }
    return 1;
    
}


int checkbox(int*** arr, int box)
{
    int i = 0;
    int* tracker = malloc(sizeof(int)*9);
    for(i=0; i<9; i++)
    {
        
        
        if(*(*(*(arr +box) +i/3)+i%3)!=0)
        {
            
            
            if(   *(tracker+  (*(*(*(arr +box) +i/3)+i%3)-1) ) == 0)
            {
                *(tracker+ (*(*(*(arr +box) +i/3)+i%3)-1) ) =1;
            }
            else
            return 0;
        }
    }
    return 1;
    
}


void printSudoku(int*** arr){
	// This function will print out the complete Sudoku grid (arr). It must produce the output in the SAME format as the samples in the instructions. 	
    int i =0, x =0;
	// Your implementation here
    
    for(i=0; i<9; i++)
    {
        if(i%3==0)
        {
            printf("\n");
        }
        for(x=0; x<9; x++)
        {
            
            if(x%3==0)
            {
                printf("   ");
            }
            printf("%d ", *(*(*(arr+3*(i/3)+(x/3)) + i%3)+ x%3) );
            
        }
        printf("\n");
    }
    
    
}


void deepptrcopy(int*** blocks, int*** copy)
{
    
    int c =0, i=0, x=0;
    
    for(c=0; c<9; c++)
    {
        *(copy+c) =malloc(sizeof(int*)*3);
        for(i=0; i<3; i++)
        {
            *(*(copy+c)+i) =malloc(sizeof(int)*3);
            for(x=0; x<3; x++)
            {
                *(*(*(copy+c)+i)+x)= *(*(*(blocks+c)+i)+x);
            }
        }
    }
}

void deepset(int*** copy, int*** target)
{
    
    int c =0, i=0, x=0;
    
    for(c=0; c<9; c++)
    {
        for(i=0; i<3; i++)
        {
            for(x=0; x<3; x++)
            {
                *(*(*(target+c)+i)+x)= *(*(*(copy+c)+i)+x);
            }
        }
    }
}







int solveSudoku(int*** arr)
{
	// This is the function to solve the Sudoku (blocks). Feel free to use any helper functions.
	// YOU MUST NOT USE ANY ARRAY NOTATION ([])!
    
    int*** copy = malloc(sizeof(int**)*9);
    
    deepptrcopy(arr, copy);
    
    
    int c =1, i=0, x=0;
    for(i=0; i<9; i++)
    {
        for(x=0; x<9; x++)
        {
            if(*(*(*(arr+3*(i/3)+(x/3)) + i%3)+ x%3)==0)
            {
                
                
                for(c=1; c<=9; c++)
                {
                    *(*(*(copy+3*(i/3)+(x/3)) + i%3)+ x%3) = c;
                    
                    if (checkrow( copy,i) && checkcol(copy,x) && checkbox(copy,3*(i/3)+(x/3)))
                    {
                        
                        if(i*x==64)
                        {
                            deepset(copy, arr);
                            return 1;
                        }
                        else if(solveSudoku(copy) == 1)
                        {
                            deepset(copy, arr);
                            return 1;
                        }
                        
                    }
                    
                    
                }
                
            }
            
            //printf("%d ", *(*(*(arr+3*(i/3)+(x/3)) + i%3)+ x%3) );
            
        }
    }
	//Your implementation here

	return 0;
}


