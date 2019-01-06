#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6
#define EXIT_ROW 5
#define EXIT_COL 5
#define START_ROW 1		
#define START_COL 2   
#define S 255
#define E -255
#define true 1
#define false 0 

int top;
int mark[MAX_STACK_SIZE][MAX_STACK_SIZE]; //거쳤는지 저장//
int maze[MAX_STACK_SIZE][MAX_STACK_SIZE];


typedef struct {
	short int vert;
	short int horiz;
} offsets;
offsets move[8] = {//방향//
	{-1,0},//N
	{-1,1},//NE
	{0,1},//E
	{1,1},//SE
	{1,0},//S
	{1,-1},//SW
	{0,-1},//W
	{-1,-1}//NW
};


typedef struct {//경로저장//
	short int row;
	short int col;
	short int dir;
} element;

element stack[MAX_STACK_SIZE];//이동경로 저장//


element pop(int* top) {
	element result;
	if (*top < 0) {
		printf("Stack is Empty. \n");//비었을때//
	}
	else {
		result = stack[*top];//top을result에 저장//
		(*top)--;
	}
	return result;
}

void push(int* top, element position) {//스택에 저장//
	(*top)++;//하나 올리고 저장//
	stack[*top].row = position.row;
	stack[*top].col = position.col;
	stack[*top].dir = position.dir;
}


//경로출력 여기서//
void path() {
	int i, j, row, col, next_row, next_col, dir, found = false;
	element position;//현재위치//
	mark[1][1] = 1; 
	top = 0;
	stack[0].row = 1; 
	stack[0].col = 1; 
	stack[0].dir = 1;//초기화//

	while (top > -1 && !found) {//찾기시작//
		position = pop(&top);//top에서 현재위치를 받아옴//
		row = position.row; 
		col = position.col;
		dir = position.dir;

		while (dir < 8 && !found) {//못찾았으면시작//
			//현재위치+얼마나움직였나=다음위치//
			next_row = row + move[dir].vert;
			next_col = col + move[dir].horiz;

			if (next_row == EXIT_ROW && next_col == EXIT_COL) {//다음위치가 출구일때//
				found = true;//찾았다//
			}
			//벽이아니고 온적없다면//
			else if (!maze[next_row][next_col] && !mark[next_row][next_col]) {
				mark[next_row][next_col] = true;//여기가 나가는곳이라고 표시//
				position.row = row; 
				position.col = col;
				position.dir = ++dir;//방향을 시계방향으로 바꿈//
				push(&top, position);
				row = next_row; 
				col = next_col;
				dir = 0;
				
			}
			else ++dir;//방향을 시계방향으로 바꿈//
		}

	}//길찾으면 빠져나옴//
	if (found) {//출력//
		printf("The path is:\n");
		printf("row col\n");
		for (i = 0; i < top; i++) {
			printf("%2d%5d", stack[i].row, stack[i].col);
		}
		
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	}
	else printf("The maze dose not have a path\n");
}




int main() {
	int i, j;

	srand((unsigned)time(NULL));//랜덤으로 미로 생성//
	for (i = 0; i< MAZE_SIZE; i++)
		for (j = 0; j<MAZE_SIZE; j++) {
			if (i == 1 && j == 1)
				maze[i][j] = 0;
			else if (i == 0 || j == 0 || i == MAZE_SIZE - 1 || j == MAZE_SIZE - 1)
				maze[i][j] = 1;
			else
				maze[i][j] = rand() % 2;
		}
	//생성된 배열을 출력
	printf("*********** create maze ***********\n");
	printf("    ");
	for (j = 0; j<MAZE_SIZE; j++)
		printf("%2d ", j);                        //몇번째 COL인가
	printf("\n\n");
	for (i = 0; i< MAZE_SIZE; i++) {
		printf("%2d  ", i);                        //몇번째 ROW인가
		for (j = 0; j<MAZE_SIZE; j++)
			printf(" %d ", maze[i][j]);
		printf("\n");
	}
	printf("\n");

	for (i = 0; i<MAZE_SIZE; i++)
		for (j = 0; j <= MAZE_SIZE; j++)
			mark[i][j] = 0;
	printf("******** maze road ********\n");
	path();
	system("pause");
	return 0;
}