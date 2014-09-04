#include "Minion.h"
#include "MinionStats.h"

using namespace std;

Minion::Minion(Map* map, uint32 id, MinionSpawnType type, MinionSpawnPosition position, const vector<MovementVector>& constWaypoints) : Unit(map, id, "", new MinionStats(), 40, 0, 0, new MinionAI(this)), type(type), position(position), constWaypoints(constWaypoints), curConstWaypoint(0) {
   switch(position) {
   case SPAWN_BLUE_TOP:
      setSide(0);
      setPosition(907, 1715);
      break;
   case SPAWN_BLUE_BOT:
      setSide(0);
      setPosition(1533, 1321);
      break;
   case SPAWN_BLUE_MID:
      setSide(0);
      setPosition(1443, 1663);
      break;
   case SPAWN_RED_TOP:
      setSide(1);
      setPosition(14455, 13159);
      break;
   case SPAWN_RED_BOT:
      setSide(1);
      setPosition(12967, 12695);
      break;
   case SPAWN_RED_MID:
      setSide(1);
      setPosition(12433, 12623);
      break;
   }
   
   // TODO : make these data dynamic with the game elapsed time
   switch(type) {
   case MINION_TYPE_MELEE:
      stats->setCurrentHealth(475.0f);
      stats->setMaxHealth(475.0f);
      stats->setBaseAd(12.0f);
      break;
   case MINION_TYPE_CASTER:
      stats->setCurrentHealth(279.0f);
      stats->setMaxHealth(279.0f);
      stats->setBaseAd(23.0f);
      break;
   case MINION_TYPE_CANNON:
      stats->setCurrentHealth(600.0f);
      stats->setMaxHealth(600.0f);
      stats->setBaseAd(40.0f);
      break;
   }
   
   std::string minionModel;
   if (position == SPAWN_BLUE_TOP ||
       position == SPAWN_BLUE_MID ||
       position == SPAWN_BLUE_BOT) {
       minionModel += "Blue_Minion_";
   } else {
       minionModel += "Red_Minion_";
   }
   
   if (type == MINION_TYPE_MELEE) {
       minionModel += "Basic";
   } else if (type == MINION_TYPE_CASTER) {
       minionModel += "Wizard"; 
   } else {
       minionModel += "MechCannon";
   }
   
   setModel(minionModel);
   
   stats->setMovementSpeed(325.f);
   stats->setBaseAttackSpeed(0.625f);
   stats->setAttackSpeedMultiplier(1.0f);
   
   vector<MovementVector> newWaypoints = { MovementVector(MovementVector::targetXToNormalFormat(x), MovementVector::targetYToNormalFormat(y)), MovementVector(MovementVector::targetXToNormalFormat(x), MovementVector::targetYToNormalFormat(y)) };
   setWaypoints(newWaypoints);
}

void Minion::update(int64 diff) {
   Unit::update(diff);
   
   if(unitTarget) {
      return;
   }
   
   // Minion reached its temporary destination
   if(curWaypoint == 2 && ++curConstWaypoint < constWaypoints.size()) {
      printf("Minion reached ! Going to %d;%d\n", constWaypoints[curConstWaypoint].x, constWaypoints[curConstWaypoint].y);
      vector<MovementVector> newWaypoints = { MovementVector(MovementVector::targetXToNormalFormat(x), MovementVector::targetYToNormalFormat(y)), MovementVector(constWaypoints[curConstWaypoint].x, constWaypoints[curConstWaypoint].y) };
      setWaypoints(newWaypoints);
   }
}