#pragma once

#include "drawable/sprite.h"
#include "hp_dot.h"
#include <vector>

using namespace std;

class Hp_dots
{
	int hp;
	int screen_w;
	int main_alpha;
	MySprite sprite;
	vector <Hp_dot*> dots;
	
public:
	
	Hp_dots();
	~Hp_dots();
	void free();
	void reset();
	
	void load( int type, int screen_w );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	// In action
	void moveX( sf::Uint8 d, float v );
	void undoFall( sf::Uint8 add );
	void mechanics();
	void setAlpha( int alpha );
	
	bool drop( Rect* rect );
	bool uplift( Rect* rect );
	int getHP();
};