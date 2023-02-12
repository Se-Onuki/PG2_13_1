#pragma once

#include "Object/Object.hpp"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#include <cmath>

// Ray‚ÆBall‚ªŒğ·‚·‚é‚©‚ğ”»’è‚·‚é
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


// Ray‚ğ”½Ë‚³‚¹‚é
Ray ReflectRay(const Ray &ray, const Vector2 &normal, float t);

/// <summary>
/// RayˆÚ“®ŠÖ”
/// </summary>
/// <param name="ray">ˆÚ“®Ray</param>
/// <param name="Obj">áŠQ•¨</param>
/// <returns>’†Œp“_ƒŠƒXƒg</returns>
std::vector<Vector2> MoveRay(Ray &ray, const Ball &Obj);

bool HitCheckPath(const std::vector<Vector2> &path, const float &radiusA, const Vector2 &position, const float &radiusB);