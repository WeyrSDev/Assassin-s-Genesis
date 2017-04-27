/**
    reset_button.h
    Purpose: class Reset_button after click reset each txt file, all settings, all money getted etc.

    @author Adrian Michalek
    @version 2017.03.07
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/sprite.h"
#include "drawable/text.h"
#include "menu/click.h"
#include "menu/explanator/explanator.h"

class Reset_button :public Click
{
	Explanator explanator;
	mutable sf::Uint8 state;
	mutable MySprite mySprite;
	MyText myText;
	
	bool reset;
	MySprite button;
	float scale;

public:
	
	// Basics.
	Reset_button();
    ~Reset_button();
	void free();
	
	void load( unsigned w, unsigned h );
	void handle( sf::Event &event, int r_x, int r_y );
	void draw( sf::RenderWindow* &window );
	void drawButton( sf::RenderWindow* &window );
   
	
	void fadein( int i = 1, int max = 0xFF );
	void fadeout( int i = 1, int min = 0 );
	
	// Extra.
	bool doReset();
	const sf::Uint8& getState() const;
	
	// Window.
	void setScale( float s_x, float s_y );
	void setView( unsigned w, unsigned h, int r_x, int r_y );
};