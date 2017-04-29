/**
    core.h
    Purpose: class Core responsible for sending renderer, accessing start valuables etc.

    @author Adrian Michalek
    @version 2016.08.19
	@email adrmic98@gmail.com
*/

#include "core.h"
#include <stdio.h>
#include <SDL2/SDL_mixer.h>

Core::Core( unsigned w, unsigned h, int state )
{
	this->state = state;
	open = true;
	
    width = w;
	height = h;
	
	// printf( /*"\x1B[1mFPS\x1B[0m=%d  */"\x1B[33mscreen_width\x1B[0m=%d  \x1B[33mscreen_height\x1B[0m=%d\n"/*, FPS*/, width, height );

    window = NULL;
	
	color.r = 21;
	color.g = 21;
	color.b = 29;
	color.a = 0xFF;
}

Core::~Core()
{
    free();
}



void Core::free()
{
    if( window != NULL )
    {
        window->close();
        delete window;
        window = NULL;

        state = 0;
        open = true;

        width = 0;
        height = 0;

        color.r = 0;
        color.g = 0;
        color.b = 0;
        color.a = 0;
		
		Mix_Quit();
    }
}

bool Core::load( string title )
{
    bool success = true;

    free();

    window = new sf::RenderWindow( sf::VideoMode( width, height ), title, sf::Style::Titlebar | sf::Style::Close );
    if( window == NULL )
    {
        printf( "Not created window!\n" );
        success = false;
    }
    else
    {
        // window->setFramerateLimit( FPS );
        // printf( "\x1B[97;1mCreated window!\x1B[0m\n" );

		if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
		{
			printf( "Mix could not initialize! Error: %s\n", Mix_GetError() );
			success = false;
		}
		else
		{
			Mix_AllocateChannels( 0xFF );
		}
	}


    return success;
}



sf::Event& Core::getEvent()
{
    return event;
}

sf::RenderWindow*& Core::getWindow()
{
    return window;
}



void Core::clear()
{
    window->clear( color );
}

void Core::display()
{
    window->display();
}



void Core::setVisible( const bool& visible )
{
    window->setVisible( visible );
}

void Core::setColor( const sf::Color& color )
{
    this->color.r = color.r;
    this->color.g = color.g;
    this->color.b = color.b;
    this->color.a = color.a;
}



int& Core::getState()
{
    return state;
}

bool& Core::isOpen()
{
    return open;
}



const unsigned Core::getWidth() const
{
    return width;
}

const unsigned Core::getHeight() const
{
    return height;
}