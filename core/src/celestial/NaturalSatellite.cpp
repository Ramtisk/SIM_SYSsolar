#include "../../include/celestial/NaturalSatellite.h"
#include <cmath>

// Helper function to calculate mean motion from orbital period
double calculateMeanMotionFromPeriod(double orbitalPeriod) {
    if (orbitalPeriod < 1e-10) return 0.0;
    return 2.0 * M_PI / orbitalPeriod;
}

// Helper function to check if moon is within Hill sphere of parent
bool isWithinHillSphere(double moonDistance, double hillRadius) {
    return moonDistance < hillRadius;
}