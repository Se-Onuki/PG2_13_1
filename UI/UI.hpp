#pragma once



#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "BaseData.hpp"

#include "Math/Vector2.hpp"
#include "./Object/Object.hpp"
#include "./Render/SpriteClass.hpp"

#include "Timer/Timer.hpp"

#include "Input/Json.hpp"


class UI :public Box {
public:
	// コンストラクタ
	UI() : parent_(nullptr), name_("") {}
	UI(Box box) : parent_(nullptr), name_(""), Box(box), spriteBox({ 0,0 }, box.radius, { 1,1 }) {}
	UI(Box box, const std::string &name) : parent_(nullptr), name_(name), Box(box), spriteBox({ 0,0 }, box.radius, { 1,1 }) {}
	// デストラクタ
	virtual ~UI() {
		for (auto &element : children_) {
			delete element;
		}
		children_.clear();
	}

	UI &operator=(const Box &other) {
		Box::operator=(other);
		return *this;
	}

	UI *operator[](const std::string &name) {
		if (this->name_ == name) {
			return this;
		}
		for (auto child : children_) {
			UI *result = (*child)[name];
			if (result != nullptr) {
				return result;
			}
		}
		return nullptr;
	}

	inline void operator<<(Json &json) {
		DeleteChild();

		LoadFromJson(json);
	}

	inline void operator>>(Json &json) {
		SaveToJson(json);
	}

	inline void DeleteChild() {
		for (auto &element : children_) {
			delete element;
		}
		children_.clear();
	}

	/// <summary>
	/// -親UIを設定する
	/// </summary>
	/// <param name="parent">親UI</param>
	void SetParent(UI *parent);

	/// <summary>
	/// -子UIを追加する
	/// </summary>
	/// <param name="child">子UI</param>
	void AddChild(UI *const child);

	/// <summary>
	/// -子UIを作成する
	/// </summary>
	/// <param name="Collision">当たり判定</param>
	/// <param name="name">UI名</param>
	void CreateChild(const Box &Collision, const std::string &name);

	/// <summary>
	/// -名前を設定する
	/// </summary>
	/// <param name="name">設定するUI名</param>
	void SetName(const std::string &name) { name_ = name; }




	/// <summary>
	/// -親UIを取得する
	/// </summary>
	/// <returns>親UIアドレス</returns>
	UI *GetParent() const;

	/// <summary>
	/// -子UIのリストを取得する
	/// </summary>
	/// <returns>子UIアドレス行列</returns>
	const std::vector<UI *> &GetChildren() const;

	/// <summary>
	/// -名前を取得する
	/// </summary>
	/// <returns>UI名</returns>
	const std::string &GetName() const { return name_; }


	/// <summary>
	/// -毎フレーム更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// -自身以下全ての子UIに同じ関数を実行する
	/// </summary>
	/// <param name="func">関数ポインタ、ラムダ式関数</param>
	void ForEach(std::function<void(const UI *)> func) const;


	/// <summary>
	/// -自身以下全ての子UIに同じ関数を実行する
	/// </summary>
	/// <param name="func">関数ポインタ、ラムダ式関数</param>
	void ForEach(std::function<void(UI *)> func);

	/// <summary>
	/// -UIを描画する
	/// </summary>
	virtual void Draw() const;

	void LoadFromJson(Json &json);

	void SaveToJson(Json &json);

	SpriteBox spriteBox;
protected:
	UI *parent_;
	std::vector<UI *> children_;
	std::string name_;
};

class Button : public UI {
public:
	using UI::UI;

	// ボタンを描画する
	void Draw() const override;
	void Update() override;

	bool button = false;
};


class GaugeUI : public UI {
public:
	using UI::UI;
	// コンストラクタ
	GaugeUI() : UI(), direction_(Direction::LEFT) {}
	GaugeUI(Box box) : UI(box), direction_(Direction::LEFT) {}
	GaugeUI(Box box, const std::string &name) : UI(box, name), direction_(Direction::LEFT) {}

	enum Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	// メンバ関数
	inline void SetDirection(Direction direction) { direction_ = direction; }
	inline virtual void SetLength(float t) { t_ = Clamp(t, 0.f, 1.f); }
	inline float GetLength() { return t_; }

	inline void SetBackLength() { backT_ = t_; };
	void StartEase(const int &needTime);

	/// <summary>
	/// -毎フレーム更新処理
	/// </summary>
	virtual void Update();

	// 描画関数
	virtual void Draw() const override;

private:

	float t_ = 1.f;
	Direction direction_;
	float backT_ = 1.f;
	Timer timer_ = {};
};