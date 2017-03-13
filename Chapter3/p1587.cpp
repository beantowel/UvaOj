#include <stdio.h>
#include <string.h>
int abc[3];
int l[2][6],count[3],sum; //ab,bc,ac
int Count(int i);
void Sort(int *a,int *b){
	if((*a)>(*b)){
		int t=*a;
		*a=*b;
		*b=t;
	}
}
int main(){
	while(scanf("%d %d\n",&l[0][0],&l[1][0])!=EOF){
		int b=0;
		sum=l[0][0]+l[1][0];
		for(int i=1;i<6;i++){
			scanf("%d %d\n",&l[0][i],&l[1][i]);
			sum+=l[0][i];
			sum+=l[1][i];
		}
		sum=sum/4;
		abc[0]=l[0][0];
		abc[1]=l[1][0];
		abc[2]=sum-abc[0]-abc[1];Sort(&abc[0],&abc[1]);
		Sort(&abc[0],&abc[2]);
		Sort(&abc[1],&abc[2]);

		// for(int i=0;i<6;i++)
		// 	printf("l[%d]=%d,%d\n",i,l[0][i],l[1][i]);
		// printf("sum=%d\n",sum);
		// for(int i=0;i<3;i++)
		// 	printf("abc[%d]=%d ",i,abc[i]);
		// printf("\n");
		
		memset(count,0,sizeof(count));
		for(int i=0;i<6;i++)
			if(Count(i)){
				printf("IMPOSSIBLE\n");
				b=1;
				break;
			}
		if(b) continue;
		for(int i=0;i<3;i++)
			if(count[i]!=2){
				printf("IMPOSSIBLE\n");
				b=1;
				break;
			}
		if(b) continue;
		printf("POSSIBLE\n");
	}
	return 0;
}
int Count(int i){
	int x=l[0][i],y=l[1][i];
	Sort(&x,&y);
	for(int j=0;j<3;j++){ //count:=ab bc ac
		int x1=abc[j];
		int y1=abc[(j+1)%3];
		Sort(&x1,&y1);
		if((x==x1) && (y==y1) && (count[j]<2)){
			count[j]++;
			return 0;
		}
	}
	return 1;
}