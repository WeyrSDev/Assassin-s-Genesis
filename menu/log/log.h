/**
    log.h
    Purpose: class Log - for simple buttons, after click you have clear window to show own stuff.

    @author Adrian Michalek
    @version 2016.10.07
	@email adrmic98@gmail.com
*/

#pragma once

#include "menu/click.h"
#include "drawable/text.h"
#include "drawable/sprite.h"
#include "menu/explanator/explanator.h"

class Log :public Click
{
	Explanator explanator;
	bool state;
	bool locked;
	
	MySprite button;
	float y_state, left_state;
	float left_buf;
	float scale;
	
public:
	
	// Basics.
	Log( bool locked = false );
	~Log();
	void free();
	
	void load( string path, unsigned w, unsigned h, float left, float y );
	void handle( sf::Event &event, int r_x, int r_y );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
	
	// In addition.
	float getRight();
	const bool& getState();
	void setExplanator( string line );
	
	// Window.
	void setScale( float s_x, float s_y );
	void setView( unsigned w, unsigned h, int r_x, int r_y );
};