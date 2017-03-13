#include <stdio.h>
const long inf = 21474;
long volum;
int m, n, nRegion = 0;
int s[910];
double level;
// void PrintS() {
//     printf("S: ");
//     for(int i = 0; i < n * m + 1; i++) {
//         printf("%d ", s[i]);
//     }
//     printf("\n");
// }
void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}
void quicksort(int f, int r, int *a) {
    if(f >= r) return;
    int key = a[(f + r) / 2], i = f, j = r;
    swap(a[f], a[(f + r) / 2]);
    while(i < j) {
        while((i <= r) && (a[i] <= key))
            i++;
        while((j >= f) && (a[j] > key))
            j--;
        if(i < j) swap(a[i], a[j]);
    }
    swap(a[f], a[j]);
    quicksort(f, j - 1 , a);
    quicksort(j + 1 , r, a);
}
int main() {
    scanf("%d %d", &m, &n);
    while((m > 0) && (n > 0)) {
        nRegion++;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                scanf("%d", &s[i * n + j]);
        s[m * n] = inf;
        scanf("\n%ld\n", &volum);
        quicksort(0, n * m - 1, s);
        long sum = 0, i = 0;
        for(i = 0; i < n * m; i++) {
            // printf("i:%d\n", i);
            sum += s[i];
            if((s[i + 1] * (i + 1) - sum) * 100 > volum) {
                // printf("break i%d\n", i);
                break;
            }
        }
        // printf("final i%d\n", i);
        // printf("volum:%d\n", volum);
        // PrintS();
        printf("Region %d\n", nRegion);
        level = (sum + volum / 100.0) / (i + 1);
        printf("Water level is %.2f meters.\n", level);
        printf("%.2f percent of the region is under water.\n\n", \
               100 * (i + 1) / (float (n * m)));

        scanf("%d %d", &m, &n);
    }
    return 0;
}