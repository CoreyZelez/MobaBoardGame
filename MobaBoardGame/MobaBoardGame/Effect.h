#pragma once
#include <assert.h>


template<class T> class Effect
{
public:
	Effect(int duration): duration(duration) {};
	
	void update(T &t)
	{
		assert(duration > 0);

		apply(t);
		updateDuration();
	}

	int getDuration()
	{
		return duration;
	}

	bool isOver()
	{
		return duration == 0;
	}

protected:
	virtual void apply(T &t) = 0;  // Modifies t, representative of effect.

private:
	void updateDuration()
	{
		--duration;
	}

	int duration;
};


