#ifndef SOLARSYS_CORE_CELESTIAL_STAR_H
#define SOLARSYS_CORE_CELESTIAL_STAR_H

#include "CelestialBody.h"

/*--- O–M are Morgan–Keenan spectral classes (https://www.ebsco.com/research-starters/history/morgan-keenan-classification-system-mk-or-mkk) ---*/
enum class SpectralType 
{ 
    O,          // Very hot (≳30,000 K), blue, extremely luminous and massive, very short-lived; rare.
    B,          // Hot (≈10,000–30,000 K), blue-white, massive and luminous (young stars, often in clusters). 
    A,          // Hot/white (≈7,500–10,000 K), strong hydrogen lines (e.g., Sirius ≈ A1V).
    F,          // White–yellow (≈6,000–7,500 K), weaker H lines, stronger metal lines.
    G,          // Yellow (≈5,200–6,000 K), moderate mass/luminosity (Sun ≈ G2V).
    K,          // Orange (≈3,700–5,200 K), cooler, longer-lived than G/A types.
    M,          // Red (≲3,700 K), coolest common main‑sequence stars and many giants; most numerous.
};

enum class EvolutionaryStage
{
    PROTOSTAR,
    MAIN_SEQUENCE,
    RED_GIANT,
    WHITE_DWARF,
    NEUTRON_STAR,
    BLACK_HOLE
};

class Star : public CelestialBody
{
protected:

    /*--- Basic stellar properties ---*/
    double luminosity;          // watts
    double surfaceTemperature;  // kelvin
    double radiationReach;      // meters

    /*--- Classification & state ---*/
    SpectralType spectralType;
    EvolutionaryStage evolutionaryStage;

    /*--- Activity & variability ---*/
    double activityLevel;    // 0.0 (calm) -> 1.0 (violent)
    double flareProbability;  // solar explosion likelihood
    double flareIntensity; 
    double flareRadius;

    /*--- Age & lifecycle ---*/
    double age;  // years
    double lifespan; // years

public:
    /*--- Constructors & destructors ---*/
    using CelestialBody::CelestialBody; // Inherit constructors
    virtual ~Star() = default;

    /*--- Getters & setters  || Accessors ---*/
    double getLuminosity() const { return luminosity; }
    double getSurfaceTemperature() const { return surfaceTemperature; }
    SpectralType getSpectralType() const { return spectralType; }
    EvolutionaryStage getEvolutionaryStage() const { return evolutionaryStage; }
    double getAge() const { return age; }
    double getActivityLevel() const { return activityLevel; }
    void updateActivityLevel(double newLevel) { activityLevel = newLevel; }

    /*--- Mutators ---*/
    void setLuminosity(double L) { luminosity = L; }
    void setSurfaceTemperature(double T) { surfaceTemperature = T; }
    void setSpectralType(SpectralType s) { spectralType = s; }
    void setEvolutionaryStage(EvolutionaryStage e) { evolutionaryStage = e; }

    /*--- Behavior & dynamics ---*/
    void simulateFlareEvent();
    double irradianceAtDistance(double distance) const;

};

#endif // SOLARSYS_CORE_CELESTIAL_STAR_H 