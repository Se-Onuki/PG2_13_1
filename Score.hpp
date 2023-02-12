#pragma once

class Score final
{
public:

	Score(const Score &) = delete;
	Score &operator=(const Score &) = delete;

	/// @brief �C���X�^���X�̎擾
	/// @return �C���X�^���X�̎���
	inline static Score &GetInstance() {
		static Score instance;
		return instance;
	}
	inline void AddScore(int value) { score += value; };
	inline int GetScore() { return score; };

	inline void Init() { score = 0; }

private:
	int score;

	Score() :score(0) {}
	~Score() {}
};
