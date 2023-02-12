#pragma once


#include <Novice.h>

//#include "Resource.hpp"
#include "./Math/Vector2.hpp"

// キー入力結果を受け取る箱

class Keyboard
{
public:
	Keyboard();


	/// キーボードの(key)がトリガーされたか
	inline static bool IsTrigger(const char &key) {
		return(keys[key] && !preKeys[key]);
	}

	/// キーボードの(key)が離されたか
	inline static bool IsRelease(const char &key) {
		return (!keys[key] && preKeys[key]);
	}

	/// キーボードの(key)が押されているか
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

	// マウス座標を受け取るIntベクトル構造体
	static IntVector2 mouse, preMouse;

};








