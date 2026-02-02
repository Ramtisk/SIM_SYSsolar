#ifndef SOLARSYS_CORE_TIME_TIMESYSTEM_H
#define SOLARSYS_CORE_TIME_TIMESYSTEM_H

#include <cstdint>

/*--- Time unit constants (in seconds) ---*/
namespace TimeConstants {
    constexpr double SECOND = 1.0;
    constexpr double MINUTE = 60.0;
    constexpr double HOUR = 3600.0;
    constexpr double DAY = 86400.0;
    constexpr double WEEK = 604800.0;
    constexpr double YEAR = 31557600.0;  // Julian year (365.25 days)
    constexpr double CENTURY = YEAR * 100.0;
}

class TimeSystem {
private:
    double currentTime;         // seconds since epoch (simulation start)
    double timeStep;            // seconds per simulation tick
    double timeScale;           // multiplier for time progression (1.0 = real-time)
    bool paused;
    
    uint64_t tickCount;         // total simulation ticks

public:
    /*--- Constructors ---*/
    TimeSystem(double initialTime = 0.0, double step = TimeConstants::HOUR)
        : currentTime(initialTime), timeStep(step), timeScale(1.0), paused(false), tickCount(0) {}

    /*--- Core time advancement ---*/
    void tick() {
        if (!paused) {
            currentTime += timeStep * timeScale;
            ++tickCount;
        }
    }

    void advanceBy(double seconds) {
        if (!paused) {
            currentTime += seconds * timeScale;
        }
    }

    /*--- Accessors ---*/
    double getCurrentTime() const { return currentTime; }
    double getTimeStep() const { return timeStep; }
    double getTimeScale() const { return timeScale; }
    bool isPaused() const { return paused; }
    uint64_t getTickCount() const { return tickCount; }

    /*--- Derived time values ---*/
    double getYears() const { return currentTime / TimeConstants::YEAR; }
    double getDays() const { return currentTime / TimeConstants::DAY; }
    double getHours() const { return currentTime / TimeConstants::HOUR; }

    /*--- Mutators ---*/
    void setTimeStep(double step) { timeStep = step; }
    void setTimeScale(double scale) { timeScale = scale; }
    void pause() { paused = true; }
    void resume() { paused = false; }
    void togglePause() { paused = !paused; }
    void reset() { currentTime = 0.0; tickCount = 0; }
};

#endif // SOLARSYS_CORE_TIME_TIMESYSTEM_H