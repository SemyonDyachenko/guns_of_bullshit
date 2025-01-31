#ifndef TESTSTATE_H
#define TESTSTATE_H



#include "State.h"


class TestState :
	public State
{
protected:
	std::map<std::string, Button*> buttons;
	sf::RectangleShape workingScene;

	sf::Font font;

	//funcs
	void initFonts();
	void initButtons();
public:
	TestState(sf::RenderWindow * window, std::stack<State*>* states);
	virtual ~TestState();

	void endState();

	//funcs
	void updateInput(const float& time);
	void updateButtons();
	void update(float time);
	void renderButtons(sf::RenderWindow * window);
	void render(sf::RenderWindow * window);
};


#endif // ! TESTSTATE_H