#include <stdio.h>
#include <math.h>

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
coordinate magic_point[10] = {{0.5,0.5},{-0.5,0.5},{0.5,-0.5},{0.6,0.6}};

Circle c[1000];

int main()
{
	int i;
	Circle ctemp = {0}, cres;

	for(i = 0; i < 1000;)
	{
		for(ctemp.x = -1 + SCALE; ctemp.x < 1; ctemp.x += SCALE)
		{
			for(ctemp.y = -1 + SCALE; ctemp.y < 1; ctemp.y += SCALE)
			{
				int j;
				float rtemp = 10;
				for(j = 0; j < i; j++)
				{
					float dist = DISTANCE(ctemp, c[j]) - c[j].r;
					if(dist > 0)
						rtemp = rtemp > dist ? dist : rtemp;
					else
					{
						rtemp = 0;
						break;
					}
				}
				for(j = 0; j < 4; j++)
				{
					float dist = DISTANCE(ctemp, magic_point[j]);
					rtemp = rtemp > dist ? dist : rtemp;
				}
				float xmin = ctemp.x < 0 ? ctemp.x + 1 : 1 - ctemp.x;
				float ymin = ctemp.y < 0 ? ctemp.y + 1 : 1 - ctemp.y;
				if (rtemp > xmin)
					rtemp = xmin;
				if (rtemp > ymin)
					rtemp = ymin;
				if (cres.r < rtemp)
				{
					cres = ctemp;
					cres.r = rtemp;
				}
			}
		}
		if (cres.r > 0)
		{
			c[i++] = cres;
			printf("Filled: (%f, %f), %f\n", cres.x, cres.y, cres.r);
			cres.r = 0;
		}
	}
}

