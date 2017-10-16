#include <stdio.h>

// function declaration to calculate GCD
int gcd(int, int);
// function declaration to calculate the linear combinations
int linearCombinations(int, int, int, int);
struct AimiMinv {
    int ai, mi, Miinv, Mi, ci;
    void (*print) (const struct AimiMinv);
    int (*recover) (const struct AimiMinv);
};

// function to print values of the struct
void print(struct AimiMinv v) {
    printf("%d\t%d\t%d\t%d\t%d\n", v.ai, v.mi, v.Miinv, v.Mi, v.ci);
}

// function for calculating the product of ai and ci of the struct
int recover(struct AimiMinv v) {
    return v.ai * v.ci;
}

int main(int argc, char **argv) {
    // total count - 2 since first arg is the program and the second is A
    int mcount = argc - 2;
    int A;
    sscanf(argv[1], "%d", &A);

    struct AimiMinv vals[mcount];
    int i;
    int sum = 0;
    int M = 1;

    for (i = 0; i < mcount; i++) {
        vals[i].print = print;
        vals[i].recover = recover;

        sscanf(argv[2 + i], "%d", &vals[i].mi);
        M *= vals[i].mi;
    }

    for (i = 0; i < mcount; i++) {
        vals[i].Mi = M / vals[i].mi;
        if (gcd(vals[i].Mi, vals[i].mi) == 1) {
            vals[i].Miinv = linearCombinations(vals[i].Mi, vals[i].mi, 1, 1);
        }
        vals[i].ai = A % vals[i].mi;
        vals[i].ci = vals[i].Mi * vals[i].Miinv;
        sum += vals[i].recover(vals[i]);
    }

    printf("ai\tmi\tMiinv\tMi\tCi\n");
    for (i = 0; i < mcount; i++) {
        vals[i].print(vals[i]);
    }

    printf("Recovering A = sum(ai * ci) mod m: %d\n", sum % M);

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
