#pragma once


// Sound.
#include "sound/sound.h"
#include "sound/music.h"


// Hero.
#include "04_platform/ninja/base/ninja.h"
#include "04_platform/ninja/kunai/kunai.h"
#include "04_platform/ninja/scope/scope.h"


// Panel.
#include "04_platform/panel/skill/skills.h"
#include "04_platform/panel/heart/heart.h"
#include "04_platform/panel/scores/scores.h"
#include "04_platform/panel/money/money.h"
#include "04_platform/panel/pause/pause.h"
#include "04_platform/panel/sound_pad/sound_pad.h"


// Actions.
#include "04_platform/enemy/actions/hp_dots/hp_dots.h"
#include "04_platform/enemy/actions/coins/coins.h"
#include "04_platform/enemy/actions/show/showdamage.h"
#include "04_platform/enemy/actions/show/showheal.h"
#include "04_platform/enemy/actions/effect/effect.h"


// World,
#include "04_platform/world/background/background.h"
#include "04_platform/world/brick/brick.h"
#include "04_platform/world/islands/islands.h"
#include "04_platform/world/greenery/greenery.h"
#include "04_platform/world/ladder/ladder.h"
#include "04_platform/world/wall/wall.h"
#include "04_platform/world/boulder/boulders.h"
#include "04_platform/world/score_dots/score_dots.h"
#include "04_platform/world/exit/exit.h"
// in addition.
#include "04_platform/world/water/water.h"
#include "04_platform/world/saws/saws.h"


// Enemy.
#include "04_platform/enemy/foes/checkActivity/cruncher/cruncher.h"
#include "04_platform/enemy/foes/mines/mine_factory.h"
#include "04_platform/enemy/foes/factory/factory.h"
#include "04_platform/enemy/foes/robot/robot.h"

class Future
{
	int state;
	int type;
	string info;
	sf::Uint8 fade;
	
	int FPS;
	int width;
	int screen_w;
	int screen_h;
	
	// Sound.
	Sound sound;
	Music* music;
	
	// Hero.
	Hero* hero;
	Kunai* kunai;
	Scope* scope;
	
	// Panel.
	Skills* skills;
	Heart* heart;
	Scores* scores;
	Money* money;
	Pause* pause;
	Sound_pad* sound_pad;
	
	// Actions.
	Hp_dots* hp_dots;
	Coins* coins;
	Showdamage* showdamage;
	Showheal* showheal;
	Effect* effect;
	
	// World,
	Background* background;
	Brick* brick;
	Islands* islands;
	Greenery* greenery;
	Ladder* ladder;
	Wall* wall;
	Boulder* boulder;
	Score_dots* score_dots;
	Exit* exit;
	// in addition.
	Water* water;
	Saws* saws;
	
	// Enemy.
	Cruncher* cruncher;
	Mine_factory* mine_factory;
	Factory <Robot> robot_factory;
	
public:

	Future();
    ~Future();
    void free();
	void reset();
	
    void load( int screen_w, int screen_h, unsigned FPS );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	bool positioning( int type, int size, int flatness, int difficulty );
	string getInfo();
	
	bool defeatState();
	bool winState();
	int getScores();
	int getType();
	bool backToLevel();
	void mechanics();
	
	void setSound();
	void reloadMusic();
};