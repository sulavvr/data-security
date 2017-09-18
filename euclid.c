/**
* CS 6313 Data Security
* Homework 1
* Dr. Hai Jiang
* Q1. Euclidean algorithm for GCD
*	Write a C program euclid.c to implement the algorithm in Figure 2.2 (page 33)
*	The program should be compiled as   gcc euclid.c –o euclid
*	The program should be executed as    ./euclid a b
*	    Parameters a and b are the two positive numbers for GCD(a, b)
*	    Print out the result GCD(a, b)
**/
#include <stdio.h>

// function declaration to calculate GCD
int gcd(int, int);

int main(int argc, char **argv) {
    int a, b;   // initialize variables for program arguments
    // only continue if there are 2 numbers
    if (argc > 2) {
        sscanf(argv[1], "%d", &a);
        sscanf(argv[2], "%d", &b);

        // if b is greater then swap a and b values
        if (a < b) {
            int temp = a;
            a = b;
            b = temp;
        }
    
        printf("The GCD for %d and %d is %d. \n", a, b, gcd(a, b));
    } else { 
        // fail if not enough arguments provided
        puts("2 numbers are required to calculate gcd!");
    }

    return 0;
}

// recursive function to calculate the GCD
int gcd(int a, int b) {
    if (b == 0) return a;
    
    return gcd(b, a % b);
}