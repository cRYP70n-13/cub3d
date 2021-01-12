#include <stdio.h>
#include <math.h>

#define PV(x, y) printf("%s = " y, #x, x)

double	rad(double angle)
{
	return (M_PI * angle / 180);
}

double	deg(double angle)
{
	return (180 * angle / M_PI);
}

double  normalize_angle(double angle)
{
	// g_ray[i].rayAngle = fmod(g_ray[i].rayAngle, (2 * PI));
	// if (g_ray[i].rayAngle <= 0) {
	// 	g_ray[i].rayAngle = (2 * PI) + g_ray[i].rayAngle;
	// }
    // PV(fabs(deg(angle)), "%f before\n");
	if (fabs(deg(angle)) >= 360)
    {
		angle = (angle < 0 ? -1 : 1) * fmod(fabs(angle), rad(360));
        // PV(deg(angle), "%f after\n");
    }
    if (deg(angle) < 0)
		angle += rad(360);
	return (angle);
}

int main(int argc, char const *argv[])
{
    double a, b, c, d, e, f;
    a = rad(180);
    b = rad(361);
    c = rad(-183);
    d = rad(-580);
    e = rad(-800);
    f = rad(0);


    printf("Expected: 180, 1, 177, 140, 280, 0\n");
    printf("%f\n", deg(normalize_angle(a)));
    printf("%f\n", deg(normalize_angle(b)));
    printf("%f\n", deg(normalize_angle(c)));
    printf("%f\n", deg(normalize_angle(d)));
    printf("%f\n", deg(normalize_angle(e)));
    printf("%f\n", deg(normalize_angle(f)));
    return 0;
}
