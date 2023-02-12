#include "Object.hpp"

#include "./BaseData.hpp"
#include <Render/Resource.hpp>

Box::Box() : position(ZeroVector2), radius(ZeroVector2)
{
}

Box::Box(const Vector2 &position, const Vector2 &radius) : position(position), radius(radius)
{
}

Ball::Ball() : position(ZeroVector2), radius(ZeroVector2)
{
}

Ball::Ball(const Vector2 &position, const Vector2 &radius) : position(position), radius(radius)
{
}


Object::Object() : prePosition(position), velocity(ZeroVector2), acceleration(ZeroVector2), facing(ZeroVector2), spriteBox({ 0,0 }, { 0,0 }, { 1,1 }), isGround(false)
{
}

Object::Object(const Vector2 &position, const Vector2 &radius, const float &scale) :Ball(position, radius), prePosition(position), velocity(ZeroVector2), acceleration(ZeroVector2), facing(ZeroVector2), spriteBox{ ZeroVector2, radius , { scale, scale } }, isGround(false)
{
}



void Object::Init() {
	position = Vector2{ 0,0 };
	radius = Vector2{ 32,32 };

	isAlive = true;
	velocity.Reset();
	acceleration.Reset();
}

void Object::Update() {

	Move();

}

void Object::Move() {

	//	velocity.y -= 0.5f;


	velocity += acceleration;
	position += velocity;

	acceleration.Reset();
}

void Object::Draw() const {
	DrawObject(*this);
}

//
//void Object::MapChipHit() {
//	const Vector2 leftTop = { (position.x - radius.x) / ChipSize, (position.y + radius.y - 1) / ChipSize };
//	const Vector2 rightTop = { (position.x + radius.x - 1) / ChipSize,(position.y + radius.y - 1) / ChipSize };
//	const Vector2 leftDown = { (position.x - radius.x) / ChipSize, (position.y - radius.y) / ChipSize };
//	const Vector2 rightDown = { (position.x + radius.x - 1) / ChipSize,(position.y - radius.y) / ChipSize };
//
//
//#pragma region MapChip
//	// SA
//	if (velocity.x < 0 && velocity.y < 0) {
//		//Novice::ScreenPrintf(10, 90, "SA");
//		// 右下と左上が移動不可の場合
//		if ((Map::mapChip[(int)(rightDown.y)][(int)(rightDown.x)] != ChipData::Air) && (Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x)] != ChipData::Air)) {
//			position.x = (int)(leftTop.x + 1) * ChipSize + (radius.x);
//			position.y = (int)(rightDown.y + 1) * ChipSize + (radius.y);
//
//			velocity.x *= 0.8;
//			velocity.y = 0;
//			isGround = true;
//		}
//		// 右下が移動不可の場合
//		else if (Map::mapChip[(int)(rightDown.y)][(int)(rightDown.x)] != ChipData::Air) {
//			// 尚且つ右下の上マスが移動可能の場合
//			if (Map::mapChip[(int)(rightDown.y) + 1][(int)(rightDown.x)] == ChipData::Air) {
//				position.y = (int)(rightDown.y + 1) * ChipSize + (radius.y);
//
//				velocity.y = 0;
//				isGround = true;
//			}
//		}
//		// 左上が移動不可の場合
//		else if (Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x)] != ChipData::Air) {
//			// 尚且つ左上の右マスが開いている場合。
//			if (Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x) + 1] == ChipData::Air) {
//				position.x = (int)(leftTop.x + 1) * ChipSize + (radius.x);
//
//				velocity.x *= 0.8;
//			}
//		}
//
//		// 左下が移動不可の場合
//		else if (Map::mapChip[(int)(leftDown.y)][(int)(leftDown.x)] != ChipData::Air) {
//
//
//			// 尚且つ右と上が開いている場合
//			if (Map::mapChip[(int)(leftDown.y)][(int)(leftDown.x) + 1] == ChipData::Air && Map::mapChip[(int)(leftDown.y) + 1][(int)(leftDown.x)] == ChipData::Air) {
//
//				if ((((int)(position.x + (ChipSize / 2 - 1)) % ChipSize) < ((int)(position.y + (ChipSize / 2 - 1)) % ChipSize))) {
//					position.y = (int)(leftDown.y + 1) * ChipSize + (radius.y);
//
//					velocity.y = 0;
//					isGround = true;
//				}
//				else {
//					position.x = (int)(leftDown.x + 1) * ChipSize + (radius.x);
//
//					velocity.x *= 0.8;
//				}
//			}
//			// 尚且つ左下の上マスが開いていて、右マスが移動不可の場合。
//			else if (Map::mapChip[(int)(leftDown.y) + 1][(int)(leftDown.x)] == ChipData::Air && Map::mapChip[(int)(leftDown.y)][(int)(leftDown.x) + 1] != ChipData::Air) {
//				position.y = (int)(leftDown.y + 1) * ChipSize + (radius.y);
//
//				velocity.y = 0;
//				isGround = true;
//			}
//			// 尚且つ左下の右マスが開いていて、上マスが移動不可の場合。
//			else if (Map::mapChip[(int)(leftDown.y)][(int)(leftDown.x) + 1] == ChipData::Air && Map::mapChip[(int)(leftDown.y) + 1][(int)(leftDown.x)] != ChipData::Air) {
//				position.x = (int)(leftDown.x + 1) * ChipSize + (radius.x);
//
//				velocity.x *= 0.8;
//			}
//			// 尚且つ左下の右マスと上マスが移動不可の場合。
//			else if (Map::mapChip[(int)(leftDown.y)][(int)(leftDown.x) + 1] != ChipData::Air && Map::mapChip[(int)(leftDown.y) + 1][(int)(leftDown.x)] != ChipData::Air) {
//				position.x = (int)(leftDown.x + 1) * ChipSize + (radius.x);
//				position.y = (int)(leftDown.y + 1) * ChipSize + (radius.y);
//
//				velocity.x *= 0.8;
//				velocity.y = 0;
//				isGround = true;
//			}
//		}
//	}
//
//	// WA
//	else if (velocity.x < 0 && velocity.y > 0) {
//		//Novice::ScreenPrintf(10, 90, "WA");
//		// 右上と左下が移動不可の場合
//		if ((Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x)] != ChipData::Air) && (Map::mapChip[(int)(leftDown.y)][(int)(leftDown.x)] != ChipData::Air)) {
//			position.x = (int)(leftDown.x + 1) * ChipSize + (radius.x);
//			position.y = (int)(rightTop.y - 1) * ChipSize + (radius.y);
//
//			velocity.x *= 0.8;
//			velocity.y = 0;
//		}
//		// 右上が移動不可の場合
//		else if (Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x)] != ChipData::Air) {
//			// 右上の3ピクセルが移動不可の場合
//			if (Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x - (Extension / ChipSize))] != ChipData::Air) {
//				// 尚且つ右上の下マスが移動可能の場合
//				if (Map::mapChip[(int)(rightTop.y) - 1][(int)(rightTop.x)] == ChipData::Air) {
//					position.y = (int)(rightTop.y - 1) * ChipSize + (radius.y);
//
//					velocity.y = 0;
//				}
//			}
//			else {
//				position.x = (int)(rightTop.x - 1) * ChipSize + (radius.x);
//			}
//		}
//		// 左下が移動不可の場合
//		else if (Map::mapChip[(int)(leftDown.y)][(int)(leftDown.x)] != ChipData::Air) {
//			// 尚且つ左下の右マスが開いている場合。
//			if (Map::mapChip[(int)(leftDown.y)][(int)(leftDown.x) + 1] == ChipData::Air) {
//				position.x = (int)(leftDown.x + 1) * ChipSize + (radius.x);
//
//				velocity.x *= 0.8;
//			}
//		}
//
//		// 左上が移動不可の場合
//		else if (Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x)] != ChipData::Air) {
//
//
//			// 尚且つ右と下が開いている場合
//			if (Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x) + 1] == ChipData::Air && Map::mapChip[(int)(leftTop.y) - 1][(int)(leftTop.x)] == ChipData::Air) {
//
//				if (((int)(position.x + (ChipSize / 2 - 1)) % ChipSize) <= ((ChipSize)-((int)(position.y + (ChipSize / 2 + 1)) % ChipSize)) % ChipSize) {
//					position.y = (int)(leftTop.y - 1) * ChipSize + (radius.y);
//
//					velocity.y = 0;
//				}
//				else {
//					position.x = (int)(leftTop.x + 1) * ChipSize + (radius.x);
//
//					velocity.x *= 0.8;
//				}
//			}
//			// 尚且つ左上の下マスが開いていて、右マスが移動不可の場合。
//			else if (Map::mapChip[(int)(leftTop.y) - 1][(int)(leftTop.x)] == ChipData::Air && Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x) + 1] != ChipData::Air) {
//				position.y = (int)(leftTop.y - 1) * ChipSize + (radius.y);
//
//				velocity.y = 0;
//			}
//			// 尚且つ左上の右マスが開いていて、下マスが移動不可の場合。
//			else if (Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x) + 1] == ChipData::Air && Map::mapChip[(int)(leftTop.y) - 1][(int)(leftTop.x)] != ChipData::Air) {
//				position.x = (int)(leftTop.x + 1) * ChipSize + (radius.x);
//
//				velocity.x *= 0.8;
//			}
//			// 尚且つ左上の右マスと下マスが移動不可の場合。
//			else if (Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x) + 1] != ChipData::Air && Map::mapChip[(int)(leftTop.y) - 1][(int)(leftTop.x)] != ChipData::Air) {
//				position.x = (int)(leftTop.x + 1) * ChipSize + (radius.x);
//				position.y = (int)(leftTop.y - 1) * ChipSize + (radius.y);
//
//				velocity.x *= 0.8;
//				velocity.y = 0;
//			}
//		}
//	}
//	// SD
//	else if (velocity.x > 0 && velocity.y < 0) {
//		//Novice::ScreenPrintf(10, 90, "SD");
//		// 左下と右上が移動不可の場合
//		if ((Map::mapChip[(int)(leftDown.y)][(int)(leftDown.x)] != ChipData::Air) && (Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x)] != ChipData::Air)) {
//			position.x = (int)(rightTop.x - 1) * ChipSize + (radius.x) + ChipSize - radius.x * 2;
//			position.y = (int)(leftDown.y + 1) * ChipSize + (radius.y);
//
//			velocity.x *= 0.8;
//			velocity.y = 0;
//			isGround = true;
//		}
//		// 左下が移動不可の場合
//		else if (Map::mapChip[(int)(leftDown.y)][(int)(leftDown.x)] != ChipData::Air) {
//			// 尚且つ左下の上マスが移動可能の場合
//			if (Map::mapChip[(int)(leftDown.y) + 1][(int)(leftDown.x)] == ChipData::Air) {
//				position.y = (int)(leftDown.y + 1) * ChipSize + (radius.y);
//
//				velocity.y = 0;
//				isGround = true;
//			}
//		}// 右上が移動不可の場合
//		else if (Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x)] != ChipData::Air) {
//			// 尚且つ右上の左マスが開いている場合。
//			if (Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x) - 1] == ChipData::Air) {
//				position.x = (int)(rightTop.x - 1) * ChipSize + (radius.x) + ChipSize - radius.x * 2;
//
//				velocity.x *= 0.8;
//			}
//		}
//
//		// 右下が移動不可の場合
//		else if (Map::mapChip[(int)(rightDown.y)][(int)(rightDown.x)] != ChipData::Air) {
//
//
//			// 尚且つ左と上が開いている場合
//			if (Map::mapChip[(int)(rightDown.y)][(int)(rightDown.x) - 1] == ChipData::Air && Map::mapChip[(int)(rightDown.y) + 1][(int)(rightDown.x)] == ChipData::Air) {
//
//				if (((ChipSize)-((int)(position.x + (ChipSize / 2 + 1)) % ChipSize)) % ChipSize < ((int)(position.y + (ChipSize / 2 - 1)) % ChipSize)) {
//					position.y = (int)(rightDown.y + 1) * ChipSize + (radius.y);
//
//					velocity.y = 0;
//					isGround = true;
//				}
//				else {
//					position.x = (int)(rightDown.x - 1) * ChipSize + (radius.x) + ChipSize - radius.x * 2;
//				}
//
//			}
//			// 尚且つ右下の上マスが開いていて、左マスが移動不可の場合。
//			else if (Map::mapChip[(int)(rightDown.y) + 1][(int)(rightDown.x)] == ChipData::Air && Map::mapChip[(int)(rightDown.y)][(int)(rightDown.x) - 1] != ChipData::Air) {
//				position.y = (int)(rightDown.y + 1) * ChipSize + (radius.y);
//
//				velocity.y = 0;
//				isGround = true;
//			}
//			// 尚且つ右下の左マスが開いていて、上マスが移動不可の場合。
//			else if (Map::mapChip[(int)(rightDown.y)][(int)(rightDown.x) - 1] == ChipData::Air && Map::mapChip[(int)(rightDown.y) + 1][(int)(rightDown.x)] != ChipData::Air) {
//				position.x = (int)(rightDown.x - 1) * ChipSize + (radius.x) + ChipSize - radius.x * 2;
//
//				velocity.x *= 0.8;
//			}
//			// 尚且つ右下の左マスと上マスが移動不可の場合。
//			else if (Map::mapChip[(int)(rightDown.y)][(int)(rightDown.x) - 1] != ChipData::Air && Map::mapChip[(int)(rightDown.y) + 1][(int)(rightDown.x)] != ChipData::Air) {
//				position.x = (int)(rightDown.x - 1) * ChipSize + (radius.x) + ChipSize - radius.x * 2;
//				position.y = (int)(rightDown.y + 1) * ChipSize + (radius.y);
//
//				velocity.x *= 0.8;
//				velocity.y = 0;
//				isGround = true;
//			}
//		}
//	}
//
//	// WD
//	else if (velocity.x > 0 && velocity.y > 0) {
//		//Novice::ScreenPrintf(10, 90, "WD");
//		// 左上と右下が移動不可の場合
//		if ((Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x)] != ChipData::Air) && (Map::mapChip[(int)(rightDown.y)][(int)(rightDown.x)] != ChipData::Air)) {
//			position.x = (int)(rightDown.x - 1) * ChipSize + (radius.x) + ChipSize - radius.x * 2;
//			position.y = (int)(leftTop.y - 1) * ChipSize + (radius.y);
//
//			velocity.x *= 0.8;
//			velocity.y = 0;
//		}
//		// 左上が移動不可の場合
//		else if (Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x)] != ChipData::Air) {
//			// 左上の3ピクセルが移動不可の場合
//			if (Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x + (Extension / ChipSize))] != ChipData::Air) {
//				// 尚且つ左上の下マスが移動可能の場合
//				if (Map::mapChip[(int)(leftTop.y) - 1][(int)(leftTop.x)] == ChipData::Air) {
//					position.y = (int)(leftTop.y - 1) * ChipSize + (radius.y);
//
//					velocity.y = 0;
//				}
//			}
//			else {
//				position.x = (int)(leftTop.x + 1) * ChipSize + (radius.x);
//			}
//		}
//		// 右下が移動不可の場合
//		else if (Map::mapChip[(int)(rightDown.y)][(int)(rightDown.x)] != ChipData::Air) {
//			// 尚且つ右下の左マスが開いている場合。
//			if (Map::mapChip[(int)(rightDown.y)][(int)(rightDown.x) - 1] == ChipData::Air) {
//				position.x = (int)(rightDown.x - 1) * ChipSize + (radius.x) + ChipSize - radius.x * 2;
//
//				velocity.x *= 0.8;
//			}
//		}
//
//		// 右上が移動不可の場合
//		else if (Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x)] != ChipData::Air) {
//
//
//			// 尚且つ左と下が開いている場合
//			if (Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x) - 1] == ChipData::Air && Map::mapChip[(int)(rightTop.y) - 1][(int)(rightTop.x)] == ChipData::Air) {
//
//				if (((ChipSize)-((int)(position.x + (ChipSize / 2 + 1)) % ChipSize)) % ChipSize <= ((ChipSize)-((int)(position.y + (ChipSize / 2 + 1)) % ChipSize)) % ChipSize) {
//					position.y = (int)(rightTop.y - 1) * ChipSize + (radius.y);
//
//					velocity.y = 0;
//				}
//				else {
//					position.x = (int)(rightTop.x - 1) * ChipSize + (radius.x) + ChipSize - radius.x * 2;
//
//					velocity.x *= 0.8;
//				}
//			}
//			// 尚且つ右上の下マスが開いていて、左マスが移動不可の場合。
//			else if (Map::mapChip[(int)(rightTop.y) - 1][(int)(rightTop.x)] == ChipData::Air && Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x) - 1] != ChipData::Air) {
//				position.y = (int)(rightTop.y - 1) * ChipSize + (radius.y);
//
//				velocity.y = 0;
//			}
//			// 尚且つ右上の左マスが開いていて、下マスが移動不可の場合。
//			else if (Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x) - 1] == ChipData::Air && Map::mapChip[(int)(rightTop.y) - 1][(int)(rightTop.x)] != ChipData::Air) {
//				position.x = (int)(rightTop.x - 1) * ChipSize + (radius.x) + ChipSize - radius.x * 2;
//
//				velocity.x *= 0.8;
//			}
//			// 尚且つ右上の左マスと下マスが移動不可の場合。
//			else if (Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x) - 1] != ChipData::Air && Map::mapChip[(int)(rightTop.y) - 1][(int)(rightTop.x)] != ChipData::Air) {
//				position.x = (int)(rightTop.x - 1) * ChipSize + (radius.x) + ChipSize - radius.x * 2;
//				position.y = (int)(rightTop.y - 1) * ChipSize + (radius.y);
//
//				velocity.x *= 0.8;
//				velocity.y = 0;
//			}
//		}
//	}
//
//	else if (velocity.x > 0) {
//		if ((Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x)] != ChipData::Air) || (Map::mapChip[(int)(rightDown.y)][(int)(rightDown.x)] != ChipData::Air)) {
//			position.x = (int)(rightTop.x - 1) * ChipSize + (radius.x) + ChipSize - radius.x * 2;
//		}
//	}
//
//	else if (velocity.x < 0) {
//		if ((Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x)] != ChipData::Air) || (Map::mapChip[(int)(leftDown.y)][(int)(leftDown.x)] != ChipData::Air)) {
//			position.x = (int)(leftTop.x + 1) * ChipSize + (radius.x);
//		}
//	}
//
//	else if (velocity.y > 0) {
//		// 左上の3ピクセルが移動可の場合
//		if ((Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x)] != ChipData::Air) && Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x + (Extension / ChipSize))] == ChipData::Air) {
//			position.x = (int)(leftTop.x + 1) * ChipSize + (radius.x);
//		}
//		// 右上の3ピクセルが移動可の場合
//		else if ((Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x)] != ChipData::Air) && Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x - (Extension / ChipSize))] == ChipData::Air) {
//			position.x = (int)(rightTop.x - 1) * ChipSize + (radius.x) + ChipSize - radius.x * 2;
//		}
//
//		else if ((Map::mapChip[(int)(leftTop.y)][(int)(leftTop.x)] != ChipData::Air) || (Map::mapChip[(int)(rightTop.y)][(int)(rightTop.x)] != ChipData::Air)) {
//			position.y = (int)(rightTop.y - 1) * ChipSize + (radius.y);
//
//			velocity.y = 0;
//		}
//	}
//
//	else if (velocity.y < 0) {
//		if ((Map::mapChip[(int)(leftDown.y)][(int)(leftDown.x)] != ChipData::Air) || (Map::mapChip[(int)(rightDown.y)][(int)(rightDown.x)] != ChipData::Air)) {
//			position.y = (int)(leftDown.y + 1) * ChipSize + (radius.y);
//
//			velocity.y = 0;
//
//			isGround = true;
//
//		}
//	}
//
//#pragma endregion
//
//}
