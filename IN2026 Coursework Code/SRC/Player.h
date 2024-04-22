#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameUtil.h"

#include "GameObject.h"
#include "GameObjectType.h"
#include "IPlayerListener.h"
#include "IGameWorldListener.h"

class Player : public IGameWorldListener
{
public:
	Player() { mLives = 3; }
	virtual ~Player() {}

	void OnWorldUpdated(GameWorld* world) {}

	void OnObjectAdded(GameWorld* world, shared_ptr<GameObject> object) {}

	void OnObjectRemoved(GameWorld* world, shared_ptr<GameObject> object)
	{
		if (object->GetType() == GameObjectType("Spaceship")) {
			mLives -= 1;
			FirePlayerKilled();
		}
		if (object->GetType() == GameObjectType("HealthPowerUp")) {
			mLives += 1;
			UpdateLives();
		}
	}
	static Player& Instance() {
		static Player instance;  // Guaranteed to be destroyed and instantiated on first use.
		return instance;
	}
	void AddListener(shared_ptr<IPlayerListener> listener)
	{
		mListeners.push_back(listener);
	}

	void FirePlayerKilled()
	{
		// Send message to all listeners
		for (PlayerListenerList::iterator lit = mListeners.begin();
			lit != mListeners.end(); ++lit) {
			(*lit)->OnPlayerKilled(mLives);
		}
	}
	/*void IncrementLives(int amount) {
		mLives += amount;
		cout << "Lives incremented by " << amount << ", total lives: " << mLives << endl;
		UpdateLives();
	}*/
	void Player::UpdateLives() {
		for (auto& listener : mListeners) {
			listener->OnLivesUpdated(mLives);
		}
	}
private:
	int mLives;

	typedef std::list< shared_ptr<IPlayerListener> > PlayerListenerList;

	PlayerListenerList mListeners;
};

#endif
