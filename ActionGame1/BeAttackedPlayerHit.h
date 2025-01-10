#pragma once

class BeAttackedPlayer : public HitChecker
{
public:
	BeAttackedPlayer();
	~BeAttackedPlayer();
	bool CheckBeAttackHit(const Player& player, const Enemy& enemy);
private:

};

