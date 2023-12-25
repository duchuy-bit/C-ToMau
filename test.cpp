#include <stdio.h>

int n, a[100];

int main(){
	
	scanf("%d",&n);
	
	for (int i =0; i< n; i++){
		scanf("%d", &a[i]);
	}
	
	
	for (int i =0; i< n; i++){
		printf("%d   ", a[i]);
	}
	return 0;
}
