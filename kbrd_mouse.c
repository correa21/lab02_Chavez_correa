/*
 * kbrd_mouse_task.c
 *
 *  Created on: Apr 25, 2020
 *      Author: armando
 */


#include <kbrd_mouse.h>

#define KEYBOARD_DELAY 900000U
#define MOUSE_DELAY 10000U


typedef enum {
	STATE_0,
	STATE_1,
	STATE_2,
	STATE_3,
	STATE_4,
	STATE_5,
	STATE_6,
	STATE_7,
	STATE_8,
	STATE_9,
	STATE_10,
	STATE_11,
	STATE_12,
	STATE_13,
	STATE_14,
	STATE_15,
}state_t;

static state_t state_g = STATE_0;

static int8_t x = 0U;
static int8_t y = 0U;

static void delay(uint32_t max)
{
	uint32_t delay_counter = 0;
	while (max > delay_counter)
		delay_counter++;
}


Boolean_t squareTest(uint8_t* MouseOrKeybuffer)
{
	static Boolean_t flag = FALSE;
	switch (state_g)
	{
		case STATE_0:
			/* Move right */
			MouseOrKeybuffer[0] = 1U;
			MouseOrKeybuffer[2] = 2U;
			MouseOrKeybuffer[3] = 0U;

			x++;
			if (x > 99U) {
				state_g++;
			}
			break;

		case STATE_1:
			/* Move down */
			MouseOrKeybuffer[0] = 1U;
			MouseOrKeybuffer[2] = 0U;
			MouseOrKeybuffer[3] = 2U;
			y++;
			if (y > 99U) {
				state_g++;
			}
			break;
		case STATE_2:
			/* Move left */
			MouseOrKeybuffer[0] = 1U;
			MouseOrKeybuffer[2] = (uint8_t) (-2);
			MouseOrKeybuffer[3] = 0U;
			x--;
			if (x < 2U) {
				state_g++;
			}
			break;
		case STATE_3:
			/* Move up */
			MouseOrKeybuffer[0] = 1U;
			MouseOrKeybuffer[2] = 0U;
			MouseOrKeybuffer[3] = (uint8_t) (-2);
			y--;
			if (y < 2U) {
				state_g = STATE_0;
				flag = TRUE;
			}
			break;
		default:
			break;
		}
	return flag;
}

Boolean_t openPaint(uint8_t* MouseOrKeybuffer)
{
	static Boolean_t flag = FALSE;
	switch (state_g)
	{
	case STATE_0:
		/* WINDOWS + R*/
		MouseOrKeybuffer[3] = KEY_LEFT_GUI;
		MouseOrKeybuffer[4] = KEY_R;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_1:
		/* write M*/
		MouseOrKeybuffer[3] = KEY_M;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_2:
		/* write S*/
		MouseOrKeybuffer[3] = KEY_S;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_3:
		/* write P*/
		MouseOrKeybuffer[3] = KEY_P;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_4:
		/* write A*/
		MouseOrKeybuffer[3] = KEY_A;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_5:
		/* write I*/
		MouseOrKeybuffer[3] = KEY_I;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_6:
		/* write N*/
		MouseOrKeybuffer[3] = KEY_N;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_7:
		/* write T*/
		MouseOrKeybuffer[3] = KEY_T;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_8:
		/* ENTER*/
		MouseOrKeybuffer[3] = KEY_ENTER;
		delay(KEYBOARD_DELAY);
		break;
	default:
		break;
	}

	if (state_g == STATE_9)
	{
		delay(10 * KEYBOARD_DELAY);
		state_g = STATE_0;
		flag = TRUE;

	}
	else
	{
		delay(KEYBOARD_DELAY);
		state_g++;
	}
	return flag;

}

Boolean_t drawFigure(uint8_t* MouseOrKeybuffer)
{
	static Boolean_t flag = FALSE;

	switch (state_g) {
	case STATE_0:
		/* Move right */
		MouseOrKeybuffer[1] = 1U;
		MouseOrKeybuffer[2] = 2U;
		MouseOrKeybuffer[3] = 0U;

		x++;
		if (x > 99U) {
			state_g++;
		}
		break;

	case STATE_1:
		/* Move down */
		MouseOrKeybuffer[1] = 1U;
		MouseOrKeybuffer[2] = 0U;
		MouseOrKeybuffer[3] = 2U;
		y++;
		if (y > 99U) {
			state_g++;
		}
		break;
	case STATE_2:
		/* Move left */
		MouseOrKeybuffer[1] = 1U;
		MouseOrKeybuffer[2] = (uint8_t) (-2);
		MouseOrKeybuffer[3] = 0U;
		x--;
		if (x < 2U) {
			state_g++;
		}
		break;
	case STATE_3:
		/* Move up */
		MouseOrKeybuffer[1] = 1U;
		MouseOrKeybuffer[2] = 0U;
		MouseOrKeybuffer[3] = (uint8_t) (-2);
		y--;
		if (y < 2U) {
			state_g++;
		}
		break;
	case STATE_4:
		/* CLICK */
		MouseOrKeybuffer[0] = 1U;
		MouseOrKeybuffer[2] = 0U;
		MouseOrKeybuffer[3] = 0U;
		y--;
		if (y < 2U) {
			state_g = STATE_0;
			flag = TRUE;
		}
		break;
	default:
		break;
	}

	return flag;
}

Boolean_t openNotepad(uint8_t* MouseOrKeybuffer)
{
	static Boolean_t flag = FALSE;
	static direction_t direction = LEFT;
	switch (state_g) {
	case STATE_0:
		/* WINDOWS + R*/
		MouseOrKeybuffer[3] = KEY_LEFT_GUI;
		MouseOrKeybuffer[4] = KEY_R;

		break;
	case STATE_1:
		/* write N*/
		MouseOrKeybuffer[3] = KEY_N;
		break;
	case STATE_2:
		/* write O*/
		MouseOrKeybuffer[3] = KEY_O;
		break;
	case STATE_3:
		/* write T*/
		MouseOrKeybuffer[3] = KEY_T;
		break;
	case STATE_4:
		/* write E*/
		MouseOrKeybuffer[3] = KEY_E;
		break;
	case STATE_5:
		/* write P*/
		MouseOrKeybuffer[3] = KEY_P;
		break;
	case STATE_6:
		/* write A*/
		MouseOrKeybuffer[3] = KEY_A;
		break;
	case STATE_7:
		/* write D*/
		MouseOrKeybuffer[3] = KEY_D;
		break;
	case STATE_8:
		/* ENTER*/
		MouseOrKeybuffer[3] = KEY_ENTER;
		break;
	case STATE_9:
		//notepad 1
		if (LEFT == direction)
		{
			/* CTRL + <- */
			MouseOrKeybuffer[3] = KEY_LEFT_GUI;
			MouseOrKeybuffer[4] = KEY_LEFTARROW;
			break;
		}
		else
		{ //notepad 2
			/* CTRL + ->*/
			MouseOrKeybuffer[3] = KEY_LEFT_GUI;
			MouseOrKeybuffer[4] = KEY_RIGHTARROW;
			break;
		}
	default:
		break;
	}

	if (state_g == STATE_10 && direction == LEFT) {
		direction = RIGHT;
		state_g = STATE_0;
	} else if (state_g == STATE_10 && direction == RIGHT) {
		state_g = STATE_0;
		direction = LEFT;
		flag = TRUE;
	} else {
		state_g++;
	}
	delay(KEYBOARD_DELAY);
	return flag;
}

Boolean_t moveMouse(uint8_t* MouseOrKeybuffer, direction_t direction)
{
	static Boolean_t flag = FALSE;

	if(LEFT == direction)
	{
		/* Move left */
		MouseOrKeybuffer[0] = 1U;
		MouseOrKeybuffer[2] = (uint8_t) (-2);
		MouseOrKeybuffer[3] = 0U;
		x--;
		if (x < 2U)
		{
			state_g++;
		}
	}
	else
	{
		/* Move right */
		MouseOrKeybuffer[0] = 1U;
		MouseOrKeybuffer[2] = 2U;
		MouseOrKeybuffer[3] = 0U;

		x++;
		if (x > 99U)
		{
			state_g++;
		}
	}
	if (STATE_0 != state_g)
	{
		/* Click */
		MouseOrKeybuffer[1] = 1U;
		MouseOrKeybuffer[2] = 0U;
		MouseOrKeybuffer[3] = 0U;
		delay(MOUSE_DELAY);
		state_g = STATE_0;
		flag = TRUE;
	}
	return flag;
}

Boolean_t writeText(uint8_t* MouseOrKeybuffer)
{
	static Boolean_t flag = FALSE;

	switch (state_g)
	{
	case STATE_0:
		/*  write H*/
		MouseOrKeybuffer[3] = KEY_H;
		break;
	case STATE_1:
		/*  write A*/
		MouseOrKeybuffer[3] = KEY_A;
		break;
	case STATE_2:
		/*  write I*/
		MouseOrKeybuffer[3] = KEY_I;
		break;
	case STATE_3:
		/*  write L*/
		MouseOrKeybuffer[3] = KEY_L;
		break;
	case STATE_4:
		/*  SPACEBAR */
		MouseOrKeybuffer[3] = KEY_SPACEBAR;
		break;
	case STATE_5:
		/*  write P*/
		MouseOrKeybuffer[3] = KEY_P;
		break;
	case STATE_6:
		/*  write I*/
		MouseOrKeybuffer[3] = KEY_I;
		break;
	case STATE_7:
		/*  write Z*/
		MouseOrKeybuffer[3] = KEY_Z;
		break;
	case STATE_8:
		/*  write A*/
		MouseOrKeybuffer[3] = KEY_A;
		break;
	case STATE_9:
		/*  write N*/
		MouseOrKeybuffer[3] = KEY_N;
		break;
	case STATE_10:
		/*  write O*/
		MouseOrKeybuffer[3] = KEY_O;
		break;
	default:
		break;
	}

	if (state_g == STATE_12) {
		state_g = STATE_0;
		flag = TRUE;
		delay(10 * KEYBOARD_DELAY);
	} else {
		state_g++;
		delay(KEYBOARD_DELAY);
	}

	return flag;
}



Boolean_t copyText(uint8_t* MouseOrKeybuffer)
{
	static Boolean_t flag = FALSE;

	switch (state_g) {
	case STATE_0:
		/* CRTL */
		MouseOrKeybuffer[3] = KEY_LEFTCONTROL;
		/* DependS on the language of the computer, it could be KEY_A or KEY_E*/
		MouseOrKeybuffer[4] = KEY_A;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_2:
		delay(10 * KEYBOARD_DELAY);
		break;
	case STATE_3:
		/*  CTRL + C*/
		MouseOrKeybuffer[3] = KEY_LEFTCONTROL;
		MouseOrKeybuffer[4] = KEY_C;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_4:
		delay(10 * KEYBOARD_DELAY);
		flag = TRUE;
		break;
	default:
		break;
	}

	if (state_g == STATE_4)
	{
		state_g = STATE_0;
	}
	else
	{
		state_g++;
	}

	return flag;
}

Boolean_t pasteText(uint8_t* MouseOrKeybuffer)
{
	static Boolean_t flag = FALSE;

	switch (state_g)
	{
		case STATE_0:
			MouseOrKeybuffer[3] = KEY_LEFTCONTROL;
			MouseOrKeybuffer[4] = KEY_V;
			delay(KEYBOARD_DELAY);

			break;
		case STATE_2:
			delay(10 * KEYBOARD_DELAY);
			flag = TRUE;
			break;
		default:
			break;
	}

	if (state_g == STATE_2) {
		state_g = STATE_0;
	} else {
		state_g++;
	}

	return flag;
}
