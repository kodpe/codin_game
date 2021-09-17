#include <stdlib.h>
#include <stdio.h>

typedef struct path
{
    int id;
    int dt; // distance
    int fa; // factory a
    int fb; // factory b
}   path;

typedef struct fact
{
    int id;
    int pow; // 0 - 3
    int cyb; // 0 +
}   fact;

typedef struct unit
{
    int id;
    int cyb; // 1 +
    int dst; // factory destination
    int src; // factory source
    int dt; // nbr de tours avant d'arriver a dest
}   unit;

void    ft_display_path(path *s_path, int n_path)
{
    for (int i = 0; i < n_path; i++)
        fprintf(stderr, "path %d |%d - %d| = %d\n", s_path[i].id, s_path[i].fa, s_path[i].fb, s_path[i].dt);
}

void    ft_get_path(path *s_path, int n_path)
{
    for (int i = 0; i < n_path; i++)
    {
        s_path[i].id = i;
        scanf("%d%d%d", &s_path[i].fa, &s_path[i].fb, &s_path[i].dt);
    }
    s_path[n_path].id = -1;
}

void    ft_init_struct(fact *myf, fact *opf, fact *eqf, unit *myu, unit *opu)
{
    for (int i = 0; i < 16; i++)
        myf[i].id = -1;
    for (int i = 0; i < 16; i++)
        opf[i].id = -1;
    for (int i = 0; i < 16; i++)
        eqf[i].id = -1;
    for (int i = 0; i < 101; i++)
        myu[i].id = -1;
    for (int i = 0; i < 101; i++)
        opu[i].id = -1;
}

void    ft_display_fact(fact *s_fact)
{
    for (int i = 0; i < 16; i++)
        fprintf(stderr, "fact %d pow %d cyb %d\n", s_fact[i].id, s_fact[i].pow, s_fact[i].cyb);
}

void    ft_display_unit(unit *u)
{
    for (int i = 0; u[i].id != -1; i++)
        fprintf(stderr, "unit %d cyb %d dst %d src %d dt %d\n", u[i].id, u[i].cyb, u[i].dst, u[i].src, u[i].dt);
}

void    ft_get_fact(fact **f, int id)
{
    int i, arg_2, arg_3, arg_4, arg_5;
    scanf("%d%d%d%d", &arg_2, &arg_3, &arg_4, &arg_5);
    i = 0;
    while (f[i]->id != -1)
        i++;
    f[i]->id = id;
    f[i]->pow = arg_3;
    f[i]->cyb = arg_2;
}

void    ft_get_unit(unit *u, int id)
{
    int i, arg_2, arg_3, arg_4, arg_5;
    scanf("%d%d%d%d", &arg_2, &arg_3, &arg_4, &arg_5);
    i = 0;
    while (u[i].id != -1)
        i++;
    u[i].id = id;
    u[i].cyb = arg_4;
    u[i].dst = arg_3;
    u[i].src = arg_2;
    u[i].dt = arg_5;
}

void    ft_update_entities(fact *myf, fact *opf, fact *eqf, unit *myu, unit *opu)
{
    // the number of entities (e.g. factories and troops)
    int entity_count;
    scanf("%d", &entity_count);
    for (int i = 0; i < entity_count; i++) 
    {
        int id, entity_owner;
        char entity_type[11];
        scanf("%d%s%d", &id, entity_type, &entity_owner);

        ft_init_struct(myf, opf, eqf, myu, opu);
        if (entity_type[0] == 'F' && entity_owner == 1)
            ft_get_fact(&myf, id);
        else if (entity_type[0] == 'F' && entity_owner == -1)
            ft_get_fact(&opf, id);
        else if (entity_type[0] == 'F' && entity_owner == 0)
            ft_get_fact(&eqf, id);
        else if (entity_type[0] == 'T' && entity_owner == 1)
            ft_get_unit(myu, id);
        else if (entity_type[0] == 'T' && entity_owner == -1)
            ft_get_unit(opu, id);
    }
    // DEBUG
    fprintf(stderr, "nbr entity : %d\n", entity_count);
}
int main()
{
    int i = 0;
    // the number of factories
    int factory_count;
    scanf("%d", &factory_count);
    // the number of links between factories

    int n_path;
    scanf("%d", &n_path);
    path  s_path[n_path]; // 21 - 105
    ft_get_path(s_path, n_path);

    fact    s_myfact[16], s_opfact[16], s_eqfact[16];
    unit    s_myunit[101], s_opunit[101];

    //ft_init_struct(s_myfact, s_opfact, s_eqfact, s_myunit, s_opunit);
    while (1) {
        i++;
        ft_update_entities(s_myfact, s_opfact, s_eqfact, s_myunit, s_opunit);
        
        // Any valid action, such as "WAIT" or "MOVE source destination cyborgs"
        //printf("MOVE 1 7 1\n");
        printf("WAIT\n");

        // DEBUG
        //fprintf(stderr, "nbr factory : %d nbr entity : %d\n", factory_count, entity_count);
        fprintf(stderr, "nbr factory : %d path : %d\n", factory_count, n_path);
        //ft_display_path(s_path, n_path);
        //ft_display_fact(s_myfact);
        ft_display_fact(s_opfact);
        //ft_display_fact(s_eqfact);
        //ft_display_unit(s_myunit);
        //ft_display_unit(s_opunit);
    }

    return 0;
}
