#include "winter.h"
#include "file/file.h"	// itos()

Winter::Winter()
{
	// Base.
	state = 0;
	info = "";
	fade = 0;
	coruption = 0;
	
	FPS = 0;
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	// Sound.
	music = new Music;
	
	// Hero.
	hero = new Hero;
	kunai = new Kunai;
	scope = new Scope;
	
	// Panel.
	skills = new Skills;
	heart = new Heart;
	scores = new Scores;
	money = new Money;
	pause = new Pause;
	sound_pad = new Sound_pad;
	time_box = new Time_box;
	
	// Actions.
	hp_dots = new Hp_dots;
	coins = new Coins;
	showdamage = new Showdamage;
	showheal = new Showheal;
	effect = new Effect;
	
	// World,
	background = new Background;
	brick = new Brick;
	islands = new Islands;
	greenery = new Greenery;
	ladder = new Ladder;
	wall = new Wall;
	boulder = new Boulder;
	score_dots = new Score_dots;
	exit = new Exit;
	// in addition.
	water = new Water;
	snow = new Snow;
	spikes = new Spikes;
	
	// Enemy.
	lightning = new Lightning;
	mine_factory = new Mine_factory;
	fly_factory = new Fly_factory;
}

Winter::~Winter()
{
	free();
}

void Winter::free()
{
	// Base.
	state = 0;
	info = "";
	fade = 0;
	coruption = 0;
	
	FPS = 0;
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	// Sound.
	sound.free();
	delete music;
	
	// Hero.
	delete hero;
	delete kunai;
	delete scope;
	
	// Panel.
	delete skills;
	delete heart;
	delete scores;
	delete money;
	delete pause;
	delete sound_pad;
	delete time_box;
	
	// Actions.
	delete hp_dots;
	delete coins;
	delete showdamage;
	delete showheal;
	delete effect;
	
	// World,
	delete background;
	delete brick;
	delete islands;
	delete greenery;
	delete ladder;
	delete wall;
	delete boulder;
	delete score_dots;
	delete exit;
	// in addition.
	delete water;
	delete snow;
	delete spikes;
	
	// Enemy.
	delete lightning;
	delete mine_factory;
	golem_factory.free();
	delete fly_factory;
}

void Winter::reset()
{
	// Base.
	state = 0;
	fade = 0;
	
	// Sound.
	reloadMusic();
	
	// Hero.
	hero->reset( screen_h, width );
	hero->setKeys();
	scope->reset();
	
	// Panel.
	skills->reset();
	heart->reset();
	scores->reset();
	money->reset();
	time_box->reset();
	pause->reset();
	
	// Actions.
	hp_dots->reset();
	coins->reset();
	showdamage->reset();
	showheal->reset();
	effect->reset();
	
	// World,
	int distance = brick->reset();
	islands->reset( distance );
	greenery->reset( distance );
	ladder->reset( distance );
	wall->reset( distance );
	boulder->reset( distance );
	score_dots->reset( distance );
	exit->reset( distance );
	// in addition.
	water->reset( distance );
	snow->reset();
	spikes->reset( distance );
	
	// Enemy.
	lightning->reset();
	mine_factory->reset( distance );
	golem_factory.reset( distance );
	fly_factory->reset();
}



void Winter::load( int screen_w, int screen_h, unsigned FPS )
{
	state = 0;
	info = "setting keys";
	
	type = 2;
	this->FPS = FPS;
	this->width = 113;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Sound.
	music->setID( "forest-music" );
	music->load( "data/platform/world/" +con::itos(type) +"/music.mp3", 50 );
	
	// Panel.
	scores->load( type, screen_w );
	money->load( screen_w );
	pause->load( screen_w, screen_h, FPS );
	sound_pad->load( screen_w, screen_h );
	time_box->load( FPS );
	
	// Actions.
	hp_dots->load( type, screen_w );
	coins->load( width, screen_w, type );
	showdamage->load();
	showheal->load();
	effect->load( screen_w, screen_h );
	
	// World, 
	background->load( type, screen_w, screen_h );
	brick->load( type, width, screen_w, screen_h );
	islands->load( type, width, screen_w, screen_h );
	greenery->load( type, width, screen_w );
	ladder->load( type, width, screen_w );
	wall->load( type, width, screen_w );
	boulder->load( type, width, screen_w );
	score_dots->load( screen_w );
	exit->load( width, screen_w );
	// in addition.
	water->load( type, width, screen_w, screen_h );
	snow->load( screen_w, screen_h );
	spikes->load( type, screen_w, width );
	
	// Enemy.
	lightning->load( FPS );
	mine_factory->load( type, width, screen_w, screen_h );
	golem_factory.load( width, screen_h, screen_h, "golem_winter" );
	fly_factory->load( type, screen_w, screen_h );
}

void Winter::handle( sf::Event &event )
{
	pause->handle( event );
	sound_pad->handle( event );
}

void Winter::draw( sf::RenderWindow* &window )
{
	// Sound.
	if( sound.getMusicPlay() )
	{
		music->play();
	}
	
	// Pause
	if( !pause->isPaused() && !hero->isDead() && !exit->nextState() )
	{
		mechanics();
		music->fadein( 1, sound.getMusicVolume() );
	}
	else
	{
		music->fadeout( 1, 15 );
	}
	
	
	// Fade out, fade in.
	if( (hero->isDead() || exit->nextState() || pause->isDead()) && fade == 1 )
	{
		// Value.
		sf::Uint8 value = 1;
		
		// Conscious death.
		pause->fadeout( value );
		
		// Sound.
		music->fadeout( value );
		
		// Hero.
		hero->fadeout( value );
		kunai->fadeout( value );
		
		// Panel.
		skills->fadeout( value );
		heart->fadeout( value );
		scores->fadeout( value );
		money->fadeout( value );
		sound_pad->fadeout( value );
		
		// Actions.
		hp_dots->fadeout( value );
		coins->fadeout( value );
		showdamage->fadeout( value );
		showheal->fadeout( value );
		effect->fadeout( value );
		
		// World,
		background->fadeout( value );
		brick->fadeout( value );
		islands->fadeout( value );
		greenery->fadeout( value );
		ladder->fadeout( value );
		wall->fadeout( value );
		boulder->fadeout( value );
		score_dots->fadeout( value );
		// in addition.
		water->fadeout( value );
		snow->fadeout( value );
		spikes->fadeout( value );
		
		// Enemy.
		lightning->fadeout( value );
		mine_factory->fadeout( value );
		golem_factory.fadeout( value );
		fly_factory->fadeout( value );
		
		// Set fade.
		if( background->getAlpha() == 0 )
		{
			fade = 0;
		}
	}
	else if( fade == 0 )
	{
		// Value.
		sf::Uint8 value = 2;
		
		// Hero.
		hero->fadein( value );
		kunai->fadein( value );
		
		// Panel.
		skills->fadein( value );
		heart->fadein( value );
		scores->fadein( value );
		money->fadein( value );
		sound_pad->fadein( value );
		
		// Actions.
		hp_dots->fadein( value );
		coins->fadein( value );
		effect->fadein( value );
		
		// World,
		background->fadein( value );
		brick->fadein( value );
		islands->fadein( value );
		greenery->fadein( value );
		ladder->fadein( value );
		wall->fadein( value );
		boulder->fadein( value );
		score_dots->fadein( value );
		// in addition.
		water->fadein( value );
		snow->fadein( value );
		spikes->fadein( value );
		
		// Enemy.
		lightning->fadein( value );
		mine_factory->fadein( value );
		golem_factory.fadein( value );
		fly_factory->fadein( value );
		
		// Set fade.
		if( background->getAlpha() == 0xFF )
		{
			fade = 1;
		}
	}
	

	// Background.
	background->draw( window );
	background->drawFront( window );
	greenery->draw_bg( window );
	ladder->draw( window );
	
	// Hero.
	hero->draw( window );
	kunai->draw( window );
	
	// Enemy.
	lightning->draw( window );
	mine_factory->draw( window );
	golem_factory.draw( window );
	fly_factory->draw( window );
	kunai->drawEffects( window );
	
	// Dots.
	score_dots->draw( window );
	hp_dots->draw( window );
	
	// Rest.
	coins->draw( window );
	snow->draw( window );
	spikes->draw( window );
	wall->draw( window );
	boulder->draw( window );
	water->draw( window );
	brick->draw( window );
	islands->draw( window );
	greenery->draw( window );
	
	// Show.
	showdamage->draw( *window );
	showheal->draw( *window );
	
	// Some panel stuff.
	skills->draw( window );
	heart->draw( window );
	scores->draw( window );
	money->draw( window );
	sound_pad->draw( window );
	
	// Effect and pause.
	effect->draw( window );
	pause->draw( window );
	
	// Sound changing
	if( sound_pad->musicChanged() )
	{
		music->pause();
		sound.setMusicPlay( !sound.getMusicPlay() );
	}
	
	if( sound_pad->chunkChanged() )
	{
		hero->turn();
		kunai->turn();
		coins->turn();
		wall->turn();
		boulder->turn();
		spikes->turn();
		score_dots->turn();
		exit->turn();
		islands->turn();
		mine_factory->turn();
		golem_factory.turn();
		sound.setChunkPlay( !sound.getChunkPlay() );
	}
}



bool Winter::positioning( int type, int size, int flatness, int difficulty )
{
	switch( state )
	{
		case 0:	hero->load( type, screen_w, screen_h, width ); hero->setKeys();
		kunai->load();	skills->load( FPS, screen_w, screen_h );
		heart->load();
		info = "setting position x, y of background";	break;
		
		case 1: coruption = difficulty;
		info = "reserving memory (it can take a while)";	break;
		
		case 2:	brick->reserve( size );
		info = "creating top borders of hill";	break;
		
		case 3:	brick->createTopBorders( size, flatness, ladder->getW( 0 ), ladder->getH( 0 ) );
		info = "creating flying islands";	break;
		
		case 4:	brick->setLeft();
		info = "setting the biggest x of world";	break;
		
		case 5:	brick->setRight();
		info = "filling hills step 1";	break;
		
		case 6:	islands->createFlyingIslands( brick->getBlocks(), brick->getPlanks(), difficulty,
				static_cast <float> (screen_w), brick->getRight() -(screen_w*2) );
		info = "creating left borders of hill";	break;
		
		
		
		case 7:	brick->createLeftBorders();
		info = "creating right borders of hill";	break;

		case 8:	brick->createRightBorders();
		info = "setting the smallest x of world";	break;
		
		
		
		case 9:		brick->createStuffing( 10, 11 );
		info = "filling hills step 2";	break;
		
		case 10:	brick->createStuffing( 14, 11 );
		info = "filling hills step 3";	break;
		
		case 11:	brick->createStuffing( 8, 15 );
		info = "creating top islands";	break;
		
		
		
		case 12:	islands->createTopIslands( brick->getBlocks(), ladder->getW( 1 ), ladder->getH( 1 ), ladder->getH( 0 ) );
		info = "creating bot islands";	break;
		
		case 13:	islands->createBotIslands( brick->getBlocks(), ladder->getW( 1 ), ladder->getH( 1 ) );
		info = "creating water";	break;
		
		
		
		case 14:	water->createWater( brick->getBlocks(), islands->getBlocks(), brick->getRight() );
		info = "shrink to fit vector of blocks";	break;
		
		
		
		case 15:	brick->shrink();
		info = "setting ladders";	break;
		
		
		
		case 16:	ladder->positioning( brick->getPlanks() );
					ladder->positioning( islands->getPlanks() );
					ladder->shrink();
		info = "setting greenery";	break;
		
		case 17:	greenery->positioning( brick->getBlocks() );
					greenery->positioningIslands( islands->getBlocks() );
		info = "setting wall";	break;
		
		case 18:	wall->positioning( brick->getBlocks(), difficulty );
					wall->positioningIslands( islands->getBlocks(), difficulty );
		info = "creating mine factory";	break;
		
		
		case 19: mine_factory->positioning( brick->getBlocks(), difficulty );
				 mine_factory->positioningIslands( islands->getBlocks(), difficulty );
		info = "creating golem factory";	break;
		
		case 20: golem_factory.positioning( brick->getBlocks(), difficulty );
				 golem_factory.positioningIslands( islands->getBlocks(), difficulty );
				 if( difficulty > 66 )
				 {
					golem_factory.positioning( brick->getBlocks(), difficulty );
					golem_factory.positioningIslands( islands->getBlocks(), difficulty );
				 }
		info = "setting money multiplier";	break;
		
		case 21: coins->setChance( difficulty );
		info = "positioning boulders";	break;
		
		case 22: boulder->positioning( brick->getBlocks(), wall->getXs(), difficulty );
				 boulder->positioningIslands( islands->getBlocks(), wall->getXs(), difficulty );
		info = "setting exit";	break;
		
		case 23: exit->positioning( brick->getRight() );
		info = "loading music";	break;
		
		case 24: setSound();	reloadMusic();
		info = "loading money";	break;
		
		case 25: money->loadMoney();	money->setText();
		info = "settings scores";	break;
		
		case 26: scores->positioning( difficulty );
		info = "positioning score dots";	break;
		
		case 27: score_dots->positioning( difficulty, brick->getBlocks(), brick->getWidth() );
				 score_dots->positioningIslands( difficulty, islands->getBlocks(), brick->getWidth() );
		info = "positioning spikes";	break;
		
		case 28: spikes->positioning( brick->getBlocks(), islands->getBlocks(), difficulty );
		info = "done"; break;
		
		default:
		return true;
		break;
	}
	
	state ++;
	
	return false;
}

string Winter::getInfo()
{
	return info;
}



bool Winter::defeatState()
{
	if( (hero->isDead() || pause->isDead()) && background->getAlpha() == 0 )
	{
		money->saveMoney();
		return true;
	}
	
	return false;
}

bool Winter::winState()
{
	if( exit->nextState() && background->getAlpha() == 0 )
	{
		money->saveMoney();
		return true;
	}
	
	return false;
}

int Winter::getScores()
{
	return scores->getScores();
}

int Winter::getType()
{
	return type;
}

int Winter::getCoruption()
{
	return coruption;
}

string Winter::getTimePlayed()
{
	return time_box->getTimePlayed();
}

int Winter::getDeactivatedMines()
{
	return mine_factory->getCounter();
}

int Winter::getEarnedMoney()
{
	return money->getEarnedMoney();
}




bool Winter::backToLevel()
{
	return false;
}

void Winter::setSound()
{
	// Set chunks.
	sound_pad->setChunk( sound.getChunkPlay() );
	sound_pad->setMusic( sound.getMusicPlay() );
	
	// Set chunks.
	if( !sound.getChunkPlay() )
	{
		hero->turnOff();
		kunai->turnOff();
		coins->turnOff();
		wall->turnOff();
		boulder->turnOff();
		spikes->turnOff();
		score_dots->turnOff();
		exit->turnOff();
		islands->turnOff();
		mine_factory->turnOff();
		golem_factory.turnOff();
	}
	else
	{
		hero->turnOn();
		kunai->turnOn();
		coins->turnOn();
		wall->turnOn();
		boulder->turnOn();
		spikes->turnOn();
		score_dots->turnOn();
		exit->turnOn();
		islands->turnOn();
		mine_factory->turnOn();
		golem_factory.turnOn();
		
		// Set chunks volume.
		hero->setVolume( sound.getChunkVolume() );
		kunai->setVolume( sound.getChunkVolume() );
		coins->setVolume( sound.getChunkVolume() );
		wall->setVolume( sound.getChunkVolume() );
		boulder->setVolume( sound.getChunkVolume() );
		spikes->setVolume( sound.getChunkVolume() );
		score_dots->setVolume( sound.getChunkVolume() );
		exit->setVolume( sound.getChunkVolume() );
		islands->setVolume( sound.getChunkVolume() );
		mine_factory->setVolume( sound.getChunkVolume() );
		golem_factory.setVolume( sound.getChunkVolume() );
	}
	
	// Set music volume.
	music->setVolume( sound.getMusicVolume() );
}

void Winter::reloadMusic()
{
	music->reload();
	Mix_HaltMusic();
}