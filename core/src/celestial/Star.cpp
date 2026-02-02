#include "../../include/celestial/Star.h"
#include "../../include/physics/Gravity.h"
#include <cmath>
#include <random>

void Star::simulateFlareEvent() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);

    // Check if flare occurs based on probability
    if (dis(gen) < flareProbability * activityLevel) {
        // Flare occurred - temporarily increase activity
        activityLevel = std::min(1.0, activityLevel + flareIntensity);
        
        // Flare intensity affects radiation reach temporarily
        radiationReach *= (1.0 + flareIntensity * 0.5);
    }
}

double Star::irradianceAtDistance(double distance) const {
    if (distance < 1e-10) return 0.0;
    
    double irradiance = luminosity / (4.0 * M_PI * distance * distance);
    irradiance *= (1.0 + 0.001 * activityLevel);
    
    return irradiance;
}