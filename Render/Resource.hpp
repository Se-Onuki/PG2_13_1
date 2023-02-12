#pragma once

#include "Math/Vector2.hpp"
#include "./Object/Object.hpp"
#include "./Render/SpriteClass.hpp"

// �萔�錾

/// �X�N���[�����W�ƃ��[���h���W�ő��ݕϊ����錴�_
const int WorldPos = ScreenSize.y;

/// <summary>
/// �X�N���[�����W�ƃ��[���h���W�ő��ݕϊ�����֐��B
/// </summary>
/// <param name="y">�ϊ��������l</param>
/// <returns>�ϊ���̒l</returns>
float ToWorld(float y);


/// <summary>
/// �X�N���[�����W�ƃ��[���h���W�ő��ݕϊ�����֐��B
/// </summary>
/// <param name="position">�ϊ��������l</param>
/// <returns>�ϊ���̒l</returns>
Vector2 ToWorld(Vector2 position);


Vector2 ToScreenPosition(Vector2 DefaultPosition);


/// <summary>
	/// �l�p�`�`��
	/// </summary>
	/// <param name="centor">�`�悷��l�p�`�̒��S���W</param>
	/// <param name="size">�`�悷��l�p�`�̑傫��</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
void DrawQuadFunction(Vector2 centor, Vector2 size, int srcX, int srcY, int srcW, int srcH, unsigned int textureHandle, unsigned int color);


/// <summary>
	/// �l�p�`�`�� : ��{
	/// </summary>
	/// <param name="centor">�`�悷��l�p�`�̒��S���W</param>
	/// <param name="size">�`�悷��l�p�`�̑傫��</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="angle">�`��̉�]�p(radian)</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
void DrawObject(const Vector2 &centor, const Vector2 &size, const int &srcX, const int &srcY, const int &srcW, const int &srcH, const unsigned int &textureHandle, const unsigned int &color, const Vector2 &scale, const float &angle, const Matrix3x3 &vpVpMatrix);



/// <summary>
	/// �l�p�`�`�� 
	/// </summary>
	/// <param name="centor">�`�悷��l�p�`�̒��S���W</param>
	/// <param name="size">�`�悷��l�p�`�̑傫��</param>
	/// <param name="spriteBox">�`�悷��摜</param>
	/// <param name="angle">�`��̉�]�p(radian)</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
void DrawObject(const Vector2 &centor, const Vector2 &size, const SpriteBox spriteBox, const Vector2 &scale, const float &angle, const Matrix3x3 &vpVpMatrix);


/// <summary>
	/// �Q�[�����I�u�W�F�N�g�`��
	/// </summary>
	/// <param name="centor">�`�悷��l�p�`�̒��S���W</param>
	/// <param name="size">�`�悷��l�p�`�̑傫��</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
void DrawObject(Vector2 centor, Vector2 size, int srcX, int srcY, int srcW, int srcH, unsigned int textureHandle, unsigned int color);


/// <summary>
	/// �Q�[�����I�u�W�F�N�g�`��
	/// </summary>
	/// <param name="centor">�`�悷��l�p�`�̒��S���W</param>
	/// <param name="size">�`�悷��l�p�`�̑傫��</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
void DrawObject(Vector2 centor, Vector2 size, int srcX, int srcY, int srcW, int srcH, unsigned int textureHandle, unsigned int color);


/// <summary>
	/// �Q�[�����I�u�W�F�N�g�`��
	/// </summary>
	/// <param name="centor">�`�悷��l�p�`�̒��S���W</param>
	/// <param name="size">�`�悷��l�p�`�̑傫��</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X</param>
	/// <param name="srcY">�摜��̕`�悵�����͈͍�����W Y</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="angle">�`��̉�]�p(radian)</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
void DrawObject(Vector2 centor, Vector2 size, int srcX, int srcY, int srcW, int srcH, unsigned int textureHandle, float angle, unsigned int color);

//
///// <summary>
//	/// �Q�[�����I�u�W�F�N�g�`��
//	/// </summary>
//	/// <param name="entity">�`�悷��G���e�B�e�B</param>
//void DrawObject(const Entity &entity);
//
///// <summary>
//	/// �Q�[�����I�u�W�F�N�g�`��
//	/// </summary>
//	/// <param name="entity">�`�悷��G���e�B�e�B</param>
//	/// <param name="angle">�`��̉�]�p(radian)</param>
//void DrawObject(const Entity &entity, const float &angle);



/// <summary>
	/// �Q�[�����I�u�W�F�N�g�`��
	/// </summary>
	/// <param name="object">�`�悷��I�u�W�F�N�g</param>
	/// <param name="sprite">�`�悷��X�v���C�g</param>
void DrawObject(const Object &object, const SpriteClass &sprite);

/// <summary>
	/// �Q�[�����I�u�W�F�N�g�`��
	/// </summary>
	/// <param name="object">�`�悷��I�u�W�F�N�g</param>
	/// <param name="sprite">�`�悷��X�v���C�g</param>
void DrawObject(const Object &object, const SpriteBox &sprite);

/// <summary>
	/// �Q�[�����I�u�W�F�N�g�`��
	/// </summary>
	/// <param name="object">�`�悷��I�u�W�F�N�g</param>
	/// <param name="sprite">�`�悷��X�v���C�g</param>
	/// <param name="angle">�`��̉�]�p(radian)</param>
void DrawObject(const Box &object, const SpriteBox &sprite, const float &angle);

/// <summary>
	/// �Q�[�����I�u�W�F�N�g�`��
	/// </summary>
	/// <param name="object">�`�悷��I�u�W�F�N�g</param>
void DrawObject(const Object &object);

/// <summary>
/// ���I�u�W�F�N�g�̕`��
/// </summary>
/// <param name="start">�n�_</param>
/// <param name="end">�I�_</param>
/// <param name="color">�F</param>
/// <param name="vpVpMatrix">�r���[���e�s��</param>
void DrawLineObject(const Vector2 &start, const Vector2 &end, const unsigned int &color, const Matrix3x3 &vpVpMatrix);
