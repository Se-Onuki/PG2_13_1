#pragma once

/// @brief タイマークラス
class Timer {
public:

	Timer() :goalFlame_(0), nowFlame_(0) {}
	~Timer() {}

	/// @brief 更新処理
	/// @return bool ゴールの場合true
	bool Update();

	/// @brief タイマー開始
	/// @param ゴールフレーム
	void Start(const int &Goal);

	/// @brief フレームのリセット	
	void Reset();

	/// @brief フレームの初期化
	void Init();



	/// @brief タイマーが終点に到達しているか
	/// @return bool ゴールの場合true
	inline bool IsFinish() const { return goalFlame_ > 0 && nowFlame_ >= goalFlame_; }

	/// @brief 実行状態であるか
	/// @return bool 実行状態ならtrue
	inline bool IsActive()const { return goalFlame_ > 0 && nowFlame_ < goalFlame_; }

	/// @brief 現在フレームを取得
	/// @return int 現在フレーム
	inline int GetNowFlame()const { return nowFlame_; }

	/// @brief ゴールフレームを取得
	/// @return int ゴールフレーム
	inline int GetGoalFlame()const { return goalFlame_; }

	/// @brief 現在進行度を取得
	/// @return float 0.0f ~ 1.0fの現在進行度
	float GetProgress() const;

private:

	int goalFlame_;
	int nowFlame_;




	/// @brief フレームの加算	
	void AddFlame();


	/// @brief 終点フレームの設定
	/// @param GoalFlame 終点フレーム
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