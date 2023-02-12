#include "UI.hpp"

#include <typeinfo>

#include <Novice.h>
#include "Render/Resource.hpp"
#include "Render/Camera.hpp"
#include "Render/SpriteClass.hpp"

#include "BaseData.hpp"

using std::string;

/// -親UIを設定する
void UI::SetParent(UI *parent)
{
	parent_ = parent;
}

/// -子UIを追加する
void UI::AddChild(UI *const child)
{
	child->SetParent(this);
	children_.push_back(child);
}

/// -親UIを取得する
UI *UI::GetParent() const
{
	return parent_;
}

/// -子UIのリストを取得する
const std::vector<UI *> &UI::GetChildren() const
{
	return children_;
}

/// -UIを描画する
void UI::Draw() const
{
	//DrawQuadFunction(position, { radius.x * 2, radius.y * 2 }, spriteBox.srcX + spriteBox.srcW * spriteBox.nowFlame, spriteBox.srcY, spriteBox.srcW, spriteBox.srcH, spriteBox.textureHandle, spriteBox.color);
	DrawObject(position, radius * 2, spriteBox.srcX + spriteBox.srcW * spriteBox.nowFlame, spriteBox.srcY, spriteBox.srcW, spriteBox.srcH, spriteBox.textureHandle, spriteBox.color, spriteBox.scale, 0.0f, Camera::UIvpVpMatrix);

	//Novice::ScreenPrintf(position.x - radius.x, ToWorld(position.y + radius.y), name_.c_str());

	for (const auto &child : children_)
	{
		child->Draw();
	}
}

/// -子UIを作成する
void UI::CreateChild(const Box &Collision, const std::string &name)
{

	UI *child = new UI(Collision, name);

	AddChild(child);
}

/// 毎フレーム更新処理
void UI::Update()
{

	spriteBox.NextTextureFlame();
	for (auto &child : children_)
	{
		child->Update();
	}
}

/// -自身以下全ての子UIに同じ関数を実行する
void UI::ForEach(std::function<void(const UI *)> func) const
{
	for (const UI *const &child : children_)
	{
		child->ForEach(func);
	}
	func(this);
}

/// -自身以下全ての子UIに同じ関数を実行する
void UI::ForEach(std::function<void(UI *)> func)
{
	for (UI *const &child : children_)
	{
		child->ForEach(func);
	}
	func(this);
}

void UI::LoadFromJson(Json &json)
{
	SetName(json.Get<string>("name"));

	SetPosition(Vector2{ static_cast<float>(json.Get<Json>("position").Get<double>("x")),  static_cast<float>(json.Get<Json>("position").Get<double>("y")) });
	SetRadius(Vector2{ static_cast<float> (json.Get<Json>("radius").Get<double>("x")),  static_cast<float>(json.Get<Json>("radius").Get<double>("y")) });

	Json sprite = json.Get<Json>("spriteBox");

	spriteBox.Init(sprite.Get<string>("imagePath"), sprite.Get<double>("width"), sprite.Get<double>("height"), (int)sprite.Get<double>("maxFlame"));
	spriteBox.color = sprite.Get<double>("color");
	//	spriteBox = json.Get<Json>("spriteBox");

	std::vector<Json> childrenJson = json.Get<std::vector<Json>>("children");
	for (auto &childJson : childrenJson)
	{
		UI *child = nullptr;
		auto className = childJson.Get<string>("class");
		if (className == "class UI") {
			child = new UI();
		}
		else if (className == "class GaugeUI") {
			child = new GaugeUI();
		}
		else {
			child = new UI();
		}

		child->LoadFromJson(childJson);
		AddChild(child);
	}
}

void UI::SaveToJson(Json &json)
{
	json.Set("class", typeid(*this).name());
	json.Set("name", name_);

	json.Set("position", GetPosition());
	json.Set("radius", GetRadius());

	Json sprite;
	sprite.Set("imagePath", spriteBox.file_path);
	sprite.Set("width", spriteBox.srcW);
	sprite.Set("height", spriteBox.srcH);
	sprite.Set("maxFlame", (int)(spriteBox.maxFlame));
	sprite.Set("color", (int)(spriteBox.color));

	json.Set("spriteBox", sprite);

	std::vector<Json> childrenJson;
	for (auto &child : children_)
	{
		Json childJson;
		child->SaveToJson(childJson);
		childrenJson.push_back(childJson);
	}
	json.Set("children", childrenJson);
}

void Button::Draw() const
{

	//Novice::ScreenPrintf(position.x, position.y, name_.c_str());

	UI::Draw();
}

/// 毎フレーム更新処理
void Button::Update()
{
	spriteBox.NextTextureFlame();
	for (auto &child : children_)
	{
		child->Update();
	}
}

void GaugeUI::StartEase(const int &needTime)
{
	backT_ = Easing(backT_, t_, timer_.GetProgress());
	timer_.Init();
	timer_.Start(needTime);
};

void GaugeUI::Update()
{
	timer_.Update();
	spriteBox.NextTextureFlame();
	for (auto &child : children_)
	{
		child->Update();
	}
}

/// -UIを描画する
void GaugeUI::Draw() const
{
	float progress = timer_.GetProgress();
	switch (direction_)
	{
	case Direction::LEFT:
		DrawObject(Vector2{ position.x - radius.x + radius.x * 2 * t_ + radius.x * (backT_ - t_) * (1.f - progress), position.y }, Vector2{ radius.x * 2 * (backT_ - t_) * (1.f - progress), radius.y * 2 }, spriteBox.srcX, spriteBox.srcY, spriteBox.srcW, spriteBox.srcH, spriteBox.textureHandle, 0xFF0000FF, spriteBox.scale, 0.0f, Camera::UIvpVpMatrix);
		DrawObject(Vector2{ position.x - radius.x * (1.0f - t_), position.y }, Vector2{ radius.x * 2 * t_, radius.y * 2 }, spriteBox.srcX, spriteBox.srcY, spriteBox.srcW, spriteBox.srcH, spriteBox.textureHandle, spriteBox.color, spriteBox.scale, 0.0f, Camera::UIvpVpMatrix);
		break;
	case Direction::RIGHT:
		DrawObject(Vector2{ position.x + radius.x * (1.0f - t_), position.y }, Vector2{ radius.x * 2 * t_, radius.y * 2 }, spriteBox.srcX, spriteBox.srcY, spriteBox.srcW, spriteBox.srcH, spriteBox.textureHandle, spriteBox.color, spriteBox.scale, 0.0f, Camera::UIvpVpMatrix);
		break;
	case Direction::UP:
		DrawObject(Vector2{ position.x, position.y + radius.x * (1.0f - t_) }, Vector2{ radius.x * 2, radius.y * 2 * t_ }, spriteBox.srcX, spriteBox.srcY, spriteBox.srcW, spriteBox.srcH, spriteBox.textureHandle, spriteBox.color, spriteBox.scale, 0.0f, Camera::UIvpVpMatrix);
		break;
	case Direction::DOWN:
		DrawObject(Vector2{ position.x, position.y - radius.x * (1.0f - t_) }, Vector2{ radius.x * 2, radius.y * 2 * t_ }, spriteBox.srcX, spriteBox.srcY, spriteBox.srcW, spriteBox.srcH, spriteBox.textureHandle, spriteBox.color, spriteBox.scale, 0.0f, Camera::UIvpVpMatrix);
		break;
	}
	for (const auto &child : children_)
	{
		child->Draw();
	}
}