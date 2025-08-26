// 2D Transformations Visualizer using SFML (basic formulas, no matrices)
// Compile: g++ main.cpp -o transforms -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
using namespace std;

struct Point {
    float x, y;
};

struct Viewport {
    float scale = 1.f;
    Point worldCenter{0.f, 0.f};
    int width = 800, height = 600;
};

Viewport computeViewport(const vector<Point>& A, const vector<Point>& B, int W, int H) {
    float xmin = 1e9, xmax = -1e9, ymin = 1e9, ymax = -1e9;
    auto mix = [&](const vector<Point>& V) {
        for (auto& p : V) {
            xmin = min(xmin, p.x);
            xmax = max(xmax, p.x);
            ymin = min(ymin, p.y);
            ymax = max(ymax, p.y);
        }
    };
    mix(A); mix(B);

    float w = max(1e-3f, xmax - xmin);
    float h = max(1e-3f, ymax - ymin);
    float scale = 0.8f * min(W / w, H / h);

    Viewport vp;
    vp.scale = scale;
    vp.worldCenter = {(xmin + xmax) * 0.5f, (ymin + ymax) * 0.5f};
    vp.width = W; vp.height = H;
    return vp;
}

sf::Vector2f toScreen(const Point& world, const Viewport& vp) {
    float sx = (world.x - vp.worldCenter.x) * vp.scale + vp.width * 0.5f;
    float sy = vp.height * 0.5f - (world.y - vp.worldCenter.y) * vp.scale;
    return {sx, sy};
}

// ---- Transformation functions ----
vector<Point> translate(const vector<Point>& tri, float tx, float ty) {
    vector<Point> res;
    for (auto p : tri) res.push_back({p.x + tx, p.y + ty});
    return res;
}

vector<Point> scale(const vector<Point>& tri, float sx, float sy) {
    vector<Point> res;
    for (auto p : tri) res.push_back({p.x * sx, p.y * sy});
    return res;
}

vector<Point> rotate(const vector<Point>& tri, float deg) {
    float rad = deg * M_PI / 180.0;
    float c = cos(rad), s = sin(rad);
    vector<Point> res;
    for (auto p : tri) {
        float x = p.x * c - p.y * s;
        float y = p.x * s + p.y * c;
        res.push_back({x, y});
    }
    return res;
}

vector<Point> reflect(const vector<Point>& tri, int type) {
    vector<Point> res;
    for (auto p : tri) {
        if (type == 1) res.push_back({p.x, -p.y});        // X-axis
        else if (type == 2) res.push_back({-p.x, p.y});   // Y-axis
        else if (type == 3) res.push_back({-p.x, -p.y});  // Origin
        else if (type == 4) res.push_back({p.y, p.x});    // y = x
        else if (type == 5) res.push_back({-p.y, -p.x});  // y = -x
    }
    return res;
}

vector<Point> shear(const vector<Point>& tri, float shx, float shy) {
    vector<Point> res;
    for (auto p : tri) {
        float x = p.x + shx * p.y;
        float y = p.y + shy * p.x;
        res.push_back({x, y});
    }
    return res;
}

int main() {
    cout << "Enter triangle coordinates (x y) for 3 points:\n";
    vector<Point> tri(3);
    for (int i = 0; i < 3; i++) {
        cout << "P" << i+1 << ": ";
        cin >> tri[i].x >> tri[i].y;
    }

    cout << "\nChoose transformation:\n"
         << "1. Translation\n2. Scaling\n3. Rotation\n4. Reflection\n5. Shearing\n> ";
    int choice; cin >> choice;

    vector<Point> tri2;
    if (choice == 1) {
        float tx, ty; cout << "tx ty: "; cin >> tx >> ty;
        tri2 = translate(tri, tx, ty);
    } else if (choice == 2) {
        float sx, sy; cout << "sx sy: "; cin >> sx >> sy;
        tri2 = scale(tri, sx, sy);
    } else if (choice == 3) {
        float ang; cout << "angle (deg): "; cin >> ang;
        tri2 = rotate(tri, ang);
    } else if (choice == 4) {
        cout << "Reflect across: 1.X-axis 2.Y-axis 3.Origin 4.y=x 5.y=-x : ";
        int r; cin >> r;
        tri2 = reflect(tri, r);
    } else if (choice == 5) {
        float shx, shy; cout << "shx shy: "; cin >> shx >> shy;
        tri2 = shear(tri, shx, shy);
    } else {
        cout << "Invalid choice.\n"; return 0;
    }

    const int W = 900, H = 700;
    sf::RenderWindow window(sf::VideoMode(W, H), "2D Transformations (Original: White, Transformed: Yellow)");
    window.setFramerateLimit(60);

    Viewport vp = computeViewport(tri, tri2, W, H);

    auto makeShape = [&](const vector<Point>& pts, sf::Color outline) {
        sf::ConvexShape s; s.setPointCount(3);
        for (int i = 0; i < 3; i++) s.setPoint(i, toScreen(pts[i], vp));
        s.setFillColor(sf::Color(0,0,0,0));
        s.setOutlineColor(outline);
        s.setOutlineThickness(2.f);
        return s;
    };

    sf::ConvexShape original = makeShape(tri, sf::Color::White);
    sf::ConvexShape transformed = makeShape(tri2, sf::Color::Yellow);

    cout << "\nLegend: Original = White, Transformed = Yellow\nClose the window to exit.\n";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color(20, 24, 31));
        window.draw(original);
        window.draw(transformed);
        window.display();
    }
    return 0;
}
