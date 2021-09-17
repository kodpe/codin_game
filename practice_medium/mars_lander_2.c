#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct coord
{
	int x;
	int y;
}   coord;

typedef struct line
{
	coord   pa;
	coord   pb; 
	double  coef;
}   line;

typedef struct lander
{
	coord   pos;    // x[0, 6999] y[0,2999]
	int     hs;     // horizontal speed m/s -500 < hs < 500
	int     vs;     // vertical speed m/s -500 < vs < 500
	int     fuel;   // fuel in liters 0 to 2000
	int     angle;  // -90 to 90
	int     pow;    // power 0 to 4
	int     alt;    // altitude relative
	int     gid;    // id line ok for landing
	coord   goal;   // coord of goal
	int     fxg;    // dir x for goal
}   lander;

void    ft_get_lines(coord pt[30], line mars[30], int *nb_lines)
{
	int nb_pt;

	scanf("%d", &nb_pt);
	for (int i = 0; i < nb_pt; i++)
		scanf("%d%d", &pt[i].x, &pt[i].y);
	*nb_lines = nb_pt - 1;
	for (int i = 0; i < *nb_lines; i++) {
		mars[i].pa.x = pt[i].x;
		mars[i].pa.y = pt[i].y;
		mars[i].pb.x = pt[i + 1].x;
		mars[i].pb.y = pt[i + 1].y;
		mars[i].coef = (double)(mars[i].pb.y - mars[i].pa.y) / (mars[i].pb.x - mars[i].pa.x);
	}
}

void    ft_get_lander(lander *obj)
{
	scanf("%d%d", &obj->pos.x, &obj->pos.y);
	scanf("%d%d", &obj->hs, &obj->vs);
	scanf("%d%d%d", &obj->fuel, &obj->angle, &obj->pow);
}

void    ft_get_altitude(lander *obj, line mars[30], int nb_lines)
{
	int x = obj->pos.x;
	for (int i = 0; i < nb_lines; i++)
		if (x >= mars[i].pa.x && x <= mars[i].pb.x)
			obj->alt = obj->pos.y - (mars[i].pa.y + ((x - mars[i].pa.x) * mars[i].coef));
}

void    ft_get_goal(lander *obj, line mars[30], int nb_lines)
{
	for (int i = 0; i < nb_lines; i++)
	{
		if (mars[i].coef == 0.00000)
		{
			obj->gid = i;
			obj->goal.x = mars[i].pa.x + (mars[i].pb.x - mars[i].pa.x) / 2;
			obj->goal.y = mars[i].pa.y;
		}
	}
}
void    ft_get_dir_x(lander *obj, line mars[30], int nb_lines)
{
	if (obj->pos.x > obj->goal.x + 400)
		obj->fxg = -1;
	else if (obj->pos.x < obj->goal.x - 400)
		obj->fxg = 1;
	else
		obj->fxg = 0;
}

void    ft_stab_lander(lander obj)
{
	int angle;
	int power;
	if (obj.hs > 3 && obj.fxg == -1)
		angle = 90;
	else if (obj.hs < -3 && obj.fxg == 1)
		angle = -90;
	else
		angle = 0;
	/**/
	if (obj.vs >= 0)
		power = 0;
	else if (obj.vs < -39)
		power = 4;
	else
		power = 0;

	if (obj.alt <= 10)
		power = 0;
	/**/
	//power = 0;
	printf("%d %d\n", angle, power);
}

int     ft_vitesse(int v, int alt)
{
	return (v + sqrt(2 * 3.711 * alt));
}

void    ft_display(lander *obj, line mars[30], int nb_lines)
{
	fprintf(stderr, "LANDER goal %d |%d : %d| dir fxg %d\n", obj->gid, obj->goal.x, obj->goal.y, obj->fxg);
	fprintf(stderr, "pos |%d : %d| alt [ %d ]\n", obj->pos.x, obj->pos.y, obj->alt);
	fprintf(stderr, " fuel %d pow %d\n", obj->fuel, obj->pow);
	fprintf(stderr, " hs %d vs %d angle %d\n", obj->hs, obj->vs, obj->angle);
	/*for (int i = 0; i < nb_lines; i++) {
	  fprintf(stderr, "n°%d  %d.%d >", i, mars[i].pa.x, mars[i].pa.y);
	  fprintf(stderr, " %d.%d (%0.1f)\n", mars[i].pb.x, mars[i].pb.y, mars[i].coef);
	  }*/
	fprintf(stderr, " vitesse de contact au sol %d\n", ft_vitesse(abs(obj->vs), obj->alt));
}

int main(void)
{
	lander  obj;
	coord   pt[30]; // the number of points used to draw the surface of Mars.
	line    mars[30];
	int nb_lines;
	ft_get_lines(pt, mars, &nb_lines);
	ft_get_goal(&obj, mars, nb_lines);

	while (1) {
		ft_get_lander(&obj);
		ft_get_altitude(&obj, mars, nb_lines);
		ft_get_dir_x(&obj, mars, nb_lines);
		ft_display(&obj, mars, nb_lines);

		// rotate power. rotate is the desired rotation angle. power is the desired thrust power.
		//printf("-20 3\n");
		//if (obj.alt < 1000 || obj.vs < -19)
		/*
		   if (obj.fxg == 1)
		   printf("-15 3\n");
		   if (obj.fxg == -1)
		   printf("15 3\n");
		   if (obj.fxg == 0)
		   printf("0 3\n");
		 */
		ft_stab_lander(obj);
	}
	return (0);
}
