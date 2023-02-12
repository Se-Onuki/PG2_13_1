#pragma once

#include <Novice.h>
#include "Math/Vector2.hpp"


/// (0 <= x <= 10)�̂悤�Ȍ`�̃}�N���֐�
#define isInner(leftNumber,leftOperator,number,rightOperator,rightNumber) (((leftNumber)leftOperator(number)) && ((number)rightOperator(rightNumber)))


// �萔�錾

/// �X�N���[�����W�ƃ��[���h���W�ő��ݕϊ����錴�_
//const int WorldPos = ScreenSize.y;


/// MenuUI�̍ő區�ڐ�
const int SetMaxMenuItem = 16;


// �ϐ��錾

extern int flame;


//
///// <summary>
//	/// Line�N���X
//	/// </summary>
//	/// <param name="start">�n�_�ʒu�x�N�g��</param>
//	/// <param name="end">�I�_�ʒu�x�N�g��</param>
//	/// <param name="norm">�m����</param>
//	/// <param name="color">�F 0xRRGGBBAA</param>
//class Line
//{
//public:
//	Vector2 start;
//	Vector2 end;
//	float norm;
//	unsigned int color;
//
//	void DrawLine();
//};
//
//
///// <summary>
//	/// Ball�N���X
//	/// </summary>
//	/// <param name="position">�ʒu�x�N�g��</param>
//	/// <param name="velocity">�ړ����x�x�N�g��</param>
//	/// <param name="acceleration">�����x�x�N�g��</param>
//	/// <param name="radius">���a</param>
//	/// <param name="norm">�m����</param>
//	/// <param name="mass">�d��</param>
//	/// <param name="color">�F 0xRRGGBBAA</param>
//class Ball
//{
//public:
//	Vector2 position;
//	Vector2 velocity;
//	Vector2 acceleration;
//	float radius;
//	float norm;
//	float mass;
//	unsigned int color = 0xFFFFFFFF;
//};
//
///// <summary>
//	/// Box�N���X
//	/// </summary>
//	/// <param name="position">�ʒu�x�N�g��</param>
//	/// <param name="velocity">�ړ����x�x�N�g��</param>
//	/// <param name="acceleration">�����x�x�N�g��</param>
//	/// <param name="radius">���a</param>
//	/// <param name="norm">�m����</param>
//	/// <param name="mass">�d��</param>
//	/// <param name="color">�F 0xRRGGBBAA</param>
//class Box
//{
//public:
//	Vector2 position = ZeroVector2;
//	Vector2 velocity = ZeroVector2;
//	Vector2 acceleration = ZeroVector2;
//	Vector2 radius = ZeroVector2;
//	float norm = 0;
//	float mass = 0;
//	unsigned int color = 0;
//};

/// <summary>
/// ���������֐�
/// </summary>
/// <param name="min">����</param>
/// <param name="max">���</param>
/// <returns>����</returns>
float GetRandom(float min, float max);


/// <summary>
/// �ʓx�@��x���@�ɂ���
/// </summary>
/// <param name="radian">�ʓx�@</param>
/// <returns>�x���@</returns>
float Radian2Degree(float radian);

/// <summary>
/// �x���@���ʓx�@�ɂ���
/// </summary>
/// <param name="degree">�x���@</param>
/// <returns>�ʓx�@</returns>
float Degree2Radian(float degree);


/// <summary>
/// �ʒu�x�N�g��A����B�ւ̒������o���֐�
/// </summary>
/// <param name="start">�n�_�ʒu�x�N�g��</param>
/// <param name="end">�I�_�ʒu�x�N�g��</param>
/// <returns>A����B�ւ̒���</returns>
float Length(Vector2 start, Vector2 end);


/// <summary>
/// �{�[�����m�̓����蔻��
/// </summary>
/// <param name="ballA">�{�[��A</param>
/// <param name="ballB">�{�[��B</param>
/// <returns>�ڐG�̐^�U</returns>
bool BallCollision(Vector2 positionA, float radiusA, Vector2 positionB, float radiusB);

/// <summary>
/// �x�N�g���̐��K��
/// </summary>
/// <param name="OriginalVector2">���̃x�N�g��</param>
/// <returns>���K�������x�N�g��</returns>
Vector2 Nomalize(Vector2 OriginalVector2);


/// <summary>
/// �񎟌����ϊ֐�
/// </summary>
/// <param name="startA">����A�̎n�_</param>
/// <param name="endA">����A�̏I�_</param>
/// <param name="startB">����B�̎n�_</param>
/// <param name="endB">����B�̏I�_</param>
/// <param name="normalizeFlagA"></param>
/// <param name="normalizeFlagB"></param>
/// <returns>���όv�Z�̌���</returns>
float DotProduct(Vector2 startA, Vector2 endA, Vector2 startB, Vector2 endB, bool normalizeFlagA, bool normalizeFlagB);



/// <summary>
/// �񎟌��O�ϊ֐�
/// </summary>
/// <param name="startA">����A�̎n�_</param>
/// <param name="endA">����A�̏I�_</param>
/// <param name="startB">����B�̎n�_</param>
/// <param name="endB">����B�̏I�_</param>
/// <param name="normalizeFlagA"></param>
/// <param name="normalizeFlagB"></param>
/// <returns>���όv�Z�̌���</returns>
float CrossProduct(Vector2 startA, Vector2 endA, Vector2 startB, Vector2 endB, bool normalizeFlagA, bool normalizeFlagB);



/// <summary>
/// Clamp�֐�
/// </summary>
/// <param name="number">���ƂȂ鐔</param>
/// <param name="min">����</param>
/// <param name="max">���</param>
/// <returns>���߂��l</returns>
float Clamp(float number, float min, float max);



/// <summary>
/// �����������Ă��邩
/// </summary>
/// <param name="startA">����A�̎n�_</param>
/// <param name="endA">����A�̏I�_</param>
/// <param name="startB">����B�̎n�_</param>
/// <param name="endB">����B�̏I�_</param>
/// <returns>�����̐^�U�l</returns>
bool isCross(Vector2 startA, Vector2 endA, Vector2 startB, Vector2 endB);


/// <summary>
/// �~�Ɛ����̊Ԃ̋���
/// </summary>
/// <param name="Ellipse">�~�̒��S</param>
/// <param name="start">�����̏I�_</param>
/// <param name="end">�����̎n�_</param>
/// <returns>�����̒l</returns>
float Ellipse2LineLength(Vector2 Ellipse, Vector2 start, Vector2 end);



/// <summary>
	/// ���̓��Ƀ}�E�X�������Ă��邩
	/// </summary>
	/// <param name="centor">���̒��S���W</param>
	/// <param name="size">���̑傫��</param>
bool IsMouseInBox(Vector2 centor, Vector2 size);


/// <summary>
	/// ���̓��Ƀ}�E�X�������Ă��邩
	/// </summary>
	/// <param name="centor">���̒��S���W</param>
	/// <param name="size">���̑傫��</param>
	/// <param name="position">���f�_</param>
	/// <returns> �����Ă��邩�̐^�U</returns>
bool IsPositionInBox(Vector2 centor, Vector2 size, Vector2 position);


/// <summary>
/// �x�N�g������]������
/// </summary>
/// <param name="OriginalVector">���̃x�N�g��</param>
/// <param name="radian">��]��(�ʓx�@)</param>
/// <returns>��]��̃x�N�g��</returns>
Vector2 RotateVector2(Vector2 OriginalVector, float radian);

/// <summary>
/// �x�N�g��A��̌�_�̊������o��
/// </summary>
/// <param name="startA">�x�N�g��A�̎n�_</param>
/// <param name="endA">�x�N�g��B�̏I�_</param>
/// <param name="startB">�x�N�g��B�̎n�_</param>
/// <param name="endB">�x�N�g��B�̏I�_</param>
/// <returns>0.0����1.0�̊������o��</returns>
float CrossDistance(const Vector2 &startA, const Vector2 &endA, const Vector2 &startB, const Vector2 &endB);

/// <summary>
/// �x�N�g���̌�_�̍��W���o��
/// </summary>
/// <param name="startA">A�x�N�g���̎n�_</param>
/// <param name="endA">A�x�N�g���̏I�_</param>
/// <param name="startB">B�x�N�g���̎n�_</param>
/// <param name="endB">B�x�N�g���̏I�_</param>
/// <returns>�x�N�g���̌�_</returns>
Vector2 VectorCrossPosition(const Vector2 &startA, const Vector2 &endA, const Vector2 &startB, const Vector2 &endB);


/// <summary>
/// ��_����̔��˃x�N�g����Ԃ�
/// </summary>
/// <param name="MoveVecotor2">�����x�N�g��</param>
/// <param name="SurfaceVector2">���˖ʂ̃x�N�g��</param>
/// <returns>���ˌ�̍��W</returns>
Vector2 ReflectionVector2(Vector2 MoveStart, Vector2 MoveEnd, Vector2 SurfaceStart, Vector2 SurfaceEnd);



/// <summary>
/// �x�N�g������
/// </summary>
/// <param name="vec">��_����̈ړ��x�N�g��</param>
/// <param name="normal">�@���x�N�g��</param>
/// <returns>���˃x�N�g��</returns>
Vector2 ReflectVector2(Vector2 vec, Vector2 normal);

/// <summary>
/// �x�N�g���ɑ΂���@�����擾(�G)
/// </summary>
/// <param name="vec">�x�N�g��</param>
/// <returns>�@��</returns>
inline Vector2 GetNormal2(const Vector2 &vec) {
	return Vector2{ vec.y,vec.x }.Nomalize();
}
