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

	// -�t�H���g�T�C�Y
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
	/// -��������
	/// </summary>
	/// <param name="String">���͕�����</param>
	void TypeString(const std::string String);

	/// <summary>
	/// -��������
	/// </summary>
	/// <param name="wString">���͕�����</param>
	void TypeString(const std::wstring wString);

	/// <summary>
	/// -�����ǉ�
	/// </summary>
	/// <param name="CharString">�ǉ�������</param>
	void AddString(const std::string String);

	/// <summary>
	/// -���͕�����Unicode������
	/// </summary>
	void ToUnicode();

	/// <summary>
	/// -Unicode�������`�悷��
	/// </summary>
	/// <param name="position">�`��ʒu</param>
	void DrawString(Vector2 position, Vector2 Size, Vector2 coeff, unsigned int color) const;

	/// @brief - Unicode�������`�悷��
	/// @param wString ���C�h������(Unicode������)
	/// @param file �ǂݍ��ރt�@�C����
	/// @param position �`��ʒu
	/// @param Size 
	/// @param color 
	static void DrawString(const std::wstring wString, const std::string font, Vector2 position, Vector2 Size, Vector2 coeff, unsigned int color);



	inline static void AddFont(const std::string &file_name, Vector2 Size) {
		fontList[file_name].SetFont(file_name, Size);
	}

private:
	static std::unordered_map<std::string, FontTexture> fontList;

	// -������
	std::string charString_ = {};

	// -���C�h��������i�[����o�b�t�@
	std::wstring wideString_ = {};
};