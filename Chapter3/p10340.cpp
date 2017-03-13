#include <stdio.h>
#include <string.h>
const int maxn=100000;
char s[maxn],t[maxn];
int main(){
	while(scanf("%s %s\n",s,t)!=EOF){
		//printf("s:%s t:%s\n",s,t);
		int i=0,j=0;
		while((j<strlen(t)) && (i<strlen(s))){
			//printf("s[%d]:%c t[%d]:%c\n",i,s[i],j,t[j]);
			if(t[j]==s[i]) i++;
			j++;
		}
		if(i==strlen(s)){
			printf("Yes\n");
			continue;
		}else{
			printf("No\n");
			continue;
		}
	}
	return 0;
}