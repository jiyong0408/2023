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
		memcpy(&maze[i][0], "��", sizeof(char*));
		memcpy(&maze[i][HEIGHT - 1], "��", sizeof(char*));
	}
	for (int i = 0; i < HEIGHT; i++)
	{
		memcpy(&maze[0][i], "��", sizeof(char*));
		memcpy(&maze[WIDTH - 1][i], "��", sizeof(char*));
	}
	//�� ���ε�..
	memcpy(&maze[enter][0], "��", sizeof(char*));
	//���� ������ �ٵ��Ұ�, check_maze_row �� 1�̸� ���� ������
	//i�� ���� ��Ÿ����.

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
					memcpy(&maze[x][y], "��", sizeof(char*));
				}
				else
				{
					memcpy(&maze[x][y], "��", sizeof(char*));
				}
				x++;
			}
			memcpy(&maze[previous_path][y], "��", sizeof(char*));
			previous_path = find_previous_path(previous_path, y++, maze);
			record_path_stack[m++] = previous_path;
		}
		else
		{
			memcpy(&maze[previous_path][y], "��", sizeof(char*));
			record_path_stack[m] = previous_path;
			print_maze(maze);
			break;
		}

	}

	int cross = 0, upper = 0, left = 0, current = 0;

	y = 2;
	//�ܼ��� ������ ó�� �Ų����� �������
	while (y < (HEIGHT - 1))
	{
		int x = 2;

		while (x < (WIDTH - 1))
		{
			cross = 0, upper = 0, left = 0, current = 0;

			if (!memcmp(&maze[x - 1][y], "��", sizeof(char*)))
			{
				left = 1;
			}
			if (!memcmp(&maze[x - 1][y - 1], "��", sizeof(char*)))
			{
				cross = 1;
			}
			if (!memcmp(&maze[x][y - 1], "��", sizeof(char*)))
			{
				upper = 1;
			}

			if (record_path_stack[y] == x) // ������� ����Ǵ� ��
			{	
				current = 1;
				while (1)
				{
					//���ϳ� �ִ� ��찡 ����
					if (cross && current && upper && left)
					{
						if (record_path_stack[y - 1] != (x - 1))
						{
							memcpy(&maze[x - 1][y], "��", sizeof(char*));
							left = 0;
						}
						else
						{
							memcpy(&maze[x][y - 1], "��", sizeof(char*));
							upper = 0;
						}
					}
					else break;
				}
				x++;
			}
			//���� ��� ����Ǵ� ���� �ƴ� ��
			else
			{
				if (!memcmp(&maze[x][y], "��", sizeof(char*)))
				{
					current = 1;
				}

				while (1)
				{
					if (cross && current && !left && !upper)
					{
						memcpy(&maze[x - 1][y], "��", sizeof(char*));
						left = 1;
					}
					else if (!cross && !current && left && upper)
					{
						memcpy(&maze[x][y], "��", sizeof(char*));
						current = 1;
					}
					else if (cross && upper && left && current)
					{
						memcpy(&maze[x][y], "��", sizeof(char*));
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

//�������� ��� ����� ���� ������ 1�� ��ȯ �ƴϸ� 0�� ��ȯ
// ���� ��� ����Ȱ� ������ ��� �׸��� ������ �������� (--- ������) �̾��� ���� �������� ����2���̻� �Ȱ��̰�ġ�� �̹����� ���� �ϳ��� ������ �ٲ۴�..


int find_previous_path(int p_path, int row, const char* maze[][WIDTH])
{
	int stack[WIDTH - 2] = { 0, };
	int next_path = 0;
	int i = p_path;
	int j = p_path + 1;
	int k = 0;

	while (1)
	{
		if (!memcmp(&maze[i][row], "��", sizeof(char*))) break;
		else
		{
			stack[k++] = i;
			i--;
		}
	}

	while (1)
	{
		if (!memcmp(&maze[j][row], "��", sizeof(char*))) break;
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