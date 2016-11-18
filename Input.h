#ifndef INPUT_H
#define INPUT_H

#include "common.h"

#define INPUT_LONG_PRESS_TIME   (1 * 1000 * 1000) // 1 Second

extern int pressedButtons;
extern int currentButtons;

bool Input_HoldButtons(uint32_t);

void Input_Update();

#endif // INPUT_H
