#pragma once

// Sound
#include "sound/sound.h"

// Hero stuff
#include "04_platform/hero/hero.h"
#include "04_platform/hero/kunai/kunai.h"
#include "04_platform/hero/scope/scope.h"

// Panel stuff
#include "04_platform/panel/heart/heart.h"
#include "04_platform/panel/money/money.h"
#include "04_platform/enemy/coins/coins.h"
#include "04_platform/panel/skill/skills.h"
#include "04_platform/panel/action/showdamage.h"
#include "04_platform/panel/action/showheal.h"

// World stuff
#include "04_platform/world/brick/brick.h"
#include "04_platform/world/background/effect.h"
#include "04_platform/world/background/background.h"
#include "04_platform/world/islands/islands.h"
#include "04_platform/world/water/water.h"
#include "04_platform/world/wall/wall.h"
#include "04_platform/world/ladder/ladder.h"
#include "04_platform/world/greenery/greenery.h"
#include "04_platform/world/background/day.h"
#include "04_platform/world/weather/sun/sun.h"

// Enemy
#include "04_platform/enemy/mine/mine_factory.h"
#include "04_platform/enemy/factory/factory.h"
#include "04_platform/enemy/golem/golem.h"
#include "04_platform/enemy/checkActivity/fireball/fireball.h"

class Forest
{
	int state;
	string info;
	
	int FPS;
	int width;
	int screen_w;
	int screen_h;
	
	// sound
	Sound sound;
	
	// hero
	Hero* hero;
	Kunai* kunai;
	Scope* scope;
	
	// panel
	Heart* heart;
	Money* money;
	Coins* coins;
	Skills* skills;
	Showdamage* showdamage;
	Showheal* showheal;
	
	// world
	Brick* brick;
	Effect* effect;
	Background* background;
	Islands* islands;
	Water* water;
	Wall* wall;
	Ladder* ladder;
	Greenery* greenery;
	Day* day;
	Sun* sun;
	
	// enemy
	Mine_factory* mine_factory;
	Factory <Golem> golem_factory;
	Fireball* fireball;
	
public:

	Forest();
    ~Forest();
    void free();
	void reset();
	
    void load( int screen_w, int screen_h, unsigned FPS );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	bool positioning( int type, int size, int flatness, int difficuly );
	string getInfo();
	
	bool nextState();
	bool backToLevel();
	void mechanics();
};