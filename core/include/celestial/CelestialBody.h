#ifndef SOLARSYS_CORE_CELESTIAL_CELESTIAL_BODY_H
#define SOLARSYS_CORE_CELESTIAL_CELESTIAL_BODY_H

#include <string>

class CelestialBody {
public:
    /*--- Body type enum (public for external access) ---*/
    enum class BodyType { PLANET, STAR, MOON, DWARF_PLANET, ASTEROID, COMET, ARTIFICIAL };

private:
    /*---Identity---*/
    int id;
    std::string name;
    BodyType type;

    /*---Physical properties---*/
    double mass;               // kilograms
    double radius;             // meters

    /*---Spatial state---*/
    double position;
    double velocity;

public:
    /*--- Constructors & Destructors ---*/
    CelestialBody(
        int id_,
        const std::string& name_,
        BodyType type_,
        double mass_ = 0.0,
        double radius_ = 0.0,
        double position_ = 0.0,
        double velocity_ = 0.0)
        : id(id_), name(name_), type(type_), mass(mass_), radius(radius_), position(position_), velocity(velocity_) {}
    
    virtual ~CelestialBody() = default;

    /*--- Getters & Setters ---*/
    int getId() const { return id; }
    std::string getName() const { return name; }
    BodyType getType() const { return type; }
    double getMass() const { return mass; }
    double getRadius() const { return radius; }
    double getPosition() const { return position; }
    double getVelocity() const { return velocity; }
};

#endif // SOLARSYS_CORE_CELESTIAL_CELESTIAL_BODY_H