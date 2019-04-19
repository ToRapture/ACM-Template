const int MAX = 1200;
int c[MAX][MAX];
int n;
int LowBit(int t) {
	return t & (-t);
}
int Sum(int endx,int endy) {
	int sum = 0;
	int temp = endy;
	while(endx > 0) {
		endy = temp;
		while (endy > 0) {
			sum += c[endx][endy];
			endy -= LowBit(endy);
		}

		endx -= LowBit(endx);
	}
	return sum;
}
void add(int addx,int addy,int num) {
	int temp = addy;
	while (addx <= n) {
		addy = temp;
		while(addy <= n) {
			c[addx][addy] += num;
			addy += LowBit(addy);
		}
		addx += LowBit(addx);
	}
}
int GetSum(int l,int b,int r,int t) {
	return Sum(r,t) - Sum(r,b-1) - Sum(l-1,t) + Sum(l-1,b-1);
}

int main() {
	
	return 0;
}