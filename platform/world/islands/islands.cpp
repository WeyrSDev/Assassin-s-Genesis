#include "islands.h"
#include <cstdlib>
#include "file/file.h"

Islands::Islands()
{
	free();
}

Islands::~Islands()
{
	free();
}

void Islands::free()
{
	width = 0;
	screen_w = 0;
	screen_h = 0;
	moved = false;
	main_vel = 0;
	
	if( !hovers.empty() )
	{
		for( auto &it :hovers )
		{
			it->free();
		}
		
		hovers.clear();
	}
	
	if( !blocks.empty() )
	{
		for( auto &it :blocks )
		{
			it->free();
		}
		
		blocks.clear();
	}
	
	if( !planks.empty() )
	{
		for( auto &it :planks )
		{
			it->free();
		}
		
		planks.clear();
	}
	
	if( !sprites.empty() )
	{
		for( auto &it :sprites )
		{
			it->free();
		}
		
		sprites.clear();
	}
	
	hit.free();
}

void Islands::reset( int distance )
{
	for( auto &it :hovers )
	{
		it->moveX( distance );
	}
	
	for( auto &it :blocks )
	{
		it->x += distance;
	}
}

void Islands::load( int type, int width, int screen_w, int screen_h )
{
	free();
	
	// Load data.
	for( int i = 0; i < 9; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ i ]->setName( "islands-sprites[" +con::itos( i ) +"]" );
	}
	
	sprites[ 0 ]->load( "data/platform/world/" +con::itos( type ) +"/0.png" );
	sprites[ 1 ]->load( "data/platform/world/" +con::itos( type ) +"/1.png" );
	sprites[ 2 ]->load( "data/platform/world/" +con::itos( type ) +"/2.png" );
	sprites[ 3 ]->load( "data/platform/world/" +con::itos( type ) +"/5.png" );
	sprites[ 4 ]->load( "data/platform/world/" +con::itos( type ) +"/6.png" );
	sprites[ 5 ]->load( "data/platform/world/" +con::itos( type ) +"/7.png" );
	sprites[ 6 ]->load( "data/platform/world/" +con::itos( type ) +"/10.png" );
	sprites[ 7 ]->load( "data/platform/world/" +con::itos( type ) +"/11.png" );
	sprites[ 8 ]->load( "data/platform/world/" +con::itos( type ) +"/12.png" );
	
	for( auto &it :sprites )
	{
		it->setScale( 0.9, 0.9 );
	}
	
	this->width = width;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	
	// Set main vel.
	MyFile file;
	file.load( "data/txt/world/island_vel.txt" );
	if( file.is_good() )
	{
		string line;
		int c = type;
		while( file.get() >> line )
		{
			if( c == 0 )
			{
				main_vel = con::stof( line.c_str() );
				break;
			}
			c--;
		}
	}
	file.free();
	
	hit.setName( "islands-hit" );
	hit.load( "data/platform/world/sounds/island/0.wav" );
}

void Islands::draw( sf::RenderWindow* &window )
{
	for( auto &it :hovers )
	{
		for( unsigned i = 0; i < it->getSize(); i++ )
		{
			if( it->getX(i) > -width*2 && it->getX(i) < screen_w +width )
			{
				sprites[ it->getNr(i) ]->setPosition( it->getX(i), it->getY(i) );
				window->draw( sprites[ it->getNr(i) ]->get() );
			}
		}
	}
	
	for( auto &it :blocks )
	{
		if( it->nr != -1 )
		{
			if( it->x > -width && it->x < screen_w )
			{
				sprites[ it->nr ]->setPosition( it->x, it->y );
				window->draw( sprites[ it->nr ]->get() );
			}
		}
	}
}

void Islands::fadein( int v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Islands::fadeout( int v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}



void Islands::addHover( float startX, float endX, float y, float vel )
{
	int nr = 0;
	if( rand()%2 == 1 )	nr = 1;
	
	hovers.push_back( new Hover() ); 	// add block.
	hovers[ hovers.size()-1 ]->positioning( width, nr );
	hovers[ hovers.size()-1 ]->setPosition( startX, endX, y, vel );
}

void Islands::addBlock( int n, int x, int y )
{
	blocks.push_back( new Block() ); 	// add block.
	blocks[ blocks.size()-1 ]->nr = n; 	// set chosen.
	blocks[ blocks.size()-1 ]->x = x; 	// set x.
	blocks[ blocks.size()-1 ]->y = y; 	// set y.
}

void Islands::addPlank( int n, int x, int y )
{
	planks.push_back( new Block() ); 	// add block.
	planks[ planks.size()-1 ]->nr = n; 	// set chosen.
	planks[ planks.size()-1 ]->x = x; 	// set x.
	planks[ planks.size()-1 ]->y = y; 	// set y.
}



void Islands::createFlyingIslands( vector <Block*> blocks, vector <Block*> planks, int chance, float min, float max )
{
	for( unsigned i = 0; i < blocks.size()-2; i++ )
	{
		if( (blocks[ i ]->nr == 2 || blocks[ i ]->nr == 7) && blocks[ i ]->x > min && blocks[ i ]->x < max )
		{
			if( blocks[ i ]->y == blocks[ i +2 ]->y && blocks[ i +2 ]->nr != -1 )
			{
				if( rand()%100 < chance )
				{
					int distance = rand()%2 +4;
				
					int startX = blocks[ i ]->x +width;
					int endX = blocks[ i ]->x + (distance +2)*width;
					int y = blocks[ i ]->y;
					
					float vel = main_vel;
					
					if( rand()%6 < 2 )
					{
						vel += static_cast <float> (rand()%80) /100;
					}
					else
					{
						vel += static_cast <float> (rand()%40) /100;
					}
					
					addHover( startX, endX, y, vel );
					
					for( unsigned j = 0; j < planks.size(); j++ )
					{
						if( planks[ j ]->x > blocks[ i +2 ]->x )
						{
							for( unsigned k = j; k < planks.size(); k++ )
							{
								planks[ k ]->x += distance*width;
							}
							
							break;
						}
					}
					
					for( unsigned j = i +1; j < blocks.size(); j++ )
					{
						blocks[ j ]->x += distance*width;
					}
					
					// put -1
					int new_x = blocks[ i ]->x;
					
					for( int j = 0; j < distance; j++ )
					{
						blocks.push_back( new Block() );
						blocks[ blocks.size() -1 ]->x = new_x + width*j;
						blocks[ blocks.size() -1 ]->y = blocks[ i ]->y;
						blocks[ blocks.size() -1 ]->nr = -1;
					}
				}
			}
		}
	}
}

void Islands::createBotIslands( vector <Block*> blocks, int w, int h )
{
	vector <int> posX;
	vector <int> posY;
	vector <int> counters;
	
	// Searcher
	for( auto i = blocks.begin(); i != blocks.end(); i++ )
	{
		// blocks with grass, apriopriate y
		if( (*i)->y < screen_h -width*2 )
		{
			if( (*i)->nr >= 5 && (*i)->nr <= 7 )
			{
				posX.push_back( (*i)->x );
				posY.push_back( (*i)->y );
				counters.push_back( 1 );
				
				for( auto j = i +1; j != blocks.end(); j++ )
				{
					if( (*j)->y == (*i)->y ) // check y
					{
						if( ((*j)->nr >= 5 && (*j)->nr <= 7) || (*j)->nr == -1 )
						{
							counters[ counters.size()-1 ] ++;
						}
						else
						{
							i = j +1;
							break;
						}
					}
					else
					{
						i = j +1;
						break;
					}
				}
			}
			
		}
	}

	
	// Creator
	for( unsigned i = 0; i < posX.size(); i++ )
	{
		// x and y for ladder
		int myX, myY;
		
		// searching for free space
		sf::Uint8 success = 0;
		
		// check left
		for( unsigned j = 0; j < blocks.size(); j++ )
		{
			if( blocks[ j ]->y == posY[ i ] && blocks[ j ]->nr == -1 )
			{
				if( blocks[ j ]->x == posX[ i ] -width )
				{
					success = 1;
					myX = blocks[ j ]->x +width -w +10;
					break;
				}
			}
		}
		
		int surplus = 0;
		// check right
		if( success == 0 )
		{
			for( unsigned j = 1; j < blocks.size()-1; j++ )
			{
				if( blocks[ j ]->y == posY[ i ] && blocks[ j ]->nr == -1 && blocks[j -1]->nr != -1 )
				{
					if( blocks[ j ]->x == posX[ i ] + width *(counters[ i ]-1)
					&& blocks[ j ]->x != blocks[ j +1 ]->x )	// check if we can climb (change of floor)
					{
						success = 2;
						myX = blocks[ j ]->x -10;
						surplus = 0 *width;
						// printf( "2 %d\n", myX );
						break;
					}
				}
			}
		}
		
		if( success != 0 )
		{
			// add ladder
			addPlank( 1, myX, posY[ i ] -h +width*2 );
			
			if( success == 2 )
			{
				myX -= width*(counters[ i ] -1) -w -surplus;
				counters[ i ] -= 1;
			}
			
			if( posY[ i ] == screen_h -width*4 ) // 0, 1, 2.
			{
				myY = screen_h -width;
				int saveX = myX;
				
				addBlock( 6, myX, myY );
				myX += width;
				
				for( int j = 0; j < counters[ i ]-2; j++ )
				{
					addBlock( 7, myX, myY );
					myX += width;
				}
				
				addBlock( 8, myX, myY );
				
				myY = screen_h -width*2;
				myX = saveX;
			}
			else
			{
				myY = screen_h -width;
			}
			
			addBlock( 0, myX, myY );
			myX += width;
			
			for( int j = 0; j < counters[ i ]-2; j++ )
			{
				addBlock( 1, myX, myY );
				myX += width;
			}
			
			addBlock( 2, myX, myY );
		}
	}
}

void Islands::createTopIslands( vector <Block*> blocks, int w, int h, int h2 )
{
	vector <int> posX;
	vector <int> posY;
	
	// Searcher
	unsigned last = 0;
	for( unsigned i = 0; i < blocks.size() -1; i++ )
	{
		// blocks with grass, apriopriate y
		if( blocks[ i ]->y >= screen_h -width*2 && 
			blocks[ i ]->nr >= -1 && blocks[ i ]->nr <= 7 )
		{
			posX.push_back( blocks[ i ]->x );
			posY.push_back( blocks[ i ]->y -width*2 );
			
			if( blocks[ i ]->y != blocks[ i +1 ]->y )
			{
				posX.erase( posX.begin() +posX.size() -1 );
				posY.erase( posY.begin() +posY.size() -1 );
			}
			
			if( last == i-1 && posX[ posX.size() -2 ] != posX[ posX.size() -1 ] -width )
			{
				int x = posX[ posX.size() -2 ];
				int nr = (posX[ posX.size() -1 ] -width -x) /width;
				for( int j = 0; j < nr; j++ )
				{
					posX.push_back( x +(width*(j+1)) );
					posY.push_back( blocks[ i ]->y -width*2 );
				}
			}
				
			last = i;
		}
	}
	
	// Merger
	for( unsigned i = 0; i < posY.size() -1; i++ )
	{
		if( posY[ i ] != posY[ i +1 ] && posX[ i ] == posX[ i +1 ] -width )
		{
			posY[ i ] = posY[ i +1 ];
		}
	}
	
	// Rubbish
	bool rubbish = true;
	while( rubbish )
	{
		rubbish = false;
		for( unsigned i = 0; i < posX.size(); i++ )
		{
			for( unsigned j = 0; j < blocks.size(); j++ )
			{
				if( (posX[ i ] == blocks[ j ]->x -width && posY[ i ] == blocks[ j ]->y -width) ||
				(posX[ i ] == blocks[ j ]->x +width && posY[ i ] == blocks[ j ]->y -width))
				{
					posX.erase( posX.begin() +i );
					posY.erase( posY.begin() +i );
					rubbish = true;
					break;
					i = posX.size();
				}
			}
		}
	}
	
	
	if( posY[ 0 ] != posY[ 1 ] )
	{
		posX.erase( posX.begin() );
		posY.erase( posY.begin() );
	}
	
	
	for( unsigned i = 0; i < posX.size() -1; i++ )
	{
		if( posX[ i ] > posX[ i +1 ] )
		{
			swap( posX[ i ], posX[ i +1 ] );
			swap( posY[ i ], posY[ i +1 ] );
		}
	}
	
	/*
	for( unsigned i = 0; i < posX.size() -1; i++ )
	{
		if( posX[ i ] > posX[ i +1 ] )
		{
			printf( "--%d %d\n", posX[ i ], posY[ i ] );
		}
	}
	*/
	

	// Creator
	vector <int> c;
	vector <int> x;
	vector <int> y;
	
	c.push_back( 1 );
	x.push_back( posX[ 0 ] );
	y.push_back( posY[ 0 ] );
	
	for( unsigned i = 0; i < posX.size() -1; i++ )
	{
		if( posX[ i ] == posX[ i +1 ] -width && posY[ i ] == posY[ i +1 ] )
		{
			c[ c.size() -1 ] ++;
		}
		else
		{
			c.push_back( 1 );
			x.push_back( posX[ i +1 ] );
			y.push_back( posY[ i +1 ] );
		}
	}
	
	
	
	
	
	bool flag = true;
	while( flag )
	{
		flag = false;
		for( unsigned i = 0; i < c.size(); i++ )
		{
			if( c[ i ] < 2 )
			{
				c.erase( c.begin() +i );
				x.erase( x.begin() +i );
				y.erase( y.begin() +i );
				flag = true;
			}
		}
	}
	
	for( unsigned i = 0; i < x.size(); i++ )
	{
		int lastNr = 3;
		unsigned actual_size = this->blocks.size();
		
		if( this->blocks.size() > 0 )
		{
			if( this->blocks[ this->blocks.size() -1 ]->x == x[ i ] &&
				this->blocks[ this->blocks.size() -1 ]->y == y[ i ] )
			{
				if( c[ i ] >= 4 )
				{
					lastNr = 3;
					addBlock( lastNr, x[ i ] +width*2, y[ i ] );
					c[ i ] -= 2;
				}
				else
				{
					c[ i ] = 0;
				}
			}
			else if( this->blocks[ this->blocks.size() -1 ]->x +width == x[ i ] &&
					 this->blocks[ this->blocks.size() -1 ]->y == y[ i ] )
			{
				if( c[ i ] >= 3 )
				{
					lastNr = 3;
					addBlock( lastNr, x[ i ] +width, y[ i ] );
					c[ i ] --;
				}
				else
				{
					c[ i ] = 0;
				}
			}
			else
			{
				lastNr = 3;
				addBlock( lastNr, x[ i ], y[ i ] );
				c[ i ] --;
			}
		}
		else
		{
			lastNr = 3;
			addBlock( lastNr, x[ i ], y[ i ] );
			c[ i ] --;
		}
		
		
		while( c[ i ] > 0 )
		{
			c[ i ] --;
			if( lastNr == 3 || lastNr == 4 )
			{
				if( c[ i ] == 0 )
				{
					lastNr = 5;
					addBlock( lastNr, this->blocks[ this->blocks.size() -1 ]->x +width, y[ i ] );
				}
				else if( c[ i ] > 1 )
				{
					if( rand()%6 < 2 )
					{
						lastNr = 5;
						addBlock( lastNr, this->blocks[ this->blocks.size() -1 ]->x +width, y[ i ] );
					}
					else
					{
						lastNr = 4;
						addBlock( lastNr, this->blocks[ this->blocks.size() -1 ]->x +width, y[ i ] );
					}
				}
			}
			
			else if( lastNr == 5 )
			{
				lastNr = -1;
				addBlock( lastNr, this->blocks[ this->blocks.size() -1 ]->x +width, y[ i ] );
			}
			else if( lastNr == -1 && c[ i ] > 0 )
			{
				lastNr = 3;
				addBlock( lastNr, this->blocks[ this->blocks.size() -1 ]->x +width, y[ i ] );
			}
		}
		
		
		if( i < x.size() -1 )
		{
			if( this->blocks[ this->blocks.size() -1 ]->x +width == x[ i+1 ] &&
				this->blocks[ this->blocks.size() -1 ]->y != y[ i+1 ] &&
				this->blocks[ this->blocks.size() -1 ]->nr != -1 )
			{
				addPlank( 0, x[ i+1 ] -w +10, y[ i ] -h2 );
			}
			else
			{
				for( unsigned j = 0; j < blocks.size(); j++ )
				{
					for( unsigned k = actual_size; k < this->blocks.size(); k++ )
					{
						if( this->blocks[ k ]->nr == 5 )
						{
							if( this->blocks[ k ]->x == blocks[ j ]->x -width && this->blocks[ k ]->y == blocks[ j ]->y -width*2 )
							{
								if( blocks[ j ]->nr != -1 )
								{
									// printf( "1sth\n" );
									addPlank( 1, blocks[ j ]->x -10, blocks[ j ]->y -h );
									j = blocks.size();
									break;
								}
							}
						}
						else if( this->blocks[ k ]->nr == 3 )
						{
							if( this->blocks[ k ]->x == blocks[ j ]->x +width && this->blocks[ k ]->y == blocks[ j ]->y -width*2 )
							{
								if( blocks[ j ]->nr != -1 )
								{
									// printf( "2sth\n" );
									addPlank( 1, blocks[ j ]->x +width +10 -w, blocks[ j ]->y -h );
									j = blocks.size();
									break;
								}
							}
						}
					}
				}
			}
		}
		
		
	}
	
	
	/*
	for( unsigned i = 0; i < this->blocks.size() -1; i++ )
	{
		if( this->blocks[ i ]->x == this->blocks[ i +1 ]->x -width &&
			this->blocks[ i ]->y == this->blocks[ i +1 ]->y &&
			this->blocks[ i ]->nr == 7 &&
			this->blocks[ i +1 ]->nr == 5 )
			{
				printf( "%d %d\n", this->blocks[ i ]->x, this->blocks[ i ]->y );
			}
	}
	*/
}



void Islands::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :hovers )
		{
			it->moveX( vel );
		}
		
		for( auto &it :blocks )
		{
			it->x += vel;
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :hovers )
		{
			it->moveX( -vel );
		}
		
		for( auto &it :blocks )
		{
			it->x -= vel;
		}
	}
}

void Islands::moveX_stand( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :hovers )
		{
			it->moveX_stand( vel );
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :hovers )
		{
			it->moveX_stand( -vel );
		}
	}
}



void Islands::undoFall( sf::Uint8 add )
{
	for( auto &it :hovers )
	{
		it->moveX( add );
	}
	
	for( auto &it :blocks )
	{
		it->x += add;
	}
}

void Islands::setColor( sf::Color color )
{
	for( auto &i :sprites )
	{
		i->setColor( color );
	}
}



void Islands::mechanics()
{
	for( auto &it :hovers )
	{
		if( it->mechanics( width ) )
		{
			if( it->getX(0) > -width*2 && it->getX(it->getSize() -1) < screen_w +width )
			{
				if( hit.isPlayable() )
				{
					hit.play();
				}
			}
		}
	}
}

void Islands::stop( sf::Uint8 direction )
{
	if( !moved )
	{
		if( direction == 1 )
		{
			for( auto &it :hovers )
			{
				it->moveX( -2 );
			}
		}
		else if( direction == 2 )
		{
			for( auto &it :hovers )
			{
				it->moveX( 2 );
			}
		}
		
		moved = true;
	}
	
	for( auto &it :hovers )
	{
		it->turnOff();
	}
}

void Islands::start()
{
	moved = false;
	
	for( auto &it :hovers )
	{
		it->turnOn();
	}
}



vector <Block*> Islands::getBlocks()
{
	return blocks;
}

vector <Block*> Islands::getPlanks()
{
	return planks;
}


bool Islands::checkCollision( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &it :hovers )
		{
			for( unsigned i = 0; i < it->getSize(); i++ )
			{
				if( it->getX(i) > -width*2 && it->getX(i) < screen_w +width )
				{
					sprites[ it->getNr(i) ]->setPosition( it->getX(i), it->getY(i) );
					if( sprites[ it->getNr(i) ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
					{
						return true;
					}
				}
			}
		}
		
		for( auto &i :blocks )
		{
			if( i->nr != -1 )
			{
				if( i->x > -width && i->x < screen_w )
				{
					sprites[ i->nr ]->setPosition( i->x, i->y );
					if( sprites[ i->nr ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
					{
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

bool Islands::checkPixelCollision( Rect* rect )
{
	if( rect != NULL )
	{
		int l = rect->getX();		// left
		int r = rect->getRight();	// right
		int t = rect->getY();		// top
		int b = rect->getBot(); 	// bot
		
		for( auto &it :hovers )
		{
			for( unsigned i = 0; i < it->getSize(); i++ )
			{
				if( it->getX(i) > -width*2 && it->getX(i) < screen_w +width )
				{
					sprites[ it->getNr(i) ]->setPosition( it->getX(i), it->getY(i) );
					
					for( int j = l; j <= r; j++ )
					{
						if( sprites[ it->getNr(i) ]->checkPixelCollision( j, t ) )		return true;
						else if( sprites[ it->getNr(i) ]->checkPixelCollision( j, b ) )	return true;
					}
					
					for( int j = t; j <= b; j++ )
					{
						if( sprites[ it->getNr(i) ]->checkPixelCollision( l, j ) )		return true;
						else if( sprites[ it->getNr(i) ]->checkPixelCollision( r, j ) )	return true;
					}
				}
			}
		}
		
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			if( blocks[ i ]->nr != -1 )
			{
				if( blocks[ i ]->x > -width && blocks[ i ]->x < screen_w )
				{
					sprites[ blocks[ i ]->nr ]->setPosition( blocks[ i ]->x, blocks[ i ]->y );
				
					for( int j = l; j <= r; j++ )
					{
						if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( j, t ) )		return true;
						else if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( j, b ) )	return true;
					}
					
					for( int j = t; j <= b; j++ )
					{
						if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( l, j ) )		return true;
						else if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( r, j ) )	return true;
					}
				}
			}
		}
	}
	
	return false;
}

bool Islands::checkFlyingIslands( Rect* rect )
{
	if( rect != NULL )
	{
		int l = rect->getX() -10;		// left
		int r = rect->getRight() +10;	// right
		int t = rect->getY();		// top
		int b = rect->getBot(); 	// bot
		
		for( auto &it :hovers )
		{
			for( unsigned i = 0; i < it->getSize(); i++ )
			{
				if( it->getX(i) > -width && it->getX(i) < screen_w +width )
				{
					sprites[ it->getNr(i) ]->setPosition( it->getX(i), it->getY(i) );
					
					for( int j = l; j <= r; j++ )
					{
						if( sprites[ it->getNr(i) ]->checkPixelCollision( j, t ) )
						{
							return true;
						}
						else if( sprites[ it->getNr(i) ]->checkPixelCollision( j, b ) )
						{
							return true;
						}
					}
					
					for( int j = t; j <= b; j++ )
					{
						if( sprites[ it->getNr(i) ]->checkPixelCollision( l, j ) )
						{
							return true;
						}
						else if( sprites[ it->getNr(i) ]->checkPixelCollision( r, j ) )
						{
							return true;
						}
					}
				}
			}
		}
	}
	
	return false;
}

bool Islands::checkOtherIslands( Rect* rect )
{
	if( rect != NULL )
	{
		int l = rect->getX();		// left
		int r = rect->getRight();	// right
		int t = rect->getY();		// top
		int b = rect->getBot(); 	// bot
		
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			if( blocks[ i ]->nr != -1 )
			{
				if( blocks[ i ]->x > -width && blocks[ i ]->x < screen_w )
				{
					sprites[ blocks[ i ]->nr ]->setPosition( blocks[ i ]->x, blocks[ i ]->y );
				
					for( int j = l; j <= r; j++ )
					{
						if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( j, t ) )		return true;
						else if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( j, b ) )	return true;
					}
					
					for( int j = t; j <= b; j++ )
					{
						if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( l, j ) )		return true;
						else if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( r, j ) )	return true;
					}
				}
			}
		}
	}
	
	return false;
}

void Islands::checkStands( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &it :hovers )
		{
			for( unsigned i = 0; i < it->getSize(); i++ )
			{
				if( it->getX(i) > -width*2 && it->getX(i) < screen_w +width )
				{
					sprites[ it->getNr(i) ]->setPosition( it->getX(i), it->getY(i) -5 );
					if( sprites[ it->getNr(i) ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
					{
						it->setStand( true );
						break;
					}
					else
					{
						it->setStand( false );
					}
				}
			}
		}
	}
}

bool Islands::isStand()
{
	for( auto &it :hovers )
	{
		for( unsigned i = 0; i < it->getSize(); i++ )
		{
			if( it->isStand() )
			{
				return true;
			}
		}
	}
	
	return false;
}

float Islands::getVel()
{
	for( auto &it :hovers )
	{
		for( unsigned i = 0; i < it->getSize(); i++ )
		{
			if( it->getX(i) > -width*2 && it->getX(i) < screen_w +width )
			{
				if( it->isStand() )
				{
					return it->getVel();
				}
			}
		}
	}
	
	return 0;
}

sf::Uint8 Islands::getDirection()
{
	for( auto &it :hovers )
	{
		for( unsigned i = 0; i < it->getSize(); i++ )
		{
			if( it->getX(i) > -width*2 && it->getX(i) < screen_w +width )
			{
				if( it->isStand() )
				{
					return it->getDirection();
				}
			}
		}
	}
	
	return 0;
}



void Islands::turn()
{
	hit.turn();
}

void Islands::turnOn()
{
	hit.turnOn();
}

void Islands::turnOff()
{
	hit.turnOff();
}

void Islands::setVolume( int v )
{
	hit.setVolume( v );
}
