#pragma once
class Bot
{
private:
	enum Stage {
		Random,
		FindAround,
		VectorContinue,
		ChangeVector
	};
public:
	void Attack();
};

