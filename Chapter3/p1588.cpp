#include <stdio.h>
#include <string.h>
char s1[110],s2[110],s3[330];
int min,t;
int main(){
	while(scanf("%s\n",s1)!=EOF){
		min=300;
		scanf("%s\n",s2);
		//printf("s1:%s l%d s2:%s\n",s1,strlen(s1),s2);
		for(int i=0;i<int(strlen(s1));i++)
			if(s1[i]=='1') s1[i]=1;
			else s1[i]=2;
		for(int i=0;i<int(strlen(s2));i++)
			if(s2[i]=='1') s2[i]=1;
			else s2[i]=2;
		int i=0,j=int(strlen(s1))+5,k=0;
		memset(s3,0,sizeof(s3));
		for(k=0;k<int(strlen(s2));k++)
			s3[k+j]=s2[k];
		for(i=0;i<j+int(strlen(s2));i++){
			for(k=0;k<int(strlen(s1));k++){
				if((s3[k+i]+s1[k])>3) break;
			}
			k=k-1;
			if((k+1==int(strlen(s1))) && (s3[k+i]+s1[k]<=3)){
				t=k+i-j+1;
				t=(t>(j+int(strlen(s2))-i))?t:(j+int(strlen(s2))-i);
				t=(t>int(strlen(s2)))?t:int(strlen(s2));
				t=(t>int(strlen(s1)))?t:int(strlen(s1));			
			}
			min=t<min?t:min;
		}
		printf("%d\n", min);
	}
	return 0;
}