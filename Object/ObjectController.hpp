#pragma once

#include "Object/Object.hpp"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#include <cmath>

// RayとBallが交差するかを判定する
inline bool IsIntersect(const Ray &ray, const Ball &ball) {
	/*
	if ((ball.position - ray.origin).Length() <= ball.radius.x || (ball.position - ray.origin + ray.direction).Length() <= ball.radius.x)return true;

	float distance = fabs((ball.position - ray.origin) ^ ray.direction.Nomalize());
	if (distance <= ball.radius.x) return true;

	return false;
	*/

	return (ray.origin + ray.direction - ball.position).Length() >= ball.radius.x;
	

}



Vector2 GetIntersection(const Ray &ray, const Ball &Obj);


// Rayを反射させる
Ray ReflectRay(const Ray &ray, const Vector2 &normal, float t);

/// <summary>
/// Ray移動関数
/// </summary>
/// <param name="ray">移動Ray</param>
/// <param name="Obj">障害物</param>
/// <returns>中継点リスト</returns>
std::vector<Vector2> MoveRay(Ray &ray, const Ball &Obj);

bool HitCheckPath(const std::vector<Vector2> &path, const float &radiusA, const Vector2 &position, const float &radiusB);