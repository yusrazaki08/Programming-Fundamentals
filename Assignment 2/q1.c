#include <stdio.h>

int main() {
    int rows, cols, i, j, m, k, mid, found, row_free;
    int seats[100][100];
    int total_free = 0;
    int target_r, target_c;
    int r1, r2, d, ok, rem_free;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter seating plan (0 for available, 1 for booked):\n");
    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++) {
            scanf("%d", &seats[i][j]);
        }
    }

    printf("\nFree seats per row: ");
    for(i = 0; i < rows; i++) {
        row_free = 0;
        for(j = 0; j < cols; j++) {
            if(seats[i][j] == 0) {
                row_free++;
            }
        }
        total_free += row_free;
        printf("%d ", row_free);
    }
    printf(" Total free: %d\n", total_free);

    printf("Enter number of customers (k): ");
    scanf("%d", &k);

    if(k <= 0 || k > cols) {
        printf("Invalid group size!\n");
        return 0;
    }

    mid = rows / 2;
    found = 0;
    target_r = -1;
    target_c = -1;

    for(d = 0; d < rows && !found; d++) {
        r1 = mid - d;
        if(r1 >= 0 && r1 < rows) {
            for(j = 0; j <= cols - k; j++) {
                ok = 1;
                for(m = 0; m < k; m++) {
                    if(seats[r1][j + m] == 1) {
                        ok = 0;
                        break;
                    }
                }
                if(ok) {
                    target_r = r1;
                    target_c = j;
                    found = 1;
                    break;
                }
            }
        }

        if(found) {
            break;
        }

        if(d > 0) {
            r2 = mid + d;
            if(r2 >= 0 && r2 < rows) {
                for(j = 0; j <= cols - k; j++) {
                    ok = 1;
                    for(m = 0; m < k; m++) {
                        if(seats[r2][j + m] == 1) {
                            ok = 0;
                            break;
                        }
                    }
                    if(ok) {
                        target_r = r2;
                        target_c = j;
                        found = 1;
                        break;
                    }
                }
            }
        }
    }

    if(found) {
        printf("Group of %d seated in Row %d, Seats %d to %d\n", k, target_r, target_c, target_c + k - 1);
        for(m = 0; m < k; m++) {
            seats[target_r][target_c + m] = 1;
        }
    } 
    else {
        printf("No row contains %d consecutive available seats.\n", k);
    }

    printf("\n   ");
    for(j = 0; j < cols; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for(i = 0; i < rows; i++) {
        printf("R%d  ", i);
        for(j = 0; j < cols; j++) {
            if(seats[i][j] == 0) {
                printf("_ ");
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }

    rem_free = 0;
    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++) {
            if(seats[i][j] == 0) {
                rem_free++;
            }
        }
    }
    printf("\nRemaining free seats: %d\n", rem_free);

    return 0;
}
