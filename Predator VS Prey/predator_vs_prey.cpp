#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

using namespace std;

// Constants for ecosystem parameters
const int INITIAL_RABBITS = 32;
const int INITIAL_FOXES = 17;
const int INITIAL_WOLVES = 6;

const int MAX_RABBITS = 500;
const int MAX_FOXES = 500;
const int MAX_WOLVES = 500;

const double RABBIT_REPRODUCTION_RATE = 0.8; 
const double FOX_REPRODUCTION_RATE = 0.4;
const double WOLF_REPRODUCTION_RATE = 0.2;

const double FOX_EATEN_RATE = 0.2;
const double WOLF_EATEN_RATE = 0.1;

const double RABBIT_ENERGY_GAIN = 8.0;
const double FOX_ENERGY_GAIN = 7.0;
const double WOLF_ENERGY_GAIN = 5.0;

const double RABBIT_ENERGY_LOSS = 3.0;
const double FOX_ENERGY_LOSS = 5.0;
const double WOLF_ENERGY_LOSS = 7.0;

const double DISEASE_DEATH_RATE = 0.05;

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

    // Simulate ecosystem dynamics for 100 time steps
    for (int i = 0; i < 100; ++i) {
        system(CLEAR_SCREEN); // Clear the terminal
        cout << "\n\n=== Time Step: " << i+1 << " ===" << endl;
        printPopulation(rabbits, foxes, wolves);
        this_thread::sleep_for(chrono::milliseconds(1000)); // Delay for better visualization

        vector<string> events;

        // Reproduction of rabbits
        if (rabbits.size() < MAX_RABBITS) {
            // Calculate the reproduction rate based on available resources
            double reproductionRate = static_cast<double>(MAX_RABBITS - rabbits.size()) / MAX_RABBITS;
            int newRabbits = static_cast<int>(rabbits.size() * RABBIT_REPRODUCTION_RATE * reproductionRate);
            if (newRabbits > 0) {
                rabbits.insert(rabbits.end(), newRabbits, Rabbit());
                events.push_back("New Rabbits born! +" + to_string(newRabbits));
            }
        }

        // Reproduction of foxes
        if (foxes.size() < MAX_FOXES) {
            // Calculate the reproduction rate based on available resources
            double reproductionRate = static_cast<double>(MAX_FOXES - foxes.size()) / MAX_FOXES;
            int newFoxes = static_cast<int>(foxes.size() * FOX_REPRODUCTION_RATE * reproductionRate);
            if (newFoxes > 0) {
                foxes.insert(foxes.end(), newFoxes, Fox());
                events.push_back("New Foxes born! +" + to_string(newFoxes));
            }
        }

        // Reproduction of wolves
        if (wolves.size() < MAX_WOLVES) {
            // Calculate the reproduction rate based on available resources
            double reproductionRate = static_cast<double>(MAX_WOLVES - wolves.size()) / MAX_WOLVES;
            int newWolves = static_cast<int>(wolves.size() * WOLF_REPRODUCTION_RATE * reproductionRate);
            if (newWolves > 0) {
                wolves.insert(wolves.end(), newWolves, Wolf());
                events.push_back("New Wolves born! +" + to_string(newWolves));
            }
        }

        // Foxes hunt rabbits
        for (auto& fox : foxes) {
            if (rabbits.empty()) break; // No more rabbits to hunt
            if (rand() / double(RAND_MAX) < FOX_EATEN_RATE) {
                // Randomly select and remove a random number of rabbits
                int numCaught = rand() % (rabbits.size() + 1);
                fox.increaseEnergy(RABBIT_ENERGY_GAIN * numCaught); // Fox gains energy by eating
                rabbits.erase(rabbits.begin(), rabbits.begin() + numCaught);
                events.push_back("A fox caught " + to_string(numCaught) + " rabbits!");
                break; // Foxes can catch only once per time step
            }
        }

        // Wolf hunts fox
        for (auto& wolf : wolves) {
            if (foxes.empty()) break; // No more foxes to hunt
            if (rand() / double(RAND_MAX) < WOLF_EATEN_RATE) {
                // Randomly select and remove a random number of foxes
                int numCaught = rand() % (foxes.size() + 1);
                wolf.increaseEnergy(FOX_ENERGY_GAIN * numCaught); // Wolf gains energy by eating
                foxes.erase(foxes.begin(), foxes.begin() + numCaught);
                events.push_back("A wolf caught " + to_string(numCaught) + " foxes!");
                break; // Wolves can catch only once per time step
            }
        }

        // Wolf hunts rabbit
        for (auto& wolf : wolves) {
            if (rabbits.empty()) break; // No more rabbits to hunt
            if (rand() / double(RAND_MAX) < WOLF_EATEN_RATE) {
                // Randomly select and remove a random number of rabbits
                int numCaught = rand() % (rabbits.size() + 1);
                wolf.increaseEnergy(RABBIT_ENERGY_GAIN * numCaught); // Wolf gains energy by eating
                rabbits.erase(rabbits.begin(), rabbits.begin() + numCaught);
                events.push_back("A wolf caught " + to_string(numCaught) + " rabbits!");
                break; // Wolves can catch only once per time step
            }
        }

        // Introduce random deaths due to disease
        for (auto& animal : rabbits) {
            if (rand() / double(RAND_MAX) < DISEASE_DEATH_RATE) {
                rabbits.pop_back();
                events.push_back("A rabbit died from disease.");
            }
        }

        for (auto& animal : foxes) {
            if (rand() / double(RAND_MAX) < DISEASE_DEATH_RATE) {
                foxes.pop_back();
                events.push_back("A fox died from disease.");
            }
        }

        for (auto& animal : wolves) {
            if (rand() / double(RAND_MAX) < DISEASE_DEATH_RATE) {
                wolves.pop_back();
                events.push_back("A wolf died from disease.");
            }
        }

        // Update energy levels and remove dead animals
        for (auto& animal : rabbits) {
            animal.decreaseEnergy(5.0); // Energy loss per time step
            if (animal.getEnergy() <= 0) {
                rabbits.pop_back();
                events.push_back("A rabbit died of exhaustion.");
            }
        }

        for (auto& animal : foxes) {
            animal.decreaseEnergy(10.0); // Energy loss per time step
            if (animal.getEnergy() <= 0) {
                foxes.pop_back();
                events.push_back("A fox died of starvation.");
            }
        }

        for (auto& animal : wolves) {
            animal.decreaseEnergy(10.0); // Energy loss per time step
            if (animal.getEnergy() <= 0) {
                wolves.pop_back();
                events.push_back("A wolf died of starvation.");
            }
        }

        // Print accumulated events
        for (const auto& event : events) {
            cout << event << endl;
        }

        cout << "\nPress Enter to continue..." << endl;
        cin.get(); // Wait for user to press Enter
    }

    cout << "\n\nSimulation ended. Final population: " << endl;
    printPopulation(rabbits, foxes, wolves);

    return 0;
}
