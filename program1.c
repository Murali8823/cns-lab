/*
Program 1a – Experimenting on arrarys 
Author: Muralidhar
USN: ENG23CY0103
*/
#include <stdio.h>
int main(){
int a[] = {10, 12, 18, 9, -1, 7, 8, 9, 6};
int b[3][3];
/* Print 1D array */
for(int i = 0; i < 9; i++) printf("%d ", a[i]);
printf("\n");
/* Convert 1D to 2D */
for(int i = 0, idx = 0; i < 3; i++)
for(int j = 0; j < 3; j++)
b[i][j] = a[idx++];
/* Print 2D array */
for(int i = 0; i < 3; i++){
for(int j = 0; j < 3; j++) printf("%d ", b[i][j]);
printf("\n");
}
/* Convert 2D back to 1D and print */
for(int i = 0; i < 3; i++)
for(int j = 0; j < 3; j++)
printf("%d\n", b[i][j]);
return 0;
}





	
