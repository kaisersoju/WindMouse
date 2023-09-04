# ChatGPT helped me code an aimbot faster

I was looking into novel a way of making an existing aimbot more human-like and found an ideal candidate: [https://ben.land/post/2021/04/25/windmouse-human-mouse-movement/](https://ben.land/post/2021/04/25/windmouse-human-mouse-movement/)

WindMouse is pretty interesting and I wanted to try it out. Except I had one small problem. My existing aimbot was coded in c++ so I would need to translate python code to c++ before I can even begin. And that to me didn’t seem very fun or very good use of my time. I heard somewhere that ChatGPT has a knack for doing this type of work so I fired up the bot and quickly got this:

```
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
```
I recommend you take ChatGPT for a spin the next time you want to explore some low effort coding because you’ll very likely gain from the time saved by trying it. I asked ChatGPT how to translate python to c followed by prompting it with the full python code. Of course, one shouldn’t just trust ChatGPT’s word for it and paste code. There’s a few things to consider. 

This code presents mouse movements as absolute positions to your screen because WindMouse was originally intended for Runescape. For such use cases, it likely might be a simple matter of replacing line 54 with your mouse function. If you read over the cited link above then you’ll see how convincing it looks.

However, sometimes your mouse movement is presented as relative positions such as in my case. That means your starting position is likely the center of your screen and your target is relative to the distance from your crosshair. The take away from that is your relative mouse function won’t be taking start_x and start_y as inputs. Instead it should be taking v_x and v_y as inputs.

I would like to conclude that wind_mouse for c/c++ is pretty cool and worked quite nicely result-wise. There’s probably areas you might need refining for your specific needs to get this code to perform to your expectation. Credit completely goes to the author Benjamin Land for his original work (which has GPLv3 restrictions). ChatGPT of course provided another massive productivity bonus by spitting out translated code in a matter of seconds. I was going through a phase where use of my time was not effective and limited but I also had ideas I wanted to explore without expending heavy commitments like converting code. I hope you find this post helpful even though nothing new is really being shared here. 

:::

Notes: I used ekknod’s EC base for features including the basic smoothing for aim that I supplemented with this wind_mouse function. My goal wasn’t to get a super accurate or fast aiming but to make the aimbot less distinguishable from my own mouse movements when manually reviewed (as if that’s any real concern for any of us). Lot’s of you might think you need ML to create a humanized version but this old code proves that a few simple physics formulas works just as well. To this end, I’ve scratched an itch. Maybe ChatGPT will do the same for you?

[https://streamable.com/1rbce4?src=player-page-share](https://streamable.com/1rbce4?src=player-page-share)
