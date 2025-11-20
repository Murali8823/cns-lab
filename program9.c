/*
Program: Playfair Cipher Timing Analysis
Author: Muralidhar Reddy L (ENG23CY0103)
Description: Encrypts/Decrypts files of various sizes and measures execution time.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define CHUNK 5000

void toLower(char *s, int n){for(int i=0;i<n;i++)if(s[i]>='A'&&s[i]<='Z')s[i]+=32;}
int rmSpace(char *s,int n){int j=0;for(int i=0;i<n;i++)if(!isspace(s[i]))s[j++]=s[i];s[j]='\0';return j;}
int mod5(int a){return (a+5)%5;}
int prepare(char *s,int n){if(n%2)s[n++]='z';s[n]='\0';return n;}

void keyTable(char *key,int ks,char t[5][5]){
    int used[26]={0},i=0,j=0;
    for(int k=0;k<ks;k++)if(key[k]!='j')used[key[k]-'a']=1;
    for(int k=0;k<26;k++){
        if(key[k]&&used[key[k]-'a'])continue;
        char c=k<ks?key[k]:k+'a';
        if(!used[c-'a']&&c!='j'){t[i][j++]=c;used[c-'a']=1;if(j==5){i++;j=0;}}
    }
}

void locate(char t[5][5],char a,char b,int *p){
    if(a=='j')a='i';if(b=='j')b='i';
    for(int i=0;i<5;i++)for(int j=0;j<5;j++){
        if(t[i][j]==a){p[0]=i;p[1]=j;}
        if(t[i][j]==b){p[2]=i;p[3]=j;}
    }
}

void playfair(char *s,char t[5][5],int n,int enc){
    int p[4];
    for(int i=0;i<n;i+=2){
        locate(t,s[i],s[i+1],p);
        if(p[0]==p[2]){
            s[i]=t[p[0]][mod5(p[1]+(enc?1:-1))];
            s[i+1]=t[p[0]][mod5(p[3]+(enc?1:-1))];
        }else if(p[1]==p[3]){
            s[i]=t[mod5(p[0]+(enc?1:-1))][p[1]];
            s[i+1]=t[mod5(p[2]+(enc?1:-1))][p[1]];
        }else{
            s[i]=t[p[0]][p[3]];s[i+1]=t[p[2]][p[1]];
        }
    }
}

double processFile(char *infile,char *outfile,char *key,int enc){
    FILE *in=fopen(infile,"rb"),*out=fopen(outfile,"wb");
    if(!in||!out)return -1;
    char buf[CHUNK],t[5][5];int ks=strlen(key);ks=rmSpace(key,ks);toLower(key,ks);keyTable(key,ks,t);
    clock_t st=clock();int n;
    while((n=fread(buf,1,CHUNK,in))>0){
        if(enc){n=rmSpace(buf,n);toLower(buf,n);n=prepare(buf,n);}
        playfair(buf,t,n,enc);fwrite(buf,1,n,out);
    }
    fclose(in);fclose(out);
    return ((double)(clock()-st)/CLOCKS_PER_SEC)*1000;
}

int main(){
    char key[100];printf("Enter key: ");scanf("%s",key);
    char files[5][20]={"test1kb.txt","test10kb.txt","test1mb.txt","test10mb.txt","test100mb.txt"};
    char sizes[5][10]={"1KB","10KB","1MB","10MB","100MB"};
    FILE *r=fopen("playfair_results.txt","w");
    fprintf(r,"File\tET(ms)\tDT(ms)\tTotal\n");
    for(int i=0;i<5;i++){
        FILE *f=fopen(files[i],"r");if(!f){fprintf(r,"%s\tNotFound\n",sizes[i]);continue;}fclose(f);
        char encf[50],decf[50];sprintf(encf,"enc_%s",files[i]);sprintf(decf,"dec_%s",files[i]);
        double et=processFile(files[i],encf,key,1),dt=processFile(encf,decf,key,0);
        printf("%s -> ET: %.3f ms, DT: %.3f ms\n",sizes[i],et,dt);
        fprintf(r,"%s\t%.3f\t%.3f\t%.3f\n",sizes[i],et,dt,et+dt);
    }
    fclose(r);
    printf("\nResults saved to playfair_results.txt\n");
    return 0;
}
