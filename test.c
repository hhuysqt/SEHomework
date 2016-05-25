#include <stdio.h>
#include <math.h>

typedef struct tag_point
{
	float x, y;
	float r;
} Circle;
#define DISTANCE(a, b) sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y))
#define SCALE 0.001

Circle c[1000];

int main()
{
	int i;
	Circle ctemp = {0};

	c[0].x = c[0].y = 0, c[0].r = 1;

	for(i = 1; i < 1000; i++)
	{
		for(ctemp.x = -1; ctemp.x < 1; ctemp.x += SCALE)
		{
			for(ctemp.y = -1; ctemp.y < 1; ctemp.y += SCALE)
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
				rtemp = rtemp > ctemp.y ? ctemp.y : rtemp;
				rtemp = rtemp > ctemp.x ? ctemp.x : rtemp;
				if(ctemp.r < rtemp)
					ctemp.r = rtemp;
			}
		}
		c[i] = ctemp;
		printf("Filled: (%f, %f), %f\n", ctemp.x, ctemp.y, ctemp.r);
	}
}
