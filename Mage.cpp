#include "Mage.h"
#include <iostream>
using namespace std;

Mage::Mage(string type, int life, int attackpts, int level, int mana){
    this->type = type;
    this->set_life(life);
    this->set_health(life);
    this->set_attackpts(attackpts);
    this->set_level(level);
    this->mana = mana;
}

int Mage::getMana(){
    return mana;
}

void Mage::setMana(int mana){
    this->mana = mana;
}

void Mage::revive(){
    /*A combatant will not only be considered dead when losing all life points, but this will also depend on the specialization 
    attribute of the derived classes. Therefore, this method will not be implemented in the base class, and being pure virtual, 
    it will make the base class abstract. This method must be implemented in each derived class.

    Add the revive() method to your derived classes. As mentioned above, this method should not depend solely on the current life 
    points, but also on at least one specialized attribute of the object. For example, for a Mage whose attribute is mana: if the 
    Mage loses all health but still has sufficient mana, some life points may be restored and the character will not die. You may 
    display a message such as “The character revived due to mana” and reduce the mana value (so that this ability can only be used 
    once or twice at most). If the Mage does not have sufficient mana, then the health remains at 0 and a message indicating that the
    character has died should be displayed. Update the receiveAttack methods in the derived classes to use revive(). This should 
    be done after updating the health points. By doing so, you will need to override and ensure runtime polymorphic behavior. */

    if (get_health() <= 0 && mana >= 20) { // if the mage has at least 20 mana, they can revive
        set_health(get_life() / 2); // restore half of the life points
        mana -= 20; // reduce mana by 20
        cout << type << " revived using mana! Current health: " << get_health() << ", Remaining mana: " << mana << endl;
    } else if (get_health() <= 0) {
        set_health(0);
        cout << type << " has died." << endl;
    }
}

void Mage::receiveAttack(int attackPoints){
    /* the mage can avoid taking the full damage by using mana to create a shield. the strength of said shield depends on the
    amount of mana the mage has and their level. */
    int shield = (mana * get_level()) / 10; // the shield strengthis calculated as mana multiplied by level divided by 10
    cout << type << " used " << mana << " mana to create a shield with " << shield << " strength!" << endl;
    if (shield >= attackPoints) {
        this->mana -= (attackPoints * 10) / get_level(); // if the shield fully blocks the attack, the mages loses mana intead of health
    } else {
        this->set_health(this->get_health() - (attackPoints - shield)); // mage takes any remaining damage the shield didnt block
    }
    cout << type << " received " << attackPoints << " damage." << endl << endl;

    revive(); // check if the mage can revive after receiving damage
}

void Mage::attack(CombatUnit &target){
    /* the mage can use mana to increase the damage of their attack. the amount of extra damage depends on the amount of mana 
    and the mage's level.*/
    int extradmg = (mana * get_level()) / 10; // the extra damage is calculated as mana multiplied by level divided by 10
    cout << type << " used " << mana << " mana to increase the attack!" << endl;
    cout << "The extra damage is " << extradmg << "." << endl;
    int damage = get_attackpts() + extradmg; // the total damage is the base attack points plus the extra damage from mana
    target.receiveAttack(damage);
    this->mana -= extradmg; // reduce the mage's mana by the amount used for the extra damage
    cout << type << " attacked " << target.type << " for " << damage << " damage." << endl << endl;
}

void Mage::print(){
    cout << "Unit:" << type << endl << "Level: "<<get_level()<<endl;
    cout << "Life: "<< get_health() <<"/"<<get_life()<<" ";
    printHealthBar();
    cout << "Mana: " << mana << endl;
    cout << endl << endl;
}