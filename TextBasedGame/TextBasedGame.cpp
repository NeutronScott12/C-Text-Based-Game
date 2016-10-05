// TextBasedGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <random>
#include <chrono>
#include <thread>

class GameLogic {
	
	public:
		int RandomEnemyGenerator() {
			std::mt19937 rng;
			rng.seed(std::random_device()());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1); // distribution in range [1, 6]

			return dist6(rng);
		}
		int RandomItemDrop() {
			std::mt19937 rng;
			rng.seed(std::random_device()());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 2); // distribution in range [1, 6]

			return dist6(rng);
		}
		int FleeDamage() {
			std::mt19937 rng;
			rng.seed(std::random_device()());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 4); 

			return dist6(rng);
		}
		int MonsterAttack() {
			std::mt19937 rng;
			rng.seed(std::random_device()());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 4); 

			return dist6(rng);
		}
};

class BaseEnemy {
	private:
		int health = 100;
		int score = 0;

	public:
		BaseEnemy() {

		}
		~BaseEnemy() {

		}
		int EnemyHealth() {
			return health;
		}
		int damageTaken(int a) {
			return health -= a;
		}
		int damageCaused(int a) {
			return a;
		}
		int currentHealth() {
			return health;
		}
		//static void score() {
			//score++;
		//}
};

class Player {
	private:
		int health = 100;
		int healthPortion = 3;
		int mana = 100;
		int manaPortion = 3;
		int money;
		int baseDamage = 20;

	public:
		Player() {

		}

		int playerHealth() {
			return health;
		}
		void playerHealth(int a) {
			health = a;
		}
		void heal(int a) {
			health += a;
		}
		int hardDamage() {
			health -= 20;
			return health;
		}
		int MediumDamage() {
			health -= 10;
			return health;
		}
		int SmallDamage() {
			health -= 5;
			return health;
		}
		void addHealthPortion() {
			healthPortion += 1;
		}
		void UseHealthPortion() {
			healthPortion -= 1;
		}
		int currentHealthPortions(){
			return healthPortion;
		}
		int currentHealth() {
			return health;
		}
		int WeaponAttack() {
			return baseDamage;
		}
		void playerMana(int a) {
			mana = a;
		}
		void addManaPortion() {
			manaPortion += 1;
		}
		void useManaPortion() {
			manaPortion -= 1;
		}
		int currentManaPortion() {
			return manaPortion;
		}
		int ManaAttack(int a) {
			return mana -= a;
		}
		int ManaHeal(int a) {
			return mana += a;
		}
		int playerMana() {
			return mana;
		}
		int currentMana() {
			return mana;
		}
};

class Game {
	private:
		bool GameOver = false;
		bool runGame = true;
		bool startGame = false;
		std::string anything;
		std::string response;
		std::string anwser;
		std::string action;
		Player player;
		GameLogic logic;
		BaseEnemy enemy;
		int playerBaseWeaponAttack = player.WeaponAttack();
		int monsterHealth = enemy.currentHealth();
		//int rand = rand() % 1 + 1;

	public:

	Game() {

	}

	void run() {

	reset:
		while (runGame) {

			std::cout << "**************************************" << std::endl;
			std::cout << "*      " << "Welcome to the Dungeon" << "       *" << std::endl;
			std::cout << "**************************************" << std::endl;

			std::cout << "Game is running \n" << std::endl;
			std::cout << "1)Play Game" << std::endl;
			std::cout << "2)Exit Game" << std::endl;

			std::getline(std::cin, response);

			if (response == "1") {
				startGame = true;
				goto start;
			}
			else if (response == "2") {
				system("EXIT");
			}
			else {
				system("CLS");
				goto reset;
			}
		}

	start:
		if (startGame == true) {
			system("CLS");
			do {
				std::cout << "Dungeon, here are some options\n" << std::endl;
				restart:
				std::cout << "Current Health: " << player.currentHealth() << std::endl;
				std::cout << "Current Mana " << player.currentMana() << "\n" << std::endl;
				std::cout << "1)Leave" << std::endl;
				std::cout << "2)Go further" << std::endl;

				std::getline(std::cin, anwser);

				if (anwser == "2") {
					int random = logic.RandomEnemyGenerator();
					if (random == 1) {
						system("CLS");
						std::cout << "Monster Appears, what is your response\n" << std::endl;
						std::cout << "1)Run Away, 'Chance of getting hurt'" << std::endl;
						std::cout << "2)Attack with weapon" << std::endl;
						std::cout << "3)Attack with spell" << std::endl;

						BaseEnemy Goblin;

						std::getline(std::cin, action);

						if (action == "1") {
							std::cout << "You try to run away" << std::endl;
							std::cout << "Press any key to see if you escaped without getting hurt" << std::endl;
							std::getline(std::cin, anything);

							int fleedamage = logic.FleeDamage();
							if (fleedamage == 1) {
								std::cout << "The monster hits your hard" << std::endl;
								
								std::cout << "Press any key to continue your journey" << std::endl;
								std::getline(std::cin, anything);
								goto restart;
							}
							else if (fleedamage == 2) {
								std::cout << "Medium Damage" << std::endl;
								std::cout << "it reduced your health by: " << player.MediumDamage();
								std::getline(std::cin, anything);

							}
							else if (fleedamage == 3) {
								std::cout << "Low Damage" << std::endl;
								std::cout << "it reduced your health by: " << player.SmallDamage();
								std::getline(std::cin, anything);
							}
							else if (fleedamage == 4) {
								std::cout << "The monster missed you" << std::endl;
								std::cout << "Press any key to continue your journey" << std::endl;
								std::getline(std::cin, anything);
							}
						}
						if (action == "2") {
							system("CLS");
							std::cout << "Player Health: " << player.currentHealth() << "\n" << std::endl;
							std::cout << "Monster Health: " << Goblin.EnemyHealth() << "\n" << std::endl;

							Goblin.damageTaken(playerBaseWeaponAttack);

							std::cout << "You swing your weapon at the monster" << std::endl;
							std::cout << "It inflicts " << player.WeaponAttack() << " damage onto the monster\n" << std::endl;

							std::cout << "Press any key to continue" << std::endl;
							std::getline(std::cin, anything);

							do{
								system("CLS");
								std::cout << "Player Health: " << player.currentHealth() << "\n" << std::endl;
								std::cout << "Monster Health: " << Goblin.currentHealth() << "\n" << std::endl;
								
								if (player.currentHealth() <= 0) {
									std::cout << "Monster defeats you better luck next time" << std::endl;
									std::cout << "Press any key to continue" << std::endl;
									std::getline(std::cin, anything);
									goto gameover;
								}

								if (Goblin.currentHealth() <= 0) {
									std::cout << "Monster has been defeated" << std::endl;
									if (logic.RandomItemDrop() == 0) {
										std::cout << "The monster drops nothing " << std::endl;
										std::cout << "Press any key to continue " << std::endl;
										std::getline(std::cin, anything);
									}
									else if (logic.RandomItemDrop() == 1) {
										std::cout << "The monster drops a health portion" << std::endl;
										std::cout << "Press any key to continue " << std::endl;
										std::getline(std::cin, anything);
									}
									else if (logic.RandomItemDrop() == 2) {
										std::cout << "The monster drops a mana portion " << std::endl;
										std::cout << "Press any key to continue " << std::endl;
										std::getline(std::cin, anything);
									}
									std::cout << "You continue with your journey, press any key to continue" << std::endl;
									std::getline(std::cin, anything);
									break;
								}
								else {
									std::cout << "What is your next move " << std::endl;
									std::cout << "1)Run away " << std::endl;
									std::cout << "2)Attack again" << std::endl;
									std::cout << "3)Take Health Portion " << std::endl;

									std::cout << "Press any key to continue" << std::endl;
									std::getline(std::cin, response);

									if (response == "1") {
										std::cout << "You leave to fight another time" << std::endl;
										std::cout << "Press any key to continue " << std::endl;
										std::getline(std::cin, anything);
										break;
									}

									if (response == "2") {
										std::cout << "You swing again at the monster, doing " << player.WeaponAttack() << " damage" << std::endl;

										Goblin.damageTaken(player.WeaponAttack());
										
										std::cout << "The monsters tries to attack you " << std::endl;
										if (logic.MonsterAttack() == 1) {
											std::cout << "Monster misses you" << std::endl;
										}
										else if (logic.MonsterAttack() == 2) {
											std::cout << "scratches you for " << player.SmallDamage() << std::endl;
											player.SmallDamage();
										}
										else if (logic.MonsterAttack() == 3) {
											std::cout << "cuts you for " << player.MediumDamage() << std::endl;
											player.MediumDamage();
										}
										else if (logic.MonsterAttack() == 4) {
											std::cout << "cuts you deeply for " << player.hardDamage() << std::endl;
											player.hardDamage();
										}
										std::cout << "Press any key to continue " << std::endl;
										std::getline(std::cin, anything);
									}
									if (response == "3") {
										if (player.currentHealth() >= 100) {
											std::cout << "Health already max, no need for a health portion" << std::endl;
											std::cout << "Press any key to continue" << std::endl;
											std::getline(std::cin, anything);
										}
										else if(player.currentHealth() >= 81) {
											std::cout << "Your health has been restored to max" << std::endl;
											std::cout << "Press any key to continue" << std::endl;
											std::getline(std::cin, anything);
											player.playerHealth(100);
										}
										else {
											std::cout << "You drink a health portions which restores " << 20 << std::endl;
											std::cout << "Press any key to continue" << std::endl;
											std::getline(std::cin, anything);
											player.heal(20);
										}
									}
								}
							} while (true);
						}
						if (action == "3") {
							system("CLS");
							std::cout << "Fires spell at monster \n" << std::endl;
							player.useManaPortion();
							Goblin.damageTaken(30);
							player.ManaAttack(30);
		
							do {
								if (Goblin.currentHealth() <= 0) {
									std::cout << "You've defeated the monster" << std::endl;
									std::cout << "Press any key to continue" << std::endl;
									if (logic.RandomItemDrop() == 0) {
										std::cout << "The monster drops nothing" << std::endl;
										std::cout << "Press any key to continue " << std::endl;
										std::getline(std::cin, anything);
									}
									else if (logic.RandomItemDrop() == 1) {
										std::cout << "The monster drops a health portion" << std::endl;
										player.addHealthPortion();
										std::cout << "Press any key to continue " << std::endl;
										std::getline(std::cin, anything);
									}
									else if (logic.RandomItemDrop() == 2) {
										std::cout << "The monster drops a mana portion" << std::endl;
										player.addManaPortion();
										std::cout << "Press any key to continue " << std::endl;
										std::getline(std::cin, anything);
									}
									std::getline(std::cin, anything);
									break;
								}

								if (player.currentHealth() <= 0) {
									std::cout << "Monster defeated you, better luck next time" << std::endl;
									std::cout << "Press any key to continue " << std::endl;
									std::getline(std::cin, anything);
									goto gameover;
								}
								else {
									std::cout << "Player Health " << player.currentHealth() << std::endl;
									std::cout << "Player Mana " << player.currentMana() << std::endl;
									std::cout << "Mana portions " << player.currentManaPortion() << std::endl;
									std::cout << "Health portions " << player.currentHealthPortions() << std::endl;
									std::cout << "Enemy Health " << Goblin.currentHealth() << "\n" << std::endl;

									std::cout << "What is your next move " << std::endl;
									std::cout << "1)Run away" << std::endl;
									std::cout << "2)Attack with spell again" << std::endl;
									std::cout << "3)Take Mana portion" << std::endl;
									std::getline(std::cin, action);
									
									if (action == "1") {
										system("CLS");
										std::cout << "You try to run away" << std::endl;
										std::cout << "Press any key to continue " << std::endl;

										switch (logic.FleeDamage()) {
											case 1:
												std::cout << "The monsters misses you, you get away freely" << std::endl;
												std::cout << "Press any key to continue " << std::endl;
												std::getline(std::cin, anything);
												break;
											case 2:
												std::cout << "The monsters scratches you for " << 5 << std::endl;
												std::cout << "Press any key to continue " << std::endl;
												std::getline(std::cin, anything);
												player.SmallDamage();
												break;
											case 3:
												std::cout << "The monsters cuts you deep for " << 10 << std::endl;
												std::cout << "Press any key to continue " << std::endl;
												std::getline(std::cin, anything);
												player.MediumDamage();
												break;
											case 4:
												std::cout << "The monsters causes heavy bleeding and hurts you for " << 20;
												std::cout << "Press any key to continue " << std::endl;
												std::getline(std::cin, anything);
												player.hardDamage();
												break;
										}
										std::cout << "Press any key to continue" << std::endl;
										std::getline(std::cin, anything);
										break;
									}
									if (action == "2")
									{
										system("CLS");

										if (player.currentMana() <= 0) {
											std::cout << "current Mana pool is too low " << std::endl;
											std::cout << "Press any key to continue " << std::endl;
											std::getline(std::cin, anything);
											break;
										}

										std::cout << "You fire another spell at the monsters " << std::endl;
										player.useManaPortion();
										Goblin.damageTaken(30);
										player.ManaAttack(30);
										std::cout << "The monsters counters attacks " << std::endl;
										
										switch (logic.MonsterAttack()) {
											case 1:
												std::cout << "The monster misses you " << std::endl;
												std::cout << "Press any key to continue " << std::endl;
												std::getline(std::cin, anything);
												break;
											case 2:
												std::cout << "The monster hits you for " << 5 << std::endl;
												std::cout << "Press any key to continue " << std::endl;
												player.SmallDamage();
												std::getline(std::cin, anything);
												break;
											case 3:
												std::cout << "The monster hits you for " << 10 << std::endl;
												std::cout << "Press any key to continue " << std::endl;
												player.MediumDamage();
												std::getline(std::cin, anything);
												break;
											case 4:
												std::cout << "The monster hits you for " << 20 << std::endl;
												std::cout << "Press any key to continue " << std::endl;
												player.hardDamage();
												std::getline(std::cin, anything);
												break;
										}
									}
									if (action == "3") {
										system("CLS");
										if (player.currentManaPortion() == 0) {
											std::cout << "You lack Mana portions " << std::endl;
											std::cout << "Press any key to continue " << std::endl;
											std::getline(std::cin, anything);
										}
										else {
											if (player.currentMana() > 81) {
												std::cout << "Your Mana has been set to max " << std::endl;
												player.playerMana(100);
												player.useManaPortion();
												std::cout << "Press any key to continue " << std::endl;
												std::getline(std::cin, anything);
											}
											else if (player.currentMana() == 100) {
												std::cout << "The mana already at max " << std::endl;
												std::cout << "Press any key to continue " << std::endl;
												std::getline(std::cin, anything);
											}
											else {
												std::cout << "You drink mana portion for " << 20 << std::endl;
												player.ManaHeal(20);
												player.useManaPortion();
												std::cout << "Press any key to continue " << std::endl;
												std::getline(std::cin, anything);
											}
										}		
									}
								}
							} while (true);
						}
					}
					else if (random == 0) {
						again:
						system("CLS");

						std::cout << "Seems Empty, what is your next move\n" << std::endl;

						std::cout << "Current Health " << player.currentHealth() << std::endl;
						std::cout << "Health Portions " << player.currentHealthPortions() << std::endl;
						std::cout << "Mana Portions " << player.currentManaPortion() << std::endl;
						std::cout << "Current Mana " << player.currentMana() << "\n" << std::endl;
						std::cout << "1)Take health portion" << std::endl;
						std::cout << "2)Take Mana portion" << std::endl;
						std::cout << "3)Leave Dungeon" << std::endl;
						std::cout << "4)Continue into the Dungeon\n" << std::endl;

						std::getline(std::cin, action);

						if (action == "1") {
							int PH = player.playerHealth();
							if (PH >= 100) {
								std::cout << "Health already at max, pick another option" << std::endl;
								std::cout << "Press any key to continue, and press enter" << std::endl;
								getline(std::cin, anything);
								goto again;
							}
							else {
								player.heal(20);
								std::cout << "Heatlh has been restored" << std::endl;
								std::cout << "Press any key to continue, and press enter" << std::endl;
								getline(std::cin, anything);
								goto again;
							}
						}
						if (action == "2") {
							system("CLS");
							if (player.currentManaPortion() == 0) {
								std::cout << "You lack Mana portions " << std::endl;
								std::cout << "Press any key to continue " << std::endl;
								std::getline(std::cin, anything);
							}
							else {
								if (player.currentMana() == 100) {
									std::cout << "Mana already at max" << "\n" << std::endl;
									std::cout << "Press any key to continue " << std::endl;
									std::getline(std::cin, anything);
								}
								else if (player.currentMana() >= 81) {
									std::cout << "Your Mana has been set to max " << std::endl;
									player.useManaPortion();
									std::cout << "Press any key to continue " << std::endl;
									std::getline(std::cin, anything);
								}
								else {
									std::cout << "Mana portion has restored " << player.ManaHeal(20);
									player.useManaPortion();
									std::cout << "Press any key to continue " << std::endl;
									std::getline(std::cin, anything);
								}
							}
						}
						if (action == "3") {
							std::cout << "You decide to leave the dungeon " << std::endl;
							std::cout << "press enter to leave" << std::endl;
							std::getline(std::cin, anything);
							goto gameover;
						}
					}
				}
				else if (anwser == "1") {
					break;
				}
				system("CLS");
			} while (true);
			gameover:
			try {
				std::cout << "Thanks for playing" << std::endl;
			}
			catch (const std::exception& e) {
				std::cout << "Error with game ending message:" << e.what() << std::endl;
			}
		}
	}	
};


int main()
{
	
	Game game;

	game.run();

	system("PAUSE");

    return 0;
}

