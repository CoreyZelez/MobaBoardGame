#pragma once
#include <memory>
#include <assert.h>

class Character;

template<class T> class Effect
{
public:
	explicit Effect(int duration) : duration(duration) {};
	Effect(int duration, Character *sender) : duration(duration), sender(sender) {};

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

	Character *getSender() { return sender; }

protected:
	virtual void apply(T &t) = 0;  // Modifies t, representative of effect.

private:
	void updateDuration()
	{
		--duration;
	}

	int duration;
	Character *sender = nullptr;  // Only relevant if effect sent by character.
};

