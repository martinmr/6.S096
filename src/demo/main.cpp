#include <nbody/Simulation.h>

#include <iostream>
#include <fstream>

int main() {
  try {
    std::ifstream input{ "resources/nbody/binary-system-simple.txt" };
    nbody::Simulation sim{};
    sim.loadRun(input);
    sim.evolveSystem( 1e4, 0.001 );
    sim.saveRun();
    return 0;
  } catch( const std::exception &e ) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
