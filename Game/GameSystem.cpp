#include "GameSystem.h"

#include <sstream>

using namespace std;

//maps
map<string, GameSystem::ChipElement>	GameSystem::ELEMENT_STRING_MAP			;
map<string, GameSystem::DamageType>		GameSystem::DAMAGE_STRING_MAP			;
map<string, GameSystem::TargetType>		GameSystem::TARGET_STRING_MAP			;
map<string, GameSystem::ChipType>		GameSystem::CHIPTYPE_STRING_MAP			;

map<string, GameSystem::PanelTeam> 		GameSystem::PANELTEAM_STRING_MAP		;

map<string, GameSystem::ProjectileMovingType> GameSystem::PROJECTILE_MOVING_MAP;
//map<string, GameSystem::ProjectilePositionType> GameSystem::PROJECTILE_POSITION_MAP;

//pictures
OSL_IMAGE* GameSystem::m_controller_pics[CONTROLLER_NB];
OSL_IMAGE* GameSystem::m_chip_pics[CHIP_TYPE_NB];
OSL_IMAGE* GameSystem::m_element_pics[CHIP_ELEMENT_NB];

//fonts
MMBNFont* GameSystem::m_actor_life_font;
MMBNFont* GameSystem::m_battle_chip_name_font;
MMBNFont* GameSystem::m_battle_chip_power_font;
MMBNFont* GameSystem::m_battle_chip_letter_font;
MMBNFont* GameSystem::m_battle_enemy_name_font;
MMBNFont* GameSystem::m_enemy_life_font;
MMBNFont* GameSystem::m_custom_window_letter_font;

//others
vector<AnimationPtr> GameSystem::LOADING_ANIMATIONS;

vector<string> 					GameSystem::ACTORS_NAMES	;
vector<pair<string,string> > 	GameSystem::BGM_NAMES		;
vector<pair<string,string> > 	GameSystem::BACKGROUNDS_NAMES;

void GameSystem::Initialize()
{

	//ELEMENTS
	ELEMENT_STRING_MAP["fire"]		= GameSystem::FIRE_ELEMENT		;
	ELEMENT_STRING_MAP["water"]		= GameSystem::WATER_ELEMENT		;
	ELEMENT_STRING_MAP["thunder"]	= GameSystem::THUNDER_ELEMENT	;
	ELEMENT_STRING_MAP["grass"]		= GameSystem::GRASS_ELEMENT		;
	ELEMENT_STRING_MAP["heal"]		= GameSystem::HEAL_ELEMENT		;
	ELEMENT_STRING_MAP["sword"]		= GameSystem::SWORD_ELEMENT		;
	ELEMENT_STRING_MAP["none"]		= GameSystem::NONE_ELEMENT		;

	//DAMAGE
	DAMAGE_STRING_MAP["fixed"]		= GameSystem::FIXED_DAMAGE		;
	DAMAGE_STRING_MAP["current_hp"]	= GameSystem::CURRENT_HP_DAMAGE	;
	DAMAGE_STRING_MAP["diff_hp"]	= GameSystem::DIFF_HP_DAMAGE	;
	DAMAGE_STRING_MAP["max_hp"]		= GameSystem::MAX_HP_DAMAGE		;
	DAMAGE_STRING_MAP["heal"]		= GameSystem::HEAL_DAMAGE		;
	DAMAGE_STRING_MAP["none"]		= GameSystem::NONE_DAMAGE		;

	//TARGET
	TARGET_STRING_MAP["user"]		= GameSystem::USER_TARGET		;
	TARGET_STRING_MAP["enemy"]		= GameSystem::ENEMY_TARGET		;
	TARGET_STRING_MAP["user_area"]	= GameSystem::USER_AREA_TARGET	;
	TARGET_STRING_MAP["enemy_area"]	= GameSystem::ENEMY_AREA_TARGET	;
	TARGET_STRING_MAP["none"]		= GameSystem::NONE_TARGET		;

	//TYPE
	CHIPTYPE_STRING_MAP["normal"]	= GameSystem::NORMAL_CHIP		;
	CHIPTYPE_STRING_MAP["mega"]		= GameSystem::MEGA_CHIP			;
	CHIPTYPE_STRING_MAP["giga"]		= GameSystem::GIGA_CHIP			;
	CHIPTYPE_STRING_MAP["dark"]		= GameSystem::DARK_CHIP			;
	
	
	
	
	//PANEL TEAMS
	PANELTEAM_STRING_MAP["player"]	= GameSystem::PLAYER			;
	PANELTEAM_STRING_MAP["enemy"]	= GameSystem::ENEMY				;
	
	//PROJECTILES MOVING TYPE
	PROJECTILE_MOVING_MAP["straight"] 		= GameSystem::STRAIGHT_PROJECTILE_MOVING_TYPE				;
	PROJECTILE_MOVING_MAP["follow_actor"] 	= GameSystem::FOLLOW_ACTOR_PROJECTILE_MOVING_TYPE			;
	PROJECTILE_MOVING_MAP["follow_enemy"] 	= GameSystem::FOLLOW_ENEMY_PROJECTILE_MOVING_TYPE			;
	PROJECTILE_MOVING_MAP["none"] 			= GameSystem::NONE_PROJECTILE_MOVING_TYPE					;
	
	//PROJECTILES POSITION TYPE
	//PROJECTILE_POSITION_MAP["relative_to_owner"] 			= GameSystem::RELATIVE_TO_OWNER_PROJECTILE_POSITION_TYPE			;
	//PROJECTILE_POSITION_MAP["relative_to_closest_enemy"] 	= GameSystem::RELATIVE_TO_CLOSEST_ENEMY_PROJECTILE_POSITION_TYPE	;
	//PROJECTILE_POSITION_MAP["relative_to_farest_enemy"] 	= GameSystem::RELATIVE_TO_FAREST_ENEMY_PROJECTILE_POSITION_TYPE		;
	
	//========================
	// PICTURES
	//========================
	//CONTROLLER
	m_controller_pics[TRIANGLE]	= ImgManager::GetImage("System/Menus/triangle.png")						;
	m_controller_pics[SQUARE]	= ImgManager::GetImage("System/Menus/square.png")						;
	m_controller_pics[CIRCLE]	= ImgManager::GetImage("System/Menus/circle.png")						;
	m_controller_pics[CROSS]	= ImgManager::GetImage("System/Menus/cross.png")						;
	m_controller_pics[L_TRIGGER]= ImgManager::GetImage("System/Menus/L.png")							;
	m_controller_pics[R_TRIGGER]= ImgManager::GetImage("System/Menus/R.png")							;
	
	//CHIPS
	m_chip_pics[NORMAL_CHIP]	= ImgManager::GetImage("System/Chips/CustomWindow/normal.png")			;
	m_chip_pics[MEGA_CHIP]		= ImgManager::GetImage("System/Chips/CustomWindow/mega.png")			;
	m_chip_pics[GIGA_CHIP]		= ImgManager::GetImage("System/Chips/CustomWindow/giga.png")			;
	m_chip_pics[DARK_CHIP]		= ImgManager::GetImage("System/Chips/CustomWindow/dark.png")			;
	
	//========================
	// ANIMATIONS
	//========================
	//LOADING ANIMATIONS
	{
		ifstream in( "System/Animation/Loading/animations.txt" , ifstream::in);
		
		if(!in.good())
		{
			LOG("Impossible de trouver le fichier System/Animation/Loading/animations.txt");
			oslQuit();
		}
		
		string line;
		while(getline(in, line))
		{
			vector<string> v = StringUtils::Split(line, ":");
			LOADING_ANIMATIONS.push_back(Animation::Load(string("System/Animation/Loading/") + v[0]));
		}
		
		in.close();
	}
	//========================
	// GAME DATA
	//========================
	//ACTORS NAMES
	{
		ifstream in( "Actors/actors.txt" , ifstream::in);
		
		if(!in.good())
		{
			LOG("Impossible de trouver le fichier Actors/actors.txt");
			oslQuit();
		}
		
		string line;
		while(getline(in, line))
		{
			vector<string> v = StringUtils::Split(line, ":");
			ACTORS_NAMES.push_back(v[0]);
		}
		
		in.close();
	}
	
	//BGM NAMES
	{
		ifstream in( "Audio/BGM/bgm.txt" , ifstream::in);
		
		if(!in.good())
		{
			LOG("Impossible de trouver le fichier Audio/BGM/bgm.txt");
			oslQuit();
		}
		
		string line;
		while(getline(in, line))
		{
			vector<string> v = StringUtils::Split(line, ":");
			vector<string> w = StringUtils::Split(v[0], "|");
			BGM_NAMES.push_back(pair<string,string>(w[0], w[1]));
		}
		
		in.close();
	}
	
	//BACKGROUNDS NAMES
	{
		ifstream in( "Backgrounds/backgrounds.txt" , ifstream::in);
		
		if(!in.good())
		{
			LOG("Impossible de trouver le fichier Backgrounds/backgrounds.txt");
			oslQuit();
		}
		
		string line;
		while(getline(in, line))
		{
			vector<string> v = StringUtils::Split(line, ":");
			vector<string> w = StringUtils::Split(v[0], "|");
			BACKGROUNDS_NAMES.push_back(pair<string,string>(w[0], w[1]));
		}
		
		in.close();
	}
}

void GameSystem::Destroy()
{
	
}

GameSystem::ChipElement GameSystem::GetElementOfString(string e)
{
	return ELEMENT_STRING_MAP[e];
}

GameSystem::DamageType 	GameSystem::GetDamageOfString(string d)
{
	return DAMAGE_STRING_MAP[d];
}

GameSystem::TargetType 	GameSystem::GetTargetOfString(string t)
{
	return TARGET_STRING_MAP[t];
}

GameSystem::ChipType 	GameSystem::GetChipTypeOfString(string c)
{
	return CHIPTYPE_STRING_MAP[c];
}


GameSystem::PanelTeam 	GameSystem::GetPanelTeamOfString(string p)
{
	return PANELTEAM_STRING_MAP[p];
}

GameSystem::ProjectileMovingType GameSystem::GetProjectileMovingOfString(string p)
{
	return PROJECTILE_MOVING_MAP[p];
}

GameSystem::ProjectilePositionType GameSystem::GetProjectilePositionOfString(string p)
{
	if(p == "relative_to_owner")
		return GameSystem::RELATIVE_TO_OWNER_PROJECTILE_POSITION_TYPE;
	if(p == "relative_to_closest_enemy")
		return GameSystem::RELATIVE_TO_CLOSEST_ENEMY_PROJECTILE_POSITION_TYPE;
	if(p == "relative_to_farest_enemy")
		return GameSystem::RELATIVE_TO_FAREST_ENEMY_PROJECTILE_POSITION_TYPE;
		
	return GameSystem::RELATIVE_TO_OWNER_PROJECTILE_POSITION_TYPE;
}

/*void GameSystem::InitAttackInfo(std::string file, AttackInfo* ai)
{
	#ifdef _DEBUG
		LOG("Init attack info from file " + file)
	#endif
	
	ifstream in_info( file.c_str() , ifstream::in);

	if(!in_info.good())
	{
		LOG("Impossible de trouver le fichier " + file)
		oslQuit();
	}
	
	string line;
	while(getline(in_info, line))
	{
		//target type
		if(line.find("target_type") == 0)
		{	
			vector<string> v = StringUtils::Split(line, " \r\n");
			ai->target_type = TARGET_STRING_MAP[v.at(1)];
			#ifdef _DEBUG
				LOG("target type " + v.at(1))
			#endif
			
		}
		//range
		else if(line.find("range") == 0)
		{	
			vector<string> v = StringUtils::Split(line, " \r\n");
			for(unsigned int i = 1 ; i < v.size() ; ++i)
			{
				vector<string> r = StringUtils::Split(v[i], ",");
				istringstream iss(r.at(0) + " " + r.at(1));
				int x_range;
				int y_range;
				iss >> x_range;
				iss >> y_range;
				ai->range.push_back(Vector2i(x_range,y_range));
				#ifdef _DEBUG
					LOG("range " + r.at(0) + " " + r.at(1))
				#endif
			}
			
		}
		//target teams
		else if(line.find("target_teams") == 0)
		{	
			vector<string> v = StringUtils::Split(line, " \r\n");
			for(unsigned int i = 1 ; i < v.size() ; ++i)
			{
				ai->target_teams.push_back(PANELTEAM_STRING_MAP[v.at(i)]);
				#ifdef _DEBUG
					LOG("target teams " + v.at(i))
				#endif
			}
			
		}
		//piercing attack
		else if(line.find("pierce") == 0)
		{
			vector<string> v = StringUtils::Split(line, " \r\n");
			if(v.at(1).compare("true") == 0)
				ai->pierce_attack = true;
			else
				ai->pierce_attack = false;
				
			#ifdef _DEBUG
				LOG("pierce " + v.at(1))
			#endif
		}
		//stagger enemy
		else if(line.find("stagger") == 0)
		{
			vector<string> v = StringUtils::Split(line, " \r\n");
			if(v.at(1).compare("true") == 0)
				ai->stagger_enemy = true;
			else
				ai->stagger_enemy = false;
				
			#ifdef _DEBUG
				LOG("stagger" + v.at(1))
			#endif
		}
		//frames
		else if(line.find("hit_frames") == 0)
		{
			vector<string> v = StringUtils::Split(line, " \r\n");
			for(unsigned int i = 1 ; i < v.size() ; ++i)
			{
				istringstream iss(v.at(i));
				unsigned int frame;
				iss >> frame;
				ai->hit_frames.push_back(frame);
				
				#ifdef _DEBUG
					LOG("hit frame " + v.at(i))
				#endif
			}
			
		}
	}

	in_info.close();
}

void GameSystem::InitBattleAttack(string file, BattleAttack* ba)
{
	ifstream in_info( file.c_str() , ifstream::in);

	if(!in_info.good())
	{
		LOG("Impossible de trouver le fichier " + file);
		oslQuit();
	}

	string line;
	while(getline(in_info, line))
	{
		//name
		if(line.find("name") == 0)
		{	
			vector<string> v = StringUtils::Split(line, " \r\n");
			ba->name = v.at(1);
			
		}
		//power
		if(line.find("power") == 0)
		{	
			vector<string> v = StringUtils::Split(line, " \r\n");
			istringstream iss(v.at(1));
			iss >> ba->power;
			
		}
		
		//use projectile
		else if(line.find("use_projectile") == 0)
		{
			vector<string> v = StringUtils::Split(line, " \r\n");
			if(v.at(1).compare("true") == 0)
				ba->use_projectile = true;
			else
				ba->use_projectile = false;
		}
		
		//projectiles number
		if(line.find("projectiles_number") == 0)
		{	
			vector<string> v = StringUtils::Split(line, " \r\n");
			istringstream iss(v.at(1));
			iss >> ba->projectiles_number;
			
		}
		//animation name
		if(line.find("animation") == 0)
		{	
			vector<string> v = StringUtils::Split(line, " \r\n");
			//ba->actor_animation_name = string("Battle/Animations/Attacks/") + v.at(1);
			ba->actor_animation = Animation::Load( string("Battle/Animations/Attacks/") + v.at(1), false, false );
		}
	}

	in_info.close();
}
*/




OSL_IMAGE* GameSystem::GetControllerImage(GameController controller)
{
	return m_controller_pics[controller];
}

OSL_IMAGE* GameSystem::GetChipImage(ChipType type)
{
	return m_chip_pics[type];
}

OSL_IMAGE* GameSystem::GetElementImage(ChipElement element)
{
	return m_element_pics[element];
}

MMBNFont* GameSystem::GetBattleFont()
{
	return FontManager::GetFont("MMBNBattleFont");
}

MMBNFont* GameSystem::GetActorLifeFont()
{
	return FontManager::GetFont("MMBNActorLifeFont");
}

MMBNFont* GameSystem::GetBattleChipNameFont()
{
	return FontManager::GetFont("MMBNBattleFont");
}

MMBNFont* GameSystem::GetBattleChipPowerFont()
{
	return FontManager::GetFont("MMBNBattleChipPowerFont");
}

MMBNFont* GameSystem::GetBattleChipLetterFont()
{
	return FontManager::GetFont("MMBNBattleChipLetterFont");
}

MMBNFont* GameSystem::GetBattleChipNormalDescFont()
{
	return FontManager::GetFont("MMBNBattleChipNormalDescFont");
}

MMBNFont* GameSystem::GetBattleEnemyNameFont()
{
	return FontManager::GetFont("MMBNBattleFont");
}

MMBNFont* GameSystem::GetEnemyLifeFont()
{
	return FontManager::GetFont("MMBNEnemyLifeFont");
}

MMBNFont* GameSystem::GetCustomWindowLetterFont()
{
	return FontManager::GetFont("MMBNCustomWindowLetterFont");
}
		
		
AnimationPtr GameSystem::GetLoadingAnimation()
{
	return LOADING_ANIMATIONS[Random::RandomInt(0, LOADING_ANIMATIONS.size())];
}




vector<string>& GameSystem::GetActorsNames()
{
	return ACTORS_NAMES;
}

vector<pair<string,string> >& GameSystem::GetBGMNames()
{
	return BGM_NAMES;
}

vector<pair<string,string> >& GameSystem::GetBackgroundsNames()
{
	return BACKGROUNDS_NAMES;
}