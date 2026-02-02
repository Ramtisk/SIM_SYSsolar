#ifndef SOLARSYS_CORE_PHYSICS_INTEGRATOR_H
#define SOLARSYS_CORE_PHYSICS_INTEGRATOR_H

#include "Gravity.h"
#include <vector>
#include <functional>

/*--- State of a body for integration ---*/
struct BodyState {
    int id;
    double mass;
    Vec3 position;
    Vec3 velocity;
    Vec3 acceleration;
};

/*--- Acceleration function type ---*/
using AccelerationFunc = std::function<Vec3(const BodyState&, const std::vector<BodyState>&)>;

class Integrator {
public:
    /*--- Euler method (1st order, simple but inaccurate) ---*/
    static void euler(BodyState& body, double dt, const AccelerationFunc& accelFunc, 
                      const std::vector<BodyState>& allBodies) {
        body.acceleration = accelFunc(body, allBodies);
        body.position += body.velocity * dt;
        body.velocity += body.acceleration * dt;
    }

    /*--- Symplectic Euler (better energy conservation) ---*/
    static void symplecticEuler(BodyState& body, double dt, const AccelerationFunc& accelFunc,
                                 const std::vector<BodyState>& allBodies) {
        body.acceleration = accelFunc(body, allBodies);
        body.velocity += body.acceleration * dt;
        body.position += body.velocity * dt;
    }

    /*--- Velocity Verlet (2nd order, good for orbital mechanics) ---*/
    static void velocityVerlet(BodyState& body, double dt, const AccelerationFunc& accelFunc,
                                const std::vector<BodyState>& allBodies) {
        // Half-step velocity
        Vec3 oldAccel = body.acceleration;
        body.position += body.velocity * dt + oldAccel * (0.5 * dt * dt);
        
        // Compute new acceleration
        body.acceleration = accelFunc(body, allBodies);
        
        // Complete velocity update
        body.velocity += (oldAccel + body.acceleration) * (0.5 * dt);
    }

    /*--- Runge-Kutta 4th order (high accuracy) ---*/
    static void rk4(BodyState& body, double dt, const AccelerationFunc& accelFunc,
                    const std::vector<BodyState>& allBodies) {
        BodyState temp = body;
        
        // k1
        Vec3 k1v = accelFunc(body, allBodies);
        Vec3 k1r = body.velocity;
        
        // k2
        temp.position = body.position + k1r * (dt * 0.5);
        temp.velocity = body.velocity + k1v * (dt * 0.5);
        Vec3 k2v = accelFunc(temp, allBodies);
        Vec3 k2r = temp.velocity;
        
        // k3
        temp.position = body.position + k2r * (dt * 0.5);
        temp.velocity = body.velocity + k2v * (dt * 0.5);
        Vec3 k3v = accelFunc(temp, allBodies);
        Vec3 k3r = temp.velocity;
        
        // k4
        temp.position = body.position + k3r * dt;
        temp.velocity = body.velocity + k3v * dt;
        Vec3 k4v = accelFunc(temp, allBodies);
        Vec3 k4r = temp.velocity;
        
        // Combine
        body.position += (k1r + k2r * 2.0 + k3r * 2.0 + k4r) * (dt / 6.0);
        body.velocity += (k1v + k2v * 2.0 + k3v * 2.0 + k4v) * (dt / 6.0);
        body.acceleration = accelFunc(body, allBodies);
    }

    /*--- Compute N-body gravitational acceleration ---*/
    static Vec3 nBodyAcceleration(const BodyState& body, const std::vector<BodyState>& allBodies) {
        Vec3 totalAccel;
        for (const auto& other : allBodies) {
            if (other.id != body.id) {
                totalAccel += Gravity::computeAcceleration(other.mass, body.position, other.position);
            }
        }
        return totalAccel;
    }
};

/*--- Integration method enum ---*/
enum class IntegrationMethod {
    EULER,
    SYMPLECTIC_EULER,
    VELOCITY_VERLET,
    RK4
};

#endif // SOLARSYS_CORE_PHYSICS_INTEGRATOR_H