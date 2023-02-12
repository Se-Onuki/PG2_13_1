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
	/// Sprite�N���X
	/// </summary>
	/// <param name="textureHandle">�e�N�X�`��</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
class SpriteClass
{
public:
	SpriteClass();
	SpriteClass(int srcW, int srcH, unsigned int maxFlame);

	SpriteClass(unsigned int textureHandle, int srcW, int srcH, unsigned int maxFlame);

	SpriteClass(const std::string &file_path, int srcW, int srcH, unsigned int maxFlame);
	inline ~SpriteClass() {  }

	// +�e�N�X�`����ǂݍ��ފ֐�
	void LoadTexture(const std::string &file_path);
	// -�e�N�X�`������������֐�
	void ReleaseTexture();

	void Init(unsigned int textureHandle, int srcW, int srcH, unsigned int maxFlame);
	void Init(const std::string &file_path, int srcW, int srcH, unsigned int maxFlame);
	void Init(int srcW, int srcH, unsigned int maxFlame);

	std::string file_path = {};
	bool hasTexture = false;

	unsigned int textureHandle;
	int srcX; // �摜��̕`�悵�����͈͍�����W X
	int srcY; // �摜��̕`�悵�����͈͍�����W Y
	int srcW; // �摜��̕`�悵�����͈͉���
	int srcH; // �摜��̕`�悵�����͈͏c��
	//	unsigned int needNextFlame;

	// -�F
	unsigned int color;

	// -���݃t���[��
	unsigned int nowFlame;
	unsigned int minFlame;
	unsigned int maxFlame;

	//	static int textureFlame;
	/*
	void AnimationUpdate();
	void AnimationUpdate(const int &Flame);
	*/

	// -�e�N�X�`���t���[����1�i�߂�
	void NextTextureFlame();

	// +���݃t���[����ݒ肷��
	void SetNowFlame(const unsigned int &value);

	// -���݃t���[����͈͂Ɏ��߂�
	void ClampTextureFlame();

	/// <summary>
	/// =���݂̃A�j���[�V�����i�s�x
	/// </summary>
	/// <returns>�i�s�x</returns>
	inline float GetProgress() const {
		return (float)(nowFlame - minFlame) / (maxFlame - minFlame);
	}

	/// <summary>
	/// +�A�j���[�V�����i�s�x�Őݒ肷��
	/// </summary>
	/// <param name="start">�J�n�_</param>
	/// <param name="end">�I���_</param>
	/// <param name="volume">�i�s�x</param>
	inline void SetProgress(unsigned int start, unsigned int end, float volume) {
		nowFlame = (int)Easing<float>(start, end, volume);
	}

	/// <summary>
	/// +�A�j���[�V�����i�s�x�Őݒ肷��
	/// </summary>
	/// <param name="volume">�i�s�x</param>
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
	// +�摜�̕\���ʒu�ύX
	/// </summary>
	/// <param name="offset"></param>
	inline void SetSpriteOffset(Vector2 offset) {
		this->offset = offset;
	}


	/// <summary>
	/// +�摜�̉�ʓ��ŕ\������X�P�[���̕ύX
	/// </summary>
	/// <param name="scale">�{��</param>
	inline void SetSpriteScale(Vector2 scale) {
		this->scale = scale;
	}


	// -�e�N�X�`���̈ʒu����
	Vector2 offset;
	// -�e�N�X�`���̃X�P�[���B�{���B
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