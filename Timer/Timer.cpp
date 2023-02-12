#include "Timer.hpp"
#include "BaseData.hpp"


bool Timer::Update() {
	if (IsActive()) {
		AddFlame();
	}
	return IsFinish();
}

void Timer::AddFlame() {
	nowFlame_++;
}


void Timer::Reset() {
	nowFlame_ = -1;
}


void Timer::Init() {
	nowFlame_ = -1;
	goalFlame_ = 0;
}


void Timer::Start(const int &Goal) {
	if (!IsActive()) {
		Reset();
		SetGoal(Goal);
	}
}




float Timer::GetProgress() const {
	if (goalFlame_ == 0) return 0;
	return Clamp((float)nowFlame_ / goalFlame_, 0.0f, 1.0f);
}
