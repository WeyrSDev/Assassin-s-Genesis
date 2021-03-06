#include "mine.h"
// #include <stdio.h>

Mine::Mine()
{
	nr = 0;
	x1 = x2 = y = 0;
	state = 0;
	offset = 0;
	delay = 0;
	counter = 0;
	
	line_one = 0;
	line_two = 0;
	
	harmed = false;
	exploded = false;
	ticktocked = false;
}

Mine::~Mine()
{
	free();
}

void Mine::free()
{
	nr = 0;
	x1 = x2 = y = 0;
	state = 0;
	offset = 0;
	delay = 0;
	counter = 0;
	
	line_one = 0;
	line_two = 0;
	
	harmed = false;
	exploded = false;
	ticktocked = false;
}

void Mine::reset()
{
	nr = 0;
	state = 0;
	offset = 0;
	delay = 24;
	counter = 0;
	harmed = false;
	exploded = false;
	ticktocked = false;
}



float Mine::getX()
{
	if( state == 2 )
	{
		return x2;
	}
	
	return x1;
}

float Mine::getY()
{
	return y;
}



void Mine::setActive()
{
	if( state == 0 )
	{
		// printf( "activated\n" );
		state = 1;
	}
}

bool Mine::isActive()
{
	if( state == 0 )
	{
		return false;
	}
	
	return true;
}



void Mine::moveX( float vel )
{
	x1 += vel;
	x2 += vel;
}



void Mine::mechanics()
{
	if( state == 1 )
	{
		nr = 0;
		offset ++;
		
		if( offset /delay == line_one )
		{
			counter ++;
			offset = 0;
		}
		
		if( counter == 4 )
		{
			state = 2;
			counter = 0;
			offset = 0;
			delay = 8;
		}
	}
	else if( state == 2 )
	{
		nr = 1;
		offset ++;
		
		if( offset /delay == line_two )
		{
			state = 3;
		}
	}
}

void Mine::positioning( float x1, float x2, float y )
{
	this->x1 = x1;
	this->x2 = x2;
	this->y = y;
	
	line_one = 2;
	line_two = 7;
	
	offset = 0;
	delay = 20;
}



sf::Uint8 Mine::getOffset()
{
	return offset /delay;
}

sf::Uint8 Mine::getNr()
{
	return nr;
}

bool Mine::harm()
{
	if( state == 2 && offset /delay == line_two/2 && !harmed )
	{
		harmed = true;
		return true;
	}
	
	return false;
}

bool Mine::ableToDraw()
{
	if( state < 3 )
	{
		return true;
	}
	
	return false;
}

bool Mine::ableToDestroy()
{
	if( state == 3 )
	{
		return true;
	}
	
	return false;
}

bool Mine::explosion()
{
	if( !exploded && nr == 1 )
	{
		exploded = true;
		return true;
	}
	
	return false;
}

bool Mine::ticktock()
{
	if( !ticktocked && nr == 0 )
	{
		ticktocked = true;
		return true;
	}
	
	return false;
}