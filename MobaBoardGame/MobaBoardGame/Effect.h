#pragma once
#include <memory>
#include <assert.h>


template<class T> class Effect
{
public:
	Effect(int duration): duration(duration) {};

	virtual std::unique_ptr<Effect<T>> clone() = 0;  // Allows for copying of unique_ptrs to base class.
	
	void update(T &t)
	{
		assert(duration > 0);

		apply(t);
		updateDuration();
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


