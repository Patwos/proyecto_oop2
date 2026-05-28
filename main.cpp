#include "CombatUnit.h"
#include "Archer.h"
#include "Mage.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    srand(time(NULL));

    // CombatUnit hero("Knight", 100, 30, 5);
    // CombatUnit villain("Wizard", 100, 20, 3);

    // cout << "Fight Start" << endl;
    // hero.print();
    // villain.print();

    // cout << "The " << hero.type << " attacks " << villain.type << "!" << endl;
    // hero.attack(villain);

    // // 4. Mostrar resultado
    // villain.print();

    // testing the archer class
    // Archer archer1("Archer", 80, 25, 4, 30.0, 20);
    // CombatUnit enemy("Enemy", 100, 20, 3);

    // cout << "Fight Start" << endl;
    // archer1.print();
    // enemy.print();

    // cout << "The " << archer1.type << " attacks " << enemy.type << "!" << endl;
    // archer1.attack(enemy);

    // enemy.print();

    // cout << "The " << enemy.type << " attacks " << archer1.type << "!" << endl;
    // enemy.attack(archer1);

    // archer1.print();

    // // testing the archer's dodge ability
    // archer1.setAgility(100); // set agility to 100% for testing
    // cout << "The " << enemy.type << " attacks " << archer1.type << "!" << endl;
    // enemy.attack(archer1); // should always dodge

    // archer1.print();

    //testing the mage and archer together
    Archer archer1("Archer", 80, 25, 4, 30.0, 20);
    Mage mage1("Mage", 70, 30, 5, 50);
    cout << "Fight Start" << endl;
    archer1.print();
    mage1.print();

    cout << "The " << archer1.type << " attacks " << mage1.type << "!" << endl;
    archer1.attack(mage1);

    mage1.print();
    cout << "The " << mage1.type << " attacks " << archer1.type << "!" << endl;
    mage1.attack(archer1);
    archer1.print();

    

    return 0;

}