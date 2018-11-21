#include <stdio.h>
#include <math.h>

void solve(double meal_cost, int tip_percent, int tax_percent)
{
    double tip, tax;
    tip = meal_cost * tip_percent / 100;
    tax = meal_cost * tax_percent / 100;
    printf("%.0f\n", round(meal_cost + tip + tax));
}

int main(int argc, char **argv)
{
    double meal_cost;
    int tip_percent, tax_percent;
    
    scanf("%lf %d %d", &meal_cost, &tip_percent, &tax_percent);
    solve(meal_cost, tip_percent, tax_percent);

    return 0;
}
