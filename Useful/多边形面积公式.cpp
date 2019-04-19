#include<stdio.h>
#define M 1000
struct node {
	int x,y;
} p[M];
int main() {
	int n;
	while(~scanf("%d",&n) && n) {
		for(int i=0; i<n; ++i) {
			scanf("%d%d",&p[i].x,&p[i].y);
		}
		int sum = 0;
		for(int i=0; i<n; ++i) {
			sum += p[i].x*p[(i+1) % n].y - p[(i+1) % n].x*p[i].y;
		}
		printf("%.1f\n",sum / 2.00);
	}

}