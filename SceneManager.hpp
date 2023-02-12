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

	/// @brief �C���X�^���X�̎擾
	/// @return �C���X�^���X�̎���
	inline static SceneManager &GetInstance() {
		static SceneManager instance;
		return instance;
	}

	/// @brief �V�[���J��
	/// @param name �J�ڐ�̖��O�L�[
	/// @param transitionTime �K�v�Ƃ��鎞��
	inline void StartTransition(const std::string &name, const int &transitionTime) {
		if (currentSceneName == name) return;

		if (sceneList.contains(name)) {
			nextSceneName = name;
			nextScene = sceneList[name];
		}
		else return;

		transitionTimer.Start(transitionTime);
	}

	/// @brief �V�[���̒ǉ�
	/// @param name �V�[����
	/// @param scene �V�[���̃|�C���^
	inline void AddScene(const std::string &name, Scene *scene) {
		sceneList[name] = scene;
	}


	/// @brief �V�[���̑J��
	/// @param name �J�ڐ�̃V�[��
	inline void ChangeScene(const std::string &name) {
		// ���݂̃V�[���Ɠ����ł������ꍇ�A���s���Ȃ��B
		if (currentSceneName == name) return;
		// �}�b�v�Ɉ�v����v�f���������ꍇ�A���s�B
		if (sceneList.contains(name)) {
			if (currentScene != nullptr) {
				// �J�ڑO����
				currentScene->OnExit();
			}
			// ���݂̃V�[���̃L�[�ƃ|�C���^���X�V
			currentSceneName = name;
			currentScene = sceneList[name];
			// �J�ڌ㏈��
			currentScene->Reset();
			currentScene->OnEnter();
		}
	}


	/// @brief �V�[���̍X�V
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


	/// @brief �V�[���̕`��
	void Draw() {
		if (currentScene) {
			currentScene->Draw();
		}
		fadeUI.Draw();
	}
};