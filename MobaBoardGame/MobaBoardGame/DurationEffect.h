#pragma once
class DurationEffect
{
public:
	void updateDuration();
	bool isOver();

private:
	unsigned int duration;
};

