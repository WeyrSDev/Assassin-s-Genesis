/**
    keyboard.h
    Purpose: class Keyboard and Key - to manage keyboard.

    @author Adrian Michalek
    @version 2016.11.11
	@email adrmic98@gmail.com
*/

#pragma once

#include "drawable/text.h"
#include "drawable/sprite.h"
#include "menu/click.h"
#include <vector>

class Key
{
public:
	
	int one, two;

	Key( int one = -1, int two = -1 );
	~Key();
	void free();
	
	bool isEmpty();
	bool oneIsFree();
};

class Keyboard :public Click
{
	MySprite save_button;
	
	vector <MyText*> text;
	vector <Key*> keys; 		// Basics.
	vector <Key*> actual_keys;	// Useable keys.
	vector <sf::Uint8> banned_keys;
	
	int which;	// -1 = nothing was clicked;
	
	bool addMode;
	bool release;
	int lastChosen;
	
public:
	
	// Basics.
	Keyboard();
    ~Keyboard();
	void free();
	
	template <typename object>
	void freeObject( vector <object> o );
	
    void load( unsigned screen_w, unsigned screen_h, float y );
    void draw( sf::RenderWindow &window );
	void handle( sf::Event &event );

	void fadein( int j = 1, int max = 0xFF );
	void fadeout( int j = 1, int min = 0 );
	
	// Other.
	string getName( int n ); 	// e. g. n == 71, return == "left"
	float getSaveY();
	
	
	void add( sf::Event &event );			// add
	bool substract( sf::Event &event );		// remove
	bool isPossibleKey( sf::Event &event ); // check whether key is possible to add
	void handleButton( sf::Event &event );	// specially for button
};

/*
enum  	Key { 
  Unknown = -1, 
  A = 0, 
  B, 
  C, 
  D, // 3
  E, 
  F, 
  G, 
  H, 
  I, 
  J, 
  K, // 10
  L, 
  M, 
  N, 
  O, 
  P, // 15
  Q, 
  R, 
  S, 
  T, 
  U, // 20
  V, 
  W, 
  X, 
  Y, 
  Z, // 25
  Num0, 
  Num1, 
  Num2, 
  Num3, 
  Num4, // 30
  Num5, 
  Num6, 
  Num7, 
  Num8, 
  Num9, // 35
  Escape, 
  LControl, 
  LShift, 
  LAlt, 
  LSystem, // 40
  RControl, 
  RShift, 
  RAlt, 
  RSystem, 
  Menu, // 45
  LBracket, 
  RBracket, 
  SemiColon, 
  Comma, 
  Period,  // 50
  Quote, 
  Slash, 
  BackSlash, 
  Tilde, 
  Equal, // 55
  Dash, 
  Space, 
  Return, 
  BackSpace, 
  Tab, // 60
  PageUp, 
  PageDown, 
  End, 
  Home, 
  Insert, // 65
  Delete, 
  Add, 
  Subtract, 
  Multiply, 
  Divide, // 70
  Left, // 71
  Right, // 72
  Up, // 73
  Down, // 74 
  Numpad0, // 75
  Numpad1, 
  Numpad2, 
  Numpad3, 
  Numpad4, 
  Numpad5, 
  Numpad6, 
  Numpad7, 
  Numpad8, 
  Numpad9, // 84
  F1, 
  F2, 
  F3, 
  F4, 
  F5, 
  F6, 
  F7, 
  F8, 
  F9, 
  F10, 
  F11, 
  F12, 
  F13, 
  F14, 
  F15, 
  Pause, 
  KeyCount 
}
*/