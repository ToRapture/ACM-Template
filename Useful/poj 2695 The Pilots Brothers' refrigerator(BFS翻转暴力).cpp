#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>
#define OPEN 0
using namespace std;

struct nod {
    int step;
    int father,iFlip;
} node[67000];
bool vis[65535] = { false };

int state = 0;
int q[67000];
int head = 0;
int tail = 0;
int flip(int i,int pre) {
    int temp = 0 | 1<<i;
    int row = i % 4;
    int column = i / 4;
    for(int j=1; j<=row; j++)
        temp |= 1<<(i-j);
    for(int j=1; j<=3-row; j++)
        temp |= 1<<(i+j);
    for(int j=1; j<=column; j++)
        temp |= 1<<(i-4*j);
    for(int j=1; j<=3-column; j++)
        temp |= 1<<(i+4*j);
    return pre ^ temp;
}

void BFS() {
    vis[state] = true;
    node[state].step = 0;
    q[tail++] = state;
    while(tail != head) {
        int pre = q[head++];
        if(pre == OPEN) {
            cout<<node[pre].step<<endl;
            int tempStore[16];
            for(int i=0; i<node[OPEN].step; i++) {
                tempStore[i] = node[pre].iFlip;
                pre = node[pre].father;
            }
            for(int i=node[OPEN].step-1; i>=0; i--) {
                cout<<tempStore[i]/4+1<<' '<<tempStore[i]%4+1<<endl;
            }
            return;
        }
        for(int i=0; i<16; i++) {
            int temp = flip(i,pre);
            if(!vis[temp]) {
                node[temp].father = pre;
                node[temp].iFlip = i;
                node[temp].step = node[pre].step + 1;
                vis[temp] = true;
                q[tail++] = temp;
            }
        }
    }
}

int main() {
    int nChars = 0;
    char ch;
    while(nChars != 16) {
        ch = getchar();
        if(ch == '-' || ch == '+') {
            if(ch == '+') state |= 1<<nChars;
            nChars++;
        }
    }
    BFS();
    return 0;
}
