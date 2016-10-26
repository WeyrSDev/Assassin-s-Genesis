#include "halloween/play_halloween.h"

Play_halloween::Play_halloween()
{
	state = new State;
	hero = new Hero;
}

Play_halloween::~Play_halloween()
{
	free();
}

void Play_halloween::free()
{
	delete state;
	delete hero;
}

	
void Play_halloween::load( int screen_w, int screen_h )
{
	hero->load( screen_w, screen_h );
	//...
}


void Play_halloween::handle( sf::Event &event )
{
	hero->handle( event );
}

void Play_halloween::draw( sf::RenderWindow* &window )
{
	hero->draw( window );
	
	hero->fadein( 2 );
}

	
State* Play_halloween::getState()
{
	return state;
}

void Play_halloween::set( State* state )
{
	this->state = state;
	state->state = 0;
	
	/*
	// Set chunks
	if( !state->cSwitch )
	{
		backtomenu->turn();
		choice->turn();
	}
	
	// Set music volume
	music->setVolume( state->mVolume );
	
	// Set chunk volume
	backtomenu->setVolume( state->cVolume );
	choice->setVolume( state->cVolume );
	*/
}

	
bool Play_halloween::isQuit()
{
	if( state->state == 3 )
	{
		return true;
	}
	
	return false;
}

bool Play_halloween::nextState()
{
	if( state->state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Play_halloween::backToLevel()
{
	if( state->state == 2 )
	{
		state->state = 0;
		// backtomenu->setState( 0 );
		return true;
	}
		
	return false;
}

	
void Play_halloween::reloadMusic()
{
	// music->reload();
}
