/*
Program : Caesar Cipher Timing Analysis
Author: Muralidhar Reddy L
USN: ENG23CY0103
Description: Computes encryption and decryption time of Caesar cipher
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
char encrypt_char(char ch, int key){
if(isupper(ch)) return (char)((ch-'A'+key)%26+'A');
if(islower(ch)) return (char)((ch-'a'+key)%26+'a');
if(isdigit(ch)) return (char)((ch-'0'+key)%10+'0');
return ch;
}
char decrypt_char(char ch, int key){
if(isupper(ch)) return (char)((ch-'A'-key+260)%26+'A');
if(islower(ch)) return (char)((ch-'a'-key+260)%26+'a');
if(isdigit(ch)) return (char)((ch-'0'-key+100)%10+'0');
return ch;
}
double encrypt_string_with_timing(char *plaintext, char *ciphertext, int key){
clock_t start=clock();
for(int i=0;plaintext[i]!='\0';i++){
ciphertext[i]=encrypt_char(plaintext[i],key);
}
ciphertext[i]='\0';
return ((double)(clock()-start)/CLOCKS_PER_SEC)*1000.0;
}
double decrypt_string_with_timing(char *ciphertext, char *plaintext, int key){
clock_t start=clock();
for(int i=0;ciphertext[i]!='\0';i++){
plaintext[i]=decrypt_char(ciphertext[i],key);
}
plaintext[i]='\0';
return ((double)(clock()-start)/CLOCKS_PER_SEC)*1000.0;
}
int main(void){
char plaintext[5000],ciphertext[5000],decrypted[5000];
int key;
printf("========== Caesar Cipher Timing Analysis ==========\n");
printf("Enter the plaintext: ");
scanf("%4999s",plaintext);
printf("Enter the key (shift value): ");
scanf("%d",&key);
int text_length=strlen(plaintext);
double encryption_time=encrypt_string_with_timing(plaintext,ciphertext,key);
printf("\nEncrypted text: %s\n",ciphertext);
printf("Text length: %d characters\n",text_length);
printf("Encryption Time (ET): %.6f milliseconds\n",encryption_time);
double decryption_time=decrypt_string_with_timing(ciphertext,decrypted,key);
printf("\nDecrypted text: %s\n",decrypted);
printf("Decryption Time (DT): %.6f milliseconds\n",decryption_time);
printf("\n========== Timing Summary ==========\n");
printf("Text Length: %d characters\n",text_length);
printf("Encryption Time: %.6f ms\n",encryption_time);
printf("Decryption Time: %.6f ms\n",decryption_time);
printf("Total Time: %.6f ms\n",encryption_time+decryption_time);
return 0;
}
