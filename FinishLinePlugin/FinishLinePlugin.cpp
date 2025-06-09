#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include "../rF2SharedMemoryMapPlugin/Include/rF2Plugin.h"
#include "../rF2SharedMemoryMapPlugin/Include/rF2SharedMemoryMap.hpp"

// Plugin name and version
#define PLUGIN_NAME "FinishLinePlugin"
#define PLUGIN_VERSION "1.0.0"

// Global variables
static bool gPluginEnabled = true;
static bool gHasCrossedFinishLine = false;
static double gLastLapTime = 0.0;
static int gLastLapNumber = 0;

// Plugin entry point
extern "C" __declspec(dllexport) const char* __cdecl GetPluginName() { return PLUGIN_NAME; }
extern "C" __declspec(dllexport) const char* __cdecl GetPluginVersion() { return PLUGIN_VERSION; }

// Function to check if we've crossed the finish line
bool CheckFinishLineCrossing(const rF2Telemetry& telemetry, const rF2Scoring& scoring) {
    // Get player vehicle index
    int playerIdx = scoring.mScoringInfo.mPlayerVehicleIndex;
    if (playerIdx < 0 || playerIdx >= scoring.mScoringInfo.mNumVehicles)
        return false;

    const rF2VehicleScoring& playerVehicle = scoring.mVehicles[playerIdx];
    
    // Check if we've completed a new lap
    if (playerVehicle.mLapNumber > gLastLapNumber) {
        gLastLapNumber = playerVehicle.mLapNumber;
        gLastLapTime = playerVehicle.mLastLapTime;
        return true;
    }
    
    return false;
}

// Function to take car off track
void TakeCarOffTrack(rF2Telemetry& telemetry, rF2Scoring& scoring) {
    // Get player vehicle index
    int playerIdx = scoring.mScoringInfo.mPlayerVehicleIndex;
    if (playerIdx < 0 || playerIdx >= scoring.mScoringInfo.mNumVehicles)
        return;

    // Set steering to full lock and apply brakes
    telemetry.mVehicles[playerIdx].mUnfilteredSteering = 1.0f;  // Full right lock
    telemetry.mVehicles[playerIdx].mFilteredThrottle = 0.0f;    // No throttle
    telemetry.mVehicles[playerIdx].mFilteredBrake = 1.0f;       // Full brake
}

// Plugin update function
extern "C" __declspec(dllexport) void __cdecl UpdateTelemetry(const rF2Telemetry* telemetry, const rF2Scoring* scoring) {
    if (!gPluginEnabled || !telemetry || !scoring)
        return;

    // Check for finish line crossing
    if (!gHasCrossedFinishLine && CheckFinishLineCrossing(*telemetry, *scoring)) {
        gHasCrossedFinishLine = true;
        // Take car off track when finish line is crossed
        TakeCarOffTrack(*telemetry, *scoring);
    }
}

// Plugin shutdown function
extern "C" __declspec(dllexport) void __cdecl Shutdown() {
    gPluginEnabled = false;
    gHasCrossedFinishLine = false;
    gLastLapTime = 0.0;
    gLastLapNumber = 0;
}

// Plugin initialization function
extern "C" __declspec(dllexport) void __cdecl Initialize() {
    gPluginEnabled = true;
    gHasCrossedFinishLine = false;
    gLastLapTime = 0.0;
    gLastLapNumber = 0;
} 