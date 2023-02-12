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

	// ���ˌ��Ray�𐶐�����
	Vector2 reflectedDirection = (ray.direction * (1 - t)).Reflect(normal);
	Ray reflectedRay(ray(t), reflectedDirection);

	return reflectedRay;
}




std::vector<Vector2> MoveRay(Ray &ray, const Ball &Obj) {

	Ray rayBuf = ray;
	std::vector<Vector2> collision;
	collision.push_back(rayBuf.origin);


	// Ray��Ball����������ԁARay�𔽎˂�����
	while (IsIntersect(rayBuf, Obj)) {
		// Ray��Ball�̌�_���擾����
		Vector2 intersection = GetIntersection(rayBuf, Obj);
		collision.push_back(intersection);

		// Ray�̐i�s�x���擾����
		float IntLength = (intersection - rayBuf.origin).Length();
		float t = IntLength / rayBuf.direction.Length();


		// Ball�̖@��
		Vector2 normal = (intersection - Obj.position).Nomalize();

		// Ray�𔽎˂�����
		rayBuf = ReflectRay(rayBuf, normal, t);
	}

	collision.push_back(rayBuf.GetEnd());


	// Ray���ړ�������
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