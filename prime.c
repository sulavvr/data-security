/**
 * CS 6313 Data Security
 * Homework 2
 * Dr. Hai Jiang
 * 1. Miller Rabin Algorithm for primality testing       (10 points)
 *     Write a C program prime.c to implemt Miller Rabin Algorithm
 *
 *      Note: In the beginning of the program, check if the input is an even number or a multiple of 5.
 *      If yes, output “composite” directly.
 *      The program should be compiled as   gcc prime.c –o prime
 *      The program should be executed as    ./prime a n
 *      Parameters a is the witness we select and n is the number we are checking the primality
 *      Print out the judgment
 **/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// define a constant size for array allocation for decimal to binary conversion
#define MAX_SIZE 100
// global variable to store the size of array for binary
int size_of_bin = 0;
// struct definition to return from function
struct nums {
    int k, q;
};

// function declarations
char *millerRabin(int, int);                        // miller rabin test for primality
int modularExponentiationAlgorithm(int, int, int);  // use mod exp algorithm to get values for large numbers
int *generateBinary(int);                           // binary generator for mod exp algorithm
struct nums getKQ(int, int);                        // recursively calculate k and q

// main
int main(int argc, char **argv) {
    int a, n;

    if (argc > 2) {
        sscanf(argv[1], "%d", &a);
        sscanf(argv[2], "%d", &n);

        // if number is even or multiple of 5, we return composite
        if ((n > 5) && (n % 2 == 0 || n % 5 == 0)) {
            puts("composite");
        } else {
            char *result = millerRabin(a, n);
            printf("%s\n", result);
        }
    }
    return 0;
}

// actual miller rabin test for primality returns "maybe prime" or "composite"
char *millerRabin(int a, int n) {
    struct nums kq = getKQ(n, 1); // q = 1

    // check if the mod exp is 1
    if (modularExponentiationAlgorithm(a, kq.q, n) == 1) {
        return "maybe prime";
    }

    int i = 0;
    for (; i < kq.k; i++) {
        int twoiq = (int) pow(2, i) * kq.q;

        if (modularExponentiationAlgorithm(a, twoiq, n) == (n - 1)) {
            return "maybe prime";
        }
    }

    return "composite";
}

// get values for k and q recursively using log2 to get the value of k
struct nums getKQ(int n, int q) {
    struct nums num;
    float f = log2((n - 1) / (float) q);

    // if we get integer when doing a log, we get the value of k
    if (ceilf(f) == f) {
        num.k = (int) f;
        num.q = q;

        return num;
    }

    q += 2; // odd
    return getKQ(n, q); // call again if integer for k not found
}

// mod exp algorithm to get the mod of large numbers (from previous assigment)
int modularExponentiationAlgorithm(int a, int q, int n) {
    // store binary array pointer
    int *bin = generateBinary(q);
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

    // free dynamically allocated memory
    free(bin);
    return d;
}

// iterative algorithm to generate binary for an integer (from previous assigment)
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
