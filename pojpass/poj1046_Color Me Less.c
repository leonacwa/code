/* poj 1046 Color Me Less */
#include <stdio.h>
typedef struct _RGB{
    unsigned int r, g, b;
}RGB;
RGB color[16], tmp;

int eu_distance(RGB a, RGB b)
{
    return (a.r-b.r)*(a.r-b.r) + (a.g-b.g)*(a.g-b.g) + (a.b-b.b)*(a.b-b.b);
}
int main()
{
    int i, k, dmin, t;
    for (i = 0; i < 16; i++) {
        scanf("%u %u %u", &color[i].r, &color[i].g, &color[i].b);
    }
    while (scanf("%u %u %u", &tmp.r, &tmp.g, &tmp.b)
           && tmp.r != -1 && tmp.g != -1 && tmp.b != -1) {
        dmin = 9999999;
        for (i = 0; i < 16; i++) {
            t = eu_distance(color[i], tmp);
            if (dmin > t) {
                dmin = t;
                k = i;
            }
        }
        printf("(%u,%u,%u) maps to (%u,%u,%u)\n",
               tmp.r, tmp.g, tmp.b,
               color[k].r, color[k].g, color[k].b);
    }
    return 0;
}
