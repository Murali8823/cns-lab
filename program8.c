/*
Program : Activity - Caesar Cipher Timing Analysis for Different File Sizes
Author: Muralidhar Reddy L
USN: ENG23CY0103
Description: Tests encryption/decryption time on 1KB, 10KB, 100KB, 1MB text files
*/
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
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
double process_file(char *input_file, char *output_file, int key, int mode){
FILE *in=fopen(input_file,"rb");
if(in==NULL) return -1;
FILE *out=fopen(output_file,"wb");
if(out==NULL){fclose(in);return -1;}
clock_t start=clock();
int ch;
while((ch=fgetc(in))!=EOF){
fputc(mode?decrypt_char((char)ch,key):encrypt_char((char)ch,key),out);
}
double time_taken=((double)(clock()-start)/CLOCKS_PER_SEC)*1000.0;
fclose(in);
fclose(out);
return time_taken;
}
long get_file_size(char *filename){
FILE *file=fopen(filename,"rb");
if(file==NULL) return -1;
fseek(file,0,SEEK_END);
long size=ftell(file);
fclose(file);
return size;
}
int main(void){
printf("============================================================\n");
printf("Caesar Cipher Timing Analysis for Different File Sizes\n");
printf("============================================================\n");
printf("Test files: 1KB, 10KB, 100KB, 1MB\n");
printf("Note: Create test files named test1kb.txt, test10kb.txt, etc.\n");
printf("============================================================\n\n");
printf("Enter the encryption key: ");
int key;
scanf("%d",&key);
char test_files[4][20]={"test1kb.txt","test10kb.txt","test100kb.txt","test1mb.txt"};
char file_sizes_str[4][10]={"1 KB","10 KB","100 KB","1 MB"};
FILE *results=fopen("timing_results.txt","w");
if(results==NULL){printf("Error: Cannot create results file\n");return 1;}
fprintf(results,"========== Caesar Cipher Timing Analysis Results ==========\n\n");
fprintf(results,"Key: %d\n\n",key);
fprintf(results,"%-15s%-20s%-20s%-20s\n","File Size","ET (ms)","DT (ms)","Total (ms)");
fprintf(results,"%-15s%-20s%-20s%-20s\n","----------","-------","-------","---------");
for(int i=0;i<4;i++){
FILE *check=fopen(test_files[i],"r");
if(check==NULL){
printf("Warning: File %s not found. Skipping...\n",test_files[i]);
fprintf(results,"%-15s - File not found\n",file_sizes_str[i]);
continue;
}
fclose(check);
long file_size=get_file_size(test_files[i]);
char encrypted_file[100],decrypted_file[100];
sprintf(encrypted_file,"encrypted_%s",test_files[i]);
sprintf(decrypted_file,"decrypted_%s",test_files[i]);
printf("Processing %s... ",file_sizes_str[i]);
double et=process_file(test_files[i],encrypted_file,key,0);
double dt=process_file(encrypted_file,decrypted_file,key,1);
printf("ET: %.6f ms, DT: %.6f ms\n",et,dt);
fprintf(results,"%-15s%-20.6f%-20.6f%-20.6f\n",file_sizes_str[i],et,dt,et+dt);
}
fprintf(results,"\n========== Analysis Summary ==========\n");
fprintf(results,"Encryption Time (ET): Time taken to encrypt the file\n");
fprintf(results,"Decryption Time (DT): Time taken to decrypt the file\n");
fprintf(results,"Total Time: ET + DT\n\n");
fprintf(results,"Note: Times may vary depending on system performance.\n");
fclose(results);
printf("\n========== Timing Analysis Complete ==========\n");
printf("Results saved to: timing_results.txt\n");
return 0;
}
