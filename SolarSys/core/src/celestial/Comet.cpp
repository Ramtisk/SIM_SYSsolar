#include "../../include/celestial/Comet.h"
#include "../../include/physics/Gravity.h"
#include <cmath>

// Calculate if comet should have active tail based on distance to sun
bool shouldHaveActiveTail(double distanceToSun) {
    // Comets typically become active within ~3 AU of the Sun
    const double activationDistance = 3.0 * PhysicsConstants::AU;
    return distanceToSun < activationDistance;
}

// Estimate coma radius based on solar distance
double estimateComaRadius(double distanceToSun, double baseRadius) {
    // Coma grows as comet approaches sun
    const double AU = PhysicsConstants::AU;
    if (distanceToSun > 5.0 * AU) return 0.0;
    
    // Rough approximation: coma size inversely proportional to distance
    double scaleFactor = std::max(0.0, (5.0 * AU - distanceToSun) / (5.0 * AU));
    return baseRadius * 1000.0 * scaleFactor;  // Can grow to 1000x nucleus size
}