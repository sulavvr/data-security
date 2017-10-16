/**
 * CS 6313 Data Security
 * Homework 2
 * Dr. Hai Jiang
 * 2. Chinese Remainder Theorem     (15 points)
 *       Write a C program crt.c to implement Chinese Remainder Theorem
 *           Break A into a sequence over co-primed factors  m1 m2 m3  of  M
 *       The program should be compiled as   gcc crt.c –o crt
 *       The program should be executed as    ./crt A m1 m2 m3 …
 *           Parameters A is the number in domain ZM
 *           Any number of co-primed factors can be accepted (dealt with argc)
 *           Print out all ai and the contents of ci (Mi and M-1i ).
 *           You might need to call extended Euclidean algorithm for the inverse.
 *           Demonstrate that we can recover A
 */
#include <stdio.h>

// define constants for exiting
#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

// function declaration to calculate GCD
int gcd(int, int);
// function declaration to calculate the linear combinations to get the multiplicative inverse
int linearCombinations(int, int, int, int);

// struct declaration
struct CRT {
    int a, m, Minv, M, c;                   // stores values for ai, mi, Minvi, Mi and ci
    void (*print) (const struct CRT, int);  // pointer to the print function
    int (*recover) (const struct CRT);      // pointer to the recover funciton
};

// function to print values of the struct
void print(struct CRT val, int i) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, val.a, val.m, val.Minv, val.M, val.c);
}

// function for calculating the product of a and c of the struct
int recover(struct CRT val) {
    return val.a * val.c;       // (ai * ci)
}

// main
int main(int argc, char **argv) {
    // total count - 2 since first arg is the program and the second is A
    int count = argc - 2;
    int A;
    sscanf(argv[1], "%d", &A);

    // declare array of structs based on co-primed factors m1 m2 m3 ....
    struct CRT vals[count];

    int i;              // declaration for the for loops
    int sum = 0;        // variable to hold sum(ai * ci)
    int M = 1;          // M = m1 * m2 * m3 ....

    for (i = 0; i < count; i++) {
        vals[i].print = print;      // assign print function to struct function pointer
        vals[i].recover = recover;  // assign recover function to struct member

        // store m in struct
        sscanf(argv[2 + i], "%d", &vals[i].m);
        // get M from product of co-primed factors
        M *= vals[i].m;
    }

    for (i = 0; i < count; i++) {
        vals[i].M = M / vals[i].m;      // calculate Mi from M / mi

        // if gcd(Mi, mi) is 1, then we get the multiplicative inverse else we know that the mi's are not co-primes
        // which does not apply to the Chinese Remainder Theorem
        if (gcd(vals[i].M, vals[i].m) == 1) {
            vals[i].Minv = linearCombinations(vals[i].M, vals[i].m, 1, 1);
        } else {
            puts("ERROR! Found values that are not relatively prime (co-primed factors), so we cannot continue the Chinese Remainder Theorem! Exiting...");
            return EXIT_FAILURE;
        }

        vals[i].a = A % vals[i].m;              // ai = A mod mi
        vals[i].c = vals[i].M * vals[i].Minv;   // ci = Mi * (Mi^-1 mod mi)
        sum += vals[i].recover(vals[i]);        // recover A using A = sum(ai * ci)
    }

    printf("--------------------------------------------------------------\n");
    printf("A = %d; M = %d\n", A, M);

    // print values of ai, Mi, ci
    printf("i\tai\tmi\tMinvi\tMi\tCi\n");
    for (i = 0; i < count; i++) {
        vals[i].print(vals[i], i+1);
    }

    printf("\n");
    printf("Recovering A = sum(ai * ci) mod m: %d\n", sum % M); // final step for recovering A = sum mod M
    printf("---------------------------------------------------------------\n");

    return EXIT_SUCCESS;
}

// recursive function to calculate the GCD
int gcd(int a, int b) {
    if (b == 0) return a;

    return gcd(b, a % b);
}

// recursive function to calculate x and y from the equation
// ax + by = gcd(a, b) also known as the linear combinations
int linearCombinations(int a, int b, int x, int y) {
    if ((a*x) + (b*y) == 1) {           // if sum is 1, found the appropriate x andy
        return x;
    } else if ((a*x) + (b*y) > b) {     // if sum is greater than b, decrement y and recurse
        return linearCombinations(a, b, x, --y);
    } else {                            // if sum is less than b, increment x and recurse
        return linearCombinations(a, b, ++x, y);
    }
}
