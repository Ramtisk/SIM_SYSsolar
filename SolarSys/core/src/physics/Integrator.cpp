#include "../../include/physics/Integrator.h"

// Integrator class is header-only with static methods
// Additional integration utilities go here

namespace IntegratorUtils {

    // Compute total system energy (kinetic + potential)
    double computeTotalEnergy(const std::vector<BodyState>& bodies) {
        double totalEnergy = 0.0;
        
        for (size_t i = 0; i < bodies.size(); ++i) {
            // Kinetic energy: 0.5 * m * v²
            double ke = 0.5 * bodies[i].mass * bodies[i].velocity.magnitudeSquared();
            totalEnergy += ke;
            
            // Potential energy (pairs counted once)
            for (size_t j = i + 1; j < bodies.size(); ++j) {
                double pe = Gravity::computePotentialEnergy(
                    bodies[i].mass, bodies[j].mass,
                    bodies[i].position, bodies[j].position
                );
                totalEnergy += pe;
            }
        }
        
        return totalEnergy;
    }

    // Compute total angular momentum
    Vec3 computeTotalAngularMomentum(const std::vector<BodyState>& bodies) {
        Vec3 totalL;
        for (const auto& body : bodies) {
            // L = r × p = r × (m*v)
            Vec3 L = body.position.cross(body.velocity * body.mass);
            totalL += L;
        }
        return totalL;
    }

    // Compute center of mass position
    Vec3 computeCenterOfMass(const std::vector<BodyState>& bodies) {
        Vec3 com;
        double totalMass = 0.0;
        
        for (const auto& body : bodies) {
            com += body.position * body.mass;
            totalMass += body.mass;
        }
        
        if (totalMass > 1e-10) {
            com = com / totalMass;
        }
        
        return com;
    }

    // Compute center of mass velocity
    Vec3 computeCenterOfMassVelocity(const std::vector<BodyState>& bodies) {
        Vec3 comV;
        double totalMass = 0.0;
        
        for (const auto& body : bodies) {
            comV += body.velocity * body.mass;
            totalMass += body.mass;
        }
        
        if (totalMass > 1e-10) {
            comV = comV / totalMass;
        }
        
        return comV;
    }
}