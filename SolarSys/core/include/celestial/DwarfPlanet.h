#ifndef SOLARSYS_CORE_CELESTIAL_DWARF_PLANET_H
#define SOLARSYS_CORE_CELESTIAL_DWARF_PLANET_H

#include "CelestialBody.h"

class DwarfPlanet : public CelestialBody {
protected:
    /*--- Orbital characteristics ---*/
    double semiMajorAxis;       // meters
    double eccentricity;
    double orbitalPeriod;       // seconds
    double inclination;         // radians

    /*--- Classification ---*/
    std::string region;         // e.g., "Kuiper Belt", "Asteroid Belt"
    bool hasCleared;            // has cleared its orbital neighborhood

public:
    /*--- Constructors & Destructors ---*/
    using CelestialBody::CelestialBody;
    virtual ~DwarfPlanet() = default;

    /*--- Accessors ---*/
    double getSemiMajorAxis() const { return semiMajorAxis; }
    double getEccentricity() const { return eccentricity; }
    double getOrbitalPeriod() const { return orbitalPeriod; }
    double getInclination() const { return inclination; }
    std::string getRegion() const { return region; }
    bool hasOrbitallyCleared() const { return hasCleared; }

    /*--- Mutators ---*/
    void setSemiMajorAxis(double a) { semiMajorAxis = a; }
    void setEccentricity(double e) { eccentricity = e; }
    void setOrbitalPeriod(double p) { orbitalPeriod = p; }
    void setInclination(double i) { inclination = i; }
    void setRegion(const std::string& r) { region = r; }
    void setHasCleared(bool c) { hasCleared = c; }
};

#endif // SOLARSYS_CORE_CELESTIAL_DWARF_PLANET_H