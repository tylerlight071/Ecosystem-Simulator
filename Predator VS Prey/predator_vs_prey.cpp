#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

// Constants for ecosystem parameters
const int INITIAL_RABBITS = 32;
const int INITIAL_FOXES = 17;
const int INITIAL_WOLVES = 6;
const int MAX_RABBITS = 500;
const int MAX_FOXES = 500;
const int MAX_WOLVES = 500;
const double RABBIT_REPRODUCTION_RATE = 0.3;
const double FOX_REPRODUCTION_RATE = 0.1;
const double WOLF_REPRODUCTION_RATE = 0.1;
const double FOX_EATEN_RATE = 0.2;
const double WOLF_EATEN_RATE = 0.2;
const double RABBIT_ENERGY_GAIN = 20.0;
const double FOX_ENERGY_GAIN = 10.0;
const double WOLF_ENERGY_GAIN = 5.0;

// Class representing a Rabbit
class Rabbit {
private:
    double energy;
public:
    Rabbit() : energy(50.0) {} // Initial energy level for rabbits

    double getEnergy() const {
        return energy;
    }

    void decreaseEnergy(double amount) {
        energy -= amount;
    }

    void increaseEnergy(double amount) {
        energy += amount;
    }
};

// Class representing a Fox
class Fox {
private:
    double energy;
public:
    Fox() : energy(100.0) {} // Initial energy level for foxes

    double getEnergy() const {
        return energy;
    }

    void decreaseEnergy(double amount) {
        energy -= amount;
    }

    void increaseEnergy(double amount) {
        energy += amount;
    }
};

// Class representing a Wolf
class Wolf {
private:
    double energy;
public:
    Wolf() : energy(100.0) {} // Initial energy level for wolves

    double getEnergy() const {
        return energy;
    }

    void decreaseEnergy(double amount) {
        energy -= amount;
    }

    void increaseEnergy(double amount) {
        energy += amount;
    }
};

// Function to print ASCII art representing rabbits and foxes
void printPopulation(const vector<Rabbit>& rabbits, const vector<Fox>& foxes, const vector<Wolf>& wolves) {
    cout << "Rabbits: " << rabbits.size() << " ";
    for (int i = 0; i < rabbits.size(); ++i) {
        cout << "(\\_/) ";
    }
    cout << endl;

    cout << "Foxes:   " << foxes.size() << " ";
    for (int i = 0; i < foxes.size(); ++i) {
        cout << "(^_^) ";
    }
    cout << endl;

   cout << "Wolves:  " << wolves.size() << " ";
    for (int i = 0; i < wolves.size(); ++i) {
        cout << "/\\_/\\ ";
    }
    cout << endl;
}

int main() {
    srand(time(NULL));

    vector<Rabbit> rabbits(INITIAL_RABBITS);
    vector<Fox> foxes(INITIAL_FOXES);
    vector<Wolf> wolves(INITIAL_WOLVES);

    cout << "Welcome to the Ecosystem Simulation!" << endl;
    cout << "Press Enter to begin..." << endl;
    cin.get(); // Wait for user to press Enter

    // Simulate ecosystem dynamics for 10 time steps
    for (int i = 0; i < 10; ++i) {
        cout << "\n\n=== Time Step: " << i+1 << " ===" << endl;
        printPopulation(rabbits, foxes, wolves);
        this_thread::sleep_for(chrono::milliseconds(1000)); // Delay for better visualization

        // Reproduction of rabbits
        if (rabbits.size() < MAX_RABBITS) {
            // Calculate the reproduction rate based on avaliable resources
            double reproductionRate = static_cast<double>(MAX_RABBITS -  - rabbits.size()) / MAX_RABBITS;

            int newRabbits = static_cast<int>(rabbits.size() * reproductionRate * RABBIT_REPRODUCTION_RATE);
            if (newRabbits > 0) {
                rabbits.insert(rabbits.end(), newRabbits, Rabbit());
                cout << "New Rabbits born! +" << newRabbits << endl;
            }
        }

        // Reproduction of foxes
        if (foxes.size() < MAX_FOXES) {
            // Calculate the reproduction rate based on available resources
            double reproductionRate = static_cast<double>(MAX_FOXES - foxes.size()) / MAX_FOXES;

            int newFoxes = static_cast<int>(foxes.size() * reproductionRate);
            if (newFoxes > 0) {
            foxes.insert(foxes.end(), newFoxes, Fox());
            cout << "New Foxes born! +" << newFoxes << endl;
            }
        }

        // Reproduction of wolves
        if (wolves.size() < MAX_WOLVES) {
            // Calculate the reproduction rate based on available resources
            double reproductionRate = static_cast<double>(MAX_WOLVES - wolves.size()) / MAX_WOLVES;

            int newWolves = static_cast<int>(wolves.size() * reproductionRate);
            if (newWolves > 0) {
                wolves.insert(wolves.end(), newWolves, Wolf());
                cout << "New Wolves born! +" << newWolves << endl;
        }
    }

        // Foxes hunt rabbits
        for (auto& fox : foxes) {
            if (rabbits.empty()) break; // No more rabbits to hunt

            if (rand() / double(RAND_MAX) < FOX_EATEN_RATE) {
                // Randomly select and remove a rabbit
                int index = rand() % rabbits.size();
                fox.increaseEnergy(RABBIT_ENERGY_GAIN); // Fox gains energy by eating
                rabbits.erase(rabbits.begin() + index);
                cout << "A fox caught a rabbit!" << endl;
            }
        }


        // Wolf hunts fox
        for (auto& Wolf : wolves) {
            if (foxes.empty()) break; // No more foxes to hunt

            if (rand() / double(RAND_MAX) < WOLF_EATEN_RATE) {
                // Randomly select and remove a fox
                int index = rand() % foxes.size();
                Wolf.increaseEnergy(FOX_ENERGY_GAIN); // Wolf gains energy by eating
                foxes.erase(foxes.begin() + index);
                cout << "A wolf caught a fox!" << endl;
            }
        }

        // Wolf hunts rabbit
        for (auto& Wolf : wolves) {
            if (rabbits.empty()) break; // No more rabbits to hunt

            if (rand() / double(RAND_MAX) < WOLF_EATEN_RATE) {
                // Randomly select and remove a rabbit
                int index = rand() % rabbits.size();
                Wolf.increaseEnergy(RABBIT_ENERGY_GAIN); // Wolf gains energy by eating
                rabbits.erase(rabbits.begin() + index);
                cout << "A wolf caught a rabbit!" << endl;
            }
        }

        // Update energy levels and remove dead rabbits, foxes and wolves
        for (auto it = rabbits.begin(); it != rabbits.end();) {
            it->decreaseEnergy(5.0); // Energy loss per time step
            if (it->getEnergy() <= 0) {
                it = rabbits.erase(it);
                cout << "A rabbit died of exhaustion." << endl;
            } else {
                ++it;
            }
        }

        for (auto it = foxes.begin(); it != foxes.end();) {
            it->decreaseEnergy(10.0); // Energy loss per time step
            if (it->getEnergy() <= 0) {
                it = foxes.erase(it);
                cout << "A fox died of starvation." << endl;
            } else {
                ++it;
            }
        }

        for (auto it = wolves.begin(); it != wolves.end();) {
            it->decreaseEnergy(10.0); // Energy loss per time step
            if (it->getEnergy() <= 0) {
                it = wolves.erase(it);
                cout << "A wolf died of starvation." << endl;
            } else {
                ++it;
            }
        }

        cout << "\nPress Enter to continue..." << endl;
        cin.get(); // Wait for user to press Enter
    }

    cout << "\n\nSimulation ended. Final population: " << endl;
    printPopulation(rabbits, foxes, wolves);

    return 0;
}
