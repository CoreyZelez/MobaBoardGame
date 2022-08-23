#pragma once
#include <assert.h>


template<class T> class DurationEffect
{
public:
	DurationEffect(int duration): duration(duration) {};
	
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
	virtual void apply(T &t) = 0;  // Defines the effect and applys it to t.

private:
	void updateDuration()
	{
		--duration;
	}

	int duration;
};


