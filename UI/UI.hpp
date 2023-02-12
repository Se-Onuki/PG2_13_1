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
	// �R���X�g���N�^
	UI() : parent_(nullptr), name_("") {}
	UI(Box box) : parent_(nullptr), name_(""), Box(box), spriteBox({ 0,0 }, box.radius, { 1,1 }) {}
	UI(Box box, const std::string &name) : parent_(nullptr), name_(name), Box(box), spriteBox({ 0,0 }, box.radius, { 1,1 }) {}
	// �f�X�g���N�^
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
	/// -�eUI��ݒ肷��
	/// </summary>
	/// <param name="parent">�eUI</param>
	void SetParent(UI *parent);

	/// <summary>
	/// -�qUI��ǉ�����
	/// </summary>
	/// <param name="child">�qUI</param>
	void AddChild(UI *const child);

	/// <summary>
	/// -�qUI���쐬����
	/// </summary>
	/// <param name="Collision">�����蔻��</param>
	/// <param name="name">UI��</param>
	void CreateChild(const Box &Collision, const std::string &name);

	/// <summary>
	/// -���O��ݒ肷��
	/// </summary>
	/// <param name="name">�ݒ肷��UI��</param>
	void SetName(const std::string &name) { name_ = name; }




	/// <summary>
	/// -�eUI���擾����
	/// </summary>
	/// <returns>�eUI�A�h���X</returns>
	UI *GetParent() const;

	/// <summary>
	/// -�qUI�̃��X�g���擾����
	/// </summary>
	/// <returns>�qUI�A�h���X�s��</returns>
	const std::vector<UI *> &GetChildren() const;

	/// <summary>
	/// -���O���擾����
	/// </summary>
	/// <returns>UI��</returns>
	const std::string &GetName() const { return name_; }


	/// <summary>
	/// -���t���[���X�V����
	/// </summary>
	virtual void Update();

	/// <summary>
	/// -���g�ȉ��S�Ă̎qUI�ɓ����֐������s����
	/// </summary>
	/// <param name="func">�֐��|�C���^�A�����_���֐�</param>
	void ForEach(std::function<void(const UI *)> func) const;


	/// <summary>
	/// -���g�ȉ��S�Ă̎qUI�ɓ����֐������s����
	/// </summary>
	/// <param name="func">�֐��|�C���^�A�����_���֐�</param>
	void ForEach(std::function<void(UI *)> func);

	/// <summary>
	/// -UI��`�悷��
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

	// �{�^����`�悷��
	void Draw() const override;
	void Update() override;

	bool button = false;
};


class GaugeUI : public UI {
public:
	using UI::UI;
	// �R���X�g���N�^
	GaugeUI() : UI(), direction_(Direction::LEFT) {}
	GaugeUI(Box box) : UI(box), direction_(Direction::LEFT) {}
	GaugeUI(Box box, const std::string &name) : UI(box, name), direction_(Direction::LEFT) {}

	enum Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	// �����o�֐�
	inline void SetDirection(Direction direction) { direction_ = direction; }
	inline virtual void SetLength(float t) { t_ = Clamp(t, 0.f, 1.f); }
	inline float GetLength() { return t_; }

	inline void SetBackLength() { backT_ = t_; };
	void StartEase(const int &needTime);

	/// <summary>
	/// -���t���[���X�V����
	/// </summary>
	virtual void Update();

	// �`��֐�
	virtual void Draw() const override;

private:

	float t_ = 1.f;
	Direction direction_;
	float backT_ = 1.f;
	Timer timer_ = {};
};