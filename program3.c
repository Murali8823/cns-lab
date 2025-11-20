/*
Program : Transposition Cipher Implementation with Random Key
Author: Muralidhar Reddy L
USN: ENG23CY0103
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
void generate_random_key(int *key, int size){
for(int i=0;i<size;i++) key[i]=i;
for(int i=size-1;i>0;i--){
int j=rand()%(i+1);
int temp=key[i];
key[i]=key[j];
key[j]=temp;
}
}
void encrypt_transposition(char *plaintext, char *ciphertext, int *key, int cols){
int rows=(strlen(plaintext)+cols-1)/cols;
char matrix[100][100];
int index=0;
for(int i=0;i<rows;i++){
for(int j=0;j<cols;j++){
matrix[i][j]=(index<strlen(plaintext))?plaintext[index++]:' ';
}
}
index=0;
for(int j=0;j<cols;j++){
int col=key[j];
for(int i=0;i<rows;i++){
ciphertext[index++]=matrix[i][col];
}
}
ciphertext[index]='\0';
}
void decrypt_transposition(char *ciphertext, char *plaintext, int *key, int cols){
int rows=(strlen(ciphertext)+cols-1)/cols;
char matrix[100][100];
int index=0;
for(int j=0;j<cols;j++){
int col=key[j];
for(int i=0;i<rows;i++){
matrix[i][col]=ciphertext[index++];
}
}
index=0;
for(int i=0;i<rows;i++){
for(int j=0;j<cols;j++){
plaintext[index++]=matrix[i][j];
}
}
plaintext[index]='\0';
}
int main(void){
char plaintext[200],ciphertext[200],decrypted[200];
int key[100],cols;
srand(time(NULL));
printf("Enter plaintext (no spaces): ");
scanf("%199s",plaintext);
printf("Enter number of columns: ");
scanf("%d",&cols);
generate_random_key(key,cols);
printf("\nGenerated random key: ");
for(int i=0;i<cols;i++) printf("%d ",key[i]);
printf("\n");
encrypt_transposition(plaintext,ciphertext,key,cols);
printf("Ciphertext: %s\n",ciphertext);
decrypt_transposition(ciphertext,decrypted,key,cols);
printf("Decrypted text: %s\n",decrypted);
return 0;
}
