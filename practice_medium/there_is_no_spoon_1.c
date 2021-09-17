#include <stdio.h>
#include <string.h>

typedef struct coord
{
	int x;
	int y;
}   coord;

typedef struct  node
{
	coord   pos;
	coord   r;
	coord   d;
}   node;

void    ft_get_neighbor(char puce[30][30], coord p, node *nod)
{
	int y = nod->pos.y;
	int x = nod->pos.x;

	nod->r.x = -1;
	nod->r.y = -1;
	for (int x = nod->pos.x + 1; puce[y][x]; x++)
		if (puce[y][x] == '0') {
			nod->r.x = x;
			nod->r.y = y;
			break ;
		}
	nod->d.x = -1;
	nod->d.y = -1;
	for (int y = nod->pos.y + 1; y < p.y; y++)
		if (puce[y][x] == '0') {
			nod->d.x = x;
			nod->d.y = y;
			break ;
		}
}

void	ft_print_node(node n)
{
	printf("%d %d %d %d %d %d\n", n.pos.x, n.pos.y, n.r.x, n.r.y, n.d.x, n.d.y);
}

int main(void)
{
	char    puce[30][30];
	node    nod;
	coord   p;

	scanf("%d%d", &p.x, &p.y); fgetc(stdin);
	for (int y = 0; y < p.y; y++) {
		char line[32];
		scanf("%[^\n]", line); fgetc(stdin);
		strcpy(puce[y], line);
	}
	for (int y = 0; y < p.y; y++)
		for (int x = 0; puce[y][x]; x++)
			if (puce[y][x] == '0') {
				nod.pos.x = x;
				nod.pos.y = y;
				ft_get_neighbor(puce, p, &nod);
				ft_print_node(nod);
			}
	return (0);
}
