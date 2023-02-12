#pragma once

#include <Novice.h>

#include "BaseData.hpp"
#include "Math/Vector2.hpp"
#include "Math/PolarCoordinates.hpp"
#include "Math/Math.hpp"	

#include "Shake.hpp"

#include "Easing.hpp"

#include <string>

extern unsigned int TestWhiteTexture;
extern unsigned int TestCircleTexture;
extern unsigned int TestUVTexture;


extern int TextureFlame;

/// <summary>
	/// Spriteクラス
	/// </summary>
	/// <param name="textureHandle">テクスチャ</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
class SpriteClass
{
public:
	SpriteClass();
	SpriteClass(int srcW, int srcH, unsigned int maxFlame);

	SpriteClass(unsigned int textureHandle, int srcW, int srcH, unsigned int maxFlame);

	SpriteClass(const std::string &file_path, int srcW, int srcH, unsigned int maxFlame);
	inline ~SpriteClass() {  }

	// +テクスチャを読み込む関数
	void LoadTexture(const std::string &file_path);
	// -テクスチャを解除する関数
	void ReleaseTexture();

	void Init(unsigned int textureHandle, int srcW, int srcH, unsigned int maxFlame);
	void Init(const std::string &file_path, int srcW, int srcH, unsigned int maxFlame);
	void Init(int srcW, int srcH, unsigned int maxFlame);

	std::string file_path = {};
	bool hasTexture = false;

	unsigned int textureHandle;
	int srcX; // 画像上の描画したい範囲左上座標 X
	int srcY; // 画像上の描画したい範囲左上座標 Y
	int srcW; // 画像上の描画したい範囲横幅
	int srcH; // 画像上の描画したい範囲縦幅
	//	unsigned int needNextFlame;

	// -色
	unsigned int color;

	// -現在フレーム
	unsigned int nowFlame;
	unsigned int minFlame;
	unsigned int maxFlame;

	//	static int textureFlame;
	/*
	void AnimationUpdate();
	void AnimationUpdate(const int &Flame);
	*/

	// -テクスチャフレームを1つ進める
	void NextTextureFlame();

	// +現在フレームを設定する
	void SetNowFlame(const unsigned int &value);

	// -現在フレームを範囲に収める
	void ClampTextureFlame();

	/// <summary>
	/// =現在のアニメーション進行度
	/// </summary>
	/// <returns>進行度</returns>
	inline float GetProgress() const {
		return (float)(nowFlame - minFlame) / (maxFlame - minFlame);
	}

	/// <summary>
	/// +アニメーション進行度で設定する
	/// </summary>
	/// <param name="start">開始点</param>
	/// <param name="end">終了点</param>
	/// <param name="volume">進行度</param>
	inline void SetProgress(unsigned int start, unsigned int end, float volume) {
		nowFlame = (int)Easing<float>(start, end, volume);
	}

	/// <summary>
	/// +アニメーション進行度で設定する
	/// </summary>
	/// <param name="volume">進行度</param>
	inline void SetProgress(float volume) {
		nowFlame = (int)Easing<float>(this->minFlame, this->maxFlame, volume);
	}

private:

};

class SpriteBox :public SpriteClass {
public:
	SpriteBox() :offset(ZeroVector2), scale({ 1,1 }) {}
	SpriteBox(const Vector2 &offset, const Vector2 &radius, const Vector2 &scale) :offset(offset), scale(scale) {}

	~SpriteBox() {};

	SpriteBox &operator=(const SpriteClass &other) {
		SpriteClass::operator=(other);
		return *this;
	}

	/// <summary>
	// +画像の表示位置変更
	/// </summary>
	/// <param name="offset"></param>
	inline void SetSpriteOffset(Vector2 offset) {
		this->offset = offset;
	}


	/// <summary>
	/// +画像の画面内で表示するスケールの変更
	/// </summary>
	/// <param name="scale">倍率</param>
	inline void SetSpriteScale(Vector2 scale) {
		this->scale = scale;
	}


	// -テクスチャの位置調整
	Vector2 offset;
	// -テクスチャのスケール。倍率。
	Vector2 scale;

	Shaker shake = {};


	inline void Shake(const float &minRadian, const float &maxRadian, const float &strength, const unsigned int &flame) {
		shake.Shake(minRadian, maxRadian, strength, flame);
	}

	inline void ShakeUpdate() {
		offset = shake.ShakeUpdate();
	}

};



static void ImportTexture() {
	TestWhiteTexture = Novice::LoadTexture("white1x1.png");
	TestCircleTexture = Novice::LoadTexture("./Resources/Texture/TestTexture/Circle.png");
	TestUVTexture = Novice::LoadTexture("uvChecker.png");
}

inline void TextureUpdate() {
	//	SpriteClass::textureFlame++;
	TextureFlame++;
}