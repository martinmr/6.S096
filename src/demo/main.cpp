#include <nbody/Simulation.h>

#include <iostream>
#include <fstream>

int main(int argc, char * argv) {
  try {
    std::ifstream input{ "resources/nbody/system.txt" };
    nbody::Simulation sim{};
    sim.loadRun(input);
    sim.evolveSystem( 1e4, 0.000001 );
    sim.saveRun();
    return 0;
  } catch( const std::exception &e ) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
