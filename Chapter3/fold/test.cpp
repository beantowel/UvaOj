#include <stdio.h>
int main(){
	char temp;
	while(true){
		scanf("%c",&temp);
		printf("%x ", temp);
		if(temp=='Z') return 0;
	}
	return 0;
}