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
int mark[MAX_STACK_SIZE][MAX_STACK_SIZE]; //���ƴ��� ����//
int maze[MAX_STACK_SIZE][MAX_STACK_SIZE];


typedef struct {
	short int vert;
	short int horiz;
} offsets;
offsets move[8] = {//����//
	{-1,0},//N
	{-1,1},//NE
	{0,1},//E
	{1,1},//SE
	{1,0},//S
	{1,-1},//SW
	{0,-1},//W
	{-1,-1}//NW
};


typedef struct {//�������//
	short int row;
	short int col;
	short int dir;
} element;

element stack[MAX_STACK_SIZE];//�̵���� ����//


element pop(int* top) {
	element result;
	if (*top < 0) {
		printf("Stack is Empty. \n");//�������//
	}
	else {
		result = stack[*top];//top��result�� ����//
		(*top)--;
	}
	return result;
}

void push(int* top, element position) {//���ÿ� ����//
	(*top)++;//�ϳ� �ø��� ����//
	stack[*top].row = position.row;
	stack[*top].col = position.col;
	stack[*top].dir = position.dir;
}


//������ ���⼭//
void path() {
	int i, j, row, col, next_row, next_col, dir, found = false;
	element position;//������ġ//
	mark[1][1] = 1; 
	top = 0;
	stack[0].row = 1; 
	stack[0].col = 1; 
	stack[0].dir = 1;//�ʱ�ȭ//

	while (top > -1 && !found) {//ã�����//
		position = pop(&top);//top���� ������ġ�� �޾ƿ�//
		row = position.row; 
		col = position.col;
		dir = position.dir;

		while (dir < 8 && !found) {//��ã���������//
			//������ġ+�󸶳���������=������ġ//
			next_row = row + move[dir].vert;
			next_col = col + move[dir].horiz;

			if (next_row == EXIT_ROW && next_col == EXIT_COL) {//������ġ�� �ⱸ�϶�//
				found = true;//ã�Ҵ�//
			}
			//���̾ƴϰ� �������ٸ�//
			else if (!maze[next_row][next_col] && !mark[next_row][next_col]) {
				mark[next_row][next_col] = true;//���Ⱑ �����°��̶�� ǥ��//
				position.row = row; 
				position.col = col;
				position.dir = ++dir;//������ �ð�������� �ٲ�//
				push(&top, position);
				row = next_row; 
				col = next_col;
				dir = 0;
				
			}
			else ++dir;//������ �ð�������� �ٲ�//
		}

	}//��ã���� ��������//
	if (found) {//���//
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

	srand((unsigned)time(NULL));//�������� �̷� ����//
	for (i = 0; i< MAZE_SIZE; i++)
		for (j = 0; j<MAZE_SIZE; j++) {
			if (i == 1 && j == 1)
				maze[i][j] = 0;
			else if (i == 0 || j == 0 || i == MAZE_SIZE - 1 || j == MAZE_SIZE - 1)
				maze[i][j] = 1;
			else
				maze[i][j] = rand() % 2;
		}
	//������ �迭�� ���
	printf("*********** create maze ***********\n");
	printf("    ");
	for (j = 0; j<MAZE_SIZE; j++)
		printf("%2d ", j);                        //���° COL�ΰ�
	printf("\n\n");
	for (i = 0; i< MAZE_SIZE; i++) {
		printf("%2d  ", i);                        //���° ROW�ΰ�
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