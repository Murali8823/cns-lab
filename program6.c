/*
Program 5: Caesar Cipher (Encryption/Decryption) with File Input
Author: Muralidhar Reddy L
USN: ENG23CY0103
Description: Reads plaintext from file and encrypts/decrypts it
*/
#include <stdio.h>
#include <ctype.h>
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
void encrypt_file(char *input_filename, char *output_filename, int key){
FILE *input_file=fopen(input_filename,"r");
if(input_file==NULL){
printf("Error: Cannot open input file %s\n",input_filename);
return;
}
FILE *output_file=fopen(output_filename,"w");
if(output_file==NULL){
printf("Error: Cannot create output file %s\n",output_filename);
fclose(input_file);
return;
}
int ch;
while((ch=fgetc(input_file))!=EOF){
fputc(encrypt_char((char)ch,key),output_file);
}
fclose(input_file);
fclose(output_file);
printf("File encrypted successfully!\nEncrypted file saved as: %s\n",output_filename);
}
void decrypt_file(char *input_filename, char *output_filename, int key){
FILE *input_file=fopen(input_filename,"r");
if(input_file==NULL){
printf("Error: Cannot open input file %s\n",input_filename);
return;
}
FILE *output_file=fopen(output_filename,"w");
if(output_file==NULL){
printf("Error: Cannot create output file %s\n",output_filename);
fclose(input_file);
return;
}
int ch;
while((ch=fgetc(input_file))!=EOF){
fputc(decrypt_char((char)ch,key),output_file);
}
fclose(input_file);
fclose(output_file);
printf("File decrypted successfully!\nDecrypted file saved as: %s\n",output_filename);
}
int main(void){
char input_filename[100],output_filename[100];
int key,choice;
printf("========== Caesar Cipher with File Input/Output ==========\n");
printf("1. Encrypt file\n2. Decrypt file\n");
printf("Enter your choice (1 or 2): ");
scanf("%d",&choice);
printf("Enter input filename: ");
scanf("%99s",input_filename);
printf("Enter output filename: ");
scanf("%99s",output_filename);
printf("Enter the key (shift value): ");
scanf("%d",&key);
if(choice==1) encrypt_file(input_filename,output_filename,key);
else if(choice==2) decrypt_file(input_filename,output_filename,key);
else printf("Invalid choice!\n");
return 0;
}
*/