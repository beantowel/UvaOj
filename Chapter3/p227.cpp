#include <stdio.h>
char a[10][10];
char m[1000];
char temp;
int pi,pj,nPuzzle=0;
void solve();
void printA(int legal);
void swap(int i,int j,int i1,int j1){
	char t=a[i][j];
	a[i][j]=a[i1][j1];
	a[i1][j1]=t;
}
int check(int i1,int j1){
	if(i1<0 or i1>=5 or j1<0 or j1>=5){printA(0); return 0;}
	return 1;
}
int main(){
	while(true){
		for(int i=0;i<5;i++){ //read puzzle
			for(int j=0;j<5;j++){
				scanf("%c",&temp);
				if(temp=='Z') return 0;
				if(temp==' '){pi=i;pj=j;};
				a[i][j]=temp;
			}
			scanf("%c",&temp);
		}
		for(int i=0;;i++){ //read moves
			scanf("%c",&temp);
			m[i]=temp;
			if(temp=='0'){
				scanf("%c",&temp);
				break;
			}
			if(temp=='\n') i--;
		}
		nPuzzle++;
		solve(); //solve puzzle
	}
	return 0;
}
void solve(){
	for(int i=0;;i++){
		switch(m[i]){
			case 'A':
				if (!check(pi-1,pj)) return;
				swap(pi,pj,pi-1,pj);
				pi--;
				break;
			case 'B':
				if (!check(pi+1,pj)) return;
				swap(pi,pj,pi+1,pj);
				pi++;
				break;
			case 'R':
				if (!check(pi,pj+1)) return;
				swap(pi,pj,pi,pj+1);
				pj++;
				break;
			case 'L':
				if (!check(pi,pj-1)) return;
				swap(pi,pj,pi,pj-1);
				pj--;
				break;
			case '0':
				printA(1);
				return;
			default:
				printA(0);
				return;
		}
	}
}
void printA(int legal){
	if(nPuzzle==1)
		printf("Puzzle #%d:\n",nPuzzle);
	else
		printf("\nPuzzle #%d:\n",nPuzzle);
	if(!legal){
		printf("This puzzle has no final configuration.\n");
		return;
	}
	for(int i=0;i<5;i++){
		printf("%c",a[i][0]);
		for(int j=1;j<5;j++){
			printf(" %c",a[i][j]);
		}
		printf("\n");
	}
}