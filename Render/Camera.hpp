#pragma once

#include "Math/Vector2.hpp"
#include "Math/Matrix3x3.hpp"


class Camera
{
public:
	Camera();
	// �X�N���[���l
	static Vector2 scrollReference;
	// ������X�N���[���l
	static Vector2 scroll;

	static void Reset();
	static void PositionReset();
	static void EffectReset();

	static void Shake(Vector2 radius, unsigned int flame);

	static void Update();

	// �Y�[���̃t�H�[�J�X���W�̐ݒ�
	static void SetFocus(const Vector2 &Positon);
	inline static Vector2 GetFocus() { return focusPosition; };


	inline static void SetAngle(const float &Angle) {
		angle = Angle;
	}

	inline static float GetAngle() {
		return angle;
	}

	// �`��{��
	static float DrawScale;




	static Matrix3x3 vpVpMatrix;
	static Matrix3x3 UIvpVpMatrix;

private:
	// �X�N���[���̂ǂ��𒆐S�ɃY�[�����邩
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
