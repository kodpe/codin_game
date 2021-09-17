#include <stdio.h>

int main(void)
{
    int h, idh, mount;

    while (1) {
        h = 0;
        idh = 0;
        for (int i = 0; i < 8; i++) {
            scanf("%d", &mount);
            if (mount > h) {
                h = mount;
                idh = i;
            }
        }
        printf("%d\n", idh);
    }
    return 0;
}
