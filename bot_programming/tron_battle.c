#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

typedef struct data
{
    int t;      // time
    int np;     // total number of players (2 to 4).
    int me;     // your player number (0 to 3).
}   data;

typedef struct player
{
    int e;      // etat 1 = alive // etat 0 = dead
    int xi;     // x initial (or -1) origin
    int yi;     // y initial (or -1) origin
    int xc;     // x current (same as xi if you play before this player)
    int yc;     // y current (same as yi if you play before this player)
    int historic[600];
}   player;

void    ft_world_init(int w[22][32]) 
{
    for (int i = 0; i < 22; i++)
        for (int j = 0; j < 32; j++)
        {
            w[i][j] = 7; // void
            if (i == 0 || i == 21 || j == 0 || j == 31) // wall
                w[i][j] = 4; // 0 1 2 3 player 4 wall 7 void 
        }
}

void    ft_display_world(int w[22][32])
{
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            if (w[i][j] == 7)
                fprintf(stderr, "  ");
            else
                fprintf(stderr, " %d", w[i][j]);
        }
        fprintf(stderr, "\n");
    }
}

void    ft_world_update(data *index, player p[4], int w[22][32])
{
    scanf("%d%d", &index->np, &index->me);
        for (int i = 0; i < index->np; i++) 
        {
            scanf("%d%d%d%d", &p[i].xi, &p[i].yi, &p[i].xc, &p[i].yc);
            w[p[i].yc + 1][p[i].xc + 1] = i;
            p[i].e = 1;
            if (index->t == 0)
                w[p[i].yi + 1][p[i].xi + 1] = i;
        }
}

void    ft_dir(int dir)
{
    if (dir == 0) // UP
        printf("UP\n");
    if (dir == 1) // DOWN
        printf("DOWN\n");
    if (dir == 2) // LEFT
        printf("LEFT\n");
    if (dir == 3) // RIGHT
        printf("RIGHT\n");
}

int ft_check_next_case(int w[22][32], int x, int y, int dir)
{
    if (dir == 0) // UP
        if (w[y - 1][x] == 7 && w[y - 2][x] == 7)
            return (1);
    if (dir == 1) // DOWN
        if (w[y + 1][x] == 7  && w[y + 2][x] == 7)
            return (1);
    if (dir == 2) // LEFT
        if (w[y][x - 1] == 7  && w[y][x - 2] == 7 )
            return (1);
    if (dir == 3) // RIGHT
        if (w[y][x + 1] == 7  && w[y][x + 2] == 7)
            return (1);
    return (0);
}

// compte le nombre de case vides == 7 qui sont en contact !!!!!
void    ft_explorer(int w[22][32], int x, int y, int *score)
{
    if (w[y - 1][x] == 7)
    {
        w[y - 1][x] = 9;
        *score += 1;
        ft_explorer(w, x, y - 1, score);
    }
    if (w[y + 1][x] == 7)
    {
        w[y + 1][x] = 9;
        *score += 1;
        ft_explorer(w, x, y + 1, score);
    }
    if (w[y][x + 1] == 7)
    {            
        w[y][x + 1] = 9;
        *score += 1;
        ft_explorer(w, x + 1, y, score);
    }
    if (w[y][x - 1] == 7)
    {            
        w[y][x - 1] = 9;
        *score += 1;
        ft_explorer(w, x - 1, y, score);
    }
}

void    ft_preshot_players(int wc[22][32], player p[4], data index)
{
    int x, y, i;
    for (i = 0; i < index.np; i++)
        if (i != index.me)
            {
                x = p[i].xc + 1;
                y = p[i].yc + 1;
                if (wc[y - 1][x] == 7)
                    wc[y - 1][x] = 9;
                if (wc[y + 1][x] == 7)
                    wc[y + 1][x] = 9;
                if (wc[y][x - 1] == 7)
                    wc[y][x - 1] = 9;
                if (wc[y][x + 1] == 7)
                    wc[y][x + 1] = 9;
            }
}

void    ft_init_wc(int w[22][32], int wc[22][32])
{
        for (int i = 0; i < 22; i++)
            for (int j = 0; j < 32; j++)
                    wc[i][j] = w[i][j];
}

int    ft_best_dir(int w[22][32], player p[4], data index, int score[4])
{
    int wc[22][32];
    int high_score = 0;
    int dir = 0;
    int x = p[index.me].xc + 1;
    int y = p[index.me].yc + 1;

    if (w[y - 1][x] == 7)
    {
        ft_init_wc(w, wc); ft_preshot_players(wc, p, index); ft_explorer(wc, x, y - 1, &score[0]); // UP
    }
    if (w[y + 1][x] == 7)
    {
        ft_init_wc(w, wc); ft_preshot_players(wc, p, index); ft_explorer(wc, x, y + 1, &score[1]); // DOWN
    }
    if (w[y][x - 1] == 7)
    {
        ft_init_wc(w, wc); ft_preshot_players(wc, p, index); ft_explorer(wc, x - 1, y, &score[2]); // LEFT
    }
    if (w[y][x + 1] == 7)
    {
        ft_init_wc(w, wc); ft_preshot_players(wc, p, index); ft_explorer(wc, x + 1, y, &score[3]); // RIGHT
    }
    for (int i = 0; i < 4; i++)
        if (score[i] > high_score)
        {
            high_score = score[i];
            dir = i;
        }
    return (dir);
}

int ft_best_dir_for_target(player p[4], data index, int *tx, int *ty)
{
    int xc = p[index.me].xc;
    int yc = p[index.me].yc;
    int opp;

    if (index.me == 0)
        opp = 1;
    if (index.me == 1)
        opp = 0;
    if (index.t == 2)
    { 
        *tx = 2 * (p[opp].xi) - p[opp].xc;
        *ty = 2 * (p[opp].yi) - p[opp].yc;
    }
    if (index.t < 2)
        return (0);
    if (index.t % 2 == 0)
    {
        if (*tx < xc)
            return (2);
        if (*tx > xc)
            return (3);
        if (*ty < yc)
            return (0);
        if (*ty > yc)
            return (1);
    }
    if (*ty < yc)
        return (0);
    if (*ty > yc)
        return (1);
    if (*tx < xc)
        return (2);
    if (*tx > xc)
        return (3);
    return (-1);
}
/*
int ft_is_wall(int w[22][32], player p[4], data index)
{
    int x = p[index.me].xc + 1;
    int y = p[index.me].yc + 1;

    if (w[y - 2][x] == 4)
        return (1);
    if (w[y + 2][x] == 4)
        return (1);
    if (w[y][x - 2] == 4)
        return (1);
    if (w[y][x + 2] == 4)
        return (1);
    return (0);
}*/

int main()
{
    data    index;
    player  p[4];
    int     w[22][32];
    int     mission[4] = {0, 2, 1, 3};
    int     tir = 0;
    int     tx = -1;
    int     ty = -1;
    int     last_dir = 0;
    int     dir_next = -1;

    index.t = 0;
    ft_world_init(w);
    // srand(time(NULL));

    // game loop
    while (1) {
        index.t++;
        if (index.t > 1000)
            return (0);
        ft_world_update(&index, p, w);
        
        int score[4] = {0};
        int dir;
        dir = ft_best_dir(w, p, index, score);
        if (score[last_dir] == score[dir])
            dir = last_dir;

        for (int i = 0; i < 4; i++)
            fprintf(stderr, "score[%d] %d \n", i, score[i]);
        fprintf(stderr, " best dir is %d \n", dir); // tmp dir
        /*
        if (tir != -1)
        {
            tir = ft_best_dir_for_target(p, index, &tx, &ty);
            if (score[tir] == score[dir])
                dir = tir;
        }*/
        /*
        if (ft_is_wall(w, p, index))
        {
            for (int i = 0; i < 4; i++)
                if (score[i] == score[dir])
                    dir = i;
        }*/


    //////////////////////////// anticipe la colision
    /*
    int opp;
    if (index.me == 0)
        opp = 1;
    if (index.me == 1)
        opp = 0;
    int x_opp = p[opp].xc;
    int y_opp = p[opp].yc;
    int x_me = p[index.me].xc;
    int y_me = p[index.me].yc;

    if (abs(x_me - x_opp) == 5 && dir_next == -1)
    {
        if (score[0] == score[dir])
                dir = 0;
        if (score[1] == score[dir])
                dir = 1;
        dir_next = p[index.me].historic[index.t - 1];
    }
    if (abs(y_me - y_opp) == 5 && dir_next == -1)
    {
        if (score[2] == score[dir])
                dir = 2;
        if (score[3] == score[dir])
                dir = 3;
        dir_next = p[index.me].historic[index.t - 1];
    }
    if (dir_next != -1)
        {
            dir = dir_next;
            dir_next = -1;
        } */
    ////////////////////////////

        ft_dir(dir);
        last_dir = dir;
        p[index.me].historic[index.t] = dir;
        
        /**/ //DEBUG ZONE
        //fprintf(stderr, " best dir is %d \n", dir);
        fprintf(stderr, " best tir is %d \n", tir);
        fprintf(stderr, " target is (%d, %d)\n", tx, ty);

        //ft_display_world(w); // display world update
        fprintf(stderr, " DEBUG t %d np %d me %d\n", index.t, index.np, index.me);
        /*
        for (int i = 0; i < index.np; i++) 
            fprintf(stderr, " player %d [ %d : %d ]\n", i, p[i].xc, p[i].yc);*/
        /**/
        // display choice at last

        //int dir = mission[index.t % 4];
        /*
        if ( index.t % 20 == 0)
        {
            int r = rand() % 4;
            while (ft_check_next_case(w, x, y, r) == 0)
                r = rand() % 4;
            ft_dir(r);
        }
        else if (ft_check_next_case(w, x, y, dir) == 1)
            ft_dir(dir);
        */
        /*
        int x = p[index.me].xc + 1;
        int y = p[index.me].yc + 1;

        if (w[y - 1][x] == 7 && w[y - 2][x] == 7)
            printf("UP\n");
        else if (w[y + 1][x] == 7  && w[y + 2][x] == 7)
            printf("DOWN\n");
        else if (w[y][x + 1] == 7  && w[y][x + 2] == 7)
            printf("RIGHT\n");
        else if (w[y][x - 1] == 7  && w[y][x - 2] == 7 )
            printf("LEFT\n");
        else if (w[y - 1][x] == 7)
            printf("UP\n");
        else if (w[y + 1][x] == 7)
            printf("DOWN\n");
        else if (w[y][x + 1] == 7)
            printf("RIGHT\n");
        else if (w[y][x - 1] == 7)
            printf("LEFT\n");
        /*/
    }
    return (0);
}
