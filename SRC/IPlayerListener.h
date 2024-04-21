#ifndef __IPLAYERLISTENER_H__
#define __IPLAYERLISTENER_H__

class IPlayerListener
{
public:
	virtual void OnPlayerKilled(int lives_left) = 0;
	virtual void OnPlayerLivesChanged(int new_lives) = 0;
};

#endif
