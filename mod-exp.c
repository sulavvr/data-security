/**
* CS 6313 Data Security
* Homework 1
* Dr. Hai Jiang
* Q3. Modular exponentiation algorithm
*	Write a C program mod-exp.c to implement modular exponentiation algorithm:
*       To compute ab mod n:
*       d := 1
*       let bk bk-1 … b0 be the binary form of b
*       for i := k downto 0
*            d := d2 mod n
*           if bi = 1 then d := da mod n
*        return d
*   The program should be compiled as   gcc mod-exp.c –o mod-exp
*	The program should be executed as    ./mod-exp a b
*	    Print out the result 

**/
**/
#include <stdio.h>
#include <stdlib.h>

// define a constant size for array allocation for decimal to binary conversion
#define MAX_SIZE 100
// function declaration for generating binary
int *generateBinary(int);

// global variable to store the size of array for binary
int size_of_bin = 0;
int main(int argc, char **argv) {
    int a, b, n;    // initialize variables for program arguments

    // only continue if there are 3 numbers
    if (argc > 3) {
        sscanf(argv[1], "%d", &a);
        sscanf(argv[2], "%d", &b);
        sscanf(argv[3], "%d", &n);

        // store binary array pointer
        int *bin = generateBinary(b);

        // modular exponentiation algorithm
        int i = size_of_bin - 1;    // initialization for loop
        int d = 1;
        // loop through the size of binary array
        for (; i >= 0; i--) {
            d = (d * d) % n;    // d^2 mod n
            if (bin[i] == 1) {  // if b[i] is 1 then da mod n
                d = (d * a) % n;
            }
        }

        printf("The remainder using the Modular exponentiation algorithm is %d. \n", d);

        // free dynamically allocated memory
        free(bin);
    } else {
        // fail if not enough arguments provided
        puts("3 numbers are required to calculate the modular exponentiation!");
    }
    return 0;
}

// iterative algorithm to generate binary for an integer
int *generateBinary(int b) {
    int r = 0; // initialization (remainder)
    int *bin = (int*) calloc(MAX_SIZE, sizeof(int)); // allocate memory of size 100 for binary
    int size = 0; // initalization (size)
    // keep going until quotient is 0
    while (b > 0) {
        r = b % 2;      // remainder is stored into the array
        b /= 2;         // get the quotient

        bin[size] = r;  // store remainder in array at size index
        size++;         // increment size for later
    }

    size_of_bin = size; // assign to global size variable for loop
    return bin;
}