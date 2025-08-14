#include <graphics.h>
#include <math.h>
#include <stdio.h>

// Add prototype to avoid implicit declaration warning
void closegraph(void);
#include <graphics.h>
#include <math.h>
#include <stdio.h>

void draw_triangle(int x[3], int y[3]) {
    line(x[0], y[0], x[1], y[1]);
    line(x[1], y[1], x[2], y[2]);
    line(x[2], y[2], x[0], y[0]);
}

int main() {
    int gd = DETECT, gm;
    int x[3], y[3], tx_x[3], tx_y[3];
    int i, choice;
    float tx, ty, sx, sy, angle, shx, shy;
    initgraph(&gd, &gm, "");

    // Input triangle coordinates
    printf("Enter coordinates of triangle:\n");
    for (i = 0; i < 3; i++) {
        printf("x%d y%d: ", i+1, i+1);
        scanf("%d %d", &x[i], &y[i]);
        tx_x[i] = x[i];
        tx_y[i] = y[i];
    }

    cleardevice();
    setcolor(15); // WHITE
    draw_triangle(x, y); // Draw original triangle

    printf("\n1. Translation\n2. Scaling\n3. Rotation\n4. Reflection\n5. Shearing\nEnter choice: ");
    scanf("%d", &choice);

    // Copy original points for transformation
    for (i = 0; i < 3; i++) {
        tx_x[i] = x[i];
        tx_y[i] = y[i];
    }

    switch (choice) {
        case 1: // Translation
            printf("Enter tx and ty: ");
            scanf("%f %f", &tx, &ty);
            for (i = 0; i < 3; i++) {
                tx_x[i] = x[i] + tx;
                tx_y[i] = y[i] + ty;
            }
            break;

        case 2: // Scaling
            printf("Enter sx and sy: ");
            scanf("%f %f", &sx, &sy);
            for (i = 0; i < 3; i++) {
                tx_x[i] = x[i] * sx;
                tx_y[i] = y[i] * sy;
            }
            break;

        case 3: // Rotation (about origin)
            printf("Enter angle in degrees: ");
            scanf("%f", &angle);
            angle = angle * 3.14159 / 180;
            for (i = 0; i < 3; i++) {
                tx_x[i] = (int)(x[i] * cos(angle) - y[i] * sin(angle));
                tx_y[i] = (int)(x[i] * sin(angle) + y[i] * cos(angle));
            }
            break;

        case 4: // Reflection
            printf("1.X-axis 2.Y-axis 3.Origin 4.y=x 5.y=-x\nEnter choice: ");
            scanf("%d", &i);
            for (int j = 0; j < 3; j++) {
                int tempX = x[j], tempY = y[j];
                if (i == 1) { tx_x[j] = tempX; tx_y[j] = -tempY; }
                else if (i == 2) { tx_x[j] = -tempX; tx_y[j] = tempY; }
                else if (i == 3) { tx_x[j] = -tempX; tx_y[j] = -tempY; }
                else if (i == 4) { tx_x[j] = tempY; tx_y[j] = tempX; }
                else if (i == 5) { tx_x[j] = -tempY; tx_y[j] = -tempX; }
            }
            break;

        case 5: // Shearing
            printf("Enter shx and shy: ");
            scanf("%f %f", &shx, &shy);
            for (i = 0; i < 3; i++) {
                tx_x[i] = x[i] + shx * y[i];
                tx_y[i] = y[i] + shy * x[i];
            }
            break;
        default:
            printf("Invalid choice!\n");
            getch();
            closegraph();
            return 1;
    }

    // Draw transformed triangle
    setcolor(14); // YELLOW
    draw_triangle(tx_x, tx_y);

    // Add legend
    setcolor(15); // WHITE
    outtextxy(10, 10, "Original Triangle (White)");
    setcolor(14); // YELLOW
    outtextxy(10, 30, "Transformed Triangle (Yellow)");

    getch();
    closegraph();
    return 0;
}
