/*
Program: Character Encryption using Caesar Cipher with Key
Author: Muralidhar Reddy L
USN: ENG23CY0103
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
char encrypt_alphanumeric(char ch, int key){
if(islower(ch)) return (char)((ch-'a'+key)%26+'a');
if(isupper(ch)) return (char)((ch-'A'+key)%26+'A');
if(isdigit(ch)) return (char)((ch-'0'+key)%10+'0');
return ch;
}
char encrypt_special_char(char ch, int key){
if(ch>=32&&ch<=47) return (char)((ch-' '+key)%16+' ');
if(ch>=58&&ch<=64) return (char)((ch-':'+key)%7+':');
if(ch>=91&&ch<=96) return (char)((ch-'['+key)%6+'[');
if(ch>=123&&ch<=126) return (char)((ch-'{'+key)%4+'{');
return ch;
}
void encrypt_message(int key, char *tt){
for(int i=0;tt[i]!='\0';i++){
if(isalnum(tt[i])) tt[i]=encrypt_alphanumeric(tt[i],key);
else tt[i]=encrypt_special_char(tt[i],key);
}
}
int main(void){
char text[500];
int key;
printf("Enter a message to encrypt: ");
scanf("%499s",text);
printf("Enter the key: ");
scanf("%d",&key);
encrypt_message(key,text);
printf("Encrypted message: %s\n",text);
return 0;
}
