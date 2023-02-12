#pragma once

#include "Math/Vector2.hpp"
#include "Render/SpriteClass.hpp"
#include <string>
#include <locale>
#include <codecvt>

#include <unordered_map>



class FontTexture {
public:
	SpriteClass U_Defalut;
	SpriteClass U_00;
	SpriteClass U_30;

	// -フォントサイズ
	Vector2 size_ = { 0,0 };
	void SetFont(const std::string file_name, Vector2 Size);
};


class String
{
public:
	String();
	String(const std::string String);
	~String();

	/// <summary>
	/// -文字入力
	/// </summary>
	/// <param name="String">入力文字列</param>
	void TypeString(const std::string String);

	/// <summary>
	/// -文字入力
	/// </summary>
	/// <param name="wString">入力文字列</param>
	void TypeString(const std::wstring wString);

	/// <summary>
	/// -文字追加
	/// </summary>
	/// <param name="CharString">追加文字列</param>
	void AddString(const std::string String);

	/// <summary>
	/// -入力文字をUnicode化する
	/// </summary>
	void ToUnicode();

	/// <summary>
	/// -Unicode文字列を描画する
	/// </summary>
	/// <param name="position">描画位置</param>
	void DrawString(Vector2 position, Vector2 Size, Vector2 coeff, unsigned int color) const;

	/// @brief - Unicode文字列を描画する
	/// @param wString ワイド文字列(Unicode文字列)
	/// @param file 読み込むファイル名
	/// @param position 描画位置
	/// @param Size 
	/// @param color 
	static void DrawString(const std::wstring wString, const std::string font, Vector2 position, Vector2 Size, Vector2 coeff, unsigned int color);



	inline static void AddFont(const std::string &file_name, Vector2 Size) {
		fontList[file_name].SetFont(file_name, Size);
	}

private:
	static std::unordered_map<std::string, FontTexture> fontList;

	// -文字列
	std::string charString_ = {};

	// -ワイド文字列を格納するバッファ
	std::wstring wideString_ = {};
};