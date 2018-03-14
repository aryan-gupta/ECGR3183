#pragma once

#include <chrono>
#include <iostream>

using clk = std::chrono::system_clock; // I am not typeing all that over and over
using namespace std::chrono_literals;

#include "controller.hpp"
#include "elevator.hpp"
#include "clock.hpp"
#include "memory.hpp"
#include "door.hpp"
#include "floor_lights.hpp"
#include "ir_sensor.hpp"

extern std::atomic_bool FireKey;
extern std::atomic_bool IRon;
extern std::atomic_bool Sound;

extern std::atomic_bool gStop;
extern std::atomic_bool gStart;

extern Elevator gLift;
extern Controller gControl;
extern Memory gMem;
extern Clock gClk;
extern FloorLights gFL;