//
// Created by claiff on 28.01.2022.
//

#pragma once

#include <cstdint>

struct TimingColorPart
{
	uint8_t bit[8];
};
using Timing_Part_t = TimingColorPart;

struct TimingColorFull
{
	Timing_Part_t green;
	Timing_Part_t red;
	Timing_Part_t blue;
};
using TimingColorFull_t = TimingColorFull;

static constexpr uint8_t TOH = 5;
static constexpr uint8_t T1H = 10;