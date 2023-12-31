#pragma once
#include <cmath>


namespace sb::math
{
#define PI 3.141592f
	struct Vector2
	{
		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Up;

		float x;
		float y;

		Vector2()
			: x(0.0f)
			, y(0.0f)
		{

		}
		Vector2(float _x, float _y)
			: x(_x)
			, y(_y)
		{

		}
        Vector2 operator -()
        {
            return Vector2(-x, -y);
        }

        Vector2 operator+(const Vector2& other)
        {
            Vector2 temp;
            temp.x = x + other.x;
            temp.y = y + other.y;

            return temp;
        }

        Vector2 operator-(const Vector2& other)
        {
            Vector2 temp;
            temp.x = x - other.x;
            temp.y = y - other.y;

            return temp;
        }

        Vector2 operator*(const Vector2& other)
        {
            Vector2 temp;
            temp.x = x * other.x;
            temp.y = y * other.y;

            return temp;
        }

        Vector2 operator*(const float& value)
        {
            Vector2 temp;
            temp.x = x * value;
            temp.y = y * value;

            return temp;
        }

        Vector2 operator/(const float& value)
        {
            Vector2 temp;

            temp.x = x / value;
            temp.y = y / value;

            return temp;
        }

        Vector2& operator +=(const Vector2& other)
        {
            x += other.x;
            y += other.y;

            return *this;
        }

        Vector2& operator -=(const Vector2& other)
        {
            x -= other.x;
            y -= other.y;

            return *this;
        }

        Vector2& operator *=(const float& value)
        {
            x *= value;
            y *= value;

            return *this;
        }

        bool operator ==(const Vector2& other) const
        {
            return (x == other.x && y == other.y);
        }

        bool operator !=(const Vector2& other) const
        {
            return (x != other.x && y != other.y);
        }
        void clear()
        {
            x = 0.0f;
            y = 0.0f;
        }

        float length()
        {
            return sqrtf(x * x + y * y);
        }

        Vector2 normalize()
        {
            float len = length();
            x /= len;
            y /= len;

            return *this;
        }
    };

    inline Vector2 Rotate(Vector2 vector, float degree)
    {
        float radian = (degree / 180.f) * PI;
        vector.normalize();
        float x = cosf(radian) * vector.x - sinf(radian) * vector.y;
        float y = sinf(radian) * vector.x + cosf(radian) * vector.y;

        return Vector2(x, y);
    }

    inline Vector2 BulletRotate(Vector2 vector, float degree, float speed, bool direct)
    {
        vector.x += speed * cos(degree * (PI / 180));
        if (direct == true)
        vector.y -= speed * sin(degree * (PI / 180));
        else
        vector.y += speed * sin(degree * (PI / 180));

        return vector;
    }


    inline Vector2 BulletRotate2(Vector2 vector, float degree, float speed)
    {
        vector.x += speed * cos(degree * (PI / 180));
        vector.y -= speed * sin(degree * (PI / 180));
        return vector;
    }


    inline float Dot(Vector2& v1, Vector2& v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    inline float Cross(Vector2 v1, Vector2 v2)
    {
        return v1.x * v2.y - v1.y * v2.x;
    }
}