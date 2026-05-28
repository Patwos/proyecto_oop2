#include "warrior.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

// Constructor por defecto
Warrior::Warrior() : CombatUnit("Warrior", 150, 30, 5){
    this->strength = 5;
}

// Constructor con parámetros
Warrior::Warrior(string type, int life, int attackpts, int level, int strength) : CombatUnit(type, life, attackpts, level){
    this->strength = strength;
}

int Warrior::get_strength(){
    return this->strength;
}

void Warrior::set_strength(int strength){
    this->strength = strength;
}

void Warrior::attack(CombatUnit &target){
    int damage = 0; 
    int halfattack = this->get_attackpts() / 2; 

    if (target.get_level() > this->get_level()) {
        damage = rand() % halfattack + 1;
    } else {
        damage = rand() % (this->get_attackpts() - halfattack + 1) + halfattack; 
    }

    int finalDamage = damage + this->strength;

    cout << "Damage base: " << damage << " + Force: " << this->strength << " = Final damage: " << finalDamage << endl;
    target.receiveAttack(finalDamage);
}

void Warrior::revive(){
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

    // for the warrior, they could revive by using their strength to survive a fatal attack.
    if (get_health() <= 0 && strength >= 20) { // if the warrior has at least 20 strength, they can revive
        set_health(get_life() / 2); // restore half of the life points
        strength -= 20; // reduce strength by 20
        cout << type << " revived using strength! Current health: " << get_health() << ", Remaining strength: " << strength << endl;
    } else if (get_health() <= 0) {
        set_health(0);
        cout << type << " has died." << endl;
    }
    
}

void Warrior::receiveAttack(int attackPoints){
    int mitigatedDamage = attackPoints - this->strength;

    if (mitigatedDamage < 0) {
        mitigatedDamage = 0;
    }

    cout << "The " << this->type << " blocked " << this->strength << " of damage thanks to their strength. Actual damage received: " << mitigatedDamage << endl;

    this->set_health(this->get_health() - mitigatedDamage);
    if (this->get_health() < 0) {
        this->set_health(0);
    }
} 

void Warrior::print(){ // <--- AHORA SÍ ESTÁ FUERA
    cout << "Unit: " << type << " | Level: " << get_level() << endl;
    cout << "Life: " << get_health() << "/" << get_life() << " ";
    printHealthBar();
    cout << "Strength (Defense/Attack Enhancer): " << strength << endl << endl;
} 