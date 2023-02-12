#pragma once

#include "./Math/Vector2.hpp"
#include "./Render/SpriteClass.hpp"

class Box
{
public:
	Box();
	Box(const Vector2 &position, const Vector2 &radius);

	inline Vector2 GetPosition() { return position; }
	inline Vector2 GetRadius() { return radius; }

	inline void SetPosition(const Vector2 &position) { this->position = position; }

	inline void SetRadius(const Vector2 &radius) { this->radius = radius; }
public:
	Vector2 position;
	Vector2 radius;

};

class Ball
{
public:

	Ball();
	Ball(const Vector2 &position, const Vector2 &radius);

	inline Vector2 GetPosition() { return position; }
	inline float GetRadius() { return radius.x; }

	inline void SetPosition(const Vector2 &position) { this->position = position; }

	inline void SetRadius(const float &radius) { this->radius = { radius,radius }; }

public:
	Vector2 position;
	Vector2 radius;
};
//class Ray;

class Line {
public:
	Line() : start_(ZeroVector2), end_(ZeroVector2) {};
	Line(const Vector2 &start_, const Vector2 &end_) : start_(start_), end_(end_) {};
	Vector2 start_;
	Vector2 end_;

	inline Vector2 GetDirection() { return (end_ - start_); }
	inline float Length() { return (end_ - start_).Length(); }
	inline Line Nomalize() { return { start_,(end_ - start_).Nomalize() + start_ }; }

	//inline Ray GetRay() const { return { start_, end_ - start_ }; }
};

class Ray {
public:
	Ray() : origin(ZeroVector2), direction(ZeroVector2) {};
	Ray(const Vector2 &origin, const Vector2 &direction) : origin(origin), direction(direction) {};
	Vector2 origin;
	Vector2 direction;

	inline Ray Nomalize() const { return { origin,direction.Nomalize() }; }
	// 長さ * スカラー
	inline Ray operator*(const float &s) const { return { origin,direction * s }; }

	inline Vector2 GetEnd() const { return direction + origin; }

	// Rayをtだけ進めたときの位置を取得する
	inline Vector2 operator()(float t) const { return origin + t * direction; }

};

class Object :public Ball
{
public:
	Object();
	Object(const Vector2 &position, const Vector2 &radius, const float &scale);

	Object &operator=(const SpriteClass &other) {
		spriteBox = (other);
	}

	Object &operator=(const SpriteBox &other) {
		spriteBox = (other);
	}


	virtual	void Draw() const;

	const SpriteBox &GetSpriteBox() const { return spriteBox; }
	SpriteBox &GetSpriteBox() { return spriteBox; }


	Vector2 velocity;
	Vector2 acceleration;

	// 向いている方向
	Vector2 facing;


	bool isGround;
	bool isAlive = true;

	virtual inline void Input() {}; // 入力やフラグ立て
	virtual void Update();
	virtual void Move();
	virtual void Init();
	//	void MapChipHit();
private:

	Vector2 prePosition;
	
	// テクスチャ描画ボックス
	SpriteBox spriteBox;
};

