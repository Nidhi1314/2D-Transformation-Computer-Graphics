#include <stdio.h>
#include <math.h>

struct Point {
    float x, y;
};

void display(struct Point p1, struct Point p2, struct Point p3) {
    printf("\noutput:");
    printf("Triangle coordinates:\n");
    printf("(%.2f, %.2f)\n", p1.x, p1.y);
    printf("(%.2f, %.2f)\n", p2.x, p2.y);
    printf("(%.2f, %.2f)\n", p3.x, p3.y);
}

int main() {
    struct Point p1, p2, p3;
    int choice;
    float tx, ty, sx, sy, angle, shx, shy, rad;

    printf("Enter coordinates of triangle vertices:\n");
    scanf("%f%f%f%f%f%f", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);

    while (1) {
        printf("\n--- 2D Transformations ---\n");
        printf("1. Translation\n2. Scaling\n3. Rotation\n4. Reflection\n5. Shearing\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 6) break;

        switch (choice) {
        case 1: // Translation
            printf("Enter tx, ty: ");
            scanf("%f%f", &tx, &ty);
            p1.x += tx; p1.y += ty;
            p2.x += tx; p2.y += ty;
            p3.x += tx; p3.y += ty;
            break;

        case 2: // Scaling
            printf("Enter sx, sy: ");
            scanf("%f%f", &sx, &sy);
            p1.x *= sx; p1.y *= sy;
            p2.x *= sx; p2.y *= sy;
            p3.x *= sx; p3.y *= sy;
            break;

        case 3: // Rotation
            printf("Enter angle in degrees: ");
            scanf("%f", &angle);
            // Use a defined value for pi if M_PI is not available
            rad = angle * 3.14159265358979323846 / 180;
            {
                float x1 = p1.x*cos(rad) - p1.y*sin(rad);
                float y1 = p1.x*sin(rad) + p1.y*cos(rad);
                float x2 = p2.x*cos(rad) - p2.y*sin(rad);
                float y2 = p2.x*sin(rad) + p2.y*cos(rad);
                float x3 = p3.x*cos(rad) - p3.y*sin(rad);
                float y3 = p3.x*sin(rad) + p3.y*cos(rad);
                p1.x = x1; p1.y = y1;
                p2.x = x2; p2.y = y2;
                p3.x = x3; p3.y = y3;
            }
            break;

        case 4: // Reflection
            printf("Reflect over:\n1. X-axis\n2. Y-axis\n3. Origin\n");
            int opt;
            scanf("%d", &opt);
            if (opt == 1) { p1.y = -p1.y; p2.y = -p2.y; p3.y = -p3.y; }
            else if (opt == 2) { p1.x = -p1.x; p2.x = -p2.x; p3.x = -p3.x; }
            else if (opt == 3) { p1.x = -p1.x; p1.y = -p1.y; p2.x = -p2.x; p2.y = -p2.y; p3.x = -p3.x; p3.y = -p3.y; }
            break;

        case 5: // Shearing
            printf("Enter shx, shy: ");
            scanf("%f%f", &shx, &shy);
            {
                float x1 = p1.x + shx * p1.y;
                float y1 = p1.y + shy * p1.x;
                float x2 = p2.x + shx * p2.y;
                float y2 = p2.y + shy * p2.x;
                float x3 = p3.x + shx * p3.y;
                float y3 = p3.y + shy * p3.x;
                p1.x = x1; p1.y = y1;
                p2.x = x2; p2.y = y2;
                p3.x = x3; p3.y = y3;
            }
            break;

        default:
            printf("Invalid choice!\n");
        }

        display(p1, p2, p3);
    }

    return 0;
}
