#include "Camera.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Math/Vector2.hpp"
#include "Math/Math.hpp"
#include "BaseData.hpp"

//#include "Easing.hpp"
//#include "Player.hpp"
//#include "Boss.hpp"


Camera::Camera() {
}

Matrix3x3 Camera::vpVpMatrix = Matrix3x3{};
Matrix3x3 Camera::UIvpVpMatrix = Matrix3x3{};

float Camera::angle;

Matrix3x3 Camera::cameraMatrix = Matrix3x3{};
Matrix3x3 Camera::orthoMatrix = Matrix3x3{};
Matrix3x3 Camera::viewportMatrix = Matrix3x3{};

Vector2 Camera::ZoomCentor = MiddleCentor;
float Camera::DrawScale = 1.0f;
Vector2 Camera::focusPosition = Vector2{};


Vector2 Camera::scroll = ZeroVector2;
Vector2 Camera::scrollReference = ZeroVector2;

Vector2 Camera::shakeRadius = ZeroVector2;
unsigned int Camera::shakeFlame = 0;
unsigned int Camera::maxShakeFlame = 0;

void Camera::Reset() {
	PositionReset();
	EffectReset();
}

void Camera::PositionReset() {

	Camera::scroll = ZeroVector2;
	Camera::scrollReference = ZeroVector2;
}

void Camera::EffectReset() {

	Camera::shakeRadius = ZeroVector2;
	Camera::shakeFlame = 0;
	Camera::maxShakeFlame = 0;
}
void Camera::Shake(Vector2 radius, unsigned int flame) {
	maxShakeFlame = flame;
	shakeFlame = 0;
	shakeRadius = radius;
	//	scroll = scrollReference + Vector2{(float)(shakeRadius.x * cos(Degree2Radian(shakeFlame * 75))),(float)(shakeRadius.y * sin(Degree2Radian(shakeFlame * 75))) };
}

void Camera::Update() {
	scroll = scrollReference;

	scroll = focusPosition;

	//	ScreenSize

	if (maxShakeFlame != 0) {
		if (maxShakeFlame > shakeFlame) {
			shakeFlame++;
			scroll += Vector2{
			(float)(shakeRadius.x * cos(Degree2Radian(shakeFlame * 75)) * (1 - (float)(shakeFlame) / maxShakeFlame)),
			(float)(shakeRadius.y * sin(Degree2Radian(shakeFlame * 75)) * (1 - (float)(shakeFlame) / maxShakeFlame))
			};
		}
		else {
			EffectReset();
		}

	}

	if (DrawScale <= 0) 1.0f / 8;

	cameraMatrix = MakeTranslateMatrix(-scroll) * MakeRotateMatrix3x3(angle);

	orthoMatrix = MakeOrthographicMatrix(Vector2{ -ScreenSize.x,ScreenSize.y } / 2 * DrawScale, Vector2{ ScreenSize.x,-ScreenSize.y } / 2 * DrawScale);

	viewportMatrix = MakeViewportMatrix({ 0,0 }, ScreenSize);

	vpVpMatrix = cameraMatrix * orthoMatrix * viewportMatrix;
	UIvpVpMatrix = MakeTranslateMatrix(-MiddleCentor) * MakeOrthographicMatrix(Vector2{ -ScreenSize.x,ScreenSize.y } / 2, Vector2{ ScreenSize.x,-ScreenSize.y } / 2) * viewportMatrix;

}

void Camera::SetFocus(const Vector2 &Positon) {
	focusPosition = Positon;
}
