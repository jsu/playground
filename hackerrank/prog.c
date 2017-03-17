#include <stdio.h>
#include <math.h>

int main(void)
{
    double meal_cost;
    int tip_percent, tax_percent;

    scanf("%lf %d %d", &meal_cost, &tip_percent, &tax_percent);
    printf("The total meal cost is %d dollars.\n", 
        (int)round(meal_cost * (1 + (double)(tip_percent + tax_percent) / 100)));

    return 0;
}
