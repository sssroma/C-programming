#include <stdio.h>
#include <math.h>

int main()
{
	float c = 300000000, h=600, r=6371, alfa=0, d = 0, vr = 0, vs=7560, t=0, fd=0, f0=2.18, b=0;
	f0 *= pow(10, 9);
	printf("Enter elevation angle alfa (0....90 degrees): ");
	scanf("%f", &alfa);
	alfa = alfa*3.1415926 / 180;
	d = sqrt(pow(r, 2) * pow(sin(alfa), 2) + 2*r*h + pow(h, 2)) - r * sin(alfa);
	printf("Distance: %.2f km\n", d);
	vr = vs*r*1000*cos(alfa) / (r*1000*sin(alfa) + d*1000);
	printf("Radial velocity: %.2f m/s\n", vr);
	b = vr/c;
	t = (vr/c) * pow(10, 9);
	fd = (f0 * sqrt((1+b) / (1-b))-f0)/1000;
	printf("Timedrift (dT): %.4f ns/s\nDoppler shift(fd): %.4f kHz\n", t, fd);
	if (d>1000 && (fd>42 || t>18)){
		printf("PROFILE: CRITICAL ERROR\n");
	}
	else if (fd>25 && t>10){
		printf("PROFILE: HIGH DINAMIC MODE\n");
	}
	else if (fd>3 || t>1){
		printf("PROFILE: NORMAL ACCELERATION\n");
	}
	else{
		printf("PROFILE: ZENITH MODE\n");
	}
	return 0;
}
