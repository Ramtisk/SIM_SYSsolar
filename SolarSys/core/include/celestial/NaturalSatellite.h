#ifndef SOLARSYS_CORE_CELESTIAL_NATURAL_SATELLITE_H
#define SOLARSYS_CORE_CELESTIAL_NATURAL_SATELLITE_H

#include "CelestialBody.h"

/*--- Natural Satellite (Moon) ---*/
class NaturalSatellite : public CelestialBody {
protected:
    /*--- Orbital characteristics (around parent planet) ---*/
    double semiMajorAxis;       // meters
    double eccentricity;        // 0.0 to 1.0
    double orbitalPeriod;       // seconds
    double inclination;         // radians

    /*--- Physical state ---*/
    bool tidallyLocked;         // one side always faces parent
    double meanMotion;          // radians/second

    /*--- Parent reference ---*/
    // Could store parent planet ID or pointer (design choice)
    int parentPlanetId;

public:
    /*--- Constructors & Destructors ---*/
    using CelestialBody::CelestialBody;
    virtual ~NaturalSatellite() = default;

    /*--- Accessors ---*/
    double getSemiMajorAxis() const { return semiMajorAxis; }
    double getEccentricity() const { return eccentricity; }
    double getOrbitalPeriod() const { return orbitalPeriod; }
    double getInclination() const { return inclination; }
    bool isTidallyLocked() const { return tidallyLocked; }
    double getMeanMotion() const { return meanMotion; }
    int getParentPlanetId() const { return parentPlanetId; }

    /*--- Mutators ---*/
    void setSemiMajorAxis(double a) { semiMajorAxis = a; }
    void setEccentricity(double e) { eccentricity = e; }
    void setOrbitalPeriod(double p) { orbitalPeriod = p; }
    void setInclination(double i) { inclination = i; }
    void setTidallyLocked(bool t) { tidallyLocked = t; }
    void setMeanMotion(double m) { meanMotion = m; }
    void setParentPlanetId(int id) { parentPlanetId = id; }
};

#endif // SOLARSYS_CORE_CELESTIAL_NATURAL_SATELLITE_H