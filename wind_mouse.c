#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

double sqrt3, sqrt5;

void init_constants() {
    sqrt3 = sqrt(3);
    sqrt5 = sqrt(5);
}

void wind_mouse(int start_x, int start_y, int dest_x, int dest_y, double G_0, double W_0, double M_0, double D_0) {
    int current_x = start_x;
    int current_y = start_y;
    double v_x = 0, v_y = 0, W_x = 0, W_y = 0;

    while (1) {
        double dist = sqrt(pow(dest_x - start_x, 2) + pow(dest_y - start_y, 2));

        if (dist < 1) {
            break;
        }

        double W_mag = fmin(W_0, dist);

        if (dist >= D_0) {
            W_x = W_x / sqrt3 + ((2.0 * rand() / RAND_MAX) - 1) * W_mag / sqrt5;
            W_y = W_y / sqrt3 + ((2.0 * rand() / RAND_MAX) - 1) * W_mag / sqrt5;
        } else {
            W_x /= sqrt3;
            W_y /= sqrt3;
            if (M_0 < 3) {
                M_0 = (3 + (rand() / (double)RAND_MAX) * 3);
            } else {
                M_0 /= sqrt5;
            }
        }

        v_x += W_x + G_0 * (dest_x - start_x) / dist;
        v_y += W_y + G_0 * (dest_y - start_y) / dist;

        double v_mag = sqrt(v_x * v_x + v_y * v_y);
        if (v_mag > M_0) {
            double v_clip = M_0 / 2 + (rand() / (double)RAND_MAX) * M_0 / 2;
            v_x = (v_x / v_mag) * v_clip;
            v_y = (v_y / v_mag) * v_clip;
        }

        start_x += v_x;
        start_y += v_y;
    }

    printf("Final position: %d, %d\n", start_x, start_y);
}

int main() {
    // Seed the random number generator
    srand(time(NULL));
    init_constants();

    int start_x = 0;
    int start_y = 0;
    int dest_x = 100;
    int dest_y = 50;
    double G_0 = 9.0;
    double W_0 = 3.0;
    double M_0 = 15.0;
    double D_0 = 12.0;

    wind_mouse(start_x, start_y, dest_x, dest_y, G_0, W_0, M_0, D_0);

    return 0;
}
