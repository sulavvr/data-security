/**
* CS 6313 Data Security
* Homework 1
* Dr. Hai Jiang
* Q2. Extended Euclidean algorithm for GCD and inverse     
*	Write a C program e-euclid.c to implement extended Euclidean algorithm 
*	The program should be compiled as   gcc e-euclid.c –o e-euclid
*	The program should be executed as    ./e-euclid a b
*	    Parameters a and b are the two positive numbers for GCD(a, b)
*	    Here, assume a > b
*	    Print out the result GCD(a, b)
*	    If GCD(a, b) == 1, print out the a’s multiplicative inverse a-1 mod b
**/
#include <stdio.h>

// function declaration to calculate GCD
int gcd(int, int);
// function declaration to calculate the linear combinations
int linearCombinations(int, int, int, int);

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
        
        int _gcd = gcd(a, b);
        printf("The GCD for %d and %d is %d. \n", a, b, _gcd);

        // multiplicative inverse can be found only if the GCD is 1 for two numbers
        if (_gcd == 1) {
            printf("And the multiplicative inverse of %d(-1) (mod %d) is %d. \n", a, b, linearCombinations(a, b, 1, 1));
        } else {
            // if gcd is not equal to 1
            printf("There is no multiplicative inverse of %d. \n", a);
        }
        
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

// recursive function to calculate x and y from the equation
// ax + by = gcd(a, b) also known as the linear combinations
int linearCombinations(int a, int b, int x, int y) {
    // if sum is 1, found the appropriate x andy
    if ((a*x) + (b*y) == 1) {
        return x;
    } else if ((a*x) + (b*y) > b) {     // if sum is greater than b, decrement y and recurse
        return linearCombinations(a, b, x, --y);
    } else {    // if sum is less than b, increment x and recurse
        return linearCombinations(a, b, ++x, y);
    }
}