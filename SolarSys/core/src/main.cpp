#include "../include/simulation/SolarSystem.h"
#include <iostream>
#include <iomanip>

int main() {
    std::cout << "=== Solar System Conquest Simulator ===" << std::endl;
    std::cout << "Initializing simulation..." << std::endl;

    // Create solar system
    SolarSystem solarSystem;

    // Create the Sun
    auto sun = std::make_unique<Star>(
        0, "Sun", CelestialBody::BodyType::STAR,
        PhysicsConstants::SOLAR_MASS, 6.96e8  // mass, radius
    );
    sun->setLuminosity(3.828e26);
    sun->setSurfaceTemperature(5778);
    sun->setSpectralType(SpectralType::G);
    sun->setEvolutionaryStage(EvolutionaryStage::MAIN_SEQUENCE);
    solarSystem.setStar(std::move(sun));

    // Create Earth
    auto earth = std::make_unique<Planet>(
        3, "Earth", CelestialBody::BodyType::PLANET,
        PhysicsConstants::EARTH_MASS, 6.371e6
    );
    earth->setSemiMajorAxis(PhysicsConstants::AU);
    earth->setEccentricity(0.0167);
    earth->setOrbitalPeriod(TimeConstants::YEAR);
    earth->setInclination(0.0);
    earth->setAtmosphericPressure(101325);
    earth->setAverageTemperature(288);
    earth->setNumberOfMoons(1);
    solarSystem.addPlanet(std::move(earth));

    // Set Earth's orbit (C++17 compatible initialization)
    OrbitalElements earthOrbit;
    earthOrbit.semiMajorAxis = PhysicsConstants::AU;
    earthOrbit.eccentricity = 0.0167;
    earthOrbit.inclination = 0.0;
    earthOrbit.longitudeOfAscNode = 0.0;
    earthOrbit.argumentOfPeriapsis = 0.0;
    earthOrbit.trueAnomaly = 0.0;
    earthOrbit.meanAnomaly = 0.0;
    earthOrbit.epoch = 0.0;
    
    solarSystem.setOrbit(3, Orbit(earthOrbit, PhysicsConstants::SOLAR_MASS));

    // Configure simulation
    solarSystem.getTimeSystem().setTimeStep(TimeConstants::DAY);
    solarSystem.getTimeSystem().setTimeScale(1.0);
    solarSystem.setUseKeplerianOrbits(true);

    std::cout << "Total bodies: " << solarSystem.getTotalBodyCount() << std::endl;
    std::cout << "Starting simulation..." << std::endl;

    // Run simulation for 1 year
    int stepsPerYear = static_cast<int>(TimeConstants::YEAR / TimeConstants::DAY);
    for (int i = 0; i < stepsPerYear; ++i) {
        solarSystem.step();

        // Print progress every 30 days
        if (i % 30 == 0) {
            Vec3 earthPos = solarSystem.getBodyPosition(3);
            double distanceAU = earthPos.magnitude() / PhysicsConstants::AU;
            std::cout << "Day " << std::setw(3) << i 
                      << " | Earth distance: " << std::fixed << std::setprecision(4) 
                      << distanceAU << " AU" << std::endl;
        }
    }

    std::cout << "\nSimulation complete!" << std::endl;
    std::cout << "Simulated time: " << solarSystem.getTimeSystem().getYears() 
              << " years" << std::endl;
    std::cout << "Total ticks: " << solarSystem.getTimeSystem().getTickCount() << std::endl;

    return 0;
}