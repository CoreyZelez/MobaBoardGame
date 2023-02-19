#pragma once
#include <memory>
#include <assert.h>

class Character;

template<class T> class Effect
{
public:
	explicit Effect(int duration) : duration(duration) {};
	Effect(int duration, Character &sender): duration(duration), sender(&sender) {};
	Effect(int duration, Character &sender, Character &receiver): duration(duration), sender(&sender), receiver(&receiver){};
	virtual ~Effect() = default;

	virtual std::unique_ptr<Effect<T>> clone() = 0;  // Allows for copying of unique_ptrs to base class.
	
	void update()  // Applys effect and updates effect.
	{
		assert(duration > 0);
		apply();
		updateDuration();
	}

	void initT(T &t)
	{
		this->t = &t;
	}

	bool isOver()
	{
		return duration == 0;
	}

	Character* getSender() { return sender; };
	Character* getReceiver() { return receiver; };

protected:
	virtual void apply() = 0;  // Used to alter t in some way.

	T& getT() 
	{ 
		assert(t != nullptr);
		return *t; 
	}

private:
	void updateDuration()
	{
		--duration;
	}

	T* t = nullptr;
	int duration;
	Character *sender = nullptr; 
	Character *receiver = nullptr; 
};

