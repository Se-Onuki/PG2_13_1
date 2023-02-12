#include "Input/Json.hpp"



#include <sstream>
#include <fstream>
#include <unordered_map>

std::stringstream Json::sstream = {};

Json Json::Load(const std::string &filePath) {
	std::ifstream jsonFile(filePath);
	if (!jsonFile.is_open()) {
		return {};
	}
	std::stringstream jsonStringStream;
	// StringStream型に変換
	jsonStringStream << jsonFile.rdbuf();
	// StringStream型->文字列型->空白削除->Json型読み込み
	return Parse(RemoveSpace(jsonStringStream.str()));
}

std::string Json::RemoveSpace(const std::string &str)
{
	std::string result;
	bool inside = false;

	for (char c : str) {
		if (c == '\"') {
			// ""で囲まれている箇所の場合、inside_quotesを反転させる
			inside = !inside;
		}

		if (!inside) {
			// ""で囲まれていない場合、空白文字を削除する
			if (c != '\n' && c != '\r' && !isspace(c)) {
				result += c;
			}
		}
		else {
			// ""で囲まれている場合、そのまま追加する
			result += c;
		}
	}
	return result;
}

Json Json::Parse(const std::string &jsonRawString) {
	// 戻り値のJson型
	Json json;
	// 引数をStringStream型に変換
	sstream.str(jsonRawString);
	// -呼び出しキー
	std::string key;
	// -解析用文字列
	char c;
	while (sstream >> c) {
		if (c == '{') {
			while (sstream >> c && c != '"');
		}
		// ダブルクォーテーションに到達したら、キーを解析する。
		if (c == '"') {
			std::getline(sstream, key, '"');
			// 値のパース
			sstream >> c;	// : を飛ばす
			c = sstream.peek();
			// 値が文字列型の場合
			if (c == '"') {
				sstream >> c;
				std::string value;
				std::getline(sstream, value, '"');
				// 文字列型として保存。
				json.properties[key] = value;
			}
			// 値がdouble型の場合
			else if (isdigit(c) || c == '-') {
				double value;
				sstream >> value;
				// double型として保存
				json.properties[key] = value;
			}


			//// 値がint型の場合
			//else if (true) {
			//	int value;
			//	sstream >> value;
			//	// int型として保存
			//	json.properties[key] = value;
			//}


			// 値がJson型である場合
			else if (c == '{') {
				// Json型を値として保存する。
				json.properties[key] = Parse(CutReadedString(sstream));
			}
			// 値が配列の場合
			else if (c == '[') {
				// Json型を格納するための配列を作成する
				std::vector<Json> value;
				// Jsonファイルの配列の終端に到達するまで、配列を追加
				while (sstream >> c && c != ']') {
					if (c == '{') {
						value.push_back(Parse(CutReadedString(sstream)));
					}
				}
				// 配列として保存
				json.properties[key] = value;
			}
		}
		if (c == '}') {
			break;
		}
	}
	return json;
}

std::string Json::CutReadedString(std::stringstream &sstream) {
	// str stringstream全体を文字列型に変換
	// substr 文字列のn文字目から読み始めるか指定
	// tellg stringstreamのn文字目を読んでいるか
	return sstream.str().substr(sstream.tellg());
}


void Json::Save(const std::string &filePath) {
	std::ofstream ofs(filePath);
	ofs << Serialize();
	ofs.close();
}

std::string Json::Serialize() {
	std::stringstream ss;
	Serialize(ss);
	return ss.str();
}

void Json::Serialize(std::stringstream &ss) {
	ss << "{" << std::endl;
	for (auto &[key, value] : properties) {
		ss << '"' << key << "\" : ";
		SerializeValue(value, ss);
		ss << "," << std::endl;
	}
	ss.seekp(-2, ss.cur);
	ss << std::endl << "}";
}

void Json::SerializeValue(std::variant<std::string, Json, int, double, std::vector<Json>> &value, std::stringstream &ss) {
	if (auto *pString = get_if<std::string>(&value)) {
		ss << '"' << *pString << '"';
	}
	else if (auto *pJson = get_if<Json>(&value)) {
		pJson->Serialize(ss);
	}
	else if (auto *pInt = get_if<int>(&value)) {
		ss << *pInt;
	}
	else if (auto *pDouble = get_if<double>(&value)) {
		ss << *pDouble;
	}
	else if (auto *pArray = get_if<std::vector<Json>>(&value)) {
		ss << "[ " << std::endl;
		for (std::variant<std::string, Json, int, double, std::vector<Json>> elem : *pArray) {
			SerializeValue(elem, ss);
			ss << "," << std::endl;
		}
		ss.seekp(-2, ss.cur);
		ss << "]";
	}
}