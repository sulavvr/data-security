#include <stdio.h>
#include <math.h>

char *millerRabin(int, int);
struct nums {
    int k, q;
};
struct nums getKQ(int, int);
// main
int main(int argc, char **argv) {
    int a, n;

    if (argc > 2) {
        sscanf(argv[1], "%d", &a);
        sscanf(argv[2], "%d", &n);

        // if number is even or multiple of 5, we return composite
        if (n > 2 && (n % 2 == 0 || n % 5 == 0)) {
            puts("composite");
        } else {
            char *result = millerRabin(a, n);
            printf("%s", result);
        }
    }
    return 0;
}

char *millerRabin(int a, int n) {
    struct nums kq = getKQ(n, 1); // q = 1

    // printf("%d %d\n", kq.q, kq.k);
    int aq = (int) pow(a, kq.q);
    if (aq % n == 1) {
        return "maybe prime";
    }

    int i = 0;
    for (; i < kq.k; i++) {
        int twoiq = (int) pow(2, i) * kq.q;
        int a2iq = (int) pow(a, twoiq);
        if (a2iq % n == 1) {
            return "maybe prime";
        }
    }

    return "composite";
}

struct nums getKQ(int n, int q) {
    struct nums num;
    float f = log2((n - 1) / q);

    printf("%d %f\n", q, f);

    if (ceilf(f) == f) {
        num.k = (int) f;
        num.q = q;

        return num;
    }

    q += 2; // odd
    return getKQ(n, q);
}
