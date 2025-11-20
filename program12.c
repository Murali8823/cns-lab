/*
Program 11: Diffie-Hellman Key Exchange Protocol
Author: Muralidhar Reddy L
USN: ENG23CY0103
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Function to compute modular exponentiation (a^b mod m) */
long long modExp(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }

    return result;
}

/* Main function */
int main(void)
{
    long long p = 23;  /* Prime number */
    long long g = 5;   /* Generator */
    long long privA, privB, pubA, pubB, secretA, secretB;

    srand(time(NULL));

    printf("========== Diffie-Hellman Key Exchange ==========\n");
    printf("Prime (p) = %lld, Generator (g) = %lld\n\n", p, g);

    /* Alice generates private key and computes public key */
    privA = 2 + (rand() % (p - 4));
    pubA = modExp(g, privA, p);
    printf("Alice: Private = %lld, Public = %lld\n", privA, pubA);

    /* Bob generates private key and computes public key */
    privB = 2 + (rand() % (p - 4));
    pubB = modExp(g, privB, p);
    printf("Bob:   Private = %lld, Public = %lld\n\n", privB, pubB);

    /* Both compute shared secret */
    secretA = modExp(pubB, privA, p);
    secretB = modExp(pubA, privB, p);

    printf("Alice computes: %lld^%lld mod %lld = %lld\n", pubB, privA, p, secretA);
    printf("Bob computes:   %lld^%lld mod %lld = %lld\n\n", pubA, privB, p, secretB);

    printf("Shared Secret: %lld\n", secretA);
    printf("Keys match: %s\n", secretA == secretB ? "YES" : "NO");

    return 0;
}
