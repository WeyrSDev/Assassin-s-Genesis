#include "hero/hero.h"
#include <fstream>


Hero::Hero()
{
	sprite = NULL;
	
	which = 0;
	offset = 0;
	delay = 0;
	
	
	vel = 0;
	jVel = 0;
	grav = 0;
	scale = 0;
	

	right = false;
	
	glide = false;
	
	slide = false;
	
	climb = 0;
}

Hero::~Hero()
{
	free();
}

void Hero::free()
{
	if( sprite != NULL )
	{
		for( int i = 0; i < nr; i ++ )
		{
			sprite[ i ].free();
		}
		
		delete [] sprite;
		sprite = NULL;
	}
	
	which = 0;
	offset = 0;
	delay = 0;
	
	for( unsigned i = 0; i < keys.size(); i++ )
	{
		if( keys[ i ] != NULL )
		{
			delete [] keys[ i ];
			keys[ i ] = NULL;
		}
	}
	
	keys.clear();
	
	vel = 0;
	jVel = 0;
	grav = 0;
	scale = 0;
	
	right = false;
	
	glide = false;
	
	slide = false;
	
	climb = 0;
	
	j.free();
	a.free();
	ja.free();
	t.free();
	jt.free();
	
	box.free();
}




void Hero::load( int& screen_w, int& posY, string path )
{
	free();
	
	// 	Set scale.
	scale = 0.75;
	
	// Create array.
	sprite = new MySprite [ nr ];
	
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].setName( "hero-sprite[" + to_string( i ) + "]" );
		sprite[ i ].load( path + to_string( i ) + ".png", nr -1 );
		sprite[ i ].setScale( scale, scale );
		sprite[ i ].setPosition( 200, posY -sprite[ i ].getHeight() -200 );
	}
	sprite[ JUMP_ATTACK ].setPosition( sprite[ JUMP_ATTACK ].getX(), sprite[ JUMP_ATTACK ].getY() + ( sprite[ JUMP_ATTACK ].getHeight() - sprite[ IDLE ].getHeight() ) );
	sprite[ THROW ].setPosition( sprite[ THROW ].getX() +5, sprite[ THROW ].getY() );
	sprite[ RUN ].setPosition( sprite[ RUN ].getX(), sprite[ RUN ].getY() +5 );
	
	// Start values.
	which = IDLE;
	offset = 0;
	delay = 6;
	
	
	// Set keys.
	fstream file;
	file.open( "data/txt/menu/keyboard_temporary.txt" );
	if( file.bad() )
	{
		printf( "Cannot open file! (hero)\n" );
	}
	else
	{
		string line;
		for( int i = 0; i < nr; i ++ )
		{
			int* arrow;
			keys.push_back( arrow );
			keys[ i ] = new int[ 2 ];
			
			file >> line;	keys[ i ][ 0 ] = strToInt( line );
			file >> line;	keys[ i ][ 1 ] = strToInt( line );
		}
	}
	file.close();
	
	
	
	
	
	// Set other values
	vel = 1;
	jVel = vel*2;
	grav = 1;
	right = true;
	
	

	// Duration
	j.setLine( (nr-1)*delay + 10*delay );
	a.setLine( (nr-1)*delay + 2*delay );
	ja.setLine( (nr-1)*delay + 2*delay );
	t.setLine( (nr-1)*delay + 2*delay );
	jt.setLine( (nr-1)*delay + 2*delay );
	
	
	box.setName( "hero-box" );
	box.create( 30, sprite[ ATTACK ].getHeight() );
	box.setColor( sf::Color( 0xFF, 0x00, 0x00 ) );
	box.setAlpha( 100 );
	

	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].setPosition( sprite[ i ].getX() - ( sprite[ i ].getWidth() ), sprite[ i ].getY() );
		sprite[ i ].setPosition( sprite[ IDLE ].getX() - ( sprite[ i ].getWidth() -sprite[ IDLE ].getWidth() ), sprite[ i ].getY() );
	}
	
	sprite[ ATTACK ].setPosition( sprite[ IDLE ].getX(), sprite[ IDLE ].getY() );
	sprite[ SLIDE ].setPosition( sprite[ IDLE ].getX(), sprite[ SLIDE ].getY() );
	sprite[ JUMP_ATTACK ].setPosition( sprite[ JUMP ].getX(), sprite[ JUMP ].getY() );
	sprite[ JUMP_THROW ].setPosition( sprite[ JUMP ].getX(), sprite[ JUMP ].getY() );
	sprite[ THROW ].setPosition( sprite[ THROW ].getX() +11, sprite[ IDLE ].getY() -1 );
}

void Hero::draw( sf::RenderWindow* &window )
{
	window->draw( sprite[ which ].get() );
	
	sprite[ which ].setOffset( offset /delay );
	
	if( climb == 1 || ( climb == 0 && which != CLIMB ) )
	{
		offset ++;
	}
	
	if( offset == (nr-1) *delay )
	{
		offset = 0;
		j.setActive( false );
		a.setActive( false );
		ja.setActive( false );
		t.setActive( false );
		jt.setActive( false );
	}
	
	if( which == ATTACK )
	{
		if( right )
			box.setPosition( ( sprite[ ATTACK ].getWidth() -box.getWidth() ) + sprite[ ATTACK ].getX(), sprite[ ATTACK ].getY() );
		else
			box.setPosition( sprite[ ATTACK ].getX() -sprite[ ATTACK ].getWidth(), sprite[ ATTACK ].getY() );
		window->draw( box.get() );
	}
	
	
	// printf( "X %d   Y %d  W %d   H %d\n", getX(), getY(), getW(), getH() );
}



void Hero::fadein( int v, int max )
{
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].fadein( v, max );
	}
}

void Hero::fadeout( int v, int min )
{
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].fadeout( v, min );
	}
}


int Hero::strToInt( string s )
{
    bool m = false;
    int tmp = 0;
    unsigned i = 0;
	
    if (s[ 0 ] == '-' )
    {
          i++;
          m = true;
    }
	
    while( i < s.size() )
    {
      tmp = 10*tmp+s[ i ] -48;
      i++;
    }
	
    return m ? -tmp : tmp;   
}

bool Hero::checkKeys( int a, int b )
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( a ) ) && b == -1 )
	{
		return true;
	}
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( a ) ) )
	{
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( b ) ) )
		{
			return true;
		}
	}

	return false;
}


const int Hero::getX()
{
	int x = 0;
	
	x = sprite[ IDLE ].getX();
	
	if( !right )
	{
		x -= getW();
	}
	
	return x;
}

const int Hero::getY()
{
	return sprite[ IDLE ].getY();
}

const int Hero::getW()
{
	return sprite[ IDLE ].getWidth();
}

const int Hero::getH()
{
	return sprite[ IDLE ].getHeight();
}




const int Hero::getL()
{
	int x = 0;
	
	x = sprite[ IDLE ].getX();
	
	if( !right )
	{
		x -= getW();
	}
	
	return x;
}

const int Hero::getT()
{
	return sprite[ IDLE ].getY();
}

const int Hero::getR()
{
	return getX() + getW();
}

const int Hero::getB()
{
	return getY() + getH();
}

