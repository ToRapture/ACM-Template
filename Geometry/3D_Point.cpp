#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;
typedef long long LL;

const double eps = 1e-6;
const double pi = acos(-1.0);
const int inf = 0x7F7F7F7F;

inline int dcmp(const double &x) { return x > eps ? 1 : (x < -eps ? -1 : 0); }
inline double sqr(const double &x) { return x * x; }

struct Point {
    double x, y, z;
    Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    Point operator - (const Point &rhs) const { return Point(x - rhs.x, y - rhs.y, z - rhs.z); }
    Point operator + (const Point &rhs) const { return Point(x + rhs.x, y + rhs.y, z + rhs.z); }
    Point operator / (double scale) const { return Point(x / scale, y / scale, z / scale); }
    Point operator * (double scale) const { return Point(x * scale, y * scale, z * scale); }
    double operator * (const Point &rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
    Point operator ^ (const Point &rhs) const { return Point(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x); }
    Point operator -= (const Point &rhs) { return *this = *this - rhs; }
    Point operator += (const Point &rhs) { return *this = *this + rhs; }
    Point operator /= (double scale) { return *this = *this / scale; }
    Point operator *= (double scale) { return *this = *this * scale; }

    bool operator == (const Point &rhs) const {
        return dcmp(x - rhs.x) == 0 && dcmp(y - rhs.y) == 0 && dcmp(z - rhs.z) == 0;
    }
    double vlen() const { return sqrt(sqr(x) + sqr(y) + sqr(z)); }

    bool read() { return scanf("%lf%lf%lf", &x, &y, &z) == 3; }
    void print() const { printf("(%.2f, %.2f, %.2f)\n", x, y, z); }
};
typedef Point Vector;

inline double Dist(const Point &A, const Point &B) { return sqrt(sqr(A.x - B.x) + sqr(A.y - B.y) + sqr(A.z - B.z)); }
Point Cross(Vector A, Vector B) {
    return A ^ B;
}

Point Cross(Point O, Point A, Point B) {
    return Cross(A - O, B - O);
}
double Dot(Vector A, Vector B) { return A * B; }
double Angle(Vector A, Vector B) { return acos(A * B / A.vlen() / B.vlen()); }
double Length(Vector A) { return A.vlen(); }
double DistanceToPlane(const Point &P, const Point &P0, const Vector &n) {
    return fabs(Dot(P - P0, n));
}
Point GetPlaneProjection(const Point &P, const Point &P0, const Vector &n) {
    return P - n * Dot(P - P0, n);
}
Point LinePlaneIntersection(Point p1, Point p2, Point p0, Vector n) { //假定交点唯一存在
    Vector v = p2 - p1;
    double t = Dot(n, p0 - p1) / Dot(n, p2 - p1);   // 判断分母是否为0
    return p1 + v * t;  // 如果是线段，判断t是不是在0和1之间
}
double Area2(Point A, Point B, Point C) {
    return Length(Cross(B - A, C - A));
}
bool PointInTri(Point P, Point P0, Point P1, Point P2) {    // P必须在P0，P1，P2所确定的平面内
    double area1 = Area2(P, P0, P1);
    double area2 = Area2(P, P1, P2);
    double area3 = Area2(P, P2, P0);
    return dcmp(area1 + area2 + area3 - Area2(P0, P1, P2)) == 0;
}
bool TriSegIntersection(Point P0, Point P1, Point P2, Point A, Point B, Point &P) { //没有考虑线段在平面上的情况
    Vector n = Cross(P1 - P0, P2 - P0);
    if(dcmp(Dot(n, B - A)) == 0) return false;
    else {
        double t = Dot(n, P0 - A) / Dot(n, B - A);
        if(dcmp(t) < 0 || dcmp(t - 1) > 0) return false;
        P = A + (B - A) * t;
        return PointInTri(P, P0, P1, P2);
    }
}
double DistanceToLine(Point P, Point A, Point B) {
    Vector v1 = B - A, v2 = P - A;
    return Length(Cross(v1, v2) / Length(v1));
}
double DistanceToSegment(Point P, Point A, Point B) {
    if(A == B) return Length(P - A);
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if(dcmp(Dot(v1, v2)) > 0) return Length(v3);
    else return Length(Cross(v1, v2)) / Length(v1);
}
double Volume6(Point A, Point B, Point C, Point D) {
    return Dot(D - A, Cross(B - A, C - A));
}

/*------------Template---------------*/


int main(int argc, char **argv) {

    return 0;
}

