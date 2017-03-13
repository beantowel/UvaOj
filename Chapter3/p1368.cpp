#include <stdio.h>
#include <string.h>
int nSet,n,m;
int base[4][1000];
char temp;
int Maxi(int j,int *dis){
	int max=base[0][j],maxi=0,sum=base[0][j];
	for(int i=1;i<4;i++){
		maxi=(base[i][j]>max)?i:maxi;
		max=(base[i][j]>max)?base[i][j]:max;
		sum+=base[i][j];
	}
	*dis=sum-base[maxi][j];
	// printf("\nmaxi%d\n",maxi);
	// for(int i=0;i<4;i++){
	// 	printf("%d ",base[i][j]);
	// }
	// printf("\n");
	return maxi;
}
int main(){
	scanf("%d\n",&nSet);
	for(int ni=0;ni<nSet;ni++){
		memset(base,0,sizeof(base));
		scanf("%d %d\n",&m,&n);
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				scanf("%c",&temp);
				int t=0;
				switch(temp){ //lexicographically smallest
					case 'A':t=0;
					break;
					case 'C':t=1;
					break;
					case 'G':t=2;
					break;
					case 'T':t=3;
					break;
				}
				base[t][j]++;
			}
			scanf("\n");
		}
		int hamming=0,dis;
		for(int j=0;j<n;j++){
			switch(Maxi(j,&dis)){
				case 0:temp='A';
				break;
				case 1:temp='C';
				break;
				case 2:temp='G';
				break;
				case 3:temp='T';
				break;
			}
			hamming+=dis;
			printf("%c",temp);
		}
		printf("\n%d\n",hamming);
	}
	return 0;
}