#pragma once

#include "templates/chunk.h"
#include <SFML/Graphics/Export.hpp> // sf::Uint8

class Click
{
	
protected:

	// focus on button true/false
	bool focus;	
	
	// click as sound and play as state
	bool play;
	Chunk click;
	
public:

	Click();
	~Click();
	
	void turn();	// Turn on/off chunk
	bool isPlayable();
	void setVolume( sf::Uint8 volume );
};