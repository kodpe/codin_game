#include <stdlib.h>
#include <stdio.h>

int main()
{
    int n;
    int max_pos = 5527;
    int max_neg = -274;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        // a temperature expressed as an integer ranging from -273 to 5526
        int t;
        scanf("%d", &t);
        if (t >= 0 && t < 5527 && t < max_pos)
            max_pos = t;
        if (t < 0 && t > -274 && t > max_neg)
            max_neg = t;
    }
    if (max_pos == 5527 && max_neg == -274)
    {
        printf("0\n");
        return (0);
    } 
    if ((max_pos <= max_neg * -1) || max_neg <= -274)
    {
        printf("%d\n", max_pos);
                return (0);
    } 
    if (max_pos > max_neg * -1)
    {
        printf("%d\n", max_neg);
                return (0);
    } 
    return 0;
}
