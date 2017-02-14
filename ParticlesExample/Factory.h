#pragma once

#include "Components.h"

struct entity
{
	class Factory *factory;
	ObjectPool<transform>::iterator  trans;
	ObjectPool<rigidbody>::iterator  rb;
	ObjectPool<controller>::iterator cntlr;
	ObjectPool<sprite>::iterator     sprite;
	ObjectPool<lifetime>::iterator   life;
	ObjectPool<particle>::iterator   parti;

	void onFree()
	{
		if (trans)  trans.free();
		if (rb)     rb.free();
		if (cntlr)  cntlr.free();
		if (sprite) sprite.free();
		if (life)   life.free();
		if (parti)  parti.free();
	}
};

class Factory
{
	ObjectPool<entity>     entities;
	ObjectPool<transform>  transforms;
	ObjectPool<rigidbody>  rigidbodies;
	ObjectPool<controller> controllers;
	ObjectPool<sprite>     sprites;
	ObjectPool<lifetime>   lifetimes;
	ObjectPool<particle>   particles;

public:

	Factory() : entities(512), transforms(512), rigidbodies(512), controllers(512),
				sprites(512), lifetimes(512), particles(512) 
	{}

	ObjectPool<entity>::iterator destroy(ObjectPool<entity>::iterator &h) { h->onFree(); return h.free(); }

	ObjectPool<entity>::iterator begin() { return entities.begin(); }
	ObjectPool<entity>::iterator end()   { return entities.end(); }

	ObjectPool<entity>::iterator spawnStaticImage(unsigned sprite_id, float x, float y, float w, float h, float time = -1)
	{
		ObjectPool<entity>::iterator retVal = entities.push();
		if (!retVal) return retVal;

		retVal->factory = this;

		retVal->trans  = transforms.push();
		retVal->sprite = sprites.push();

		retVal->trans->pos        = vec2{ x, y };
		retVal->trans->scale      = vec2{ w, h };
		retVal->sprite->sprite_id = sprite_id;

		if (time = 0)
		{
			retVal->life = lifetimes.push();
			retVal->life->time = time;
		}

		return retVal;
	}

	ObjectPool<entity>::iterator spawnMouseAttractor(unsigned sprite_id)
	{
		ObjectPool<entity>::iterator retVal = entities.push();
		if (!retVal) return retVal;
		retVal->factory = this;

		retVal->trans  = transforms.push();
		retVal->sprite = sprites.push();
		retVal->cntlr  = controllers.push();
		retVal->rb     = rigidbodies.push();

		retVal->trans->pos =   vec2{ 400, 300 };
		retVal->trans->scale = vec2{ 32, 32 };
		retVal->sprite->sprite_id = sprite_id;
		retVal->sprite->tint.ui_color = WHITE;
		
		retVal->cntlr->speed = 60;
		
		return retVal;
	}
};