#ifndef MMBNBATTLEACTOR_H
#define MMBNBATTLEACTOR_H

#include "Displayable.h"
#include "Animation.hpp"
#include "Utils.h"
#include "GameSystem.h"

class MMBNBattleActor : public Displayable
{

	public:

		typedef struct
		{
			unsigned int moving_time;
			unsigned int attack_time;
		} IAConfig;

		typedef struct
		{
			unsigned int attack_frame;
			GameSystem::AttackInfo attack_info;
			
		} BattleActorInfo;
		
		enum ActorDirection
		{
			LEFT,
			RIGHT,
		};

		enum ActorState
		{
			BATTLE_STANDING,
			BATTLE_ATTACK,
			BATTLE_DAMAGED,
			BATTLE_DEAD,
			BATTLE_WIN
		};

		
		static void Initialize();
		
		virtual ~MMBNBattleActor()									;
		
		static MMBNBattleActor* Load(std::string name, bool ia = true, bool loadNormalSprites = true, bool loadReverseSprites = true);
		void Display(float offX = 0, float offY = 0)		;

		void Move(float x, float y)								;
		//===============================
		// SETTERS
		//===============================
		void SetDirection(ActorDirection direction)			;
		void SetState(ActorState state)						;
		void SetPosition(float x, float y)					;

		//===============================
		// GETTERS
		//===============================
		Shape& GetColliShape()								;
		ActorDirection GetDirection() const					;
		ActorState GetState() const							;
		std::string GetName() const							;
		AnimationPtr GetCurrentAnim()						;
		Vector2f& GetPosition()								;
		int GetLV() const									;
		int GetHP() const									;
		int GetMaxHP() const								;
		int GetAtk() const									;
		int GetChrg() const									;
		int GetSpd() const									;

		void Attack(MMBNBattleActor* mmbnba)				;
		bool IsDead()										;

		IAConfig* GetIAConfig()								;
		
		BattleActorInfo* GetInfo()							;

	protected:

		//===============================
		// CONSTRUCTEUR
		//===============================
		MMBNBattleActor()								;
		MMBNBattleActor(std::string, bool loadNormalSprites = true, bool loadReverseSprites = true)					;

		//===============================
		// FONCTIONS PRIVEES
		//===============================
		//void InitDelaysOfAnim(std::string path, std::vector<int> &delays);
		void LoadStateAnim(ActorState state);

		static std::map<ActorState, std::string> 	FOLDER_NAMES_OF_STATES	;
		static std::map<ActorState, bool>			LOOP_OF_STATES			;
		
		void InitializeIA();
		void InitializeInfo();
		
		//===============================
		// ETAT & DIRECTION
		//===============================
		ActorDirection m_direction			;
		ActorState m_state					;

		bool	m_displayLife				;

		//===============================
		// ANIMATIONS
		//===============================
		std::map<ActorState,AnimationPtr> m_animMap	;
		std::map<ActorState,AnimationPtr> m_reversedAnimMap	;
		Vector2f m_position;
		float m_posX;
		float m_posY;
		float m_offX;
		float m_offY;

		//===============================
		// STATISTIQUES
		//===============================
		std::string m_name					;
		int m_lv							;
		int m_hp							;
		int m_maxHp							;
		int m_atk							;
		int m_chrg							;
		int m_spd							;

		IAConfig m_ia_config				;
		
		bool m_load_normal_sprites			;
		bool m_load_reversed_sprites		;
		
		BattleActorInfo m_actor_info		;

};

#endif //MMBNBATTLEACTOR_H