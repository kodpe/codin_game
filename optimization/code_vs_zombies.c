#include <stdio.h>
#include <math.h>

typedef struct coord
{
    int id;
    int x;
    int y;
}   coord;

typedef struct game
{
    int     id;
    int     nb_human;
    int     nb_zombi;
    coord   ash;
    coord   t_ash;
    coord   human[100];
    coord   n_zob[100];
    coord   c_zob[100];
}   game;

void    ft_init_coord(coord *s, int n)
{
    s->id = n;
    s->x = n;
    s->y = n;
}

void    ft_init_game(game *w)
{
    w->nb_human = -1;
    w->nb_zombi = -1;
    ft_init_coord(&w->ash, -1);
    for (int i = 0; i < 100; i++)
    {
        ft_init_coord(&w->human[i], -1);
        ft_init_coord(&w->n_zob[i], -1);
        ft_init_coord(&w->c_zob[i], -1);
    }
}

void    ft_display_coord(coord tab[100], int size, char *name)
{
    fprintf(stderr, "nb_%s %d\n", name, size);
    for (int i = 0; i < 100; i++)
        if (tab[i].id != -1)
            fprintf(stderr, "%s %d|%d : %d| (%d)\n", name, i, tab[i].x, tab[i].y, tab[i].id);
    fprintf(stderr, "\n");
}

void    ft_display_game(game w)
{
    fprintf(stderr, "game %d ash |%d %d| (%d) target |%d %d| (%d)\n\n", w.id, w.ash.x, w.ash.y, w.ash.id,w.t_ash.x, w.t_ash.y, w.t_ash.id);
    ft_display_coord(w.human, w.nb_human, "human");
    ft_display_coord(w.n_zob, w.nb_zombi, "n_zob");
    ft_display_coord(w.c_zob, w.nb_zombi, "c_zob");
}

void    ft_get_game(game *w)
{
    w->id++;
    w->ash.id = 1;
    scanf("%d%d", &w->ash.x, &w->ash.y);

    scanf("%d", &w->nb_human);
    for (int i = 0; i < w->nb_human; i++)
        scanf("%d%d%d", &w->human[i].id, &w->human[i].x, &w->human[i].y);

    scanf("%d", &w->nb_zombi);
    for (int i = 0; i < w->nb_zombi; i++)
    {
        int id;
        scanf("%d%d%d%d%d", &id, &w->c_zob[i].x, &w->c_zob[i].y, &w->n_zob[i].x, &w->n_zob[i].y);
        w->n_zob[i].id = id;
        w->c_zob[i].id = id;
    }
}

int ft_distance(coord a, coord b)
{
    return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

int ft_save_before_zob(game w, int  human_id)
{
    int zob_closer = 32000;
    int zob_id;
        for (int i = 0; i < w.nb_zombi; i++)
        {
            int test = ft_distance(w.c_zob[i], w.human[human_id]);
            if (test < zob_closer)
            {
                zob_closer = test;
                zob_id = i;
            }
        }
        if (zob_closer / 400 > ft_distance(w.human[human_id], w.ash) / 1000 + 2000)
            return (-1);
    //return (-1); // or -1
    return (zob_id);
}

int main()
{
    int best_dist;
    int best_id;
    int test;
    game    w;
    
    w.id = 0;
    ft_init_coord(&w.t_ash, -1);
    while (1) {
        ft_init_game(&w);
        ft_get_game(&w);
        //ft_display_game(w);
        best_dist = 32000;
        best_id = -1;
        for (int i = 0; i < w.nb_human; i++)
        {
            test = ft_distance(w.human[i], w.ash);
            if (test < best_dist)
            {
                best_dist = test;
                best_id = ft_save_before_zob(w, i);
            }
            else if (i == w.nb_human - 1)
                best_id = ft_save_before_zob(w, i);
        }
        if (best_id != -1)
        {
            w.t_ash.id = w.id;
            w.t_ash.x = w.n_zob[best_id].x;
            w.t_ash.y = w.n_zob[best_id].y;
        }
        else
        {
            best_dist = 32000;
            best_id = -1;
            for (int i = 0; i < w.nb_human; i++)
            {
                test = ft_distance(w.human[i], w.ash);
                if (test < best_dist)
                {
                    best_dist = test;
                    best_id = i; 
                }
            }
            w.t_ash.id = w.id;
            w.t_ash.x = w.human[best_id].x;
            w.t_ash.y = w.human[best_id].y;
        }
        printf("%d %d %s\n", w.t_ash.x, w.t_ash.y, "let's gooo");
    }
    return 0;
}
