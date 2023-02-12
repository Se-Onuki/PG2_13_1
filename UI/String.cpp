#include "String.hpp"

#include <string>
#include <Windows.h>
#include <Novice.h>

#include <numeric>

#include "Render/Resource.hpp"
#include "Render/Camera.hpp"

std::unordered_map<std::string, FontTexture> String::fontList = {};


void FontTexture::SetFont(const std::string file_name, Vector2 Size)
{
	U_Defalut.Init("./Resources/Texture/Font/" + file_name + "/Glyph_00.png", Size.x, Size.y, 1);
	U_00.Init("./Resources/Texture/Font/" + file_name + "/Glyph_00.png", Size.x, Size.y, 1);
	U_30.Init("./Resources/Texture/Font/" + file_name + "/Glyph_30.png", Size.x, Size.y, 1);

	size_ = Size;
}


String::String() : charString_{ '\0' }, wideString_{ L'\0' }
{
}

String::String(const std::string String)
{
	TypeString(String);
	ToUnicode();
}

String::~String()
{
}

void String::AddString(const std::string String) {
	charString_ += String;
}

void String::TypeString(const std::string String) {
	charString_ = String;
}

void String::TypeString(const std::wstring wString) {
	wideString_ = wString;
}

void String::ToUnicode() {
	//  CP_ACP = Shift_JIS
	// ビットフラグ。0。 è と e と ` の関係性とかを設定するらしい。
	// 
	// 変換元の文字列のアドレス。
	// 変換元文字列のバイト数。 -1の場合、\0まで。
	// 
	// 変換後の文字列のアドレス。
	// 変換後文字列の「文字数」。0の場合、関数の返り値がワイド文字列のバイト数になる。

	// wideCharCount-ワイド文字列長
	int wideCharCount = MultiByteToWideChar(CP_ACP, 0, charString_.c_str(), -1, nullptr, 0);
	if (wideCharCount == 0) {
		// 失敗の場合、空文字列にする
		wideString_[0] = L'\0';
		return;
	}

	wchar_t *wideArray = new wchar_t[wideCharCount];

	// マルチバイト文字をワイド文字に変換
	int result = MultiByteToWideChar(CP_ACP, 0, charString_.c_str(), -1, wideArray, wideCharCount);
	if (result == 0) {
		// 失敗の場合、空文字列にする
		wideString_[0] = L'\0';
	}
	else {
		// 成功の場合、文字列の最後を\0にする
		wideString_ = std::wstring(wideArray) + L'\0';
	}
	delete[] wideArray;
}

void String::DrawString(Vector2 position, Vector2 Size, Vector2 coeff, unsigned int color) const {
	DrawString(wideString_, "Default", position, Size, coeff, color);
}


void String::DrawString(const std::wstring wString, const std::string font, Vector2 position, Vector2 Size, Vector2 coeff, unsigned int color) {
	std::vector<float> v;
	for (auto c : wString) {
		switch (((c & 0xFF00) >> 8) & 0xFF) {
		case 0x00:
			v.push_back(2.0f / 3);
			break;
		case 0x30:
			v.push_back(1.0f);
			break;
		default:
			v.push_back(2.0f / 3);
			break;
		}
	}
	float sumLength = std::accumulate(v.begin(), v.end(), 0.f);
	float x = position.x;
	for (int i = 0; i < 256 && wString[i] != L'\0'; i++) {
		Vector2 charPosition = { x + (-v[0] / 2 + v[i] / 2) * Size.x + v[0] / 2 * Size.x - sumLength * Size.x * coeff.x, position.y };
		switch (((wString[i] & 0xFF00) >> 8) & 0xFF)
		{
		case 0x0:
			DrawObject(charPosition, Size, (wString[i] & 0x000F) * fontList[font].size_.x, ((wString[i] & 0x00F0) >> 4) * fontList[font].size_.y, fontList[font].size_.x, fontList[font].size_.y, fontList[font].U_00.textureHandle, color, { 1,1 }, 0.f, Camera::UIvpVpMatrix);
			break;
		case 0x30:
			DrawObject(charPosition, Size, (wString[i] & 0x000F) * fontList[font].size_.x, ((wString[i] & 0x00F0) >> 4) * fontList[font].size_.y, fontList[font].size_.x, fontList[font].size_.y, fontList[font].U_30.textureHandle, color, { 1,1 }, 0.f, Camera::UIvpVpMatrix);
			break;
		default:
			DrawObject(charPosition, Size, (wString[i] & 0x000F) * fontList[font].size_.x, ((wString[i] & 0x00F0) >> 4) * fontList[font].size_.y, fontList[font].size_.x, fontList[font].size_.y, fontList[font].U_Defalut.textureHandle, color, { 1,1 }, 0.f, Camera::UIvpVpMatrix);
			break;
		}
		x += v[i] * Size.x;
	}
}