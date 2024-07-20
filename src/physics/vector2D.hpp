#pragma once

#include <iostream>
#include <string>

using namespace std;

class Vector2D
{
    public:
        float X, Y;

    public:
        Vector2D(float x = 0, float y = 0): X(x), Y(y)
        {
        }
    
    public:
        // addition
        inline Vector2D operator+(const Vector2D& v2) const
        {
            return Vector2D(X + v2.X, Y + v2.Y);
        }
        // subtraction
        inline Vector2D operator-(const Vector2D& v2) const
        {
            return Vector2D(X - v2.X, Y - v2.Y);
        }
        // multiplication
        inline Vector2D operator*(const float scalar) const
        {
            return Vector2D(X * scalar, Y * scalar);
        }

        void Log(string msg)
        {
            cout << msg << "(X Y) = (" << X << " " << Y << ")" << endl;
        }
};