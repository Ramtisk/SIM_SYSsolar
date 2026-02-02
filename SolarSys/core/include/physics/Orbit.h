#ifndef SOLARSYS_CORE_PHYSICS_ORBIT_H
#define SOLARSYS_CORE_PHYSICS_ORBIT_H

#include "Gravity.h"
#include <cmath>

/*--- Keplerian orbital elements ---*/
struct OrbitalElements {
    double semiMajorAxis;       // a (meters)
    double eccentricity;        // e (0 = circle, 0-1 = ellipse, 1 = parabola, >1 = hyperbola)
    double inclination;         // i (radians)
    double longitudeOfAscNode;  // Ω (radians)
    double argumentOfPeriapsis; // ω (radians)
    double trueAnomaly;         // ν (radians)
    double meanAnomaly;         // M (radians)
    double epoch;               // reference time (seconds)
};

class Orbit {
private:
    OrbitalElements elements;
    double centralMass;         // mass of the body being orbited (kg)
    double mu;                  // standard gravitational parameter (G * M)

public:
    /*--- Constructors ---*/
    Orbit() : centralMass(0), mu(0) {}
    
    Orbit(const OrbitalElements& elem, double centralMass_)
        : elements(elem), centralMass(centralMass_) {
        mu = PhysicsConstants::G * centralMass;
    }

    /*--- Orbital period (Kepler's 3rd law) ---*/
    double getPeriod() const {
        if (elements.eccentricity >= 1.0) return -1.0;
        return 2.0 * M_PI * std::sqrt(std::pow(elements.semiMajorAxis, 3) / mu);
    }

    /*--- Mean motion (radians per second) ---*/
    double getMeanMotion() const {
        return std::sqrt(mu / std::pow(elements.semiMajorAxis, 3));
    }

    /*--- Periapsis and apoapsis distances ---*/
    double getPeriapsis() const {
        return elements.semiMajorAxis * (1.0 - elements.eccentricity);
    }

    double getApoapsis() const {
        if (elements.eccentricity >= 1.0) return -1.0;
        return elements.semiMajorAxis * (1.0 + elements.eccentricity);
    }

    /*--- Solve Kepler's equation: M = E - e*sin(E) ---*/
    double solveKeplerEquation(double meanAnomaly, double tolerance = 1e-12, int maxIter = 100) const {
        double e = elements.eccentricity;
        double E = meanAnomaly;
        
        for (int i = 0; i < maxIter; ++i) {
            double dE = (E - e * std::sin(E) - meanAnomaly) / (1.0 - e * std::cos(E));
            E -= dE;
            if (std::abs(dE) < tolerance) break;
        }
        return E;
    }

    /*--- Convert eccentric anomaly to true anomaly ---*/
    double eccentricToTrueAnomaly(double E) const {
        double e = elements.eccentricity;
        return 2.0 * std::atan2(
            std::sqrt(1.0 + e) * std::sin(E / 2.0),
            std::sqrt(1.0 - e) * std::cos(E / 2.0)
        );
    }

    /*--- Get position at given time ---*/
    Vec3 getPositionAtTime(double time) const {
        double n = getMeanMotion();
        double M = elements.meanAnomaly + n * (time - elements.epoch);
        
        M = std::fmod(M, 2.0 * M_PI);
        if (M < 0) M += 2.0 * M_PI;
        
        double E = solveKeplerEquation(M);
        double nu = eccentricToTrueAnomaly(E);
        double r = elements.semiMajorAxis * (1.0 - elements.eccentricity * std::cos(E));
        
        double xOrbital = r * std::cos(nu);
        double yOrbital = r * std::sin(nu);
        
        return transformToInertial(xOrbital, yOrbital);
    }

    /*--- Get velocity at given time ---*/
    Vec3 getVelocityAtTime(double time) const {
        double n = getMeanMotion();
        double M = elements.meanAnomaly + n * (time - elements.epoch);
        M = std::fmod(M, 2.0 * M_PI);
        if (M < 0) M += 2.0 * M_PI;
        
        double E = solveKeplerEquation(M);
        double nu = eccentricToTrueAnomaly(E);
        
        double e = elements.eccentricity;
        double a = elements.semiMajorAxis;
        double h = std::sqrt(mu * a * (1.0 - e*e));
        
        double vxOrbital = -mu / h * std::sin(nu);
        double vyOrbital = mu / h * (e + std::cos(nu));
        
        return transformVelocityToInertial(vxOrbital, vyOrbital);
    }

    /*--- Accessors ---*/
    const OrbitalElements& getElements() const { return elements; }
    double getCentralMass() const { return centralMass; }

    /*--- Mutators ---*/
    void setElements(const OrbitalElements& elem) { elements = elem; }
    void updateMeanAnomaly(double dt) {
        elements.meanAnomaly += getMeanMotion() * dt;
        elements.meanAnomaly = std::fmod(elements.meanAnomaly, 2.0 * M_PI);
    }

private:
    /*--- Transform orbital plane coordinates to inertial frame ---*/
    Vec3 transformToInertial(double xOrb, double yOrb) const {
        double i = elements.inclination;
        double omega = elements.argumentOfPeriapsis;
        double Omega = elements.longitudeOfAscNode;
        
        double cosO = std::cos(Omega), sinO = std::sin(Omega);
        double coso = std::cos(omega), sino = std::sin(omega);
        double cosi = std::cos(i), sini = std::sin(i);
        
        double x = (cosO*coso - sinO*sino*cosi) * xOrb + (-cosO*sino - sinO*coso*cosi) * yOrb;
        double y = (sinO*coso + cosO*sino*cosi) * xOrb + (-sinO*sino + cosO*coso*cosi) * yOrb;
        double z = (sino*sini) * xOrb + (coso*sini) * yOrb;
        
        return Vec3(x, y, z);
    }

    Vec3 transformVelocityToInertial(double vxOrb, double vyOrb) const {
        return transformToInertial(vxOrb, vyOrb);
    }
};

#endif // SOLARSYS_CORE_PHYSICS_ORBIT_H