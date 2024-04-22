#include "Asteroid.h"
#include "Asteroids.h"
#include "Animation.h"
#include "AnimationManager.h"
#include "GameUtil.h"
#include "GameWindow.h"
#include "GameWorld.h"
#include "GameDisplay.h"
#include "Spaceship.h"
#include "BoundingShape.h"
#include "BoundingSphere.h"
#include "GUILabel.h"
#include "Explosion.h"
#include "HealthPowerUp.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Constructor. Takes arguments from command line, just in case. */
Asteroids::Asteroids(int argc, char* argv[])
	: GameSession(argc, argv)
{
	mLevel = 0;
	mAsteroidCount = 0;
	InitializeStartScreen();
}

/** Destructor. */
Asteroids::~Asteroids(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Start an asteroids game. */
void Asteroids::Start()
{
	// Create a shared pointer for the Asteroids game object - DO NOT REMOVE
	shared_ptr<Asteroids> thisPtr = shared_ptr<Asteroids>(this);

	// Add this class as a listener of the game world
	mGameWorld->AddListener(thisPtr.get());

	// Add this as a listener to the world and the keyboard
	mGameWindow->AddKeyboardListener(thisPtr);

	// Create an ambient light to show sprite textures
	GLfloat ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
	glEnable(GL_LIGHT0);

	// Load animations for the game elements
	Animation* explosion_anim = AnimationManager::GetInstance().CreateAnimationFromFile("explosion", 64, 1024, 64, 64, "explosion_fs.png");
	Animation* asteroid1_anim = AnimationManager::GetInstance().CreateAnimationFromFile("asteroid1", 128, 8192, 128, 128, "asteroid1_fs.png");
	Animation* spaceship_anim = AnimationManager::GetInstance().CreateAnimationFromFile("spaceship", 128, 128, 128, 128, "spaceship_fs.png");
	mSpaceshipSprite1 = make_shared<Sprite>(spaceship_anim->GetWidth(), spaceship_anim->GetHeight(), spaceship_anim);
	Animation* spaceship2_anim = AnimationManager::GetInstance().CreateAnimationFromFile("spaceship", 128, 128, 128, 128, "spaceship2_fs.png");
	mSpaceshipSprite2 = make_shared<Sprite>(spaceship2_anim->GetWidth(), spaceship2_anim->GetHeight(), spaceship2_anim);

	Animation* spaceship3_anim = AnimationManager::GetInstance().CreateAnimationFromFile("spaceship", 128, 128, 128, 128, "spaceship3_fs.png");
	mSpaceshipSprite3 = make_shared<Sprite>(spaceship3_anim->GetWidth(), spaceship3_anim->GetHeight(), spaceship3_anim);

	Animation* health_anim = AnimationManager::GetInstance().CreateAnimationFromFile("health", 48, 48, 48, 48, "health_fs.png");
	shared_ptr<Sprite> healthPowerUpSprite = make_shared<Sprite>(health_anim->GetWidth(), health_anim->GetHeight(), health_anim);

	// Store it for later use
	mHealthPowerUpSprite = healthPowerUpSprite;


	// Create a spaceship and add it to the world
	mGameWorld->AddObject(CreateSpaceship());

	mGameWorld->AddObject(CreateHealthPowerUp());
	//shared_ptr<GameObject> healthPowerUp = CreateHealthPowerUp();
	// Initialize the start screen label and make it visible
	/*mStartLabel = make_shared<GUILabel>("Press X to Start");
	mStartLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
	mStartLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_MIDDLE);*/
	// Add the start screen label to the game display
	mGameDisplay->GetContainer()->AddComponent(static_pointer_cast<GUIComponent>(mStartLabel), GLVector2f(0.5f, 0.9f));

	// Set the flag that the game has not yet started
	mGameStarted = false;

	// Start the game session
	GameSession::Start();
}
void Asteroids::InitializeStartScreen() {
	if (!mStartLabel) { // Only create the start label if it hasn't been created already
		mStartLabel = make_shared<GUILabel>("Press X to Start");
		mStartLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
		mStartLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_MIDDLE);

		// Retrieve the spaceship's Y position. For now, let's say it's at the bottom 10% of the screen height.
		float spaceshipYPos = mGameDisplay->GetHeight() * 0.1f;
		// We want to place the label 40 pixels above the spaceship.
		int labelOffsetY = 40;

		// Calculate the label's X and Y position.
		int labelX = mGameDisplay->GetWidth() / 2;
		int labelY = static_cast<int>(spaceshipYPos) + labelOffsetY;

		mStartLabel->SetPosition(GLVector2i(labelX, labelY));
		mStartLabel->SetColor(GLVector3f(1.0f, 1.0f, 1.0f)); // White color
		mGameDisplay->GetContainer()->AddComponent(static_pointer_cast<GUIComponent>(mStartLabel), GLVector2f(0.5f, 0.5f + (static_cast<float>(labelOffsetY) / mGameDisplay->GetHeight())));

		// Calculate the positions based on the screen height and set the labels accordingly
		float screenHeight = mGameDisplay->GetHeight();

		// Position for "Asteroids The Game" label, which is at the top 10% of the screen height
		float asteroidsLabelYPos = screenHeight * 0.1f; // Changed from 0.1 to whatever is needed
		mTitleLabel = make_shared<GUILabel>("Asteroids The Game"); // Create the title label
		mTitleLabel->SetPosition(GLVector2i(mGameDisplay->GetWidth() / 2, asteroidsLabelYPos));
		mTitleLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
		mTitleLabel->SetVisible(true);
		mGameDisplay->GetContainer()->AddComponent(static_pointer_cast<GUIComponent>(mTitleLabel), GLVector2f(0.5f, 0.1f));
		if (!mChangeShipLabel) { // Only create the label if it hasn't been created already
			mChangeShipLabel = make_shared<GUILabel>("Press S,A or D to change spaceship");
			mChangeShipLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
			mChangeShipLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_MIDDLE);

			// Set the label's position. Let's say we want it to be 20% from the top of the screen
			float labelYPos = mGameDisplay->GetHeight() * 0.2f;
			mChangeShipLabel->SetPosition(GLVector2i(mGameDisplay->GetWidth() / 2, labelYPos));
			mChangeShipLabel->SetColor(GLVector3f(1.0f, 1.0f, 1.0f)); // Set color to white

			// Add the label to the game display's container
			mGameDisplay->GetContainer()->AddComponent(static_pointer_cast<GUIComponent>(mChangeShipLabel), GLVector2f(0.5f, 0.85f));
			mChangeShipLabel->SetVisible(true); // Make the label visible
		}

	}
	mStartLabel->SetVisible(true);
}
/** Stop the current game. */
void Asteroids::Stop()
{
	// Stop the game
	GameSession::Stop();
}

// PUBLIC INSTANCE METHODS IMPLEMENTING IKeyboardListener /////////////////////

void Asteroids::OnKeyPressed(uchar key, int x, int y)
{
	if (!mGameStarted) {
		if (key == 'x') {
			StartGame();
		}
		else if (key == 's') {
			mSpaceship->SetSprite(mSpaceshipSprite2);
			mSpaceship->SetScale(0.1f);
		}
		else if (key == 'a') {
			mSpaceship->SetSprite(mSpaceshipSprite3);
			mSpaceship->SetScale(0.1f);
		}
		else if (key == 'd') {
			mSpaceship->SetSprite(mSpaceshipSprite1);
			mSpaceship->SetScale(0.1f);
		}
	}
	else {
		// The game has started, so we ignore spaceship change keys and only respond to gameplay keys
		switch (key)
		{
		case ' ':
			mSpaceship->Shoot();
			break;
			// Add other gameplay-related key cases here if needed
		default:
			break;
		}
	}
}
void Asteroids::StartGame() {
	// Hide the start label
	if (mStartLabel) {
		mStartLabel->SetVisible(false);
	}

	// Now, create asteroids and set up the GUI
	CreateAsteroids(10); // Create 10 asteroids to start
	CreateGUI(); // Set up the score, lives, and other GUI elements
	mGameWorld->AddObject(CreateHealthPowerUp());
	// Add scorekeeper and player to the game world
	mGameWorld->AddListener(&mScoreKeeper);
	mScoreKeeper.AddListener(shared_ptr<Asteroids>(this));
	mGameWorld->AddListener(&mPlayer);
	mPlayer.AddListener(shared_ptr<Asteroids>(this));
	mChangeShipLabel->SetVisible(false);
	mTitleLabel->SetVisible(false);
	mStartLabel->SetVisible(false);
	// Mark the game as started
	mGameStarted = true;
}



void Asteroids::OnKeyReleased(uchar key, int x, int y) {}

void Asteroids::OnSpecialKeyPressed(int key, int x, int y)
{
	switch (key)
	{
		// If up arrow key is pressed start applying forward thrust
	case GLUT_KEY_UP: mSpaceship->Thrust(10); break;
		// If left arrow key is pressed start rotating anti-clockwise
	case GLUT_KEY_LEFT: mSpaceship->Rotate(90); break;
		// If right arrow key is pressed start rotating clockwise
	case GLUT_KEY_RIGHT: mSpaceship->Rotate(-90); break;
		// Default case - do nothing
	default: break;
	}
}
void Asteroids::OnSpecialKeyReleased(int key, int x, int y)
{
	switch (key)
	{
		// If up arrow key is released stop applying forward thrust
	case GLUT_KEY_UP: mSpaceship->Thrust(0); break;
		// If left arrow key is released stop rotating
	case GLUT_KEY_LEFT: mSpaceship->Rotate(0); break;
		// If right arrow key is released stop rotating
	case GLUT_KEY_RIGHT: mSpaceship->Rotate(0); break;
		// Default case - do nothing
	default: break;
	}
}


// PUBLIC INSTANCE METHODS IMPLEMENTING IGameWorldListener ////////////////////

void Asteroids::OnObjectRemoved(GameWorld* world, shared_ptr<GameObject> object)
{
	if (object->GetType() == GameObjectType("Asteroid"))
	{
		shared_ptr<GameObject> explosion = CreateExplosion();
		explosion->SetPosition(object->GetPosition());
		explosion->SetRotation(object->GetRotation());
		mGameWorld->AddObject(explosion);
		mAsteroidCount--;
		if (mAsteroidCount <= 0)
		{
			SetTimer(500, START_NEXT_LEVEL);
		}
	}
}

// PUBLIC INSTANCE METHODS IMPLEMENTING ITimerListener ////////////////////////

void Asteroids::OnTimer(int value)
{
	if (value == CREATE_NEW_PLAYER)
	{
		mSpaceship->Reset();
		mGameWorld->AddObject(mSpaceship);
	}

	if (value == START_NEXT_LEVEL)
	{
		mLevel++;
		int num_asteroids = 10 + 2 * mLevel;
		CreateAsteroids(num_asteroids);
	}

	if (value == SHOW_GAME_OVER)
	{
		mGameOverLabel->SetVisible(true);
	}

}

// PROTECTED INSTANCE METHODS /////////////////////////////////////////////////
shared_ptr<GameObject> Asteroids::CreateSpaceship()
{
	// Create a raw pointer to a spaceship that can be converted to
	// shared_ptrs of different types because GameWorld implements IRefCount
	mSpaceship = make_shared<Spaceship>();
	mSpaceship->SetBoundingShape(make_shared<BoundingSphere>(mSpaceship->GetThisPtr(), 4.0f));
	shared_ptr<Shape> bullet_shape = make_shared<Shape>("bullet.shape");
	mSpaceship->SetBulletShape(bullet_shape);
	Animation* anim_ptr = AnimationManager::GetInstance().GetAnimationByName("spaceship");
	shared_ptr<Sprite> spaceship_sprite =
		make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
	mSpaceship->SetSprite(spaceship_sprite);
	mSpaceship->SetScale(0.1f);
	// Reset spaceship back to centre of the world
	mSpaceship->Reset();
	// Return the spaceship so it can be added to the world
	return mSpaceship;

}

void Asteroids::CreateAsteroids(const uint num_asteroids)
{
	mAsteroidCount = num_asteroids;
	for (uint i = 0; i < num_asteroids; i++)
	{
		Animation* anim_ptr = AnimationManager::GetInstance().GetAnimationByName("asteroid1");
		shared_ptr<Sprite> asteroid_sprite
			= make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
		asteroid_sprite->SetLoopAnimation(true);
		shared_ptr<GameObject> asteroid = make_shared<Asteroid>();
		asteroid->SetBoundingShape(make_shared<BoundingSphere>(asteroid->GetThisPtr(), 10.0f));
		asteroid->SetSprite(asteroid_sprite);
		asteroid->SetScale(0.2f);
		mGameWorld->AddObject(asteroid);
	}
}

void Asteroids::CreateGUI()
{
	// Add a (transparent) border around the edge of the game display
	mGameDisplay->GetContainer()->SetBorder(GLVector2i(10, 10));
	// Create a new GUILabel and wrap it up in a shared_ptr
	mScoreLabel = make_shared<GUILabel>("Score: 0");
	// Set the vertical alignment of the label to GUI_VALIGN_TOP
	mScoreLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_TOP);
	// Add the GUILabel to the GUIComponent  
	shared_ptr<GUIComponent> score_component
		= static_pointer_cast<GUIComponent>(mScoreLabel);
	mGameDisplay->GetContainer()->AddComponent(score_component, GLVector2f(0.0f, 1.0f));

	// Create a new GUILabel and wrap it up in a shared_ptr
	mLivesLabel = make_shared<GUILabel>("Lives: 3");
	// Set the vertical alignment of the label to GUI_VALIGN_BOTTOM
	mLivesLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_BOTTOM);
	// Add the GUILabel to the GUIComponent  
	shared_ptr<GUIComponent> lives_component = static_pointer_cast<GUIComponent>(mLivesLabel);
	mGameDisplay->GetContainer()->AddComponent(lives_component, GLVector2f(0.0f, 0.0f));

	// Create a new GUILabel and wrap it up in a shared_ptr
	mGameOverLabel = shared_ptr<GUILabel>(new GUILabel("GAME OVER"));
	// Set the horizontal alignment of the label to GUI_HALIGN_CENTER
	mGameOverLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
	// Set the vertical alignment of the label to GUI_VALIGN_MIDDLE
	mGameOverLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_MIDDLE);
	// Set the visibility of the label to false (hidden)
	mGameOverLabel->SetVisible(false);
	// Add the GUILabel to the GUIContainer  
	shared_ptr<GUIComponent> game_over_component
		= static_pointer_cast<GUIComponent>(mGameOverLabel);
	mGameDisplay->GetContainer()->AddComponent(game_over_component, GLVector2f(0.5f, 0.5f));

}

void Asteroids::OnScoreChanged(int score)
{
	// Format the score message using an string-based stream
	std::ostringstream msg_stream;
	msg_stream << "Score: " << score;
	// Get the score message as a string
	std::string score_msg = msg_stream.str();
	mScoreLabel->SetText(score_msg);
}

void Asteroids::OnPlayerKilled(int lives_left)
{
	shared_ptr<GameObject> explosion = CreateExplosion();
	explosion->SetPosition(mSpaceship->GetPosition());
	explosion->SetRotation(mSpaceship->GetRotation());
	mGameWorld->AddObject(explosion);

	// Format the lives left message using an string-based stream
	std::ostringstream msg_stream;
	msg_stream << "Lives: " << lives_left;
	// Get the lives left message as a string
	std::string lives_msg = msg_stream.str();
	mLivesLabel->SetText(lives_msg);

	if (lives_left > 0)
	{
		SetTimer(1000, CREATE_NEW_PLAYER);
	}
	else
	{
		SetTimer(500, SHOW_GAME_OVER);
	}
}
void Asteroids::OnLivesUpdated(int current_lives) {
	// Format the current lives message using a string-based stream
	std::ostringstream msg_stream;
	msg_stream << "Lives: " << current_lives;
	// Get the lives message as a string
	std::string lives_msg = msg_stream.str();
	mLivesLabel->SetText(lives_msg);
}
shared_ptr<GameObject> Asteroids::CreateExplosion()
{
	Animation* anim_ptr = AnimationManager::GetInstance().GetAnimationByName("explosion");
	shared_ptr<Sprite> explosion_sprite =
		make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
	explosion_sprite->SetLoopAnimation(false);
	shared_ptr<GameObject> explosion = make_shared<Explosion>();
	explosion->SetSprite(explosion_sprite);
	explosion->Reset();
	return explosion;
}
shared_ptr<GameObject> Asteroids::CreateHealthPowerUp() {
	auto healthPowerUp = make_shared<HealthPowerUp>();
	healthPowerUp->SetPosition(GLVector3f(mGameDisplay->GetWidth() / 2, mGameDisplay->GetHeight() / 2, 0));
	healthPowerUp->SetVelocity(GLVector3f(0, 0, 0)); // Typically stationary
	healthPowerUp->SetAcceleration(GLVector3f(0, 0, 0)); // No acceleration

	// Use the preloaded sprite
	healthPowerUp->SetSprite(mHealthPowerUpSprite);
	healthPowerUp->SetBoundingShape(make_shared<BoundingSphere>(healthPowerUp, 10.0f));
	healthPowerUp->SetScale(0.1f);
	healthPowerUp->Render();
	mGameWorld->AddObject(healthPowerUp);
	return healthPowerUp;
}




