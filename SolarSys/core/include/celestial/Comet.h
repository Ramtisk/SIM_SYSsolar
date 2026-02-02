#ifndef SOLARSYS_CORE_CELESTIAL_COMET_H
#define SOLARSYS_CORE_CELESTIAL_COMET_H

#include "CelestialBody.h"

class Comet : public CelestialBody {
protected:
    /*--- Orbital characteristics ---*/
    double semiMajorAxis;       // meters
    double eccentricity;        // typically > 0.9 (highly elliptical)
    double orbitalPeriod;       // seconds
    double inclination;         // radians
    double perihelion;          // closest approach to sun (meters)
    double aphelion;            // farthest point (meters)

    /*--- Coma & tail ---*/
    double cometHeadRadius;     // nucleus radius (meters)
    double comaRadius;          // extent of coma (meters)
    bool hasActiveTail;

    /*--- Origin ---*/
    std::string origin;         // e.g., "Oort Cloud", "Kuiper Belt"

public:
    /*--- Constructors & Destructors ---*/
    using CelestialBody::CelestialBody;
    virtual ~Comet() = default;

    /*--- Accessors ---*/
    double getSemiMajorAxis() const { return semiMajorAxis; }
    double getEccentricity() const { return eccentricity; }
    double getOrbitalPeriod() const { return orbitalPeriod; }
    double getInclination() const { return inclination; }
    double getPerihelion() const { return perihelion; }
    double getAphelion() const { return aphelion; }
    double getCometHeadRadius() const { return cometHeadRadius; }
    double getComaRadius() const { return comaRadius; }
    bool hasActiveTailNow() const { return hasActiveTail; }
    std::string getOrigin() const { return origin; }

    /*--- Mutators ---*/
    void setSemiMajorAxis(double a) { semiMajorAxis = a; }
    void setEccentricity(double e) { eccentricity = e; }
    void setOrbitalPeriod(double p) { orbitalPeriod = p; }
    void setInclination(double i) { inclination = i; }
    void setPerihelion(double p) { perihelion = p; }
    void setAphelion(double a) { aphelion = a; }
    void setCometHeadRadius(double r) { cometHeadRadius = r; }
    void setComaRadius(double r) { comaRadius = r; }
    void setHasActiveTail(bool t) { hasActiveTail = t; }
    void setOrigin(const std::string& o) { origin = o; }
};

#endif // SOLARSYS_CORE_CELESTIAL_COMET_H