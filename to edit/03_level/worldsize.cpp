/**
    worldsize.h
    Purpose: class Worldsize - to choose size of world.

    @author Adrian Michalek
    @version 2016.12.12
	@email adrmic98@gmail.com
*/

#include "worldsize.h"

Worldsize::Worldsize()
{
	range = 0;
	blocks = 0;
	keep = false;
	
	delay = 0;
	blocks_value = 0;
	blocks_times = 0;
}

Worldsize::~Worldsize()
{
	text.free();
	blocks_text.free();
	white_bar.free();
	green_bar.free();
	
	range = 0;
	blocks = 0;
	keep = false;
	
	delay = 0;
	blocks_value = 0;
	blocks_times = 0;
	
	click.free();
}



void Worldsize::load( int screen_w, int screen_h )
{
	text.setName( "worldsize-text" );
	text.setFont( "data/fonts/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	text.setText( "Set length" );
	text.setPosition( screen_w/2 -text.getWidth()/2, screen_h/2 - text.getHeight()/2 );
	
	delay = 3.05;
	blocks_times = 5;
	blocks_value = 120;
	blocks = blocks_value;
	
	blocks_text.setName( "worldsize-blocks_text" );
	blocks_text.setFont( "data/fonts/Jaapokki-Regular.otf", 20, 0x33, 0x66, 0x99 );
	blocks_text.setText( "blocks " + to_string( blocks ) + "-" + to_string( blocks*blocks_times ) + ", est. time > " + to_string( static_cast <int> (blocks *delay) ) +"sec" );
	
	
	sf::Uint8 bar_width = 30;
	
	white_bar.setName( "worldsize-white_bar" );
	white_bar.create( screen_w/4 *3, bar_width );
	white_bar.setPosition( screen_w/2 -white_bar.getWidth()/2, text.getBot() +20 );
	white_bar.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	
	green_bar.setName( "worldsize-green_bar" );
	green_bar.create( 1, bar_width );
	green_bar.setPosition( white_bar.getLeft(), text.getBot() +20 );
	green_bar.setColor( sf::Color( 0x66, 0x99, 0x66 ) );
	
	green_bar.setScale( blocks_value/2 -10, 1 );
	
	blocks_text.setPosition( screen_w/2 -blocks_text.getWidth()/2, white_bar.getTop() +3 );
	
	click.setID( "choice-click" );
	click.load( "data/sounds/click.wav", 50 );
}

void Worldsize::handle( sf::Event &event )
{
	if( text.getAlpha() == 0xFF )
	{
		if( event.type == sf::Event::MouseButtonPressed )
		{
			int x, y;
			
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( white_bar.checkCollision( x, y ) )
			{
				if( x -white_bar.getX() )
				{
					green_bar.setScale( x -white_bar.getX() );
					
					if( play )
					{
						click.play();
					}
					
					blocks = (green_bar.getWidth()+10) *2;

					int r = static_cast <int> (blocks*delay);
						
					string t = "blocks " + to_string( blocks ) + "-" + to_string( blocks*blocks_times );
					
					if( r < 1800 )
					{
						blocks_text.setText( t + ", est. time > " + to_string( r ) + " sec" );
					}
					else if( r > 1800 && r < 2400 )
					{
						blocks_text.setText( t + ", est. time > 30 min" );
					}
					else if( r > 2400 && r < 3600 )
					{
						blocks_text.setText( t + ", est. time > 45 min" );
					}
					else if( r > 3600 && r < 4200 )
					{
						blocks_text.setText( t + ", est. time > 1 hour" );
					}
					else
					{
						blocks_text.setText( t + "   y o u   a r e   c r a z y" );
					}
					
					
					blocks_text.reloadPosition();
				}
			}
		}
	}
}

void Worldsize::draw( sf::RenderWindow &window )
{
	window.draw( text.get() );
	window.draw( white_bar.get() );
	window.draw( green_bar.get() );
	window.draw( blocks_text.get() );
}



void Worldsize::fadein( int j, int max )
{
	text.fadein( j, max );
	blocks_text.fadein( j, max );
	white_bar.fadein( j, max );
	green_bar.fadein( j, max );
	blocks_text.fadein( j, max );
}

void Worldsize::fadeout( int j, int min )
{
	text.fadeout( j, min );
	blocks_text.fadeout( j, min );
	white_bar.fadeout( j, min );
	green_bar.fadeout( j, min );
	blocks_text.fadeout( j, min );
}



int Worldsize::getResult()
{
	return blocks;
}

void Worldsize::reset()
{
	range = 0;
	blocks = blocks_value;
	green_bar.setScale( blocks_value/2 -10, 1 );
	blocks_text.setText( "blocks " + to_string( blocks ) + "-" + to_string( blocks*blocks_times ) + ", est. time > " + to_string( static_cast <int> (blocks *delay) ) +"sec" );
	blocks_text.reloadPosition();
}

	
bool Worldsize::move( int vel, int scope )
{
	if( vel < 0 )
	{
		if( range > scope )
		{
			keep = true;
		}
	}
	else if( vel > 0 )
	{
		if( range < scope )
		{
			keep = true;
		}
	}
	
	if( keep )
	{
		range += vel;
		text.setPosition( text.getX() +vel, text.getY() );
		white_bar.setPosition( white_bar.getX() +vel, white_bar.getY() );
		green_bar.setPosition( green_bar.getX() +vel, green_bar.getY() );
		blocks_text.setPosition( blocks_text.getX() +vel, blocks_text.getY() );
	}
	else
	{
		range = scope;
	}
		
		
	if( range == scope )
	{
		return true;
	}
		
	return false;
}