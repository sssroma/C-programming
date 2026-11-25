#include <stdio.h>

int main()
{
	float x = 0.0;
	float y = 0.0;
	printf("Type x y: ");
	scanf("%f %f", &x, &y);
	if (x<1 && x>-1 && y<1 && y>-1 && (y >= -1*x || y >= x))
	{
		printf("YES\n");
	}

	else
	{
		printf("no\n");
	}
}

