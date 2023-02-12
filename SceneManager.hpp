#pragma once

#include <unordered_map>
#include "Scene.hpp"
#include <Novice.h>
#include "Audio/Audio.hpp"

class SceneManager final {
private:

	Timer transitionTimer;

	std::unordered_map<std::string, Scene *> sceneList;

	std::string currentSceneName;
	Scene *currentScene;

	std::string nextSceneName;
	Scene *nextScene;

	SceneManager() {
		currentScene = nullptr;
		currentSceneName = "";
	}


	~SceneManager() {
		for (auto &element : sceneList) {
			if (element.second) {
				delete element.second;
			}
		}
		sceneList.clear();

	}

public:
	UI fadeUI;

	SceneManager(const SceneManager &) = delete;
	SceneManager &operator=(const SceneManager &) = delete;

	/// @brief インスタンスの取得
	/// @return インスタンスの実体
	inline static SceneManager &GetInstance() {
		static SceneManager instance;
		return instance;
	}

	/// @brief シーン遷移
	/// @param name 遷移先の名前キー
	/// @param transitionTime 必要とする時間
	inline void StartTransition(const std::string &name, const int &transitionTime) {
		if (currentSceneName == name) return;

		if (sceneList.contains(name)) {
			nextSceneName = name;
			nextScene = sceneList[name];
		}
		else return;

		transitionTimer.Start(transitionTime);
	}

	/// @brief シーンの追加
	/// @param name シーン名
	/// @param scene シーンのポインタ
	inline void AddScene(const std::string &name, Scene *scene) {
		sceneList[name] = scene;
	}


	/// @brief シーンの遷移
	/// @param name 遷移先のシーン
	inline void ChangeScene(const std::string &name) {
		// 現在のシーンと同じであった場合、実行しない。
		if (currentSceneName == name) return;
		// マップに一致する要素があった場合、実行。
		if (sceneList.contains(name)) {
			if (currentScene != nullptr) {
				// 遷移前処理
				currentScene->OnExit();
			}
			// 現在のシーンのキーとポインタを更新
			currentSceneName = name;
			currentScene = sceneList[name];
			// 遷移後処理
			currentScene->Reset();
			currentScene->OnEnter();
		}
	}


	/// @brief シーンの更新
	inline void Update() {
		if (transitionTimer.Update()) {
			ChangeScene(nextSceneName);
		}

		if (transitionTimer.IsActive()) {
			fadeUI.spriteBox.color = ColorEasing(0xFFFFFF00, 0xFFFFFFFF, transitionTimer.GetProgress());
		}

		if (currentScene) {
			Scene::AddFlame();
			currentScene->UpdateUI();
			currentScene->Update();
		}

	}


	/// @brief シーンの描画
	void Draw() {
		if (currentScene) {
			currentScene->Draw();
		}
		fadeUI.Draw();
	}
};