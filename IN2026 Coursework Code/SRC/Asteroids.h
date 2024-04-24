#ifndef __ASTEROIDS_H__
#define __ASTEROIDS_H__

#include "GameUtil.h"
#include "GameSession.h"
#include "IKeyboardListener.h"
#include "IGameWorldListener.h"
#include "IScoreListener.h" 
#include "ScoreKeeper.h"
#include "Player.h"
#include "IPlayerListener.h"
#include "Image.h"
class GameObject;
class Spaceship;
class GUILabel;
class Sprite;

class Asteroids : public GameSession, public IKeyboardListener, public IGameWorldListener, public IScoreListener, public IPlayerListener
{
public:
	Asteroids(int argc, char* argv[]);
	virtual ~Asteroids(void);

	virtual void Start(void);
	virtual void Stop(void);

	// Declaration of IKeyboardListener interface ////////////////////////////////

	void OnKeyPressed(uchar key, int x, int y);
	void OnKeyReleased(uchar key, int x, int y);
	void OnSpecialKeyPressed(int key, int x, int y);
	void OnSpecialKeyReleased(int key, int x, int y);

	// Declaration of IScoreListener interface //////////////////////////////////

	void OnScoreChanged(int score);

	// Declaration of the IPlayerLister interface //////////////////////////////

	void OnPlayerKilled(int lives_left);
	void OnLivesUpdated(int current_lives);
	// Declaration of IGameWorldListener interface //////////////////////////////

	void OnWorldUpdated(GameWorld* world) {}
	void OnObjectAdded(GameWorld* world, shared_ptr<GameObject> object) {}
	void OnObjectRemoved(GameWorld* world, shared_ptr<GameObject> object);

	// Override the default implementation of ITimerListener ////////////////////
	void OnTimer(int value);

private:
	shared_ptr<Spaceship> mSpaceship;
	shared_ptr<GUILabel> mScoreLabel;
	shared_ptr<GUILabel> mLivesLabel;
	shared_ptr<GUILabel> mGameOverLabel;
	shared_ptr<Sprite> mHealthPowerUpSprite;
	shared_ptr<Sprite> mThrustPowerUpSprite;
	shared_ptr<Sprite> mDestroyAllPowerUpSprite;
	shared_ptr<Sprite> mSuperPowerUpSprite;
	uint mLevel;
	uint mAsteroidCount;

	void ResetSpaceship();
	shared_ptr<GameObject> CreateSpaceship();
	void CreateGUI();
	void CreateAsteroids(const uint num_asteroids);
	//void CreateHealthPowerUp();
	shared_ptr<GameObject> CreateExplosion();
	shared_ptr<GameObject> CreateHealthPowerUp();
	shared_ptr<GameObject> CreateThrustPowerUp();
	shared_ptr<GameObject> CreateDestroyAllPowerUp();
	shared_ptr<GameObject> Asteroids::CreateSuperPowerUp();
	const static uint SHOW_GAME_OVER = 0;
	const static uint START_NEXT_LEVEL = 1;
	const static uint CREATE_NEW_PLAYER = 2;
	const static uint SPAWN_HEALTH_POWERUP = 3;
	const static uint SPAWN_THRUST_POWERUP = 3; // Timer ID for spawning thrust power-ups
	const static uint END_THRUST_BOOST = 4;  
	const static uint SPAWN_DESTROY_ALL_POWERUP = 5;// Timer ID for ending the thrust boost
	const static uint SPAWN_SUPER_POWERUP = 6;
	bool mGameStarted;
	bool mGameOver;

	shared_ptr<GUILabel> mStartLabel;
	shared_ptr<GUILabel> mLabelForTitle;
	shared_ptr<GUILabel> mChangeShipLabel;

	// Inside the Asteroids class definition
	shared_ptr<Sprite> mSpaceshipSprite1;
	shared_ptr<Sprite> mSpaceshipSprite2;
	shared_ptr<Sprite> mSpaceshipSprite3;

	//void InitializePowerUpSprites();

	void InitializeStartScreen();
	void StartGame();
	float currentThrust;

	bool healthPowerUpActive;
	bool thrustPowerUpActive;
	bool destroyAllPowerUpActive;
	bool superPowerUpActive;
	ScoreKeeper mScoreKeeper;
	Player mPlayer;
};

#endif