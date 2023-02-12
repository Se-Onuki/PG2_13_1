#pragma once

#include "Math/Vector2.hpp"
#include "Math/Matrix3x3.hpp"


class Camera
{
public:
	Camera();
	// スクロール値
	static Vector2 scrollReference;
	// 処理後スクロール値
	static Vector2 scroll;

	static void Reset();
	static void PositionReset();
	static void EffectReset();

	static void Shake(Vector2 radius, unsigned int flame);

	static void Update();

	// ズームのフォーカス座標の設定
	static void SetFocus(const Vector2 &Positon);
	inline static Vector2 GetFocus() { return focusPosition; };


	inline static void SetAngle(const float &Angle) {
		angle = Angle;
	}

	inline static float GetAngle() {
		return angle;
	}

	// 描画倍率
	static float DrawScale;




	static Matrix3x3 vpVpMatrix;
	static Matrix3x3 UIvpVpMatrix;

private:
	// スクリーンのどこを中心にズームするか
	static Vector2 ZoomCentor;

	static float angle;

	static Matrix3x3 cameraMatrix;
	static Matrix3x3 orthoMatrix;
	static Matrix3x3 viewportMatrix;


	static Vector2 focusPosition;

	static Vector2 shakeRadius;
	static unsigned int maxShakeFlame;
	static unsigned int shakeFlame;

};
