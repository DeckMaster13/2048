#ifndef __PLAYSTATE__
#define __PLAYSTATE__

#include "GameState.h"
#include "GameLogic.h"

class PlayState : public GameState
{
public:
	PlayState();

	virtual bool onEnter() override;
	virtual bool onExit() override;
	virtual void handleInputs() override;

	virtual void render() override;
	virtual void update() override;

	virtual std::string getStateID() const override { return "PLAYSTATE"; }

public:
	GameLogic m_gameLogic{};
private:
	std::vector<std::vector<GameObject*>> m_globalBackground;
};

#endif