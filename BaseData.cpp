#pragma	once

#include "baseData.hpp"


#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Windows.h>

#include <time.h>
#include <stdlib.h>

#include "Render/Resource.hpp"
#include "Input/KeyBoard.hpp"


#include "Math/Vector2.hpp"
#include "Math/Math.hpp"

#include <random>
//void Line::DrawLine() {
//	Novice::DrawLine(start.x, ToWorld(start.y), end.x, ToWorld(end.y), color);
//}


int flame = 0;

float GetRandom(float min, float max) {
	static std::mt19937 gen;
	static bool init;
	if (!init) {
		std::random_device rd;
		gen.seed(rd());
		init = true;
	}
	std::uniform_real_distribution<float> dist(min, max);
	return dist(gen);
}


float Radian2Degree(float radian) {
	return (radian) * 180 / M_PI;
}

float Degree2Radian(float degree) {
	return (degree)*M_PI / 180;
}




/// <summary>
/// �ʒu�x�N�g��A����B�ւ̒������o���֐�
/// </summary>
/// <param name="start">�n�_�ʒu�x�N�g��</param>
/// <param name="end">�I�_�ʒu�x�N�g��</param>
/// <returns>A����B�ւ̒���</returns>
float Length(Vector2 start, Vector2 end) {
	return sqrt(pow((start.x) - (end.x), 2) + pow((start.y) - (end.y), 2));
}


bool BallCollision(Vector2 positionA, float radiusA, Vector2 positionB, float radiusB) {
	return (Length(positionA, positionB) <= (radiusA + radiusB));
}


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
float DotProduct(Vector2 startA, Vector2 endA, Vector2 startB, Vector2 endB, bool normalizeFlagA, bool normalizeFlagB) {
	float normA = 1;
	float normB = 1;
	if (normalizeFlagA) {
		normA = Length(startA, endA);
	}
	if (normalizeFlagB) {
		normA = Length(startB, endB);
	}
	Vector2 a = { ((endA.x) - (startA.x)) / (normA),((endA.y) - (startA.y)) / (normA) };
	Vector2 b = { ((endB.x) - (startB.x)) / (normB),((endB.y) - (startB.y)) / (normB) };

	return a.x * b.x + a.y * b.y;
}

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
float CrossProduct(Vector2 startA, Vector2 endA, Vector2 startB, Vector2 endB, bool normalizeFlagA, bool normalizeFlagB) {
	float normA = 1;
	float normB = 1;
	if (normalizeFlagA) {
		normA = Length(startA, endA);
	}
	if (normalizeFlagB) {
		normA = Length(startB, endB);
	}
	Vector2 a = { ((endA.x) - (startA.x)) / (normA),((endA.y) - (startA.y)) / (normA) };
	Vector2 b = { ((endB.x) - (startB.x)) / (normB),((endB.y) - (startB.y)) / (normB) };

	return a.x * b.y - a.y * b.x;
}


/// <summary>
/// Clamp�֐�
/// </summary>
/// <param name="number">���ƂȂ鐔</param>
/// <param name="min">����</param>
/// <param name="max">���</param>
/// <returns>���߂��l</returns>
float Clamp(float number, float min, float max) {
	if (min > number) {			//	�������������Ȃ� min ��
		return min;
	}
	else if (max < number) {	//	����������߂Ȃ� max ��
		return max;
	}
	else {						//	����ȊO�Ȃ� number ��
		return number;
	}
}

/// <summary>
/// �����������Ă��邩
/// </summary>
/// <param name="startA">����A�̎n�_</param>
/// <param name="endA">����A�̏I�_</param>
/// <param name="startB">����B�̎n�_</param>
/// <param name="endB">����B�̏I�_</param>
/// <returns>�����̐^�U�l</returns>
bool isCross(Vector2 startA, Vector2 endA, Vector2 startB, Vector2 endB) {
	const Vector2 a0 = {
		startA.x - endA.x,
		startA.y - endA.y
	};
	const Vector2 a1 = {
		startA.x - endB.x,
		startA.y - endB.y
	};
	const Vector2 a2 = {
		endA.x - endB.x,
		endA.y - endB.y
	};

	const Vector2 b0 = {
		startB.x - endB.x,
		startB.y - endB.y
	};
	const Vector2 b1 = {
		startB.x - endA.x,
		startB.y - endA.y
	};
	const Vector2 b2 = {
		endB.x - endA.x,
		endB.y - endA.y
	};

	if ((a0.x * b1.y - a0.y * b1.x) * (a0.x * b2.y - a0.y * b2.x) / Length(a0, ZeroVector2) < 0 && (b0.x * a1.y - b0.y * a1.x) * (b0.x * a2.y - b0.y * a2.x) / Length(b0, ZeroVector2) < 0) {
		return true;
	}

	return false;
};

Vector2 Nomalize(Vector2 OriginalVector2) {
	return { ((OriginalVector2.x) / Length(ZeroVector2,(OriginalVector2))),((OriginalVector2.y) / Length(ZeroVector2, (OriginalVector2))) };
}


/// <summary>
/// �~�Ɛ����̊Ԃ̋���
/// </summary>
/// <param name="Ellipse">�~�̒��S</param>
/// <param name="start">�����̏I�_</param>
/// <param name="end">�����̎n�_</param>
/// <returns>�����̒l</returns>
float Ellipse2LineLength(Vector2 Ellipse, Vector2 start, Vector2 end) {
	Vector2 NormLine = ZeroVector2;
	float length = Length((start), (end));
	NormLine.x = ((end.x) - (start.x)) / length;
	NormLine.y = ((end.y) - (start.y)) / length;
	float dot = DotProduct((start), (Ellipse), (start), (end), false, true);

	if (dot < 0) {
		return Length((start), (Ellipse));
	}
	else if (dot > length) {
		return Length((end), (Ellipse));
	}
	else {
		return Length({ (NormLine.x * dot), (NormLine.y * dot) }, (Ellipse));
	}
	return 0;
};



/// <summary>
	/// ���̓��Ƀ}�E�X�������Ă��邩
	/// </summary>
	/// <param name="centor">���̒��S���W</param>
	/// <param name="size">���̑傫��</param>
	/// <param name="mouse">�}�E�X�\����</param>
bool IsMouseInBox(Vector2 centor, Vector2 size) {

	return (fabs((Mouse::GetMouse().x) - (centor.x)) < ((size.x) / 2) && fabs((Mouse::GetMouse().y) - (centor.y)) < ((size.y) / 2));

};

bool IsPositionInBox(Vector2 centor, Vector2 size, Vector2 position) {
	return (fabs((position.x) - (centor.x)) < ((size.x) / 2) && fabs((position.y) - (centor.y)) < ((size.y) / 2));
}



Vector2 RotateVector2(Vector2 OriginalVector, float radian) {
	return { (float)(((OriginalVector.x) * cos(radian)) - ((OriginalVector.y) * sin(radian))),(float)(((OriginalVector.y) * cos(radian)) + ((OriginalVector.x) * sin(radian))) };
}

Vector2 VectorCrossPosition(const Vector2 &startA, const Vector2 &endA, const Vector2 &startB, const Vector2 &endB) {
	// //	float normA = 0, normB = 0;
	//	/*Vector2 normalizeA = ZeroVector2, normalizeB = ZeroVector2;
	//
	// //	normA = Length(startA, endA);
	// //	normB = Length(startB, endB);
	//
	//	normalizeA = Nomalize({ endA.x - startA.x, endA.y - startA.y, });
	//	normalizeB = Nomalize({ endB.x - startB.x, endB.y - startB.y, });
	//
	//	float crossDistance = (DotProduct(startA, endA, startA, startB, true, false)
	//		- DotProduct(startB, endB, startA, startB, true, false)
	//		* DotProduct(startA, endA, startB, endB, true, true)) / (1 - pow(DotProduct(startA, endA, startB, startB, true, true), 2));
	//
	//	return { normalizeA.x * crossDistance + startA.x, normalizeA.y * crossDistance + startA.y };
	// //	return (n1�EAC - (n2�EAC)(n1�En2)) / (1 - (n1�En2)(n1�En2));
	// */
	// /*	Vector2 A = startA, B = endA, C = startB, D = endB;
	//
	//Vector2 normilzeA = Nomalize({ (B.x) - (A.x),(B.y) - (A.y) });
	//Vector2 normilzeB = Nomalize({ (D.x) - (C.x),(D.y) - (C.y) });
	//
	//float crossDistance = fabs(CrossProduct((A), (C), (C), (D), false, false)) / fabs(CrossProduct((A), (B), (C), (D), false, false));
	//Novice::ScreenPrintf(10, 310, "%.3lf", crossDistance);
	//return { A.x + (B.x) - (A.x) * crossDistance, A.y + (B.y) - (A.y) * crossDistance, };*/

	const float crossDistance = CrossDistance(startA, endA, startB, endB);
	return { (startA.x) + ((endA.x) - (startA.x)) * crossDistance , (startA.y) + ((endA.y) - (startA.y)) * crossDistance };
}



float CrossDistance(const Vector2 &startA, const Vector2 &endA, const Vector2 &startB, const Vector2 &endB) {
	const Vector2 a0 = {
		startA.x - endA.x,
		startA.y - endA.y
	};
	const Vector2 a1 = {
		startA.x - endB.x,
		startA.y - endB.y
	};
	const Vector2 a2 = {
		endA.x - endB.x,
		endA.y - endB.y
	};

	const Vector2 b0 = {
		startB.x - endB.x,
		startB.y - endB.y
	};
	const Vector2 b1 = {
		startB.x - endA.x,
		startB.y - endA.y
	};
	const Vector2 b2 = {
		endB.x - endA.x,
		endB.y - endA.y
	};


	//Novice::ScreenPrintf(10, 30, "%lf", (a0.x * b1.y - a0.y * b1.x) * (a0.x * b2.y - a0.y * b2.x) / pow(sqrt(pow(a0.x, 2) + pow(a0.y, 2)), 2));
	//Novice::ScreenPrintf(10, 50, "%lf", (b0.x * a1.y - b0.y * a1.x) * (b0.x * a2.y - b0.y * a2.x) / pow(sqrt(pow(b0.x, 2) + pow(b0.y, 2)), 2));


	return (b0.x * a1.y - b0.y * a1.x) / (b0.x * a0.y - b0.y * a0.x);

}


Vector2 ReflectionVector2(Vector2 MoveStart, Vector2 MoveEnd, Vector2 SurfaceStart, Vector2 SurfaceEnd) {
	if (!isCross(MoveStart, MoveEnd, SurfaceStart, SurfaceEnd)) {
		return	ZeroVector2;
	}
	else {
		float crossDistance = CrossDistance(MoveStart, MoveEnd, SurfaceStart, SurfaceEnd);
		return (SurfaceEnd - SurfaceStart).Nomalize() * CrossProduct((MoveEnd - MoveStart) - VectorCrossPosition(MoveStart, MoveEnd, SurfaceStart, SurfaceEnd), MoveEnd, SurfaceStart, SurfaceEnd);
		//	return ReflactEndPosition;
	}
}



Vector2 ReflectVector2(Vector2 vec, Vector2 normal) {
	normal = normal.Nomalize();
	return vec - 2 * (vec * normal) * normal;
}
