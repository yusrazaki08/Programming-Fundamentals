#include <stdio.h>

void inputReadings(int sensors, int hours, float temp[100][100]) {
    int i, j;
    for(i = 0; i < sensors; i++) {
        printf("Enter readings for Sensor %d (%d hourly values):\n", i, hours);
        for(j = 0; j < hours; j++) {
            scanf("%f", &temp[i][j]);
        }
    }
}

void analyzeSensor(int hours, float sensor_temps[100], float *total_out, float *avg_out, float *highest_out, float *lowest_out, int *critical_out, int *warning_out, int *streak_out) {
    int j;
    float total = 0;
    float high = sensor_temps[0];
    float low = sensor_temps[0];
    int critical = 0;
    int warning = 0;
    int max_streak = 0;
    int current_streak = 0;

    for(j = 0; j < hours; j++) {
        float val = sensor_temps[j];
        total += val;

        if(val > high) {
            high = val;
        }
        if(val < low) {
            low = val;
        }

        if(val >= 40.0) {
            critical++;
        }
        
        if(val >= 35.0 && val <= 39.0) {
            warning++;
        }

        if(val >= 35.0) {
            current_streak++;
            if(current_streak > max_streak) {
                max_streak = current_streak;
            }
        } else {
            current_streak = 0;
        }
    }

    *total_out = total;
    *avg_out = total / hours;
    *highest_out = high;
    *lowest_out = low;
    *critical_out = critical;
    *warning_out = warning;
    *streak_out = max_streak;
}

int findHighestAverageSensor(int sensors, int hours, float temp[100][100]) {
    int i, j;
    int best_sensor = 0;
    float max_avg = -1.0;

    for(i = 0; i < sensors; i++) {
        float sum = 0;
        for(j = 0; j < hours; j++) {
            sum += temp[i][j];
        }
        float avg = sum / hours;
        if(i == 0 || avg > max_avg) {
            max_avg = avg;
            best_sensor = i;
        }
    }
    return best_sensor;
}

int main() {
    int sensors, hours, i;
    float temp[100][100];
    
    printf("Enter number of sensors: ");
    scanf("%d", &sensors);
    
    printf("Enter number of hourly readings per sensor: ");
    scanf("%d", &hours);

    inputReadings(sensors, hours, temp);

    for(i = 0; i < sensors; i++) {
        float total, avg, highest, lowest;
        int critical, warning, streak;

        analyzeSensor(hours, temp[i], &total, &avg, &highest, &lowest, &critical, &warning, &streak);

        printf("\nSensor %d Report:\n", i);
        printf("  Total Temperature: %.2f\n", total);
        printf("  Average Temperature: %.2f\n", avg);
        printf("  Highest Temperature: %.2f\n", highest);
        printf("  Lowest Temperature: %.2f\n", lowest);
        printf("  Critical Readings (>= 40C): %d\n", critical);
        printf("  Warning Readings (35C - 39C): %d\n", warning);
        printf("  Longest Streak (>= 35C): %d\n", streak);
    }

    int best_sensor = findHighestAverageSensor(sensors, hours, temp);
    float best_sum = 0;
    for(i = 0; i < hours; i++) {
        best_sum += temp[best_sensor][i];
    }
    float best_avg = best_sum / hours;

    printf("Sensor with Highest Average Temperature: Sensor %d\n", best_sensor);
    printf("Highest Average Temperature: %.2f\n", best_avg);

    return 0;
}

