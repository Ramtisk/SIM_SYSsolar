#ifndef SOLARSYS_CORE_CELESTIAL_ASTEROID_H
#define SOLARSYS_CORE_CELESTIAL_ASTEROID_H

#include "CelestialBody.h"

class Asteroid : public CelestialBody {
protected:
    /*--- Orbital characteristics ---*/
    double semiMajorAxis;       // meters
    double eccentricity;
    double orbitalPeriod;       // seconds
    double inclination;         // radians

    /*--- Physical composition ---*/
    std::string composition;    // e.g., "Carbonaceous", "Metallic", "Silicate"
    double rotationPeriod;      // seconds

    /*--- Classification ---*/
    std::string asteroidClass;  // e.g., "C-type", "M-type", "S-type"

public:
    /*--- Constructors & Destructors ---*/
    using CelestialBody::CelestialBody;
    virtual ~Asteroid() = default;

    /*--- Accessors ---*/
    double getSemiMajorAxis() const { return semiMajorAxis; }
    double getEccentricity() const { return eccentricity; }
    double getOrbitalPeriod() const { return orbitalPeriod; }
    double getInclination() const { return inclination; }
    std::string getComposition() const { return composition; }
    double getRotationPeriod() const { return rotationPeriod; }
    std::string getAsteroidClass() const { return asteroidClass; }

    /*--- Mutators ---*/
    void setSemiMajorAxis(double a) { semiMajorAxis = a; }
    void setEccentricity(double e) { eccentricity = e; }
    void setOrbitalPeriod(double p) { orbitalPeriod = p; }
    void setInclination(double i) { inclination = i; }
    void setComposition(const std::string& c) { composition = c; }
    void setRotationPeriod(double r) { rotationPeriod = r; }
    void setAsteroidClass(const std::string& ac) { asteroidClass = ac; }
};

#endif // SOLARSYS_CORE_CELESTIAL_ASTEROID_H