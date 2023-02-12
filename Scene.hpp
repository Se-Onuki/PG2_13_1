#pragma once

#include <vector>
#include "Timer/Timer.hpp"
#include "UI/UI.hpp"
#include <memory>

#include <unordered_map>
#include "Audio/Audio.hpp"


class Scene {

protected:
	static float TransitionProgress;
	static int sceneFlame;

	std::unordered_map<std::string, UI *> uiList = {};

	/// @brief 自分自身をマネージャーに登録するための関数
	inline void SelfEntry(const std::string &name);

public:
	inline Scene() :uiList() {}
	inline virtual ~Scene() {
		DeleteUI();
	}

	virtual void Update() = 0;
	virtual void Draw() const = 0;

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

	inline void Reset() {
		sceneFlame = 0;
	}

	inline static void AddFlame() { sceneFlame++; };

	inline void AddUI(UI *ui) { uiList[ui->GetName()] = ui; }

	inline void DeleteUI() {
		for (auto &element : uiList) {
			if (element.second) {
				delete element.second;
			}
		}
		uiList.clear();
	}

	inline void UpdateUI() {
		for (auto ui : uiList) {
			if (ui.second) {
				ui.second->Update();
			}
		}
	}

	inline void DrawUI() const {
		for (auto &ui : uiList) {
			ui.second->Draw();
		}
	}

};

class TitleScene_ final : public Scene {
public:
	using Scene::Scene;

	TitleScene_();
	~TitleScene_() override;

	void OnEnter() override;
	void OnExit()override;

	void Update() override;

	void Draw() const override;

};

class GameScene_ final : public Scene {
public:
	using Scene::Scene;

	GameScene_();
	~GameScene_() override;

	void OnEnter() override;
	void OnExit()override;

	void Update() override;

	void Draw() const override;


};




class ResultScene_ final : public Scene {
public:
	using Scene::Scene;

	ResultScene_();
	~ResultScene_() override;

	void OnEnter() override;
	void OnExit()override;

	void Update() override;

	void Draw() const override;
};



