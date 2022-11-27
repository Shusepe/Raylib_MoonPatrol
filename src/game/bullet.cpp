#include "bullet.h"

#include <iostream>

namespace MoonPatrol {
	namespace Bullets {

		// Private
		
		static char shootSfx[] = "sfx/alienshoot1.wav";

		void move(Bullet& bullet);
		 
		// --

		void move(Bullet& bullet) {
			bullet.position.x += bullet.speed * cosf(bullet.directionAngle) * GetFrameTime();
			bullet.position.y += bullet.speed * sinf(bullet.directionAngle) * GetFrameTime();
		}

		// Public

		Bullet create() {
			Bullet bullet;
			bullet.position = { 0, 0 };
			bullet.radius = 0;
			bullet.directionAngle = 0;
			bullet.speed = 0;
			bullet.hurtsPlayer = 0;
			return bullet;
		}

		void draw(Bullet bullet) {
			DrawCircle(static_cast<int>(bullet.position.x), static_cast<int>(bullet.position.y), bullet.radius, WHITE);
		}

		void update(Bullet& bullet) {
			move(bullet);
		}

		void playSound(Bullet bullet) {
			SetSoundPitch(bullet.shootSound, static_cast<float>((GetRandomValue(0, 15) / 100) + 1));
			PlaySound(bullet.shootSound);
		}

		void init(Bullet& bullet, Vector2 position, float radius, float directionAngle, float speed, bool hurtsPlayer) {
			bullet = create();
			bullet.position = position;
			bullet.radius = radius;
			bullet.directionAngle = directionAngle;
			bullet.speed = speed;
			bullet.hurtsPlayer = hurtsPlayer;
			bullet.shootSound = LoadSound(shootSfx);

			playSound(bullet);
		}

	}
}