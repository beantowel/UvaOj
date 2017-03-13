#include<cstdio>  
#include<cstring>  
#include<cmath>  
using namespace std;  
  
double f(int n){  
    double ret=0;  
    n++;  
    double coul=1;  
    while(n--){  
        coul/=2;  
        ret+=coul;  
    }  
    return ret;  
}  
  
int e[31];  
double arr[31];  
  
int main(){  
    e[0]=0;  
    arr[0]=2;  
    for(int i=1;i<30;i++){  
        e[i]=e[i-1]*2;  
        arr[i]=arr[i-1]*arr[i-1]*2;  
        while(arr[i]!=0 && (arr[i]<1.0 || arr[i]>10.0)){  
            if(arr[i]<1.0){  
                arr[i]*=10;  
                e[i]--;  
            }  
            if(arr[i]>10){  
                arr[i]=arr[i]/10;  
                e[i]++;  
            }  
        }  
    }  
    double M;  
    int E;  
    char get[40];  
    while(~scanf("%s",get)){  
        char *p=strchr(get,'e');  
        *p=' ';  
        sscanf(get,"%lf %d",&M,&E);  
        if(M==0&&E==0) break;  
        int m=0,n=1;  
        double miss=10;  
        double befo;  
        int bee;  
        for(int i=0;i<10;i++){  
            for(int j=1;j<31;j++){  
                befo=f(i)*arr[j-1];  
                bee=e[j-1];  
                while(befo!=0 && (befo<1.0 || befo>10.0)){  
                    if(befo<1.0){  
                        befo*=10;  
                        bee--;  
                    }  
                    else{  
                        befo=befo/10;  
                        bee++;  
                    }  
                }  
                if(fabs(befo-M)<miss && bee==E){  
                    miss=fabs(befo-M);  
                    m=i,n=j;  
                }  
            }  
        }  
        printf("%d %d\n",m,n);  
    }  
    return 0;  
}  