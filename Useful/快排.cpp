#include<stdio.h>

void quickSort(int x[],int left,int right) {	//[left, right]
	if(left < right) {
		int i = left;
		int j = right;
		int key = x[i];

		while(i < j) {
			while(i < j && x[j] >= key) --j;
			if(i < j) x[i++] = x[j];
			while(i < j && x[i] <= key) ++i;
			if(i < j) x[j--] = x[i];
		}
		x[i] = key;
		quickSort(x, 0, i -1 );
		quickSort(x, i + 1, right);
	}
}

int main() {
	int n;
	int a[100];
	while(~scanf("%d",&n)) {
		for(int i = 0; i < n; ++i)
			scanf("%d",&a[i]);
		quickSort(a, 0, n - 1);
		for(int i = 0; i < n; ++i)
			printf("%d ",a[i]);
		puts("");
	}
	return 0;
}
