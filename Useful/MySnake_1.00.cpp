#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#define abs(a) ((a) >= 0 ? (a) : -(a))
#define Map_SIZE 20  // >= 10 
#define UP 38
#define DOWN 40
#define LEFT 37
#define RIGHT 39
int score = 0;
struct EDGE {
	int l,u,r,d;
	EDGE() {
		l = 0, u = 0, r = Map_SIZE << 1, d = Map_SIZE;
	}
} edge;

struct Map {

	int dx[4],dy[4];
	Map() {
		dx[0] = -2, dx[1] = 0, dx[2] = 2, dx[3] = 0;
		dy[0] = 0, dy[1] = -1, dy[2] = 0, dy[3] = 1;
	}
	void pos(int x,int y) { //设置光标位置函数
		COORD _pos;
		_pos.X = x;    //横坐标
		_pos.Y = y;
		HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hOutput, _pos);
		return;
	}
	void create() {
		for(int i=0; i<Map_SIZE<<1; i+=2) {
			pos(i,0),printf("■");
			pos(i,Map_SIZE),printf("■");
		}
		for(int i=0; i<=Map_SIZE; ++i) {
			pos(0,i), printf("■");
			pos(Map_SIZE<<1,i),printf("■");
		}
	}

} Map;

struct FOOD {
	bool have;
	int x,y;
	FOOD() {
		have = false;
	}
	void create() {
		if(!have) {
			x = (rand() % (Map_SIZE*2-2)) + 2;
			if(x % 2) {
				--x;
				if(x < 2) x += 2;
			}
			y = (rand() % (Map_SIZE-1)) + 1;
			have = true;
		}
	}
	void print() {
		Map.pos(x,y);
		printf("■");
	}
} food;

struct SNAKE {
	struct body {
		int x,y;
		body *next[2];
		body() {
			next[0] = next[1] = NULL;
		}
	};
	int dir;
	int len;
	int change;
	body *root;
	body *tail;
	SNAKE() {
		dir = RIGHT;
		change = 0;
		len = 0;
		root = new body;
		body *p = root;
		int hPos = Map_SIZE + 2;
		if(hPos % 2) --hPos;
		for(int i=0; i<5; ++i, hPos -= 2) {
			p -> x = hPos, p -> y = Map_SIZE / 2;
			if(i == 4) break;
			p -> next[0] = new body;
			p -> next[0] -> next[1] = p;
			p = p -> next[0];
			tail = p;
		}
	}
	~SNAKE() {
		while(root != NULL) {
			body *tmp = root -> next[0];
			delete root;
			root = tmp;
		}
	}
	void print() {
		body *p = root;
		while(p != NULL) {
			Map.pos(p->x,p->y);
			printf("■");
			p = p -> next[change];
		}
	}
	void Move() {
		body *p = new body;
		p -> x = root -> x + Map.dx[dir % LEFT];
		p -> y = root -> y + Map.dy[dir % LEFT];
		p -> next[change] = root;
		root -> next[change^1] = p;
		root = p;
		while(p -> next[change] -> next[change] != NULL) p = p -> next[change];
		Map.pos(p->next[change]->x,p->next[change]->y);
		printf("  ");
		delete p -> next[change];
		p -> next[change] = NULL;
		tail = p;
	}
	void eat() {
		int _x = root -> x + Map.dx[dir % LEFT];
		int _y = root -> y + Map.dy[dir % LEFT];
		if(_x == food.x && _y == food.y) {
			body *p = new body;
			p -> x = _x, p -> y = _y;
			p -> next[change] = root;
			root -> next[change^1] = p;
			root = p;
			food.have = false;
			++len;
		}
	}
	bool touchSelf() {
		int _x = root -> x;
		int _y = root -> y;
		body *p = root -> next[change];
		while(p != NULL) {
			if(p -> x == _x && p -> y == _y) return true;
			p = p -> next[change];
		}
	}
	void flip() {
		body *tmp = root;
		root = tail;
		tail = tmp;
		if(dir > 38) dir -= 2;
		else dir += 2;
		change ^= 1;
	}
	void changeDir() {
		for(int key = LEFT; key <= DOWN; ++key) {
			if(GetAsyncKeyState(key)) {
				if(abs(key - dir) != 2)
					dir = key;
			}
		}
	}
	void cross() {
		if(root -> x == edge.l)
			root -> x = edge.r - 2;
		if(root -> x == edge.r)
			root -> x = edge.l + 2;
		if(root -> y == edge.u)
			root -> y = edge.d - 1;
		if(root -> y == edge.d)
			root -> y = edge.u + 1;
	}
} snake;
struct GAME {
	int speed;
	int score;
	bool End;
	void init() {
		speed = 200;
		End = false;
		puts("-------------------------------------------------------------------------");
		puts("|   ** Project: Snake.cpp                                               |");
		puts("|   ** Copyright(c) 2015 ToRapture                                      |");
		puts("|   ** Creator: Abang                                                   |");
		puts("|   ** Email: abang1996@163.com                                         |");
		puts("|   ** Date: 06.04.2015                                                 |");
		puts("|   ** Last Modify: 06.04.2015                                          |");
		puts("|   ** Description: Snake Game, compiled by GNU GCC Compiler            |");
		puts("|   ** Version: 1.00 Final Release                                      |");
		puts("-------------------------------------------------------------------------");
		puts("-------------------------------------------------------------------------");
		puts("|   HOW TO PLAY:                                                        |");
		puts("|   Use your arrow keys to Move the Snake.                              |");
		puts("|   Press F1 to SpeedUp  Press F2 to SpeedDown  Press F3 to Flip        |");
		puts("|   To start the game, please press [Y]                                 |");
		puts("-------------------------------------------------------------------------");
		while(_getch() != 'y');
		system("cls");
		Map.create();
		food.create();
		food.print();
		snake.print();
	}
	void changeState() {
		if(GetAsyncKeyState(VK_BACK)) {
			End = true;
		}
		if(GetAsyncKeyState(VK_F1)) {
			if(speed >= 70) speed -= 20;
		}
		if(GetAsyncKeyState(VK_F2)) {
			if(speed <= 300) speed += 20;
		}
		if(GetAsyncKeyState(VK_F3)) {
			snake.flip();
		}
	}
	void printStatic() {
		Map.pos(Map_SIZE*2 + 10, Map_SIZE/2);
		printf("当前速度\t\t");
		Map.pos(Map_SIZE*2 + 10, Map_SIZE/2+4);
		printf("分数\t\t");
		Map.pos(Map_SIZE*2 + 10, Map_SIZE/2);
		printf("当前速度  %d",500-speed);
		Map.pos(Map_SIZE*2 + 10, Map_SIZE/2+4);
		printf("分数 %3d",snake.len * 5);
		Map.pos(Map_SIZE/3,Map_SIZE+3);
		printf("F1 加速    F2 减速   F3 反转    Backspace 退出");
	}
	void circle() {
		while(!End) {
			snake.changeDir();
			snake.eat();
			snake.Move();
			snake.cross();
			snake.print();
			printStatic();
			if(snake.touchSelf()) break;
			food.create();
			food.print();
			changeState();
			Sleep(speed);
		}
	}
	void EndImage() {
		system("cls");
		Map.pos(Map_SIZE, Map_SIZE/2);
		puts("WELCOME BACK!        ");
		Map.pos(Map_SIZE, Map_SIZE/1);
		puts("Created by Abang     ");
		Map.pos(Map_SIZE,Map_SIZE/2+2);
		puts("PRESS ESC TO EXIT    ");
		while(_getch() != VK_ESCAPE);
	}
} game;

int main() {
	game.init();
	game.circle();
	game.EndImage();
	return 0;
}
