/*
Program : Double Columnar Cipher Timing Analysis
Author: Muralidhar Reddy L (ENG23CY0103)
Description: Encrypts/Decrypts files (1KB–100MB) and records execution time.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX_KEY 100
#define CHUNK 5000

void getKeyOrder(char *key, int *order, int len) {
    for (int i = 0; i < len; i++) order[i] = i;
    for (int i = 0; i < len; i++) {
        int min = i;
        for (int j = i + 1; j < len; j++)
            if (key[order[j]] < key[order[min]]) min = j;
        int tmp = order[i];
        order[i] = order[min];
        order[min] = tmp;
    }
}

void columnarEncrypt(char *text, char *key, char *result, int len) {
    int klen = strlen(key), rows = (len + klen - 1) / klen, pos = 0;
    int order[MAX_KEY];
    char matrix[1000][100], enc[10000];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < klen; j++)
            matrix[i][j] = (pos < len) ? text[pos++] : ' ';

    getKeyOrder(key, order, klen);
    pos = 0;

    for (int i = 0; i < klen; i++) {
        int col = order[i];
        for (int j = 0; j < rows; j++)
            enc[pos++] = matrix[j][col];
    }

    enc[pos] = '\0';
    strcpy(result, enc);
}

void columnarDecrypt(char *cipher, char *key, char *result, int len) {
    int klen = strlen(key), rows = len / klen, pos = 0;
    int order[MAX_KEY];
    char matrix[1000][100], dec[10000];

    getKeyOrder(key, order, klen);

    for (int i = 0; i < klen; i++) {
        int col = order[i];
        for (int j = 0; j < rows; j++)
            matrix[j][col] = cipher[pos++];
    }

    pos = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < klen; j++)
            if (matrix[i][j] != ' ')
                dec[pos++] = matrix[i][j];

    dec[pos] = '\0';
    strcpy(result, dec);
}

double encryptFile(char *infile, char *outfile, char *key1, char *key2) {
    FILE *in = fopen(infile, "rb"), *out = fopen(outfile, "wb");
    if (!in || !out) return -1;

    char buf[CHUNK], temp[CHUNK * 2], res[CHUNK * 2];
    int n;
    clock_t start = clock();

    while ((n = fread(buf, 1, CHUNK, in)) > 0) {
        buf[n] = '\0';
        columnarEncrypt(buf, key1, temp, n);
        columnarEncrypt(temp, key2, res, strlen(temp));
        fwrite(res, 1, strlen(res), out);
    }

    fclose(in);
    fclose(out);
    return ((double)(clock() - start) / CLOCKS_PER_SEC) * 1000.0;
}

double decryptFile(char *infile, char *outfile, char *key1, char *key2) {
    FILE *in = fopen(infile, "rb"), *out = fopen(outfile, "wb");
    if (!in || !out) return -1;

    char buf[CHUNK * 2], temp[CHUNK * 2], res[CHUNK * 2];
    int n;
    clock_t start = clock();

    while ((n = fread(buf, 1, CHUNK * 2, in)) > 0) {
        buf[n] = '\0';
        columnarDecrypt(buf, key2, temp, n);
        columnarDecrypt(temp, key1, res, strlen(temp));
        fwrite(res, 1, strlen(res), out);
    }

    fclose(in);
    fclose(out);
    return ((double)(clock() - start) / CLOCKS_PER_SEC) * 1000.0;
}

long fsize(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return -1;
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return size;
}

int main() {
    char key1[MAX_KEY], key2[MAX_KEY], encfile[50], decfile[50];
    char files[5][20] = {"test1kb.txt", "test10kb.txt", "test1mb.txt", "test10mb.txt", "test100mb.txt"};
    char sizes[5][10] = {"1KB", "10KB", "1MB", "10MB", "100MB"};

    printf("Double Columnar Cipher Timing Analysis\n");
    printf("Enter Key 1: ");
    scanf("%s", key1);
    printf("Enter Key 2: ");
    scanf("%s", key2);

    for (int i = 0; i < strlen(key1); i++) key1[i] = toupper(key1[i]);
    for (int i = 0; i < strlen(key2); i++) key2[i] = toupper(key2[i]);

    FILE *res = fopen("columnar_timing_results.txt", "w");
    fprintf(res, "File\tBytes\tET(ms)\tDT(ms)\tTotal(ms)\n");

    for (int i = 0; i < 5; i++) {
        FILE *chk = fopen(files[i], "r");
        if (!chk) {
            fprintf(res, "%s\tNot Found\n", sizes[i]);
            continue;
        }
        fclose(chk);

        long size = fsize(files[i]);
        sprintf(encfile, "enc_%s", files[i]);
        sprintf(decfile, "dec_%s", files[i]);

        double et = encryptFile(files[i], encfile, key1, key2);
        double dt = decryptFile(encfile, decfile, key1, key2);

        printf("%s: ET %.3f ms, DT %.3f ms\n", sizes[i], et, dt);
        fprintf(res, "%s\t%ld\t%.3f\t%.3f\t%.3f\n", sizes[i], size, et, dt, et + dt);
    }

    fclose(res);
    printf("\nResults saved to columnar_timing_results.txt\n");
    return 0;
}
