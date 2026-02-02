#include "../../include/simulation/SolarSystem.h"
#include <algorithm>
#include <iostream>

// SolarSystem is mostly header-only
// Additional complex operations go here

namespace SolarSystemUtils {

    // Initialize body states from celestial bodies for N-body simulation
    void initializeBodyStates(SolarSystem& system, std::vector<BodyState>& states) {
        states.clear();
        
        // Add star at origin
        if (system.getStar()) {
            BodyState starState;
            starState.id = system.getStar()->getId();
            starState.mass = system.getStar()->getMass();
            starState.position = Vec3(0, 0, 0);
            starState.velocity = Vec3(0, 0, 0);
            starState.acceleration = Vec3(0, 0, 0);
            states.push_back(starState);
        }
        
        // Planets would be added here with their positions from orbits
        // This requires accessing the private orbits map, so would need
        // to be a friend function or member method
    }

    // Find closest approach between two bodies
    double findClosestApproach(const Orbit& orbit1, const Orbit& orbit2, 
                                double startTime, double endTime, double step) {
        double minDistance = std::numeric_limits<double>::max();
        
        for (double t = startTime; t <= endTime; t += step) {
            Vec3 pos1 = orbit1.getPositionAtTime(t);
            Vec3 pos2 = orbit2.getPositionAtTime(t);
            double dist = (pos1 - pos2).magnitude();
            minDistance = std::min(minDistance, dist);
        }
        
        return minDistance;
    }

    // Check for potential collisions
    bool checkCollision(const Vec3& pos1, double radius1, 
                        const Vec3& pos2, double radius2) {
        double distance = (pos1 - pos2).magnitude();
        return distance < (radius1 + radius2);
    }

    // Calculate transfer orbit delta-v (Hohmann transfer approximation)
    double hohmannTransferDeltaV(double mu, double r1, double r2) {
        double a_transfer = (r1 + r2) / 2.0;
        
        // Departure burn
        double v1_circular = std::sqrt(mu / r1);
        double v1_transfer = std::sqrt(mu * (2.0/r1 - 1.0/a_transfer));
        double dv1 = std::abs(v1_transfer - v1_circular);
        
        // Arrival burn
        double v2_circular = std::sqrt(mu / r2);
        double v2_transfer = std::sqrt(mu * (2.0/r2 - 1.0/a_transfer));
        double dv2 = std::abs(v2_circular - v2_transfer);
        
        return dv1 + dv2;
    }

    // Calculate transfer time (Hohmann transfer)
    double hohmannTransferTime(double mu, double r1, double r2) {
        double a_transfer = (r1 + r2) / 2.0;
        return M_PI * std::sqrt(a_transfer * a_transfer * a_transfer / mu);
    }
}