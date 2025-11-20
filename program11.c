/*
Program 10: Extended Euclidean Algorithm
Author: Muralidhar Reddy L
USN: ENG23CY0103
*/
#include <stdio.h>
/* Function to compute Extended Euclidean Algorithm */
int extendedGCD(int a, int b, int *x, int *y)
{
    /* Base case */
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}
/* Main function */
int main(void)
{
    int a, b, x, y, gcd;
    printf("========== Extended Euclidean Algorithm ==========\n");
    printf("Enter two numbers (a, b): ");
    scanf("%d %d", &a, &b);
  gcd = extendedGCD(a, b, &x, &y);
    printf("\nGCD(%d, %d) = %d\n", a, b, gcd);
    printf("Bezout coefficients: x = %d, y = %d\n", x, y);
    printf("Verification: %d*%d + %d*%d = %d\n", a, x, b, y, a*x + b*y);

    return 0;
}
