// This file is part of LEDStick_TFT.
// 
// LEDStick_TFT is free software : you can redistribute it and / or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// LEDStick_TFT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with LEDStick_TFT.If not, see <http://www.gnu.org/licenses/>.

#include "FadeBase.h"


// I prefer to calculate the current colour based on current step out of total steps. 
// Reason being - with deltas you can start getting rounding errors and having to check boundaries etc.
RGB FadeBase::calculate_current_colour(RGB sourceColour, RGB destinationColour, uint32_t current_step, uint32_t total_steps)
{
	RGB new_colour;
	new_colour.red = sourceColour.red + ((GetDifference(destinationColour.red, sourceColour.red) * (int32_t)current_step) / (int32_t)total_steps);
	new_colour.green = sourceColour.green + ((GetDifference(destinationColour.green, sourceColour.green) * (int32_t)current_step) / (int32_t)total_steps);
	new_colour.blue = sourceColour.blue + ((GetDifference(destinationColour.blue, sourceColour.blue) * (int32_t)current_step) / (int32_t)total_steps);

	return new_colour;
}

inline int32_t FadeBase::GetDifference(uint32_t first, uint32_t second)
{
	int32_t diff = first - second;
	return diff;
}
