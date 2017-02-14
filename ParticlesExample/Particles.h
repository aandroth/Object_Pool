#pragma once
#include "Maths.h"
#include "sfwdraw.h"

struct Particle
{
	unsigned sprite;
	vec2 pos, vel;
	vec2 begDim, endDim;
	color begColor, endColor;

	float lifeTime, lifeSpan;
	float angle;
	Particle() : lifeSpan(-1), lifeTime(0), angle(0) {}

	bool refresh(float dt)
	{
		lifeTime += dt;

		float alpha = lifeTime / lifeSpan;

		vec2 dim  = lerp(begDim, endDim, alpha);
		color col = lerp(begColor, endColor, alpha);

		pos = pos + vel * dt;

		sfw::drawTexture(sprite, pos.x, pos.y, dim.x, dim.y, angle, true, 0, col.ui_color);

		return alpha < 1;
	}

	bool isActive() const { return lifeTime < lifeSpan; };
};