#include "../../include/celestial/Asteroid.h"

// Asteroid is header-only with inline implementations
// Placeholder for future asteroid-specific calculations

// Example: Estimate asteroid density from composition
double estimateDensity(const std::string& composition) {
    if (composition == "Metallic" || composition == "M-type") {
        return 5000.0;  // kg/m³
    } else if (composition == "Silicate" || composition == "S-type") {
        return 2700.0;
    } else if (composition == "Carbonaceous" || composition == "C-type") {
        return 1300.0;
    }
    return 2000.0;  // default
}