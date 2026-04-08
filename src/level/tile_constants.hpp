#pragma once
#include "raymath.h"

const int TILE_SIZE = 10;

const Quaternion DIRECTION_NORTH = QuaternionFromEuler(90.0f * DEG2RAD, 180.0f * DEG2RAD, 0.0f);
const Quaternion DIRECTION_EAST = QuaternionFromEuler(90.0f * DEG2RAD, 90.0f * DEG2RAD, 0.0f);
const Quaternion DIRECTION_SOUTH = QuaternionFromEuler(90.0f * DEG2RAD, 0.0f * DEG2RAD, 0.0f);
const Quaternion DIRECTION_WEST = QuaternionFromEuler(90.0f * DEG2RAD, 270.0f * DEG2RAD, 0.0f);