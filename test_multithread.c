// SEHomework.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <Windows.h>

typedef struct tag_point
{
	float x, y;
	float r;
} Circle;
#define DISTANCE(a, b) sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y))
#define SCALE 0.001

// 挖空几个点
typedef struct tag_coo
{
	float x, y;
} coordinate;
coordinate magic_point[10] = {{0.5,0.5},{-0.5,0.5},{0.5,-0.5}};

HANDLE is_lock;
Circle c[1000];
int filled_num = 0;

int CheckCirDuplicate(Circle cir, int curnum)
{
	int j;

	// check each circle
	for(j = 0; j < filled_num && j != curnum; j++)
	{
		float dist = DISTANCE(cir, c[j]) - c[j].r;
		if(dist < 0)
		{
			return -1;
		}
	}
	// check each magic point
	for(j = 0; j < 3; j++)
	{
		float dist = DISTANCE(cir, magic_point[j]);
		if(dist < 0)
		{
			return -1;
		}
	}
	// check boudary
	if (
		cir.x - cir.r < -1 ||
		cir.x + cir.r > 1 ||
		cir.y - cir.r < -1 || 
		cir.y + cir.r > 1
		)
		return -1;

	return 0;
}

DWORD WINAPI FillCircleThread(LPVOID p)
{
	coordinate* coo = (coordinate*)p;
	Circle* ctemp;
	int curnum;

	WaitForSingleObject(is_lock, INFINITE);
	curnum = filled_num++;
	ReleaseMutex(is_lock);

	ctemp = &c[curnum];

	for (
	ctemp->x = coo->x, ctemp->y = coo->y, ctemp->r = 0;
	CheckCirDuplicate(*ctemp, curnum) == 0;
	ctemp->r += SCALE
		);

	if (ctemp->r > 0)
	{
		printf("Filled: (%f, %f), %f\n", ctemp->x, ctemp->y, ctemp->r);
	}
	else
		printf("Rejected...\n");

	return 0;
}

int _tmain()
{
	is_lock = CreateMutex(NULL, FALSE, _T("Circles"));

	while (filled_num < 1000)
	{
		HANDLE threads[10];
		Circle cirs[10];
		for (int i = 0; i < 5; i++)
		{
			int randx = rand() % 2000,
				randy = rand() % 2000;
			cirs[i].x = randx / 2000.0 - 1;
			cirs[i].y = randy / 2000.0 - 1;

			threads[i] = CreateThread(NULL, 0, FillCircleThread, (LPVOID)&cirs[i], 0, NULL);
		}
		WaitForMultipleObjects(1, threads, TRUE, INFINITE);
	}
}


