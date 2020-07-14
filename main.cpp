#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

template<class T>
class vec2 {
public:
    T x, y;

    vec2() : x(0), y(0) {}

    vec2(T x, T y) : x(x), y(y) {}

    vec2(const vec2 &v) : x(v.x), y(v.y) {}

    vec2 &operator=(const vec2 &v) {
        x = v.x;
        y = v.y;
        return *this;
    }

    vec2 operator+(vec2 &v) {
        return vec2(x + v.x, y + v.y);
    }

    vec2 operator-(vec2 &v) {
        return vec2(x - v.x, y - v.y);
    }

    vec2 &operator+=(vec2 &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    vec2 &operator-=(vec2 &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    vec2 operator+(double s) {
        return vec2(x + s, y + s);
    }

    vec2 operator-(double s) {
        return vec2(x - s, y - s);
    }

    vec2 operator*(double s) {
        return vec2(x * s, y * s);
    }

    vec2 operator/(double s) {
        return vec2(x / s, y / s);
    }


    vec2 &operator+=(double s) {
        x += s;
        y += s;
        return *this;
    }

    vec2 &operator-=(double s) {
        x -= s;
        y -= s;
        return *this;
    }

    vec2 &operator*=(double s) {
        x *= s;
        y *= s;
        return *this;
    }

    vec2 &operator/=(double s) {
        x /= s;
        y /= s;
        return *this;
    }

    void set(T x, T y) {
        this->x = x;
        this->y = y;
    }

    void rotate(double deg) {
        double theta = deg / 180.0 * M_PI;
        double c = cos(theta);
        double s = sin(theta);
        double tx = x * c - y * s;
        double ty = x * s + y * c;
        x = tx;
        y = ty;
    }

    vec2 &normalize() {
        if (length() == 0) return *this;
        *this *= (1.0 / length());
        return *this;
    }

    float dist(vec2 v) const {
        vec2 d(v.x - x, v.y - y);
        return d.length();
    }

    float length() const {
        return std::sqrt(x * x + y * y);
    }

    void truncate(double length) {
        double angle = atan2f(y, x);
        x = length * cos(angle);
        y = length * sin(angle);
    }

    vec2 ortho() const {
        return vec2(y, -x);
    }

    static float dot(vec2 v1, vec2 v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    static float cross(vec2 v1, vec2 v2) {
        return (v1.x * v2.y) - (v1.y * v2.x);
    }

    static float distance(vec2 v1, vec2 v2) {
        return v1.dist(v2);
    }

    static float length_squared(vec2 v1, vec2 v2) {
        return pow(distance(v1, v2), 2);
    }

};

typedef vec2<float> vec2f;

float minimum_distance(vec2f v, vec2f w, vec2f p) {
    // Return minimum distance between line segment vw and point p
    const float l2 = vec2f::length_squared(v, w);  // i.e. |w-v|^2 -  avoid a sqrt

    if (l2 == 0.0) return vec2f::distance(p, v);   // v == w case
    // Consider the line extending the segment, parameterized as v + t (w - v).
    // We find projection of point p onto the line.
    // It falls where t = [(p-v) . (w-v)] / |w-v|^2
    // We clamp t from [0,1] to handle points outside the segment vw.
    const double t = max(0.0f, min(1.0f, vec2f::dot(p - v, w - v) / l2));
    const vec2f projection = ((w - v) * t) + v;  // Projection falls on the segment
    return vec2f::distance(p, projection);
}

int main() {
    vec2f line_start(23.49, 12.46);
    vec2f line_end(23.77, 12.90);

    {
        cout << "Test case where the position is well outside (not perpendicular to any point on the line segment.)"
             << endl;
        vec2f position(37.57, 26.72);
        cout << "minimum_distance : " << minimum_distance(line_start, line_end, position) << endl;
    }

    {
        cout << "Test case where the position is well outside (notperpendicular to any point on the line segment.)"
             << endl;
        vec2f position(-37.57, -26.72);
        cout << "minimum_distance : " << minimum_distance(line_start, line_end, position) << endl;
    }

    {
        cout << "Test case where the position is perpendicular to the line segment." << endl;
        vec2f position(23.4, 12.8);
        cout << "minimum_distance : " << minimum_distance(line_start, line_end, position) << endl;
    }
    {
        cout << "Test case where the position is the same as the start_point of the line." << endl;
        vec2f position = line_start;
        cout << "minimum_distance : " << minimum_distance(line_start, line_end, position) << endl;
    }
    {
        cout << "Test case where the position is on the line segment." << endl;
        vec2f position(23.63822, 12.69292);
        cout << "minimum_distance : " << minimum_distance(line_start, line_end, position) << endl;
    }
    return 0;
}