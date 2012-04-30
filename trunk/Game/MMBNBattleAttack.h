#ifndef MMBN_ATTACKINFO_H
#define MMBN_ATTACKINFO_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include <boost/shared_ptr.hpp>

#include "Animation.hpp"
#include "GameSystem.h"
#include "Displayable.h"

class MMBNBattleActor;

class AttackInfo
{
	private:
		GameSystem::TargetType target_type;
		std::vector<Vector2i> range;
		std::vector<GameSystem::PanelTeam> target_teams;
		bool pierce_attack;
		bool stagger_enemy;
		std::vector<int> hit_frames;

		
	public:
		AttackInfo();
		AttackInfo(std::string file);
		~AttackInfo();
		
		void SetTargetType(GameSystem::TargetType target);
		void SetRange(std::vector<Vector2i> range);
		void SetTeams(std::vector<GameSystem::PanelTeam> teams);
		void SetPierceAttack(bool pierce);
		void SetStaggerEnemy(bool stagger);
		void SetHitFrames(std::vector<int> frames);
		
		GameSystem::TargetType GetTargetType() const;
		const std::vector<Vector2i>& GetRange() const;
		const std::vector<GameSystem::PanelTeam>& GetTeams() const;
		bool IsPierceAttack();
		bool IsStaggerAttack();
		const std::vector<int>& GetHitFrames() const;
		
		std::string ToString();
};

typedef boost::shared_ptr<AttackInfo> AttackInfoPtr				;

class BattleProjectile;
typedef boost::shared_ptr<BattleProjectile> BattleProjectilePtr				;

class BattleProjectile : public Displayable
{
	
	
	private:
		std::string name;
		AnimationPtr animation;
		bool reverse;
		unsigned int velocity;
		GameSystem::ProjectileMovingType moving_type;
		std::vector<unsigned int> hitting_frames;
		unsigned int trigger;
		unsigned int damage;
		MMBNBattleActor* owner;
		
		BattleProjectile();
		BattleProjectile(const std::string& name, const std::string& anim, bool reverse, unsigned int velocity, GameSystem::ProjectileMovingType mt, const std::vector<unsigned int>& hit_frames, unsigned int trigger, unsigned int damage, MMBNBattleActor* owner);
		
	public:
		
		~BattleProjectile();
		static BattleProjectilePtr Load(unsigned int proj_nb, const std::string& file, bool reverse, MMBNBattleActor* owner);
		
		const std::string& GetName() const;
		AnimationPtr GetAnimation() const;
		const unsigned int GetVelocity() const;
		const GameSystem::ProjectileMovingType& GetMovingType() const;
		const std::vector<unsigned int> GetHitFrames() const;
		const unsigned int GetDamage() const;
		const unsigned int GetTrigger() const;
		const MMBNBattleActor* GetOwner() const;
		
		void Display(float offX = 0, float offY = 0)		;
		void Move(float x, float y)							;
		void SetPosition(float x, float y)					;
		const Vector2f& GetPosition() const					;
};

class MMBNBattleAttack
{
	private:
		std::string name;
		unsigned int power;
		AttackInfoPtr attack_info;
		bool use_projectile;
		unsigned int projectiles_number;
		std::map<unsigned int, std::vector<BattleProjectilePtr> > projectiles_map;
		//std::string actor_animation_name;
		AnimationPtr actor_animation;
		
	public:
		MMBNBattleAttack();
		MMBNBattleAttack(const std::string& path, const std::string& file, bool reverse);
		~MMBNBattleAttack();
		
		const std::string GetName() const;
		const unsigned int GetPower() const;
		const AttackInfoPtr& GetAttackInfo() const;
		const bool UseProjectile() const;
		const unsigned int GetProjectilesNumber() const;
		const std::map<unsigned int, std::vector<BattleProjectilePtr> > GetProjectilesMap() const;
		AnimationPtr GetAnimation() const;
		
		const std::string ToString() const;
};

typedef boost::shared_ptr<MMBNBattleAttack> MMBNBattleAttackPtr		;

#endif
