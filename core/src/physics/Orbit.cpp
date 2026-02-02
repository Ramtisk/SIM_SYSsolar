#include "../../include/physics/Orbit.h"

// Orbit class is mostly header-only
// Additional orbit utilities go here

namespace OrbitUtils {

    // Convert state vectors to orbital elements
    OrbitalElements stateToElements(const Vec3& position, const Vec3& velocity, double mu) {
        OrbitalElements elements;
        
        Vec3 h = position.cross(velocity);  // specific angular momentum
        Vec3 n(-h.y, h.x, 0.0);              // node vector
        
        double r = position.magnitude();
        double v = velocity.magnitude();
        
        // Eccentricity vector
        Vec3 eVec = (position * (v*v - mu/r) - velocity * position.dot(velocity)) / mu;
        elements.eccentricity = eVec.magnitude();
        
        // Semi-major axis
        double energy = v*v/2.0 - mu/r;
        if (std::abs(elements.eccentricity - 1.0) > 1e-10) {
            elements.semiMajorAxis = -mu / (2.0 * energy);
        } else {
            elements.semiMajorAxis = std::numeric_limits<double>::infinity();
        }
        
        // Inclination
        elements.inclination = std::acos(h.z / h.magnitude());
        
        // Longitude of ascending node
        double nMag = n.magnitude();
        if (nMag > 1e-10) {
            elements.longitudeOfAscNode = std::acos(n.x / nMag);
            if (n.y < 0) elements.longitudeOfAscNode = 2*M_PI - elements.longitudeOfAscNode;
        } else {
            elements.longitudeOfAscNode = 0.0;
        }
        
        // Argument of periapsis
        if (nMag > 1e-10 && elements.eccentricity > 1e-10) {
            elements.argumentOfPeriapsis = std::acos(n.dot(eVec) / (nMag * elements.eccentricity));
            if (eVec.z < 0) elements.argumentOfPeriapsis = 2*M_PI - elements.argumentOfPeriapsis;
        } else {
            elements.argumentOfPeriapsis = 0.0;
        }
        
        // True anomaly
        if (elements.eccentricity > 1e-10) {
            elements.trueAnomaly = std::acos(eVec.dot(position) / (elements.eccentricity * r));
            if (position.dot(velocity) < 0) elements.trueAnomaly = 2*M_PI - elements.trueAnomaly;
        } else {
            elements.trueAnomaly = 0.0;
        }
        
        // Mean anomaly (from true anomaly via eccentric anomaly)
        double E = 2.0 * std::atan(std::sqrt((1-elements.eccentricity)/(1+elements.eccentricity)) 
                                   * std::tan(elements.trueAnomaly/2));
        elements.meanAnomaly = E - elements.eccentricity * std::sin(E);
        
        elements.epoch = 0.0;
        
        return elements;
    }

    // Calculate orbital energy
    double orbitalEnergy(double mu, double semiMajorAxis) {
        if (std::abs(semiMajorAxis) < 1e-10) return 0.0;
        return -mu / (2.0 * semiMajorAxis);
    }

    // Calculate specific angular momentum
    double specificAngularMomentum(double mu, double semiMajorAxis, double eccentricity) {
        return std::sqrt(mu * semiMajorAxis * (1.0 - eccentricity * eccentricity));
    }
}