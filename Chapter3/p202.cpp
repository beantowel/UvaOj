#include <stdio.h>
int A,B,divisor,divided,remain;
const int maxn=5000;
int intAns,ans[maxn],remainA[maxn],nP=0;
int check(int p);
int main(){
	while(scanf("%d %d",&A,&B)!=EOF){
		divided=A;
		divisor=B;
		intAns= divided / divisor;
		remain= divided % divisor;
		for(int i=0;i<maxn;i++){
			divided = remain * 10;
			ans[i] = divided / divisor;
			remain = divided % divisor;
			remainA[i] = divided % divisor;
			//printf("divided=%d ans=%d remain=%d\n", divided,ans[i],remainA[i]);
			if(check(i)) break;
		}
	}
	return 0;
}
int check(int p){
	for(int i=0;i<p;i++){
		if((ans[i]==ans[p]) && (remainA[i]==remainA[p])){
			// if(nP!=0) printf("\n");
			// nP++;
			printf("%d/%d = %d.",A,B,intAns);
			for(int j=0;j<i;j++) printf("%d",ans[j]);
			int j=i;
			printf("(");
			while((j<50) && (j<p)){
				printf("%d",ans[j]);
				j++;
			}
			if(j!=p) printf("...");
			printf(")\n");
			printf("   %d = number of digits in repeating cycle\n\n",(p-i));
			return 1;
		}
	}
	return 0;
}