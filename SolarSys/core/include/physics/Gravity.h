#ifndef SOLARSYS_CORE_PHYSICS_GRAVITY_H
#define SOLARSYS_CORE_PHYSICS_GRAVITY_H

#include <cmath>
#include <array>

/*--- Physical constants ---*/
namespace PhysicsConstants {
    constexpr double G = 6.67430e-11;
    constexpr double C = 299792458.0;
    constexpr double AU = 1.495978707e11;
    constexpr double SOLAR_MASS = 1.989e30;
    constexpr double EARTH_MASS = 5.972e24;
}

/*--- 3D Vector for positions and velocities ---*/
struct Vec3 {
    double x, y, z;

    Vec3(double x_ = 0.0, double y_ = 0.0, double z_ = 0.0) : x(x_), y(y_), z(z_) {}

    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(double s) const { return Vec3(x * s, y * s, z * s); }
    Vec3 operator/(double s) const { return Vec3(x / s, y / s, z / s); }
    Vec3& operator+=(const Vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vec3& operator-=(const Vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }

    double magnitude() const { return std::sqrt(x*x + y*y + z*z); }
    double magnitudeSquared() const { return x*x + y*y + z*z; }
    Vec3 normalized() const { 
        double m = magnitude();
        return (m > 0) ? *this / m : Vec3();
    }
    double dot(const Vec3& v) const { return x*v.x + y*v.y + z*v.z; }
    Vec3 cross(const Vec3& v) const {
        return Vec3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }
};

class Gravity {
public:
    /*--- Gravitational force between two bodies ---*/
    static Vec3 computeForce(double mass1, double mass2, const Vec3& pos1, const Vec3& pos2) {
        Vec3 r = pos2 - pos1;
        double distSq = r.magnitudeSquared();
        
        if (distSq < 1e-10) return Vec3();
        
        double forceMag = (PhysicsConstants::G * mass1 * mass2) / distSq;
        
        return r.normalized() * forceMag;
    }

    /*--- Gravitational acceleration on body at pos1 due to body at pos2 ---*/
    static Vec3 computeAcceleration(double mass2, const Vec3& pos1, const Vec3& pos2) {
        Vec3 r = pos2 - pos1;
        double distSq = r.magnitudeSquared();
        
        if (distSq < 1e-10) return Vec3();
        
        double accelMag = (PhysicsConstants::G * mass2) / distSq;
        
        return r.normalized() * accelMag;
    }

    /*--- Gravitational potential energy ---*/
    static double computePotentialEnergy(double mass1, double mass2, const Vec3& pos1, const Vec3& pos2) {
        double dist = (pos2 - pos1).magnitude();
        if (dist < 1e-10) return 0.0;
        return -(PhysicsConstants::G * mass1 * mass2) / dist;
    }

    /*--- Escape velocity from a body ---*/
    static double escapeVelocity(double mass, double radius) {
        return std::sqrt((2.0 * PhysicsConstants::G * mass) / radius);
    }

    /*--- Orbital velocity for circular orbit ---*/
    static double circularOrbitVelocity(double centralMass, double orbitalRadius) {
        return std::sqrt((PhysicsConstants::G * centralMass) / orbitalRadius);
    }

    /*--- Sphere of influence (Hill sphere approximation) ---*/
    static double hillSphereRadius(double bodyMass, double parentMass, double semiMajorAxis) {
        return semiMajorAxis * std::cbrt(bodyMass / (3.0 * parentMass));
    }
};

#endif // SOLARSYS_CORE_PHYSICS_GRAVITY_H