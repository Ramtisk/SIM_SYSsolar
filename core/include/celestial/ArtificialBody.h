#ifndef SOLARSYS_CORE_CELESTIAL_ARTIFICIAL_BODY_H
#define SOLARSYS_CORE_CELESTIAL_ARTIFICIAL_BODY_H

#include "CelestialBody.h"

class ArtificialBody : public CelestialBody {
protected:
    /*--- Operational info ---*/
    std::string owner;          // country / organization
    std::string purpose;        // e.g., "Communication", "Weather", "Navigation"
    double launchDate;          // year or unix timestamp

    /*--- Orbital characteristics ---*/
    double semiMajorAxis;       // meters
    double eccentricity;
    double inclination;         // radians

    /*--- Status ---*/
    std::string status;         // e.g., "Active", "Inactive", "Decommissioned"
    double remainingFuel;       // percentage or kg

public:
    /*--- Constructors & Destructors ---*/
    using CelestialBody::CelestialBody;
    virtual ~ArtificialBody() = default;

    /*--- Accessors ---*/
    std::string getOwner() const { return owner; }
    std::string getPurpose() const { return purpose; }
    double getLaunchDate() const { return launchDate; }
    double getSemiMajorAxis() const { return semiMajorAxis; }
    double getEccentricity() const { return eccentricity; }
    double getInclination() const { return inclination; }
    std::string getStatus() const { return status; }
    double getRemainingFuel() const { return remainingFuel; }

    /*--- Mutators ---*/
    void setOwner(const std::string& o) { owner = o; }
    void setPurpose(const std::string& p) { purpose = p; }
    void setLaunchDate(double d) { launchDate = d; }
    void setSemiMajorAxis(double a) { semiMajorAxis = a; }
    void setEccentricity(double e) { eccentricity = e; }
    void setInclination(double i) { inclination = i; }
    void setStatus(const std::string& s) { status = s; }
    void setRemainingFuel(double f) { remainingFuel = f; }
};

#endif // SOLARSYS_CORE_CELESTIAL_ARTIFICIAL_BODY_H