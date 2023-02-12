#pragma once

/// @brief �^�C�}�[�N���X
class Timer {
public:

	Timer() :goalFlame_(0), nowFlame_(0) {}
	~Timer() {}

	/// @brief �X�V����
	/// @return bool �S�[���̏ꍇtrue
	bool Update();

	/// @brief �^�C�}�[�J�n
	/// @param �S�[���t���[��
	void Start(const int &Goal);

	/// @brief �t���[���̃��Z�b�g	
	void Reset();

	/// @brief �t���[���̏�����
	void Init();



	/// @brief �^�C�}�[���I�_�ɓ��B���Ă��邩
	/// @return bool �S�[���̏ꍇtrue
	inline bool IsFinish() const { return goalFlame_ > 0 && nowFlame_ >= goalFlame_; }

	/// @brief ���s��Ԃł��邩
	/// @return bool ���s��ԂȂ�true
	inline bool IsActive()const { return goalFlame_ > 0 && nowFlame_ < goalFlame_; }

	/// @brief ���݃t���[�����擾
	/// @return int ���݃t���[��
	inline int GetNowFlame()const { return nowFlame_; }

	/// @brief �S�[���t���[�����擾
	/// @return int �S�[���t���[��
	inline int GetGoalFlame()const { return goalFlame_; }

	/// @brief ���ݐi�s�x���擾
	/// @return float 0.0f ~ 1.0f�̌��ݐi�s�x
	float GetProgress() const;

private:

	int goalFlame_;
	int nowFlame_;




	/// @brief �t���[���̉��Z	
	void AddFlame();


	/// @brief �I�_�t���[���̐ݒ�
	/// @param GoalFlame �I�_�t���[��
	inline void SetGoal(const int &Goal) { goalFlame_ = Goal; }

};


//class FunctionTimer {
//protected:
//	Timer actionTimer;
//	void (*functionPointer)();
//
//public:
//
//	bool isActive() {
//		return actionTimer.isActive();
//	}
//
//	void SetFunction(void(*functionPointer)()) {
//		this->functionPointer = functionPointer;
//	}
//
//	void TimerStart(int goalFlame) {
//
//		actionTimer.ResetFlame();
//		actionTimer.SetGoalFlame(goalFlame);
//	}
//	void TimerUpdate() {
//		if (!actionTimer.isFinish() && actionTimer.GetGoalFlame() != 0) {
//			actionTimer.AddFlame();
//		}
//		else if (actionTimer.GetGoalFlame() != 0) {
//			actionTimer.SetGoalFlame(0);
//			actionTimer.ResetFlame();
//			functionPointer();
//		}
//	}
//};
//
//class SceneChangeTimer :public FunctionTimer {
//protected:
//	void (*sceneFunctionPointer)(SceneID) = SceneChange;
//	SceneID Scene = TitleScene;
//public:
//	void SetFunction(void(*functionPointer)(SceneID), SceneID Scene) {
//		this->sceneFunctionPointer = functionPointer;
//		this->Scene = Scene;
//	}
//	void TimerUpdate() {
//		if (!actionTimer.isFinish() && actionTimer.GetGoalFlame() != 0) {
//			actionTimer.AddFlame();
//		}
//		else if (actionTimer.GetGoalFlame() != 0) {
//			actionTimer.SetGoalFlame(0);
//			actionTimer.ResetFlame();
//			sceneFunctionPointer(Scene);
//		}
//	}
//};