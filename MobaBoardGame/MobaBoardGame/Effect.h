#pragma once
#include <memory>
#include <assert.h>


/* Used to identify effects character has.*/
enum EffectType
{
	irrelevant,
	voidInfliction
};


template<class T> class Effect
{
public:
	Effect(int duration): duration(duration) {};

	Effect(int duration, EffectType type): duration(duration), type(type) {};


	virtual std::unique_ptr<Effect<T>> clone() = 0;  // Allows for copying of unique_ptrs to base class.
	
	void update(T &t)  // Applys effect and updates effect.
	{
		assert(duration > 0);
		apply(t);
		updateDuration();
	}

	bool isOver()
	{
		return duration == 0;
	}

	virtual EffectType getType() const { return type; } 

protected:
	virtual void apply(T &t) = 0;  // Modifies t, representative of effect.

private:
	void updateDuration()
	{
		--duration;
	}

	EffectType type = irrelevant;
	int duration;
};

