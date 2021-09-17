#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct coord
{
    int x;
    int y;
    int dist;
    int angle;
}   coord;

void    ft_display_cp(coord *cp)
{
    fprintf(stderr, "CP");
    for (int i = 0; i < 8; i++)
        if (cp[i].x != 0)
            fprintf(stderr, " %d|%d:%d|", i, cp[i].x, cp[i].y);     
    fprintf(stderr, "\n");   
}

void    ft_update_cp(coord *cp, coord next_cp, coord *last_cp, int *lap)
{
    if (next_cp.x != last_cp->x || next_cp.y != last_cp->y)
    {
        last_cp->x = next_cp.x;
        last_cp->y = next_cp.y;
        for (int i = 0; i < 8; i++)
        {
            if (cp[i].x == next_cp.x && cp[i].y == next_cp.y)
            {
                *lap = 1;
                return ;
            }      
        }
        for (int i = 0; i < 8; i++)
        {
            if (cp[i].x == 0)
            {
                cp[i].x = next_cp.x;
                cp[i].y = next_cp.y;
                return ;
            }
        }
    }
}

int     ft_distance(coord a, coord b)
{
    return(sqrt(pow(b.x - a.x, 2) + pow(b.y -a.y, 2)));
}

int     ft_high_distance(coord *cp)
{
    int i, id, dist, high = 0;

    for (i = 0; cp[i + 1].x != 0; i++)
    {
        dist = ft_distance(cp[i], cp[i + 1]);
        if (dist > high)
        {
            high = dist;
            id = i + 1;
        }
    }
    dist = ft_distance(cp[i], cp[0]);
        if (dist > high)
        {
            high = dist;
            id = 0;
        }
    return (id);
}

void    ft_scan_data(coord *pod, coord *opp, coord *next_cp)
{
    scanf("%d%d%d%d", &pod->x, &pod->y, &next_cp->x, &next_cp->y);
    scanf("%d%d", &next_cp->dist, &next_cp->angle);
    scanf("%d%d", &opp->x, &opp->y);
}

void    ft_get_first_cp(coord *cp, coord pod, coord opp)
{
    if (cp[0].x == 0)
    {
        cp[0].x = pod.x - (pod.x - opp.x) / 2;
        cp[0].y = pod.y - (pod.y - opp.y) / 2;
    }
}

void    ft_count_cp(coord *cp, coord next_cp, int *cpcount, int *lap)
{
    if (*cpcount > 2)
            if (next_cp.x == cp[0].x && next_cp.y == cp[0].y)
                *lap = 2;
    for (int i = 0; i < 8; i++)
            if (next_cp.x == cp[i].x && next_cp.y == cp[i].y)
                    return ;
    *cpcount += 1;
}

int     ft_index_cp(coord *cp, coord next_cp)
{
    for (int i = 0; i < 8; i++)
        if (cp[i].x == next_cp.x && cp[i].y == next_cp.y)
            return (i);
    return (-1);
}

void    ft_init_struct(coord *cp, coord *last_cp)
{
    last_cp->x = 0;
    last_cp->y = 0;
    for (int i = 0; i < 8; i++)
    {
        cp[i].x = 0;
        cp[i].y = 0;
    }
}

void    ft_power(coord *cp, coord next_cp, int *boost, int lap, int i, coord pod, coord opp)
{
    int     power;
    // DEFAULT POWER
    power = 100;
    // SLOW FOR CP APPROCHE
    if (next_cp.dist < 3000) // 3000
        power = (next_cp.dist - 600) / 24; // 600 // 24
    // SLOW FOR TURN AROUND
    if (abs(next_cp.angle) > 90)
        power = 0;
    // SPEED UP IN CP
    if (next_cp.dist < 1600) // 1300 origine // 1600 1700 win silver sebulboss
        power = 100;
    // LAP 3 FAST END 
    if (lap == 3 && i == 0)
         if (abs(next_cp.angle) < 4)
            power = 100;
    // BOOST AT TIME // SET DIRECTION + POWER
    if (lap > 1)
        if (*boost == 1 && i == ft_high_distance(cp) && abs(next_cp.angle) < 4 && next_cp.dist > 3800)
        {
            *boost = 0;
            printf("%d %d %s\n", next_cp.x, next_cp.y, "BOOST");
            return ;
        }
    /*
    if (ft_distance(pod, opp) < 900)
    {
        printf("%d %d %s\n", next_cp.x, next_cp.y, "SHIELD");
            return ;
    }*/
     printf("%d %d %d\n", next_cp.x, next_cp.y, power);       
}

int main(void)
{
    int     lap = 1;
    int     boost = 1;
    int     ncp = 1;
    int     t = 0;
    int     i = 0;
    int     laptree = 0;
    coord   pod, opp, next_cp, last_cp, cp[8];

    ft_init_struct(cp, &last_cp);
    ft_scan_data(&pod, &opp, &next_cp);
    ft_get_first_cp(cp, pod, opp);
    printf("%d %d %d\n", next_cp.x, next_cp.y, 100);
    while (lap == 1)
    {
        ft_scan_data(&pod, &opp, &next_cp);
        ft_count_cp(cp, next_cp, &ncp, &lap);
        ft_update_cp(cp, next_cp, &last_cp, &lap);
        // POD MOVE
        ft_power(cp, next_cp, &boost, lap, 0, pod, opp);
        t++;
        // DEBUG
        fprintf(stderr, "time : %d lap : %d target : %d/%d(%d, %d)\n", t, lap, 0, ncp, next_cp.x, next_cp.y);
        //ft_display_cp(cp);
        fprintf(stderr, "distance pod / opp %d\n", ft_distance(pod, opp));
    }
    while (lap > 1)
    {
        ft_scan_data(&pod, &opp, &next_cp);
        i = ft_index_cp(cp, next_cp);
        if (i == ncp - 1)
            laptree = 3;
        if (i == 1 && laptree == 3)
            lap = 3;
        // POD MOVE
        ft_power(cp, next_cp, &boost, lap, i, pod, opp);
        t++;
        // DEBUG ZONE
        fprintf(stderr, "time : %d lap : %d target : %d/%d(%d, %d)\n", t, lap, i, ncp, next_cp.x, next_cp.y);
        fprintf(stderr, "high distance : %d boost : %d\n", ft_high_distance(cp), boost);
        //ft_display_cp(cp);
        //fprintf(stderr, "lap %d target_cp : %d\n", lap, ft_target_cp(cp, lap));
        //fprintf(stderr, "last cp x.%d y.%d \n", last_cp.x, last_cp.y);
        fprintf(stderr, "distance pod / opp %d\n", ft_distance(pod, opp));
    }
    return (0);
}

/*
    // coord of pod & opp
        fprintf(stderr, "pod (%d, %d)\n", pod.x, pod.y);
        fprintf(stderr, "opp (%d, %d)\n", opp.x, opp.y);

    // distance pod vs opp 
        fprintf(stderr, "distance pod / opp %d\n", ft_distance(x, y, opp.x, opp.y));
    
    // high distance cp
        fprintf(stderr, "high distance cp %d\n", ft_high_distance(cp));

    // target_angle
        fprintf(stderr, "target_angle: %d\n", next_cp.angle);

    // next_cp.dist
        fprintf(stderr, "next_cp.dist : %d\n", next_cp.dist);

    // get speed of pod
        int speed = 0;
        int last_x = 0;
        int last_y = 0;
        speed = (abs(x - last_x) + abs(y - last_y)) / 10; last_x = x; last_y = y;
        fprintf(stderr, "speed : %d, boost : %d\n", speed, boost);
*/
