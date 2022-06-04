#include <stdio.h>
#include <string.h>

//
// Created by fitli on 04.06.22.
//
int countKMP(int* kmps, char* str, char ch, int index) {
    if (index == 0) {
        return 0;
    }
    if (ch == str[kmps[index-1]]) {
        return kmps[index-1] + 1;
    }
    return countKMP(kmps, str, ch, kmps[index-1]);
}

int main1()
{
    char result[1000000], rotated[1000000], joined[1000000];
    int kmp[1000000];
    while(scanf(" %s %s", result, rotated) > 0) {
        int len = strlen(result);
        for(int i = 0;i<len;i++) {
            joined[i] = result[i];
            joined[len+i+1] = rotated[i];
            joined[2*len+i+1] = rotated[i];
        }
        joined[len] = '#';
        joined[3*len] = '\0';
        int num_rots = 0;
        for(int i = 0; i < 3*len; i++) {
            kmp[i] = countKMP(kmp, joined, joined[i], i);
            if (kmp[i] == len) {
                num_rots++;
            }
        }
        printf("%d\n", num_rots);
    }
}

char input[10000000];
int kmp[10000000];

int main()
{
    while(scanf(" %s", input) > 0) {
        int len = strlen(input);
        fflush(stdout);
        for(int i = 0;i<len;i++) {
            input[len + i + 1] = input[i];
        }
        for(int i = 0;i<len;i++) {
            input[i] = input[2*len - i];
        }
        input[len] = '#';
        input[2*len + 1] = '\0';
        for(int i = 0; i < 2*len + 1; i++) {
            kmp[i] = countKMP(kmp, input, input[i], i);
        }
        printf("%d\n", kmp[2*len]);
    }
}