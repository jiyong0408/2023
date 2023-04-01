#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

#define WIDTH 25
#define HEIGHT 25

void print_maze(const char* maze[][WIDTH])
{
	printf("\n");
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			printf("%s", &maze[j][i]);
		}
		printf("\n");
	}
}

//random_enter
int enter = rand() % (WIDTH - 2) + 1;

int previous_path = enter;

//return next path
int find_previous_path(int p_path, int row, const char* maze[][WIDTH]);

void initialze_maze(const char* maze[][WIDTH])
{
	int y = 1;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			memcpy(&maze[j][i], "  ", sizeof(char*));
		}
	}
	for (int i = 0; i < WIDTH; i++)
	{
		memcpy(&maze[i][0], "■", sizeof(char*));
		memcpy(&maze[i][HEIGHT - 1], "■", sizeof(char*));
	}
	for (int i = 0; i < HEIGHT; i++)
	{
		memcpy(&maze[0][i], "■", sizeof(char*));
		memcpy(&maze[WIDTH - 1][i], "■", sizeof(char*));
	}
	//열 행인듯..
	memcpy(&maze[enter][0], "↓", sizeof(char*));
	//행을 끝까지 다돌았고, check_maze_row 가 1이면 다음 행으로
	//i는 행을 나타낸다.

	print_maze(maze);
	int previous_path = enter;
	int record_path_stack[HEIGHT] = { 0, };
	record_path_stack[0] = enter;
	int m = 1;
	while (1)
	{
		if (y < HEIGHT - 1)
		{
			int x = 1;

			while (x < (WIDTH - 1))
			{
				int z = rand() % 2 + 1;
				if (z / 2 == 0)
				{
					memcpy(&maze[x][y], "□", sizeof(char*));
				}
				else
				{
					memcpy(&maze[x][y], "■", sizeof(char*));
				}
				x++;
			}
			memcpy(&maze[previous_path][y], "□", sizeof(char*));
			previous_path = find_previous_path(previous_path, y++, maze);
			record_path_stack[m++] = previous_path;
		}
		else
		{
			memcpy(&maze[previous_path][y], "↓", sizeof(char*));
			record_path_stack[m] = previous_path;
			print_maze(maze);
			break;
		}

	}

	int cross = 0, upper = 0, left = 0, current = 0;

	y = 2;
	//단순히 점들을 처리 매끄럽게 만들어줌
	while (y < (HEIGHT - 1))
	{
		int x = 2;

		while (x < (WIDTH - 1))
		{
			cross = 0, upper = 0, left = 0, current = 0;

			if (!memcmp(&maze[x - 1][y], "□", sizeof(char*)))
			{
				left = 1;
			}
			if (!memcmp(&maze[x - 1][y - 1], "□", sizeof(char*)))
			{
				cross = 1;
			}
			if (!memcmp(&maze[x][y - 1], "□", sizeof(char*)))
			{
				upper = 1;
			}

			if (record_path_stack[y] == x) // 다음길과 연결되는 점
			{	
				current = 1;
				while (1)
				{
					//점하나 있는 경우가 없음
					if (cross && current && upper && left)
					{
						if (record_path_stack[y - 1] != (x - 1))
						{
							memcpy(&maze[x - 1][y], "■", sizeof(char*));
							left = 0;
						}
						else
						{
							memcpy(&maze[x][y - 1], "■", sizeof(char*));
							upper = 0;
						}
					}
					else break;
				}
				x++;
			}
			//다음 길과 연결되는 점이 아닐 때
			else
			{
				if (!memcmp(&maze[x][y], "□", sizeof(char*)))
				{
					current = 1;
				}

				while (1)
				{
					if (cross && current && !left && !upper)
					{
						memcpy(&maze[x - 1][y], "□", sizeof(char*));
						left = 1;
					}
					else if (!cross && !current && left && upper)
					{
						memcpy(&maze[x][y], "□", sizeof(char*));
						current = 1;
					}
					else if (cross && upper && left && current)
					{
						memcpy(&maze[x][y], "■", sizeof(char*));
						current = 0;
					}
					else break;
				}
				x++;
			}
		}
		y++;
	}
}

//이전행의 길과 연결된 길이 있으면 1을 반환 아니면 0을 반환
// 이전 길과 연결된게 있으면 통과 그리고 그행의 연속으로 (--- 행으로) 이어진 길들과 이전행의 길들과2개이상 똑같이겹치면 이번행의 둘중 하나를 벽으로 바꾼다..


int find_previous_path(int p_path, int row, const char* maze[][WIDTH])
{
	int stack[WIDTH - 2] = { 0, };
	int next_path = 0;
	int i = p_path;
	int j = p_path + 1;
	int k = 0;

	while (1)
	{
		if (!memcmp(&maze[i][row], "■", sizeof(char*))) break;
		else
		{
			stack[k++] = i;
			i--;
		}
	}

	while (1)
	{
		if (!memcmp(&maze[j][row], "■", sizeof(char*))) break;
		else
		{
			stack[k++] = j;
			j++;
		}
	}

	return stack[rand() % k];
}

int main()
{
	srand(time(NULL));
	const char* maze[WIDTH][HEIGHT] = { 0 , };
	initialze_maze(maze);
	print_maze(maze);
}