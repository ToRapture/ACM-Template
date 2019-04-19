/*2015/3/24
Memory(KB) 668
Time(ms) 47
昨天晚上就写完了90%，不过犯了一个非常愚蠢的错误，导致我卡了一天 = =
本题用的递归 + 位运算，想法也很简单 = =！
*/
#include<cstring>
#include<iostream>
#include<cstdio>
#define BLACK 65535     //十六位都是1对应的十进制数
#define WHITE 0         //十六位都是0对应的十进制数
#define INF 0x7f7f7f7f
using namespace std;

int state;
int minFlips = INF;     //最小的步数，首先赋值为“无限大”

void flip(int i) {      //翻转第i个格的函数,每次翻转后都会改变state的值
    int temp = 0;
    temp |= 1<<i;
    if(i%4 != 0) temp |= 1<<(i-1);
    if((i+1)%4 != 0) temp |= 1<<(i+1);
    if(i+4 < 16) temp |= 1<<(i+4);
    if(i-4 >= 0) temp |= 1<<(i-4);
    state ^= temp;
}
void solve(int n,int nFlips) {      //n代表这次反转的是第n个格，n从0开始，nFlips代表总共翻转的次数,nFlips也从零开始
    if(n == 15) {       //递归出口，当翻转完第15个格子以后结束递归
        flip(n);        //按下第15个格子，然后判断是否“清一色”
        if(state == BLACK || state == WHITE)
            if(nFlips + 1 < minFlips) minFlips = nFlips + 1;
        flip(n);        //又在那个格子按了一下，相当于取消刚才的行为，然后判断如果没有按下第15个格子对应的state
        if(state == BLACK || state == WHITE)
        if(nFlips < minFlips) minFlips = nFlips;
    }
    else {
        flip(n);    //按下第n个格子，次数+1，再去处理第n+1个格子
        solve(n+1,nFlips+1);
        flip(n);    //第n个格子没有按下，处理第n+1个格子
        solve(n+1,nFlips);
    }
}

int main() {
    minFlips = INF;
    state = 0;
    int nChars = 0;
    char ch;
    while(nChars != 16) {
        ch = getchar();
        if(ch == 'w' || ch == 'b') {    //如果状态为111111...1111111那么最后一个1代表第一位
            if(ch == 'b') state |= 1<<nChars;
            nChars++;
        }
    }
    solve(0,0); //从第0位开始翻
    if(minFlips == INF) cout<<"Impossible"<<endl;
    else cout<<minFlips<<endl;
    return 0;
}


