#include <stdio.h>

int main(void)
{
	printf("\n n11 \n");
	for (int k=0, m=1; k <= m; k++, m = m*2)
		{ printf("%d ",  k);
		printf("%d\n",m);}
	printf("\n n12\n");
	int k = 0;
	for (int n=21356, s=0; n!=0; n = n/10)
		{ k=n%10; s+=k; printf("%d %d %d\n", n, k, s);}
	printf("\n n13 \n");
	int n =0;
	scanf("%d", &n);
	for (int s=1, i=0; i<=n; i++, s*=2)
		{printf("%d %d\n", s, i);}
	printf("\n n14 \n");
	int a=0;
	printf("a= ");
	scanf("%d", &a);
	for (int n=2; n<=a; n++)
		{if (n==a) {printf("Good\n"); break;}
		 if(a%n==0) {break;}
		}
	printf("\n 15 \n");
	int a=7;
	int s=0;
	for (int n=2; n<a; n++)
		{ if (a%n==0) {s++;} /*printf("%d %d\n", s, n);}
	if (s==0) {printf("Good\n");}
	return 0;
}
