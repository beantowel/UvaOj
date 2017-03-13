#include <stdio.h>
#include <math.h>
#include <string.h>
long long a2;
long a1,b;
double a,y;
int int_x[10]={0b1,0b11,0b111,0b1111,0b11111,0b111111,\
0b1111111,0b11111111,0b111111111,0b1111111111};
double x[10];
int int_y,logy;
char s[30];
int main(){
	for(int i=0;i<10;i++){
		x[i]=((double)int_x[i])/(1<<(i+1));
	}
	while(true){
		scanf("%s",&s);
		if(s[0]=='0' && s[1]=='e' && s[2]=='0') return 0;
		scanf("\n");
		sscanf(s,"%ld.%llde%ld",&a1,&a2,&b);
		a=a1+a2*(1e-15);	
		y=(log(a)+b*log(10))/log(2);
		int_y=floor(y+1);	//0.5<=m<1
		y=floor(y+1);	
		logy=log(y+1)/log(2)+0.5; //int()???
		double t=b*log(10)/log(2)-int_y;
		t=pow(2,t);
		t=t*a;
		for(int i=0;i<10;i++){
			if((t-x[i]-0.0001)<0){
				printf("%d %d",i,logy);
				break;
			}
		}
		printf("\n");
	}
	return 0;
}