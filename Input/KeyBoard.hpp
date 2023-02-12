#pragma once


#include <Novice.h>

//#include "Resource.hpp"
#include "./Math/Vector2.hpp"

// �L�[���͌��ʂ��󂯎�锠

class Keyboard
{
public:
	Keyboard();


	/// �L�[�{�[�h��(key)���g���K�[���ꂽ��
	inline static bool IsTrigger(const char &key) {
		return(keys[key] && !preKeys[key]);
	}

	/// �L�[�{�[�h��(key)�������ꂽ��
	inline static bool IsRelease(const char &key) {
		return (!keys[key] && preKeys[key]);
	}

	/// �L�[�{�[�h��(key)��������Ă��邩
	inline static bool IsPress(const char &key) {
		return (keys[key]);
	}

	inline static void Update() {
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
	}
private:

	static char keys[256];
	static char preKeys[256];

};

class Mouse
{
public:
	Mouse();
	static void Update();

	inline static Vector2 GetMouse() {
		return { (float)mouse.x,(float)mouse.y };
	}

	inline static Vector2 GetDirection() {
		return { (float)mouse.x - preMouse.x,(float)(mouse.y - preMouse.y) * -1.f };
	}

private:

	// �}�E�X���W���󂯎��Int�x�N�g���\����
	static IntVector2 mouse, preMouse;

};








