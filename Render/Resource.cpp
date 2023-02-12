#include "Resource.hpp"

#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "BaseData.hpp"
#include "Math/Math.hpp"
#include "Math/Vector2.hpp"
#include "Math/Matrix2x2.hpp"
#include "Math/Matrix3x3.hpp"

#include "Camera.hpp"

#include "SpriteClass.hpp"



float ToWorld(float y) {
	return (-(y)+WorldPos);
};

Vector2 ToWorld(Vector2 position) {
	return { position.x,(-(position.y) + WorldPos) };
};

Vector2 ToScreenPosition(Vector2 DefaultPosition) {
	return DefaultPosition * (Camera::vpVpMatrix).Inverse();
}

void DrawQuadFunction(Vector2 centor, Vector2 size, int srcX, int srcY, int srcW, int srcH, unsigned int textureHandle, unsigned int color) {
	Novice::DrawQuad(
		(centor.x) - ((size.x) / 2), ToWorld((centor.y) + ((size.y) / 2)),
		(centor.x) + ((size.x) / 2), ToWorld((centor.y) + ((size.y) / 2)),
		(centor.x) - ((size.x) / 2), ToWorld((centor.y) - ((size.y) / 2)),
		(centor.x) + ((size.x) / 2), ToWorld((centor.y) - ((size.y) / 2)),
		srcX, srcY, srcW, srcH, textureHandle, color);
};

void DrawQuadFunction(Vector2 centor, Vector2 size, int srcX, int srcY, int srcW, int srcH, unsigned int textureHandle, float angle, unsigned int color) {
	const Vector2 LeftTop = Vector2{ -size.x / 2, size.y / 2 }.Rotate(angle);
	const Vector2 RightTop = Vector2{ size.x / 2, size.y / 2 }.Rotate(angle);
	const Vector2 LeftDown = Vector2{ -size.x / 2, -size.y / 2 }.Rotate(angle);
	const Vector2 RightDown = Vector2{ size.x / 2, -size.y / 2 }.Rotate(angle);
	Novice::DrawQuad(
		(centor.x) + LeftTop.x, ToWorld((centor.y) + LeftTop.y),
		(centor.x) + RightTop.x, ToWorld((centor.y) + RightTop.y),
		(centor.x) + LeftDown.x, ToWorld((centor.y) + LeftDown.y),
		(centor.x) + RightDown.x, ToWorld((centor.y) + RightDown.y),
		srcX, srcY, srcW, srcH, textureHandle, color);
};

/// ‘å–{
void DrawObject(const Vector2 &centor, const Vector2 &size, const int &srcX, const int &srcY, const int &srcW, const int &srcH, const unsigned int &textureHandle, const unsigned int &color, const Vector2 &scale, const float &angle, const Matrix3x3 &vpVpMatrix) {
	Matrix3x3 wvpVpMatrix = MakeAffineMatrix(scale, angle, centor) * vpVpMatrix;

	Vector2 LeftTop = Vector2{ -size.x, size.y } / 2 * wvpVpMatrix;
	Vector2 RightTop = Vector2{ size.x, size.y } / 2 * wvpVpMatrix;

	Vector2 LeftDown = Vector2{ -size.x, -size.y } / 2 * wvpVpMatrix;
	Vector2 RightDown = Vector2{ size.x, -size.y } / 2 * wvpVpMatrix;
	Novice::DrawQuad(LeftTop.x, LeftTop.y, RightTop.x, RightTop.y, LeftDown.x, LeftDown.y, RightDown.x, RightDown.y, srcX, srcY, srcW, srcH, textureHandle, color);
};


void DrawObject(const Vector2 &centor, const Vector2 &size, const SpriteBox spriteBox, const Vector2 &scale, const float &angle, const Matrix3x3 &vpVpMatrix)
{
	DrawObject(centor, size, spriteBox.srcX, spriteBox.srcY, spriteBox.srcW, spriteBox.srcH, spriteBox.textureHandle, spriteBox.color, Vector2{ 1,1 }, 0.0f, Camera::vpVpMatrix);
}

void DrawObject(Vector2 centor, Vector2 size, int srcX, int srcY, int srcW, int srcH, unsigned int textureHandle, unsigned int color) {
	DrawObject(centor, size, srcX, srcY, srcW, srcH, textureHandle, color, Vector2{ 1,1 }, 0.0f, Camera::vpVpMatrix);
};

void DrawObject(Vector2 centor, Vector2 size, int srcX, int srcY, int srcW, int srcH, unsigned int textureHandle, float angle, unsigned int color) {
	DrawObject(centor, size, srcX, srcY, srcW, srcH, textureHandle, color, Vector2{ 1,1 }, angle, Camera::vpVpMatrix);
};

void DrawObject(const Object &object, const SpriteClass &sprite) {
	DrawObject(object.position, object.radius * 2, sprite.srcX + sprite.srcW * sprite.nowFlame, sprite.srcY, sprite.srcW, sprite.srcH, sprite.textureHandle, sprite.color, { 1,1 }, 0.0f, Camera::vpVpMatrix);
};

void DrawObject(const Object &object, const SpriteBox &sprite) {
	DrawObject(object.position, object.radius * 2, sprite.srcX + sprite.srcW * sprite.nowFlame, sprite.srcY, sprite.srcW, sprite.srcH, sprite.textureHandle, sprite.color, sprite.scale, 0.0f, Camera::vpVpMatrix);
};

void DrawObject(const Object &object, const SpriteBox &sprite, const float &angle) {
	DrawObject(object.position, object.radius * 2, sprite.srcX + sprite.srcW * sprite.nowFlame, sprite.srcY, sprite.srcW, sprite.srcH, sprite.textureHandle, sprite.color, sprite.scale, angle, Camera::vpVpMatrix);
};


void DrawObject(const Object &object) {
	DrawObject(object.position + object.GetSpriteBox().offset, object.radius * 2, object.GetSpriteBox().srcX + object.GetSpriteBox().srcW * object.GetSpriteBox().nowFlame, object.GetSpriteBox().srcY, object.GetSpriteBox().srcW, object.GetSpriteBox().srcH, object.GetSpriteBox().textureHandle, object.GetSpriteBox().color, object.GetSpriteBox().scale, 0.0f, Camera::vpVpMatrix);
};

void DrawLineObject(const Vector2 &start, const Vector2 &end, const unsigned int &color, const Matrix3x3 &vpVpMatrix) {
	Vector2 centor = (start + end) / 2;
	float size = (end - start).Length();
	float angle = (end - start).GetTheta();
	DrawObject(centor, { size,1 }, 0, 0, 1, 1, TestWhiteTexture, color, Vector2{ 1, 1 }, angle, vpVpMatrix);
}