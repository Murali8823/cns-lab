/*
Program : Caesar Cipher (Encryption/Decryption)
Author: Muralidhar Reddy L
USN: ENG23CY0103
Description: Implementation considering A-Z, a-z, 0-9 characters
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
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
void encrypt_string(char *plaintext, char *ciphertext, int key){
	int i;
	for(i = 0; plaintext[i] != '\0'; i++){
		ciphertext[i] = encrypt_char(plaintext[i], key);
	}
	ciphertext[i] = '\0';
}
void decrypt_string(char *ciphertext, char *plaintext, int key){
	int i;
	for(i = 0; ciphertext[i] != '\0'; i++){
		plaintext[i] = decrypt_char(ciphertext[i], key);
	}
	plaintext[i] = '\0';
}
int main(void){
char plaintext[500],ciphertext[500],decrypted[500];
int key,choice;
printf("========== Caesar Cipher (A-Z, a-z, 0-9) ==========\n");
printf("1. Encrypt\n2. Decrypt\n");
printf("Enter your choice (1 or 2): ");
scanf("%d",&choice);
printf("Enter the text: ");
scanf("%499s",plaintext);
printf("Enter the key (shift value): ");
scanf("%d",&key);
if(choice==1){
encrypt_string(plaintext,ciphertext,key);
printf("Encrypted text: %s\n",ciphertext);
}
else if(choice==2){
decrypt_string(plaintext,decrypted,key);
printf("Decrypted text: %s\n",decrypted);
}
else printf("Invalid choice!\n");
return 0;
}
