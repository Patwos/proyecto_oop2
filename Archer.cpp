#include "Archer.h"
#include <iostream>
#include <string>

using namespace std;

Archer::Archer(string type, int life, int attackpts, int level, float accuracy, float agility){
    this->type = type;
    this->set_life(life);
    this->set_health(life);
    this->set_attackpts(attackpts);
    this->set_level(level);
    this->accuracy = accuracy;
    this->agility = agility;
}

float Archer::getAccuracy(){
    return accuracy;
}

void Archer::setAccuracy(float accuracy){
    /*accuracy is a number indicating the Archer's accuracy percentage, meaning the probability of landing a critical hit. 
    This attribute can increase the amount of damage dealt to a target.*/
    this->accuracy = accuracy;
}

int Archer::getAgility(){
    return agility;
}

void Archer::setAgility(int agility){
    /*agility is a number indicating the Archer's agility percentage, meaning the probability of dodging an attack. 
    This attribute can decrease the amount of damage received from an attack.*/
    this->agility = agility;
}

void Archer::revive(){
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

    // for the archer, they could revive by using agility to dodge a fatal attack.
    if (get_health() <= 0 && agility >= 50) { // if the archer has at least 50 agility, they can revive
        set_health(get_life() / 2); // restore half of the life points
        agility -= 50; // reduce agility by 50
        cout << type << " revived using agility! Current health: " << get_health() << ", Remaining agility: " << agility << endl;
    } else if (get_health() <= 0) {
        set_health(0);
        cout << type << " has died." << endl;
    }

}

void Archer::receiveAttack(int attackPoints) {
    /* Derived classes must override the print(), receiveAttack(), and attack() methods. Below are some suggestions for how
     the methods might vary for one of the classes (you will need to decide how they will be modified for each derived class).*/

   // The archer could have a chance to dodge an attack based on agility.
   int chance = rand() % 100;
    if (chance < agility) {
        // for example, if the archer has 30 agility, there is a 30% chance to dodge the attack
         cout << type << " dodged the attack!" << endl << endl;
         return;
    } else {
        set_health(get_health() - attackPoints);
        if (get_health() < 0) {
            set_health(0);
        }
        cout << type << " received " << attackPoints << " damage." << endl << endl;
    }

    revive(); // check if the archer can revive after receiving damage

}

void Archer::attack(CombatUnit &target){
    int damage = 0;
    int halfattack = get_attackpts()/2;
    if (target.get_level()>this->get_level()){
        damage = rand() % halfattack + 1;
    }
    else {
        damage = rand() % (this -> get_attackpts() - halfattack +1) + halfattack;
    }

    int chance = rand() % 100;
    if (chance < this->accuracy) {
        damage *= 2; // critical hit doubles the damage
        cout << type << " landed a critical hit!" << endl;
    }

    target.receiveAttack(damage);
    cout << type << " attacked " << target.type << " for " << damage << " damage." << endl << endl;
}

void Archer::print() {
    cout << "Unit: " << type << endl;
    cout << "Level: " << get_level() << endl;
    cout << "Health: " << get_health() << "/" << get_life() << endl;
    printHealthBar();

    // for the archer, we can also display accuracy and agility
    cout << "Accuracy: " << accuracy << "%" << endl;
    cout << "Agility: " << agility << "%" << endl;
    cout << endl << endl;
}