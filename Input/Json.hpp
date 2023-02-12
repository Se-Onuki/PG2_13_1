#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <variant>

#include "Math/Vector2.hpp"


class Json
{

public:
	inline Json() {}
	inline ~Json() {}

	void operator=(const Json &obj) {
		*this = obj;
	}

	static std::stringstream sstream;

	inline auto &operator[](const std::string &key) { return properties[key]; }

	template <typename T>
	inline T Get(const std::string &key) {
		return std::get<T>(properties[key]);
	}

	template <typename T>
	inline void Set(const std::string &key, const T &value) {
		properties[key] = value;
	}
	inline void Set(const std::string &key, const Vector2 &value) {
		Json vec;
		vec["x"] = value.x;
		vec["y"] = value.y;
		properties[key] = vec;
	}

	static Json Parse(const std::string &jsonString);
	static Json Load(const std::string &filePath);
	static std::string RemoveSpace(const std::string &str);

	static std::string CutReadedString(std::stringstream &sstream);

	void Save(const std::string &filePath);
	std::string Serialize();
	void Serialize(std::stringstream &ss);
	void SerializeValue(std::variant<std::string, Json, int, double, std::vector<Json>> &value, std::stringstream &ss);
private:

	std::unordered_map<std::string, std::variant<std::string, Json, int, double, std::vector<Json>>> properties;
};

inline Vector2 operator/(const Vector2 &lhs, const Vector2 &rhs) {
	return Vector2{ lhs.x / rhs.x, lhs.y / rhs.y };
}
