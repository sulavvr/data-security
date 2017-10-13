#include <stdio.h>

// function declaration to calculate GCD
int gcd(int, int);
// function declaration to calculate the linear combinations
int linearCombinations(int, int, int, int);

int main(int argc, char **argv) {
    int mcount = argc - 2;
    int A;
    sscanf(argv[1], "%d", &A);

    int i = 0;
    int mi[mcount];
    int M = 1;
    for (; i < mcount; i++) {
        sscanf(argv[2 + i], "%d", &mi[i]);
        M *= mi[i];
    }

    int Mi[mcount];
    for (i = 0; i < mcount; i++) {
        Mi[i] = M / mi[i];
    }

    int Miinv[mcount];
    for (i = 0; i < mcount; i++) {
        if (gcd(Mi[i], mi[i]) == 1) {
            Miinv[i] = linearCombinations(Mi[i], mi[i], 1, 1);
        }
    }

    int Ci[mcount];

    for (i = 0; i < mcount; i++) {
        Ci[i] = Mi[i] * Miinv[i];
    }

    int ai[mcount];

    for (i = 0; i < mcount; i++) {
        ai[i] = A % Mi[i];
    }

    int s = 0;
    for (i = 0; i < mcount; i++) {
        s += ai[i] * Ci[i];
    }

    printf("%d", s);

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
    if ((a*x) + (b*y) == 1) {           // if sum is 1, found the appropriate x andy
        return x;
    } else if ((a*x) + (b*y) > b) {     // if sum is greater than b, decrement y and recurse
        return linearCombinations(a, b, x, --y);
    } else {                            // if sum is less than b, increment x and recurse
        return linearCombinations(a, b, ++x, y);
    }
}
