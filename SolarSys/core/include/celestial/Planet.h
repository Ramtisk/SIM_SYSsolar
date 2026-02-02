#ifndef SOLARSYS_CORE_CELESTIAL_PLANET_H
#define SOLARSYS_CORE_CELESTIAL_PLANET_H

#include "CelestialBody.h"

class Planet : public CelestialBody {
protected:
    /*--- Orbital characteristics ---*/
    double semiMajorAxis;       // meters
    double eccentricity;        // 0.0 (circular) to 1.0 (parabolic)
    double orbitalPeriod;       // seconds
    double inclination;         // radians

    /*--- Atmospheric properties ---*/
    double atmosphericPressure; // pascals
    double averageTemperature;  // kelvin

    /*--- Geological / environmental ---*/
    bool hasRings;
    int numberOfMoons;

public:
    /*--- Constructors & Destructors ---*/
    using CelestialBody::CelestialBody;
    virtual ~Planet() = default;

    /*--- Accessors ---*/
    double getSemiMajorAxis() const { return semiMajorAxis; }
    double getEccentricity() const { return eccentricity; }
    double getOrbitalPeriod() const { return orbitalPeriod; }
    double getInclination() const { return inclination; }
    double getAtmosphericPressure() const { return atmosphericPressure; }
    double getAverageTemperature() const { return averageTemperature; }
    bool getHasRings() const { return hasRings; }
    int getNumberOfMoons() const { return numberOfMoons; }

    /*--- Mutators ---*/
    void setSemiMajorAxis(double a) { semiMajorAxis = a; }
    void setEccentricity(double e) { eccentricity = e; }
    void setOrbitalPeriod(double p) { orbitalPeriod = p; }
    void setInclination(double i) { inclination = i; }
    void setAtmosphericPressure(double p) { atmosphericPressure = p; }
    void setAverageTemperature(double t) { averageTemperature = t; }
    void setHasRings(bool r) { hasRings = r; }
    void setNumberOfMoons(int n) { numberOfMoons = n; }
};

#endif // SOLARSYS_CORE_CELESTIAL_PLANET_H