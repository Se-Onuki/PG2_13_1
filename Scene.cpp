#include "Scene.hpp"
#include "SceneManager.hpp"
#include <stdio.h>


#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "BaseData.hpp"
#include "Easing.hpp"

#include "Math/Math.hpp"
#include "Math/Vector2.hpp"
#include "Math/PolarCoordinates.hpp"

#include "Render/Resource.hpp"
#include "Render/Camera.hpp"

#include "Render/SpriteClass.hpp"

#include "UI/UI.hpp"
#include "UI/String.hpp"

#include "Input/KeyBoard.hpp"
#include "Input/Controller.hpp"
#include "Input/Json.hpp"

#include "Object/Object.hpp"
#include "Object/ObjectController.hpp"
#include "Object/Entity/Entity.hpp"
#include "Object/Entity/Player/Player.hpp"

#include "Enemy.hpp"

#include "PlayerManager.hpp"
#include "EntityManager.hpp"
#include "Score.hpp"

#include "Audio/Audio.hpp"

float Scene::TransitionProgress = 0.0f;
int Scene::sceneFlame = 0;

using std::string;
using std::wstring;

void Scene::SelfEntry(const std::string& name) {

	SceneManager::GetInstance().AddScene(name, this);
}

#pragma region TitleScene

TitleScene_::TitleScene_() {

}
TitleScene_::~TitleScene_() {
}

void TitleScene_::OnEnter() {
	Scene::Reset();
}

void TitleScene_::OnExit()
{
}

void TitleScene_::Update() {


	if (sceneFlame <= 60) {
		SceneManager::GetInstance().fadeUI.spriteBox.color = ColorEasing(0xFFFFFFFF, 0xFFFFFF00, (float)(sceneFlame) / 60.f);
	}
	if (Keyboard::IsTrigger(DIK_SPACE)) {
		SceneManager::GetInstance().StartTransition("Game", 60);
	}



}

void TitleScene_::Draw() const {
	DrawUI();
	String::DrawString(L"PG2 13_1 static ‚ß‚ñ‚Î‚Ö‚ñ‚·‚¤", "Default", MiddleCentor, Vector2{ 64,64 }, { 0.5f,0.5f }, 0xFFFFFFFF);
	String::DrawString(L"Press Space", "Default", DownCentor + Vector2{ 0,64 }, { 32,32 }, { 0.5f,0.5f }, 0xFFFFFFFF);
}


#pragma endregion


#pragma region GameScene

GameScene_::GameScene_() {

	AudioManager::GetInstance().Add("GameBGM", "./Resources/Sounds/BGM/GamePlay.wav");
	Json json = Json::Load("Resources/Texture/UI/UI.json");

	UI* testUI = new UI();
	(*testUI) << json;
	AddUI(testUI);

	ImportTexture();

	Vector2 focusPosition = MiddleCentor;

	Camera::DrawScale = 1.0f;
	//focusPosition = Easing(PlayerManager::player[0].GetPosition(), PlayerManager::player[1].GetPosition(), 0.5f);

	//UI *selectUI = testUI["Main"];

}

GameScene_::~GameScene_() {
}

void GameScene_::OnEnter() {
	Scene::Reset();
	//EntityManager::GetInstance().AddEntity(new	Player);
	PlayerManager::GetInstance().Init();
	Camera::SetFocus(MiddleCentor);

	AudioManager::GetInstance()["GameBGM"]->StartBGM(true, 0.5f);
	Score::GetInstance().Init();
}

void GameScene_::OnExit()
{
	AudioManager::GetInstance()["GameBGM"]->Stop();
	EntityManager::GetInstance().Init();
	Score::GetInstance().AddScore(sceneFlame / 50);
}


void GameScene_::Update() {

	if (sceneFlame <= 60) {
		SceneManager::GetInstance().fadeUI.spriteBox.color = ColorEasing(0xFFFFFFFF, 0xFFFFFF00, (float)(sceneFlame) / 60.f);
	}
	if (PlayerManager::GetInstance().GetPlayer().GetHP() <= 0) {
		SceneManager::GetInstance().StartTransition("Result", 60);
	}

	flame++;

#pragma region ConfigUI

	UI* selectUI = nullptr;


	if (Novice::IsPressMouse(0)) {
		uiList["Main"]->ForEach([&selectUI](UI* ui) { if (IsPositionInBox(ui->position, ui->radius * 2, Mouse::GetMouse() * Camera::UIvpVpMatrix.Inverse())) { selectUI = ui; }});
	}
	if (selectUI) {
		if (Keyboard::IsPress(DIK_LCONTROL)) {
			selectUI->position += Mouse::GetDirection();
		}
		else {
			selectUI->ForEach([](UI* ui) {ui->position += Mouse::GetDirection(); });
		}
	}

	if (Keyboard::IsPress(DIK_LCONTROL) && Keyboard::IsTrigger(DIK_R) ||
		Keyboard::IsPress(DIK_R) && Keyboard::IsTrigger(DIK_LCONTROL)) {
		Json json = Json::Load("Resources/Texture/UI/UI.json");
		*uiList["Main"] << json;
	}

	if (Keyboard::IsPress(DIK_LCONTROL) && Keyboard::IsTrigger(DIK_S) ||
		Keyboard::IsPress(DIK_S) && Keyboard::IsTrigger(DIK_LCONTROL)) {
		Json json = {};
		*uiList["Main"] >> json;
		json.Save("Resources/Texture/UI/UI.json");
	}

#pragma endregion

	if (sceneFlame % 50 == 0) {
		Enemy* newEnemy = new Enemy;
		newEnemy->SetPosition(PlayerManager::GetInstance().GetPlayer().GetPosition() + Polar2Rectangular(Polar{ GetRandom(300,560),GetRandom(0,360) }));
		newEnemy->SetRadius(32);
		EntityManager::GetInstance().AddEntity(newEnemy);
	}

	if (Keyboard::IsTrigger(DIK_R)) {
		Enemy::SetEnemyAlive(true);
	}

	PlayerManager::GetInstance().Input();
	PlayerManager::GetInstance().Update();
	EntityManager::GetInstance().Update();

	GaugeUI* gauge = (GaugeUI*)((*uiList["Main"])["Bar"]);
	if (gauge->GetLength() != PlayerManager::GetInstance().GetPlayer().GetHP()) {
		gauge->StartEase(32);
		gauge->SetLength(PlayerManager::GetInstance().GetPlayer().GetHP());
	}


	Camera::SetFocus(Easing(Camera::GetFocus(), PlayerManager::GetInstance().GetPlayer().GetPosition(), 0.05f));
	Camera::Update();
}

void GameScene_::Draw() const {

	wchar_t time[32];
	swprintf_s(time, L"Time : %3d", sceneFlame / 50);

	wchar_t kill[32];
	swprintf_s(kill, L"Kill : %3d", Score::GetInstance().GetScore());

	wchar_t enemyCount[32];
	swprintf_s(enemyCount, L"EnemyCount : %d", Enemy::GetCount());

	EntityManager::GetInstance().Draw();
	PlayerManager::GetInstance().Draw();

	String::DrawString(time, "Default", TopLeft - Vector2{ 0,+12 }*2, Vector2{ 24,24 }*2, { 0,0.5f }, 0xFFFFFFFF);
	String::DrawString(kill, "Default", TopLeft - Vector2{ 0,+12 + 24 }*2, Vector2{ 24,24 }*2, { 0,0.5f }, 0xFFFFFFFF);
	String::DrawString(enemyCount, "Default", TopLeft - Vector2{ 0,+12 + 24 * 2 }*2, Vector2{ 24,24 }*2, { 0,0.5f }, 0xFFFFFFFF);

	String::DrawString(L"WASD  : ‚¢‚Ç‚¤", "Default", DownLeft + Vector2{ 0,+12 }, { 24,24 }, { 0,0.5f }, 0xFFFFFFFF);
	String::DrawString(L"SPACE : ‚Í‚Á‚µ‚á", "Default", DownLeft + Vector2{ 0,+12 + 24 }, { 24,24 }, { 0,0.5f }, 0xFFFFFFFF);
	String::DrawString(L"R     : ‚è‚¹‚Á‚Æ", "Default", DownLeft + Vector2{ 0,+12 + 24 * 2 }, { 24,24 }, { 0,0.5f }, 0xFFFFFFFF);
	DrawUI();
}

#pragma endregion

#pragma region ResultScene

ResultScene_::ResultScene_() {

}
ResultScene_::~ResultScene_() {
}

void ResultScene_::OnEnter() {
	Scene::Reset();
}

void ResultScene_::OnExit()
{
}

void ResultScene_::Update() {


	if (sceneFlame <= 60) {
		SceneManager::GetInstance().fadeUI.spriteBox.color = ColorEasing(0xFFFFFFFF, 0xFFFFFF00, (float)(sceneFlame) / 60.f);
	}
	if (Keyboard::IsTrigger(DIK_SPACE)) {
		SceneManager::GetInstance().StartTransition("Title", 60);
	}



}

void ResultScene_::Draw() const {
	DrawUI();
	wchar_t score[32];
	swprintf_s(score, L"Score : %05d", Score::GetInstance().GetScore());
	String::DrawString(L"GameOver", "Default", MiddleCentor + Vector2{ 0, 64 }, Vector2{ 64,64 }*2, { 0.5f,0.5f }, 0x000000FF);
	String::DrawString(score, "Default", MiddleCentor + Vector2{ 0,-64 }, Vector2{ 64,64 }*1.5f, { 0.5f,0.5f }, 0xFFFFFFFF);
	String::DrawString(L"Press Space", "Default", DownCentor + Vector2{ 0,64 }, { 32,32 }, { 0.5f,0.5f }, 0xFFFFFFFF);
}

#pragma endregion
