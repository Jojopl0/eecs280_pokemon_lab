#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string>

#include "Pokemon.hpp"
#include "Trainer.hpp"

using namespace std;

class League {
private:  
int num_wins = 0;
int num_gym_leaders;
string ignore;
vector<Trainer*> defeated;
vector<Trainer*> gym_leaders;



public:

  // TODO: Add constructor here to initialize members
  League(ifstream &in) {
    in >> num_gym_leaders;
    in >> ignore;
    for(int i = 0; i < num_gym_leaders; ++i) {
      gym_leaders.push_back(Trainer_factory(in));
    }

  }



  // TODO: Add member functions here
  void faceOff(Trainer* player) {
    for(int i = 0; i < gym_leaders.size(); ++i) {
    player->reset();
    Trainer *current_gym_leader = gym_leaders[i];

    cout << "-----" << *player << " vs. " << *current_gym_leader << "-----" << endl;

    // Team battle against that gym leader
    for(int i = 0; i < 5; ++i) {

      // Each individual pokemon battle
      Pokemon enemy = current_gym_leader->choose_pokemon();
      cout << *current_gym_leader << " chooses " << enemy << endl;
      Pokemon p = player->choose_pokemon(enemy.get_type());
      cout << *player << " chooses " << p << endl;
      if (Pokemon_battle(p, enemy)) {
        cout << p << " defeats " << enemy << endl << endl;
        ++num_wins;
      }   else {
        cout << enemy << " defeats " << p << endl << endl;
      }

    }

    cout << "Result: " << *player << "=" << num_wins << ", "
         << *current_gym_leader << "=" << 5 - num_wins << endl;

    if (num_wins >= 3) {
      defeated.push_back(current_gym_leader);
    }

    if (num_wins == 0 || num_wins == 5) {
      cout << "It's a clean sweep!" << endl;
    }

    cout << endl;
    }


  }

  void talmBoutWins(Trainer* player) {
    cout << *player << " won " << defeated.size() << " matches by defeating:" << endl;
    for(int i = 0; i < defeated.size(); ++i) {
      cout << *defeated[i] << endl;
    }
  }
  


  ~League() {
    // TODO: put code here to clean up by deleting all Trainer objects
    for(size_t i = 0; i < gym_leaders.size(); ++i) {
      delete gym_leaders[i];
    }
  }
};

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cout << "Usage: battle.exe PLAYER_FILE GYM_LEADERS_FILE" << endl;
    return 1;
  }
  // TODO: Add code to read command line args and open file streams here
  string player_in_name = argv[1];
  string gym_leaders_in_name = argv[2];

  ifstream player_in(player_in_name);
  if ( !player_in.is_open() ) {
    cout << "Unable to open " << player_in_name << endl;
    return 1;
  }
  ifstream gym_in(gym_leaders_in_name);
  if ( !gym_in.is_open() ) {
    cout << "Unable to open " << gym_leaders_in_name << endl;
    return 1;
  }

  //initializes player
   Trainer *player = Trainer_factory(player_in);

  League l1(gym_in);
  l1.faceOff(player);
  l1.talmBoutWins(player);







  // TODO: Create a League object, call function to run the simulation
  
  delete player;
}