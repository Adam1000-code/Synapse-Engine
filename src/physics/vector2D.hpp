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
        // distance calculation
        inline Vector2D distance(Vector2D& v1, Vector2D& v2) const
        {
            // based off the euclidean distance formula. not sure if I adapted it into code that well. may recode later 
            return Vector2D(v2.X - v1.X, v2.Y - v1.Y);
        }

        void Log(string msg)
        {
            cout << msg << "(X Y) = (" << X << " " << Y << ")" << endl;
        }
};