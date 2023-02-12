
#include "SpriteClass.hpp"

#include <Novice.h>
#include "./BaseData.hpp"



//int SpriteClass::textureFlame = 0;

unsigned int TestWhiteTexture = 0;
unsigned int TestCircleTexture = 0;
unsigned int TestUVTexture = 0;

int TextureFlame = 0;


SpriteClass::SpriteClass() :textureHandle(TestWhiteTexture), srcX(0), srcY(0), srcW(1), srcH(1), color(0xFFFFFFFF), nowFlame(0), minFlame(0), maxFlame(1)/*, textureFlamePointer(&TextureFlame)*/
{
}
SpriteClass::SpriteClass(int srcW, int srcH, unsigned int maxFlame) : textureHandle(TestWhiteTexture), srcX(0), srcY(0), srcW(srcW), srcH(srcH), color(0xFFFFFFFF), nowFlame(0), minFlame(0), maxFlame(maxFlame)/*, textureFlamePointer(&TextureFlame)*/
{
}
SpriteClass::SpriteClass(unsigned int textureHandle, int srcW, int srcH, unsigned int maxFlame) : textureHandle(textureHandle), srcX(0), srcY(0), srcW(srcW), srcH(srcH), color(0xFFFFFFFF), nowFlame(0), minFlame(0), maxFlame(maxFlame)/*, textureFlamePointer(&TextureFlame)*/
{
}
SpriteClass::SpriteClass(const std::string &file_path, int srcW, int srcH, unsigned int maxFlame) : srcX(0), srcY(0), srcW(srcW), srcH(srcH), color(0xFFFFFFFF), nowFlame(0), minFlame(0), maxFlame(maxFlame)/*, textureFlamePointer(&TextureFlame)*/
{
	LoadTexture(file_path);
}


//
//void SpriteClass::AnimationUpdate() {
//	//	textureFlamePointer++;
//	if (needNextFlame != 0) {
//		srcX = (textureFlame / needNextFlame) % maxFlame * srcW;
//	}
//}
//
//void SpriteClass::AnimationUpdate(const int &Flame) {
//	//	textureFlamePointer++;
//	if (needNextFlame != 0) {
//		srcX = (Flame / needNextFlame) % maxFlame * srcW;
//	}
//}



void SpriteClass::LoadTexture(const std::string &file_path) {
	if (file_path != "") {
		ReleaseTexture();

		textureHandle = Novice::LoadTexture(file_path.c_str());
		this->file_path = file_path;
		hasTexture = true;
	}
	else {
		textureHandle = TestWhiteTexture;
	}
}


void SpriteClass::ReleaseTexture() {
	if (hasTexture) {
		Novice::UnloadTexture(textureHandle);
		this->file_path = "";
		hasTexture = false;
	}
	textureHandle = TestWhiteTexture;
}

void SpriteClass::Init(unsigned int textureHandle, int srcW, int srcH, unsigned int maxFlame) {
	this->textureHandle = textureHandle;
	this->srcW = srcW;
	this->srcH = srcH;
	this->maxFlame = maxFlame;
}



void SpriteClass::Init(const std::string &file_path, int srcW, int srcH, unsigned int maxFlame) {
	LoadTexture(file_path);
	this->srcW = srcW;
	this->srcH = srcH;
	this->maxFlame = maxFlame;
}


void SpriteClass::Init(int srcW, int srcH, unsigned int maxFlame) {
	this->srcW = srcW;
	this->srcH = srcH;
	this->maxFlame = maxFlame;
}


void SpriteClass::NextTextureFlame() {
	// 次のフレームに進める。
	nowFlame++;
	// もし、最大フレームを超えた場合、0とする。
	if (maxFlame <= nowFlame) {
		nowFlame = 0;
	}
}

void SpriteClass::SetNowFlame(const unsigned int &value) {
	nowFlame = value;
}

void SpriteClass::ClampTextureFlame() {
	nowFlame = Clamp(nowFlame, minFlame, maxFlame - 1);
}
