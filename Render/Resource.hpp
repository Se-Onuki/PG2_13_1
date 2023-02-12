#pragma once

#include "Math/Vector2.hpp"
#include "./Object/Object.hpp"
#include "./Render/SpriteClass.hpp"

// 定数宣言

/// スクリーン座標とワールド座標で相互変換する原点
const int WorldPos = ScreenSize.y;

/// <summary>
/// スクリーン座標とワールド座標で相互変換する関数。
/// </summary>
/// <param name="y">変換したい値</param>
/// <returns>変換後の値</returns>
float ToWorld(float y);


/// <summary>
/// スクリーン座標とワールド座標で相互変換する関数。
/// </summary>
/// <param name="position">変換したい値</param>
/// <returns>変換後の値</returns>
Vector2 ToWorld(Vector2 position);


Vector2 ToScreenPosition(Vector2 DefaultPosition);


/// <summary>
	/// 四角形描画
	/// </summary>
	/// <param name="centor">描画する四角形の中心座標</param>
	/// <param name="size">描画する四角形の大きさ</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
void DrawQuadFunction(Vector2 centor, Vector2 size, int srcX, int srcY, int srcW, int srcH, unsigned int textureHandle, unsigned int color);


/// <summary>
	/// 四角形描画 : 大本
	/// </summary>
	/// <param name="centor">描画する四角形の中心座標</param>
	/// <param name="size">描画する四角形の大きさ</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="angle">描画の回転角(radian)</param>
	/// <param name="color">描画するスプライトの色</param>
void DrawObject(const Vector2 &centor, const Vector2 &size, const int &srcX, const int &srcY, const int &srcW, const int &srcH, const unsigned int &textureHandle, const unsigned int &color, const Vector2 &scale, const float &angle, const Matrix3x3 &vpVpMatrix);



/// <summary>
	/// 四角形描画 
	/// </summary>
	/// <param name="centor">描画する四角形の中心座標</param>
	/// <param name="size">描画する四角形の大きさ</param>
	/// <param name="spriteBox">描画する画像</param>
	/// <param name="angle">描画の回転角(radian)</param>
	/// <param name="color">描画するスプライトの色</param>
void DrawObject(const Vector2 &centor, const Vector2 &size, const SpriteBox spriteBox, const Vector2 &scale, const float &angle, const Matrix3x3 &vpVpMatrix);


/// <summary>
	/// ゲーム内オブジェクト描画
	/// </summary>
	/// <param name="centor">描画する四角形の中心座標</param>
	/// <param name="size">描画する四角形の大きさ</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
void DrawObject(Vector2 centor, Vector2 size, int srcX, int srcY, int srcW, int srcH, unsigned int textureHandle, unsigned int color);


/// <summary>
	/// ゲーム内オブジェクト描画
	/// </summary>
	/// <param name="centor">描画する四角形の中心座標</param>
	/// <param name="size">描画する四角形の大きさ</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
void DrawObject(Vector2 centor, Vector2 size, int srcX, int srcY, int srcW, int srcH, unsigned int textureHandle, unsigned int color);


/// <summary>
	/// ゲーム内オブジェクト描画
	/// </summary>
	/// <param name="centor">描画する四角形の中心座標</param>
	/// <param name="size">描画する四角形の大きさ</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="angle">描画の回転角(radian)</param>
	/// <param name="color">描画するスプライトの色</param>
void DrawObject(Vector2 centor, Vector2 size, int srcX, int srcY, int srcW, int srcH, unsigned int textureHandle, float angle, unsigned int color);

//
///// <summary>
//	/// ゲーム内オブジェクト描画
//	/// </summary>
//	/// <param name="entity">描画するエンティティ</param>
//void DrawObject(const Entity &entity);
//
///// <summary>
//	/// ゲーム内オブジェクト描画
//	/// </summary>
//	/// <param name="entity">描画するエンティティ</param>
//	/// <param name="angle">描画の回転角(radian)</param>
//void DrawObject(const Entity &entity, const float &angle);



/// <summary>
	/// ゲーム内オブジェクト描画
	/// </summary>
	/// <param name="object">描画するオブジェクト</param>
	/// <param name="sprite">描画するスプライト</param>
void DrawObject(const Object &object, const SpriteClass &sprite);

/// <summary>
	/// ゲーム内オブジェクト描画
	/// </summary>
	/// <param name="object">描画するオブジェクト</param>
	/// <param name="sprite">描画するスプライト</param>
void DrawObject(const Object &object, const SpriteBox &sprite);

/// <summary>
	/// ゲーム内オブジェクト描画
	/// </summary>
	/// <param name="object">描画するオブジェクト</param>
	/// <param name="sprite">描画するスプライト</param>
	/// <param name="angle">描画の回転角(radian)</param>
void DrawObject(const Box &object, const SpriteBox &sprite, const float &angle);

/// <summary>
	/// ゲーム内オブジェクト描画
	/// </summary>
	/// <param name="object">描画するオブジェクト</param>
void DrawObject(const Object &object);

/// <summary>
/// 線オブジェクトの描画
/// </summary>
/// <param name="start">始点</param>
/// <param name="end">終点</param>
/// <param name="color">色</param>
/// <param name="vpVpMatrix">ビュー投影行列</param>
void DrawLineObject(const Vector2 &start, const Vector2 &end, const unsigned int &color, const Matrix3x3 &vpVpMatrix);
