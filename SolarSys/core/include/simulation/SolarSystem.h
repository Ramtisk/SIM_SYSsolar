#ifndef SOLARSYS_CORE_SIMULATION_SOLARSYSTEM_H
#define SOLARSYS_CORE_SIMULATION_SOLARSYSTEM_H

#include "../celestial/Star.h"
#include "../celestial/Planet.h"
#include "../celestial/NaturalSatellite.h"
#include "../celestial/Asteroid.h"
#include "../celestial/Comet.h"
#include "../celestial/DwarfPlanet.h"
#include "../celestial/ArtificialBody.h"
#include "../physics/Integrator.h"
#include "../physics/Orbit.h"
#include "../time/TimeSystem.h"

#include <vector>
#include <memory>
#include <unordered_map>

class SolarSystem {
private:
    /*--- Central star ---*/
    std::unique_ptr<Star> star;

    /*--- Orbiting bodies ---*/
    std::vector<std::unique_ptr<Planet>> planets;
    std::vector<std::unique_ptr<NaturalSatellite>> moons;
    std::vector<std::unique_ptr<DwarfPlanet>> dwarfPlanets;
    std::vector<std::unique_ptr<Asteroid>> asteroids;
    std::vector<std::unique_ptr<Comet>> comets;
    std::vector<std::unique_ptr<ArtificialBody>> artificialBodies;

    /*--- Body states for physics simulation ---*/
    std::vector<BodyState> bodyStates;
    std::unordered_map<int, Orbit> orbits;

    /*--- Time management ---*/
    TimeSystem timeSystem;

    /*--- Simulation config ---*/
    IntegrationMethod integrationMethod;
    bool useKeplerianOrbits;    // true = analytical, false = N-body

public:
    SolarSystem() 
        : integrationMethod(IntegrationMethod::VELOCITY_VERLET),
          useKeplerianOrbits(true) {}

    /*--- Initialization ---*/
    void setStar(std::unique_ptr<Star> s) { star = std::move(s); }
    void addPlanet(std::unique_ptr<Planet> p) { planets.push_back(std::move(p)); }
    void addMoon(std::unique_ptr<NaturalSatellite> m) { moons.push_back(std::move(m)); }
    void addDwarfPlanet(std::unique_ptr<DwarfPlanet> dp) { dwarfPlanets.push_back(std::move(dp)); }
    void addAsteroid(std::unique_ptr<Asteroid> a) { asteroids.push_back(std::move(a)); }
    void addComet(std::unique_ptr<Comet> c) { comets.push_back(std::move(c)); }
    void addArtificialBody(std::unique_ptr<ArtificialBody> ab) { artificialBodies.push_back(std::move(ab)); }

    void setOrbit(int bodyId, const Orbit& orbit) { orbits[bodyId] = orbit; }

    /*--- Simulation step ---*/
    void step() {
        double dt = timeSystem.getTimeStep();

        if (useKeplerianOrbits) {
            // Analytical orbital propagation
            for (auto& [id, orbit] : orbits) {
                orbit.updateMeanAnomaly(dt);
            }
        } else {
            // N-body numerical integration
            for (auto& state : bodyStates) {
                switch (integrationMethod) {
                    case IntegrationMethod::EULER:
                        Integrator::euler(state, dt, Integrator::nBodyAcceleration, bodyStates);
                        break;
                    case IntegrationMethod::SYMPLECTIC_EULER:
                        Integrator::symplecticEuler(state, dt, Integrator::nBodyAcceleration, bodyStates);
                        break;
                    case IntegrationMethod::VELOCITY_VERLET:
                        Integrator::velocityVerlet(state, dt, Integrator::nBodyAcceleration, bodyStates);
                        break;
                    case IntegrationMethod::RK4:
                        Integrator::rk4(state, dt, Integrator::nBodyAcceleration, bodyStates);
                        break;
                }
            }
        }

        timeSystem.tick();
    }

    /*--- Accessors ---*/
    TimeSystem& getTimeSystem() { return timeSystem; }
    const TimeSystem& getTimeSystem() const { return timeSystem; }
    Star* getStar() { return star.get(); }
    const std::vector<std::unique_ptr<Planet>>& getPlanets() const { return planets; }
    
    Vec3 getBodyPosition(int bodyId) const {
        if (useKeplerianOrbits && orbits.count(bodyId)) {
            return orbits.at(bodyId).getPositionAtTime(timeSystem.getCurrentTime());
        }
        for (const auto& state : bodyStates) {
            if (state.id == bodyId) return state.position;
        }
        return Vec3();
    }

    /*--- Configuration ---*/
    void setIntegrationMethod(IntegrationMethod method) { integrationMethod = method; }
    void setUseKeplerianOrbits(bool use) { useKeplerianOrbits = use; }
    
    /*--- Statistics ---*/
    size_t getTotalBodyCount() const {
        return (star ? 1 : 0) + planets.size() + moons.size() + 
               dwarfPlanets.size() + asteroids.size() + comets.size() + 
               artificialBodies.size();
    }
};

#endif // SOLARSYS_CORE_SIMULATION_SOLARSYSTEM_H