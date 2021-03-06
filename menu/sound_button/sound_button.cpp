/**
    sound_button.h
    Purpose: class Sound_button - for music and chunk button for changing state (on/off) - switch.

    @author Adrian Michalek
    @version 2016.10.13
	@email adrmic98@gmail.com
*/

#include "sound_button.h"
// #include <stdlib.h>


Sound_button::Sound_button( bool play )
{
    free();
	this->play = play;
}

Sound_button::~Sound_button()
{
	free();
}

void Sound_button::free()
{
	explanator.free();
	button.free();
	scratch.free();
	
	click.free();
	
	state = 0;
	focus = false;
	play = true;
}



void Sound_button::load( string path, float y )
{
	float scale = 0.5;
	
	button.setName( "sound_button-button" );
	button.load( path, 4 );
	button.setScale( scale, scale );
	button.setPosition( 10 , y );
	
	scratch.setName( "sound_button-scratch" );
	scratch.load( "data/menu/scratch.png" );
	scratch.setScale( scale, scale );
	scratch.setPosition( 10 , y );
	
	click.setID( "sound_button-click" );
	click.load( "data/menu/click.wav", 50 );
}

void Sound_button::handle( sf::Event &event )
{
	if( button.getAlpha() == 0xFF )
	{
		int x, y;
		button.setOffset( 0 );
		
		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
					
			if( button.checkCollision( x, y ) )
			{
				explanator.run();
				explanator.focus( x, y );
				button.setOffset( 1 );
			}
			else
			{
				explanator.stop();
				focus = false;
			}
		}
		
		
		if( event.type == sf::Event::MouseButtonPressed && !focus )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
					
			if( button.checkCollision( x, y ) )
			{
				focus = true;
				
				if( play )
				{
					click.play();
				}
					
				if( state == 0 )
				{
					state = 1;
				}
				else if( state == 2 )
				{
					state = 3;
				}
			}
		}
		
		if( event.type == sf::Event::MouseButtonReleased )
		{
			focus = false;
		}
		
		if( focus )
		{
			button.setOffset( 2 );
		}
	}
}

void Sound_button::draw( sf::RenderWindow* &window )
{
    window->draw( button.get() );
	
	if( state == 2 )
	{
		window->draw( scratch.get() );
	}
	
	explanator.draw( *window );
}



void Sound_button::fadein( int i, int max )
{
	button.fadein( i, max );
	scratch.fadein( i, max );
}

void Sound_button::fadeout( int i, int min )
{
	explanator.fadeout( i, min );
	button.fadeout( i, min );
	scratch.fadeout( i, min );
}



void Sound_button::setState( sf::Uint8 s )
{
	state = s;
}

float Sound_button::getBot()
{
	return button.getBot();
}

bool Sound_button::isChanged()
{
	if( state == 1 )
	{
		state = 2;
		return true;
	}
	
	if( state == 3 )
	{
		state = 0;
		return true;
	}
		
	return false;
}

void Sound_button::setExplanator( string text )
{
	explanator.load( text );
}