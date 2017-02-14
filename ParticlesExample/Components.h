#pragma once

#include "Maths.h"
#include "ObjectPool.h"
#include "sfwdraw.h"

struct transform
{
	vec2 pos, scale;
	float angle;
};

struct rigidbody
{
	vec2 velocity, acceleration;
	void integrate(transform&T, float t)
	{
		velocity = velocity + acceleration * t;
		T.pos = velocity * t;
	}
};

struct lifetime
{
	float time = 0, lifespan;

	void age(float t) { time += t; }
	bool isAlive() const { time < lifespan; }
	float pctAlive() const { return time / lifespan; }
};

struct sprite
{
	size_t sprite_id;
	color tint = { WHITE };

	void draw(transform &T)
	{
		sfw::drawTexture(sprite_id, T.pos.x, T.pos.y, T.scale.x, T.scale.y, T.angle, true, 0, tint.ui_color);
	}
};

struct controller
{
	float speed;
	void poll(transform &T, rigidbody &RB)
	{
		vec2 mouse = vec2{ sfw::getMouseX(), sfw::getMouseY() };

		RB.acceleration = normal(mouse - T.pos) * speed;
	}
};

struct particle
{
	vec2 sDim, eDim;
	color sColor, eColor;
	
	void update(const lifetime &life, transform &trans, sprite sprt)
	{
		trans.scale = lerp(sDim, eDim, life.pctAlive());
		sprt.tint =   lerp(sColor, eColor, life.pctAlive());
	}
};
