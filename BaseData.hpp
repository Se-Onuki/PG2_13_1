#pragma once

#include <Novice.h>
#include "Math/Vector2.hpp"


/// (0 <= x <= 10)のような形のマクロ関数
#define isInner(leftNumber,leftOperator,number,rightOperator,rightNumber) (((leftNumber)leftOperator(number)) && ((number)rightOperator(rightNumber)))


// 定数宣言

/// スクリーン座標とワールド座標で相互変換する原点
//const int WorldPos = ScreenSize.y;


/// MenuUIの最大項目数
const int SetMaxMenuItem = 16;


// 変数宣言

extern int flame;


//
///// <summary>
//	/// Lineクラス
//	/// </summary>
//	/// <param name="start">始点位置ベクトル</param>
//	/// <param name="end">終点位置ベクトル</param>
//	/// <param name="norm">ノルム</param>
//	/// <param name="color">色 0xRRGGBBAA</param>
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
//	/// Ballクラス
//	/// </summary>
//	/// <param name="position">位置ベクトル</param>
//	/// <param name="velocity">移動速度ベクトル</param>
//	/// <param name="acceleration">加速度ベクトル</param>
//	/// <param name="radius">半径</param>
//	/// <param name="norm">ノルム</param>
//	/// <param name="mass">重量</param>
//	/// <param name="color">色 0xRRGGBBAA</param>
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
//	/// Boxクラス
//	/// </summary>
//	/// <param name="position">位置ベクトル</param>
//	/// <param name="velocity">移動速度ベクトル</param>
//	/// <param name="acceleration">加速度ベクトル</param>
//	/// <param name="radius">半径</param>
//	/// <param name="norm">ノルム</param>
//	/// <param name="mass">重量</param>
//	/// <param name="color">色 0xRRGGBBAA</param>
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
/// 乱数生成関数
/// </summary>
/// <param name="min">下限</param>
/// <param name="max">上限</param>
/// <returns>乱数</returns>
float GetRandom(float min, float max);


/// <summary>
/// 弧度法を度数法にする
/// </summary>
/// <param name="radian">弧度法</param>
/// <returns>度数法</returns>
float Radian2Degree(float radian);

/// <summary>
/// 度数法を弧度法にする
/// </summary>
/// <param name="degree">度数法</param>
/// <returns>弧度法</returns>
float Degree2Radian(float degree);


/// <summary>
/// 位置ベクトルAからBへの長さを出す関数
/// </summary>
/// <param name="start">始点位置ベクトル</param>
/// <param name="end">終点位置ベクトル</param>
/// <returns>AからBへの長さ</returns>
float Length(Vector2 start, Vector2 end);


/// <summary>
/// ボール同士の当たり判定
/// </summary>
/// <param name="ballA">ボールA</param>
/// <param name="ballB">ボールB</param>
/// <returns>接触の真偽</returns>
bool BallCollision(Vector2 positionA, float radiusA, Vector2 positionB, float radiusB);

/// <summary>
/// ベクトルの正規化
/// </summary>
/// <param name="OriginalVector2">元のベクトル</param>
/// <returns>正規化したベクトル</returns>
Vector2 Nomalize(Vector2 OriginalVector2);


/// <summary>
/// 二次元内積関数
/// </summary>
/// <param name="startA">線分Aの始点</param>
/// <param name="endA">線分Aの終点</param>
/// <param name="startB">線分Bの始点</param>
/// <param name="endB">線分Bの終点</param>
/// <param name="normalizeFlagA"></param>
/// <param name="normalizeFlagB"></param>
/// <returns>内積計算の結果</returns>
float DotProduct(Vector2 startA, Vector2 endA, Vector2 startB, Vector2 endB, bool normalizeFlagA, bool normalizeFlagB);



/// <summary>
/// 二次元外積関数
/// </summary>
/// <param name="startA">線分Aの始点</param>
/// <param name="endA">線分Aの終点</param>
/// <param name="startB">線分Bの始点</param>
/// <param name="endB">線分Bの終点</param>
/// <param name="normalizeFlagA"></param>
/// <param name="normalizeFlagB"></param>
/// <returns>内積計算の結果</returns>
float CrossProduct(Vector2 startA, Vector2 endA, Vector2 startB, Vector2 endB, bool normalizeFlagA, bool normalizeFlagB);



/// <summary>
/// Clamp関数
/// </summary>
/// <param name="number">元となる数</param>
/// <param name="min">下限</param>
/// <param name="max">上限</param>
/// <returns>収めた値</returns>
float Clamp(float number, float min, float max);



/// <summary>
/// 線が交差しているか
/// </summary>
/// <param name="startA">線分Aの始点</param>
/// <param name="endA">線分Aの終点</param>
/// <param name="startB">線分Bの始点</param>
/// <param name="endB">線分Bの終点</param>
/// <returns>交差の真偽値</returns>
bool isCross(Vector2 startA, Vector2 endA, Vector2 startB, Vector2 endB);


/// <summary>
/// 円と線分の間の距離
/// </summary>
/// <param name="Ellipse">円の中心</param>
/// <param name="start">線分の終点</param>
/// <param name="end">線分の始点</param>
/// <returns>距離の値</returns>
float Ellipse2LineLength(Vector2 Ellipse, Vector2 start, Vector2 end);



/// <summary>
	/// 箱の内にマウスが入っているか
	/// </summary>
	/// <param name="centor">箱の中心座標</param>
	/// <param name="size">箱の大きさ</param>
bool IsMouseInBox(Vector2 centor, Vector2 size);


/// <summary>
	/// 箱の内にマウスが入っているか
	/// </summary>
	/// <param name="centor">箱の中心座標</param>
	/// <param name="size">箱の大きさ</param>
	/// <param name="position">判断点</param>
	/// <returns> 入っているかの真偽</returns>
bool IsPositionInBox(Vector2 centor, Vector2 size, Vector2 position);


/// <summary>
/// ベクトルを回転させる
/// </summary>
/// <param name="OriginalVector">元のベクトル</param>
/// <param name="radian">回転量(弧度法)</param>
/// <returns>回転後のベクトル</returns>
Vector2 RotateVector2(Vector2 OriginalVector, float radian);

/// <summary>
/// ベクトルA上の交点の割合を出す
/// </summary>
/// <param name="startA">ベクトルAの始点</param>
/// <param name="endA">ベクトルBの終点</param>
/// <param name="startB">ベクトルBの始点</param>
/// <param name="endB">ベクトルBの終点</param>
/// <returns>0.0から1.0の割合を出す</returns>
float CrossDistance(const Vector2 &startA, const Vector2 &endA, const Vector2 &startB, const Vector2 &endB);

/// <summary>
/// ベクトルの交点の座標を出す
/// </summary>
/// <param name="startA">Aベクトルの始点</param>
/// <param name="endA">Aベクトルの終点</param>
/// <param name="startB">Bベクトルの始点</param>
/// <param name="endB">Bベクトルの終点</param>
/// <returns>ベクトルの交点</returns>
Vector2 VectorCrossPosition(const Vector2 &startA, const Vector2 &endA, const Vector2 &startB, const Vector2 &endB);


/// <summary>
/// 交点からの反射ベクトルを返す
/// </summary>
/// <param name="MoveVecotor2">動くベクトル</param>
/// <param name="SurfaceVector2">反射面のベクトル</param>
/// <returns>反射後の座標</returns>
Vector2 ReflectionVector2(Vector2 MoveStart, Vector2 MoveEnd, Vector2 SurfaceStart, Vector2 SurfaceEnd);



/// <summary>
/// ベクトル反射
/// </summary>
/// <param name="vec">交点より後の移動ベクトル</param>
/// <param name="normal">法線ベクトル</param>
/// <returns>反射ベクトル</returns>
Vector2 ReflectVector2(Vector2 vec, Vector2 normal);

/// <summary>
/// ベクトルに対する法線を取得(雑)
/// </summary>
/// <param name="vec">ベクトル</param>
/// <returns>法線</returns>
inline Vector2 GetNormal2(const Vector2 &vec) {
	return Vector2{ vec.y,vec.x }.Nomalize();
}
