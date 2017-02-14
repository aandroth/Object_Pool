#include "sfwdraw.h"
#include "Maths.h"
#include <iostream>
using std::cout;
#include "ParticleEmitter.h"
#include "ObjectPool.h"
#include "Factory.h"
#include <time.h>

int main()
{
	srand(time(NULL));
	sfw::initContext();
	unsigned sprite = sfw::loadTextureMap("../res/star.png");
	unsigned BG     = sfw::loadTextureMap("../res/background.png");

	ParticleEmitter p;

	p.sprite = sprite;
	p.emitRateLo = 0.0005f;
	p.emitRateHi = 0.001f;
	p.pos = p.travel_to = vec2{ 400, 300 };
	p.angleLo = 0;
	p.angleHi = 360;
	p.speedLo = 300;
	p.speedHi = 500;
	p.dimLoBeg = vec2{ 2, 1 };
	p.dimLoEnd = vec2{ 5, 2 };
	p.dimHiBeg = vec2{ 500, 3 };
	p.dimHiEnd = vec2{ 700, 5 };
	p.colorLoBeg.ui_color = CYAN;
	p.colorHiBeg.ui_color = WHITE;
	p.colorLoEnd.ui_color = BLUE;
	p.colorHiEnd.ui_color = CYAN;
	p.lifeSpanLo = 2;
	p.lifeSpanHi = 4;

	vec2 mouse_pos = vec2{ sfw::getMouseX(), sfw::getMouseY() };

	float timer = 0;

	//Factory factory;


	while (sfw::stepContext())
	{
		//p.emit();

		sfw::drawTexture(BG, 0, 0, 1600, 1200, 0, true, 0, BLACK);
		float t = sfw::getDeltaTime();
		p.update(t);

		if (mouse_pos != vec2{ sfw::getMouseX(), sfw::getMouseY() })
		{
			mouse_pos = vec2{ sfw::getMouseX(), sfw::getMouseY() };
			p.retargetTravelTo();
		}

		//for (auto e = factory.begin(); e != factory.end();)
		//{
		//	if (e->sprite)
		//	{
		//		e->sprite->draw(e->trans);

		//		if (e->life)
		//		{
		//			e->life->age(t);
		//			if (!e->life->isAlive())
		//			{
		//				//factory.destroy(e);
		//				continue;
		//			}
		//		}
		//	}
		//	++e;
		//}
	}

	return 0;
}