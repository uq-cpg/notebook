#pragma once

#include <bits/stdc++.h>
#include "point.hpp"
#include "geoutil.hpp"
#include "../maths/euclidean.hpp"

using namespace std;

template <typename T>
struct Polygon {
    using P = Point<T>;

    int n = 0;
    vector<P> ps;
    Polygon() : n(0) {}
    Polygon(vector<P>& ps) : n(ps.size()), ps(ps) {}

    void add(P p) {
        ps.push_back(p);
        n++;
    }

    int64_t twiceArea() {
        int64_t area = 0;
        for (int i = 0; i < n; i++) {
            P p1 = ps[i];
            P p2 = ps[inc(i, n)];
            area += p1.cross(p2);
        }
        return abs(area);
    }

    double area() {
        return twiceArea() / 2.0;
    }

    int64_t boundaryLattice() {
        int64_t res = 0;
        for (int i = 0; i < n; i++) {
            int j = i + 1; if (j == n) j = 0;
            P p1 = ps[i];
            P p2 = ps[j];
            P v = p2 - p1;
            res += gcd(abs(v.x), abs(v.y));
        }
        return res;
    }

    int64_t interiorLattice() {
        return (twiceArea() - boundaryLattice()) / 2 + 1;
    }

    bool isConvex() {
        int pos = 0;
        int neg = 0;

        for (int i = 0; i < n; i++) {
            P p1 = ps[i];
            P p2 = ps[inc(i, n, 1)];
            P p3 = ps[inc(i, n, 2)];
            int o = orient(p1, p2, p3);
            if (o > 0) pos = 1;
            if (o < 1) neg = 1;
        }

        return pos ^ neg;
    }

    // -1: outside; 1: inside; 0: on boundary
    int vsPoint(P r) {
        int crossing = 0;
        for (int i = 0; i < n; i++) {
            P p1 = ps[i];
            P p2 = ps[inc(i, n)];
            if (onSegment(p1, p2, r)) {
                return 0;
            }
            if (((p2.y >= r.y) - (p1.y >= r.y)) * orient(r, p1, p2) > 0) {
                crossing++;
            }
        }
        if (crossing & 1) return 1;
        return -1;
    }
};

template <typename T>
Polygon<T> convexHull(vector<Point<T>> points) {
    using P = Point<T>;

    sort(points.begin(), points.end(),
         [](const P& p1, const P& p2) {
             if (p1.x == p2.x) return p1.y < p2.y;
             return p1.x < p2.x;
         });

    vector<P> hull;

    for (int step = 0; step < 2; step++) {
        int s = hull.size();
        for (const P& c : points) {
            while ((int) hull.size() - s >= 2) {
                P a = hull.end()[-2];
                P b = hull.end()[-1];
                // <= if points on the edges are accepted, < otherwise
                if (orient(a, b, c) <= 0) break;
                hull.pop_back();
            }
            hull.push_back(c);
        }
        hull.pop_back();
        reverse(points.begin(), points.end());
    }

    return Polygon<T>(hull);
}
