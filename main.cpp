/*
Copyright (c) 2020 Mihir Patel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <iostream>
#include "vec2.h"
using namespace std;

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