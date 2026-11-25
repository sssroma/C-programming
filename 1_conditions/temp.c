#include <stdio.h>

int main()
{
	char par = 'a';
	float t = 0.0;
	printf("Input temperature: ");
	scanf("%f%c", &t, &par);
	if (par == 'c' || par == 'C'){

		printf("Output temperature: %.1ff\n", (t * 1.8) + 32.0);

	}

	else if (par=='f' || par=='F'){
		printf("Output temperature: %.1fc\n", (t-32)/1.8);
	}

	else{
		printf("Error input\n");
	}
	return 0;
}

