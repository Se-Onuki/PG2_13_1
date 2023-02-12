#include "Object/ObjectController.hpp"

#include "BaseData.hpp"

Vector2 GetIntersection(const Ray &ray, const Ball &Obj) {

	Ray nomalRay(ray.origin - Obj.position, ray.direction.Nomalize());

	float OV = nomalRay.origin * nomalRay.direction;
	float OO = nomalRay.origin * nomalRay.origin;
	float s = OV * OV - OO + Obj.radius.x * Obj.radius.x;

	float sq = std::sqrtf(s);
	float t[2] = { -OV - sq ,-OV + sq };

	float length;

	if (t[0] > 0.1f && t[0] <= ray.direction.Length() && (t[1] >= 0.0f) && t[0] < t[1]) {
		length = t[0];
	}
	else {
		length = t[1];
	}

	return nomalRay.origin + nomalRay.direction * length + Obj.position;

}


Ray ReflectRay(const Ray &ray, const Vector2 &normal, float t) {

	// 反射後のRayを生成する
	Vector2 reflectedDirection = (ray.direction * (1 - t)).Reflect(normal);
	Ray reflectedRay(ray(t), reflectedDirection);

	return reflectedRay;
}




std::vector<Vector2> MoveRay(Ray &ray, const Ball &Obj) {

	Ray rayBuf = ray;
	std::vector<Vector2> collision;
	collision.push_back(rayBuf.origin);


	// RayとBallが交差する間、Rayを反射させる
	while (IsIntersect(rayBuf, Obj)) {
		// RayとBallの交点を取得する
		Vector2 intersection = GetIntersection(rayBuf, Obj);
		collision.push_back(intersection);

		// Rayの進行度を取得する
		float IntLength = (intersection - rayBuf.origin).Length();
		float t = IntLength / rayBuf.direction.Length();


		// Ballの法線
		Vector2 normal = (intersection - Obj.position).Nomalize();

		// Rayを反射させる
		rayBuf = ReflectRay(rayBuf, normal, t);
	}

	collision.push_back(rayBuf.GetEnd());


	// Rayを移動させる
	ray.origin = rayBuf.GetEnd();
	ray.direction = rayBuf.direction.Nomalize() * ray.direction.Length();

	return collision;
}

bool HitCheckPath(const std::vector<Vector2> &path, const float &radiusA, const Vector2 &position, const float &radiusB) {
	for (int i = 0; i < path.size() - 1; i++) {
		if (radiusA + radiusB >= Ellipse2LineLength(position, path[i], path[i + 1])) {
			return true;
		}
	}

	return false;
}