#pragma once
#include <random>
#include <math.h>

inline float rand01() { return (float)rand() / RAND_MAX; }

inline float lerp(float A, float B, float t) { return A*(1 - t) + B*t; }

#define DEG2RAD 0.0174533

struct vec2
{
public:
	float x, y;
};

vec2 operator+(const vec2 &lhs, const vec2 &rhs)
{
	return vec2{ lhs.x + rhs.x, lhs.y + rhs.y };
}

vec2 operator-(const vec2 &lhs, const vec2 &rhs)
{
	return vec2{ lhs.x - rhs.x, lhs.y - rhs.y };
}

inline vec2 operator*(const vec2 &lhs, float b)
{
	return vec2{ lhs.x * b, lhs.y * b };
}

bool operator==(const vec2 &lhs, const vec2 &rhs)
{
	return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator!=(const vec2 &lhs, const vec2 &rhs)
{
	return !(lhs == rhs);
}

inline vec2 lerp(const vec2 &A, const vec2 &B, float t)
{
	return A*(1 - t) + B*t;
}

inline vec2 randRange(const vec2 &A, const vec2 &B)
{
	return vec2{ lerp(A.x, B.x, rand01()), lerp(A.y, B.y, rand01()) };
}
//
//inline vec2 randRangeLinear(const vec2 &A, const vec2 &B)
//{
//	return lerp()
//}

inline vec2 randDir(float min_deg, float max_deg)
{
	float deg = lerp(min_deg, max_deg, rand01());
	float rad = DEG2RAD * deg;

	return vec2{ cos(rad), sin(rad) };
}


// Find the angle of the vector (2D only!)
float angle(const vec2 &v)
{
	return (atan2f(v.y, v.x)) / DEG2RAD;
}

union color
{
public:
	unsigned ui_color;
	struct { unsigned char a, b, g, r; };
};

// 0xRR GG BB AA
inline color lerp(const color &A, const color &B, const float t)
{
	color ret_color;
	ret_color.r = A.r*(1 - t) + B.r*t;
	ret_color.g = A.g*(1 - t) + B.g*t;
	ret_color.b = A.b*(1 - t) + B.b*t;
	ret_color.a = A.a*(1 - t) + B.a*t;
	return ret_color;
}

inline vec2 normal(const vec2 &A)
{
	float D = sqrt(A.x*A.x + A.y*A.y);
	return (vec2{A.x/D, A.y/D});
}