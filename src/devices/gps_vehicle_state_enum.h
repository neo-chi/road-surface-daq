#pragma once

/**
 * Specifies the possible vehicle movement states.
 *
 * @idle
 * @moving
 * @unknown if the gps is not connected to satellites.
 **/
enum vehicle_state {
        idle,
        moving,
        unknown
};
