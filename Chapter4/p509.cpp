#include <stdio.h>
int d, s, b, even, diskn = 0;
char disk[6][6410];
void printValue();
int main() {
    while(true) {
        diskn++;
        scanf("%d %d %d\n", &d, &s, &b);
        if(!d) return 0;
        char temp;
        scanf("%c\n", &temp);
        switch(temp) {
        case 'E':
            even = 0;
            break;
        case 'O':
            even = 1;
            break;
        }
        for(int i = 0; i < d; i++) {
            for(int j = 0; j < s * b; j++) {
                scanf("%c", &temp);
                switch(temp) {
                case '0':
                    disk[i][j] = 0;
                    break;
                case '1':
                    disk[i][j] = 1;
                    break;
                case 'x':
                    disk[i][j] = 2;
                }
            }
            scanf("\n");
        }
        int valid = 1;
        for(int j = 0; (j < s  * b) && valid; j++) {
            int cnt = 0, bp = -1;
            int a = disk[0][j];
            if(a == 2) {
                cnt++;
                bp = 0;
            }
            for(int i = 1; i < d; i++) {
                a = a ^ disk[i][j];
                if(disk[i][j] == 2) {
                    cnt++;
                    bp = i;
                    if(cnt > 1) {
                        valid = 0;
                        break;
                    }
                }
            }
            if((cnt == 0) && (a != even)) valid = 0;
            if(cnt == 1) disk[bp][j] = (a & 1) == even ? 0 : 1;
        }
        if(!valid)
            printf("Disk set %d is invalid.\n", diskn);
        else {
            printValue();
        }
    }
    return 0;
}
void printValue() {
    unsigned char out = 0, outI = 3;
    printf("Disk set %d is valid, contents are: ", diskn);
    for(int i = 0; i < b; i++) {
        for(int j = 0; j < d; j++)
            if(j != i % d) {
                for(int k = 0; k < s; k++) {
                    outI = (outI + 1) % 4;
                    out = (out << 1) + disk[j][i * s + k];
                    if(outI == 3) {
                        printf("%X", out);
                        out = 0;
                    }
                }
            }
    }
    if(outI != 3) {
        out = out << (3 - outI);
        printf("%X", out);
    }
    printf("\n");
}