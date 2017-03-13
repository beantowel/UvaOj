#include <stdio.h>
#include <string.h>
char a[12][12];
char temp;
int n[12][12]; //0 unhandled, -1 black, 1 startPoint
int r,c,nPuzzle=0;
void Lable();
void Solve();
void Printl(int i,int j,int k,int b);
void Testout(){
	printf("a\n");
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++)
			printf("%c", a[i][j]);
		printf("\n");
	}
	printf("n\n");
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++)
			printf("%3d", n[i][j]);
		printf("\n");
	}
}
int main(){
	while(true){
		scanf("%d",&r);
		if(r==0) return 0;
		scanf("%d\n",&c);
		memset(n,0,sizeof(n));
		for(int i=0;i<r;i++){
			for(int j=0;j<c;j++){
				scanf("%c",&a[i][j]);
				if(a[i][j]=='*') n[i][j]=-1;
			}
			scanf("\n");			
		}
		Lable();
		Solve();
		// Testout();
	}
	return 0;
}
void Lable(){
	int num=1;
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			if((n[i][j]!=-1) && ((j==0) || (i==0) ||\
				(n[i-1][j]==-1) || (n[i][j-1]==-1))){
					n[i][j]=num++;
			}
		}
	}
}
void Solve(){
	nPuzzle++;
	if(nPuzzle>1) printf("\n");
	printf("puzzle #%d:\n", nPuzzle);
	printf("Across\n");
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			if((n[i][j]<1) || ((j>0) && (n[i][j-1]>=0))) continue; //start condition
			int k=j;
			while((k+1<c) && (n[i][k+1]>=0))
				k++;
			Printl(i,j,k,0);
		}
	}
	printf("Down\n");
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			if((n[i][j]<1) || ((i>0) && (n[i-1][j]>=0))) continue;
			int k=i;
			while((k+1<r) && (n[k+1][j]>=0))
				k++;
			Printl(i,j,k,1);
		}
	}
}
void Printl(int i,int j,int k,int b){
	printf("%3d.",n[i][j]);
	if(b==0){
		for(int t=j;t<=k;t++)
			printf("%c", a[i][t]);
	} //across
	else{
		for(int t=i;t<=k;t++)
			printf("%c", a[t][j]);
	}
	printf("\n");
}