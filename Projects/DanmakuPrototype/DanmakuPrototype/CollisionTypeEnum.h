#pragma once
enum class CollisionTypeEnum {
	BEGIN,
	NO_COLLISION = BEGIN,
	PLAYER_PROJECTILE_COLLISION,
	ENEMY_PROJECTILE_COLLISION,
	END = ENEMY_PROJECTILE_COLLISION
};