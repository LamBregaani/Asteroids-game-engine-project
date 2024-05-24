#ifndef ASTEROIDS_VECTOR_2_H
#define ASTEROIDS_VECTOR_2_H
namespace Asteroids
{
	struct Vector2
	{
	public:
		float x = 0;
		float y = 0;

		Vector2() {}

		Vector2(float xin, float yin)
			:x(xin),
			y(yin)
		{

		}

		Vector2 operator + (const Vector2& rhs) const
		{
			return Vector2(x + rhs.x, y + rhs.y);
		}


		Vector2 operator - (const Vector2& rhs) const
		{
			return Vector2(x - rhs.x, y - rhs.y);
		}

		Vector2 operator * (float rhs) const
		{
			return Vector2(x * rhs, y * rhs);
		}

		Vector2 operator / (float rhs) const
		{
			return Vector2(x / rhs, y / rhs);
		}

		bool operator == (const Vector2& rhs)
		{
			if (x == rhs.x && y == rhs.y)
				return true;

			return false;

		}

		bool operator != (const Vector2& rhs)
		{
			if (x != rhs.x || y != rhs.y)
				return true;

			return false;

		}

		void operator += (const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
		}

		Vector2 Zero()
		{
			return Vector2(0, 0);
		}

		Vector2& Scale(float s)
		{
			x *= s;
			y *= s;
			return *this;
		}

		static float Distance(Vector2& a, Vector2& b);

		static Vector2& Direction(Vector2& origin, Vector2& target);

		static Vector2& Normalized(Vector2& vec);

		Vector2& normalized();
	};
}
#endif
