#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#define N 8
using namespace std;

bool board[N + 1][N + 1] = { false };
void printBoard() {
	static int cnt = 1;
	FILE *fp = fopen("eightQueen","a");
	fprintf(fp,"Case No. %d\n",cnt++);
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++)
			board[i][j] ? fprintf(fp,"%c ",'@') : fprintf(fp,". ");
		fprintf(fp,"\n");
	}
	fclose(fp);
}

bool isLegal(int row, int column) {
	for(int i=1; i<=row-1; i++) {
		for(int j=1; j<=N; j++) {
			if(board[i][j]) {
				if(j == column || abs(row-i) == abs(column-j)) return false;
			}
		}
	}
	return true;
}

void solveQueen(int i) {
	if(i > N) printBoard();
	for(int j=1; j<=N; j++) {
		board[i][j] = true;
		if(isLegal(i,j)) solveQueen(i+1);
		board[i][j] = false;
	}

}

int main() {
	solveQueen(1);
	return 0;
}
