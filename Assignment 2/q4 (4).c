#include <stdio.h>

int getValidDays()
{
    int days;
    printf("Number of days: ");
    scanf("%d", &days);

    while(days < 1 || days > 7)
    {
        printf("Invalid number. Enter again: ");
        scanf("%d", &days); }
    return days;
}

float calculateDailySales(int dayNumber) {
    int orders, i;
    float amount, average, total = 0;
    float highest = 0;

    printf("\nDay %d - Number of orders: ", dayNumber);
    scanf("%d", &orders);

    for(i = 1; i <= orders; i++)
    {
        printf("Order amount: ");
        scanf("%f", &amount);

        while(amount <= 0)
        {
            printf("Invalid amount. Enter again: ");
            scanf("%f", &amount);
        }

        total = total + amount;

        if(amount > highest)
        {
            highest = amount;
        }
    }

    average = total / orders;

    printf("Day %d Total Sales: %.2f\n", dayNumber, total);
    printf("Average Order Amount: %.2f\n", average);
    printf("Highest Order Amount: %.2f\n", highest);

    return total;
}

int findHighestSales(float dailySales[], int numberOfDays)
{
    int i;
    int highestDay = 1;
    float highestSales = dailySales[0];

    for(i = 1; i < numberOfDays; i++)
    {
        if(dailySales[i] > highestSales)
        {
            highestSales = dailySales[i];
            highestDay = i + 1; }
    }

    return highestDay;
}

void displayBarChart(float dailySales[], int numberOfDays)
{
    int i, j;
    int stars;
    printf("\nDaily Sales Bar Chart\n");
    for(i = 0; i < numberOfDays; i++)
    {
        stars = (int)(dailySales[i] / 100);
        printf("Day %d: ", i + 1);
        for(j = 0; j < stars; j++)
        {
            printf("*");}
        printf("\n");  }
}

int main()
{
    int days;
    int i;
    int highestDay;
    float dailySales[7];
    float totalFestivalSales = 0;
    days = getValidDays();

    for(i = 0; i < days; i++)
    {
        dailySales[i] = calculateDailySales(i + 1);
        totalFestivalSales = totalFestivalSales + dailySales[i];
    }

    highestDay = findHighestSales(dailySales, days);

    printf("\nFestival Sales Summary\n");
    printf("Total Festival Sales: %.2f\n", totalFestivalSales);
    printf("Day with Highest Sales: Day %d\n", highestDay);
    displayBarChart(dailySales, days);
    return 0;
}
