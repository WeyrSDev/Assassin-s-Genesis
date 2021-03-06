/**
    information.h
    Purpose: class Information - to show text during keyboard state.

    @author Adrian Michalek
    @version 2016.11.02
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/text.h"
#include "drawable/sprite.h"
#include <vector>

class Information
{
	vector <MyText*> text;
	vector <MyText*> info_text;
	MySprite arrow;
	
public:
	
	// Basics.
	Information();
    ~Information();
	void free();

    void load( unsigned screen_w, unsigned screen_h, float y, float save_y );
    void draw( sf::RenderWindow &window );

	void fadein( int j = 1, int max = 255 );
	void fadeout( int j = 1, int min = 0 );
};