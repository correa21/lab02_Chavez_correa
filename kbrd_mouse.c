/*
 * kbrd_mouse_task.c
 *
 *  Created on: Apr 25, 2020
 *      Author: armando
 */


#include <kbrd_mouse.h>

#define KEYBOARD_DELAY 2000000U
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

static void realese_Key (uint8_t* keybuffer);

static state_t state_g = STATE_0;

static int8_t g_x = 0U;
static int8_t g_y = 0U;

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

			g_x++;
			if (g_x > 99U) {
				state_g++;
			}
			break;

		case STATE_1:
			/* Move down */
			MouseOrKeybuffer[0] = 1U;
			MouseOrKeybuffer[2] = 0U;
			MouseOrKeybuffer[3] = 2U;
			g_y++;
			if (g_y > 99U) {
				state_g++;
			}
			break;
		case STATE_2:
			/* Move left */
			MouseOrKeybuffer[0] = 1U;
			MouseOrKeybuffer[2] = (uint8_t) (-2);
			MouseOrKeybuffer[3] = 0U;
			g_x--;
			if (g_x < 2U) {
				state_g++;
			}
			break;
		case STATE_3:
			/* Move up */
			MouseOrKeybuffer[0] = 1U;
			MouseOrKeybuffer[2] = 0U;
			MouseOrKeybuffer[3] = (uint8_t) (-2);
			g_y--;
			if (g_y < 2U) {
				state_g = STATE_0;
				flag = TRUE;
				delay(MOUSE_DELAY);
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
		MouseOrKeybuffer[1] = MODIFERKEYS_LEFT_GUI;
		MouseOrKeybuffer[3] = KEY_R;
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
		realese_Key(MouseOrKeybuffer);
		delay(10*KEYBOARD_DELAY);
		break;
	}

	if (state_g == STATE_9)
	{

		state_g = STATE_0;
		delay(KEYBOARD_DELAY);
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

		g_x++;
		if (g_x > 99U) {
			state_g++;
		}
		break;

	case STATE_1:
		/* Move down */
		MouseOrKeybuffer[1] = 1U;
		MouseOrKeybuffer[2] = 0U;
		MouseOrKeybuffer[3] = 2U;
		g_y++;
		if (g_y > 99U) {
			state_g++;
		}
		break;
	case STATE_2:
		/* Move left */
		MouseOrKeybuffer[1] = 1U;
		MouseOrKeybuffer[2] = (uint8_t) (-2);
		MouseOrKeybuffer[3] = 0U;
		g_x--;
		if (g_x < 2U) {
			state_g++;
		}
		break;
	case STATE_3:
		/* Move up */
		MouseOrKeybuffer[1] = 1U;
		MouseOrKeybuffer[2] = 0U;
		MouseOrKeybuffer[3] = (uint8_t) (-2);
		g_y--;
		if (g_y < 2U) {
			state_g++;
		}
		break;
	case STATE_4:
		/* CLICK */
		MouseOrKeybuffer[1] = 1U;
		MouseOrKeybuffer[2] = 0U;
		MouseOrKeybuffer[3] = 0U;
		g_y--;
		if (g_y < 2U) {
			state_g++;

		}
		break;
	case STATE_5:
		MouseOrKeybuffer[1] = 0U;
		MouseOrKeybuffer[2] = 0U;
		MouseOrKeybuffer[3] = 0U;
		state_g = STATE_0;
		flag = TRUE;
		delay(MOUSE_DELAY);
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
		MouseOrKeybuffer[1] = MODIFERKEYS_LEFT_GUI;
		MouseOrKeybuffer[3] = KEY_R;
		delay(KEYBOARD_DELAY);

		break;
	case STATE_1:
		/* write N*/
		MouseOrKeybuffer[3] = KEY_N;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_2:
		/* write O*/
		MouseOrKeybuffer[3] = KEY_O;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_3:
		/* write T*/
		MouseOrKeybuffer[3] = KEY_T;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_4:
		/* write E*/
		MouseOrKeybuffer[3] = KEY_E;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_5:
		/* write P*/
		MouseOrKeybuffer[3] = KEY_P;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_6:
		/* write A*/
		MouseOrKeybuffer[3] = KEY_A;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_7:
		/* write D*/
		MouseOrKeybuffer[3] = KEY_D;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_8:
		/* ENTER*/
		MouseOrKeybuffer[3] = KEY_ENTER;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_9:
			realese_Key(MouseOrKeybuffer);
			delay(KEYBOARD_DELAY);
		break;
	case STATE_10:
		//notepad 1
		if (LEFT == direction)
		{
			/* CTRL + <- */
			MouseOrKeybuffer[1] = MODIFERKEYS_LEFT_GUI;
			MouseOrKeybuffer[3] = KEY_LEFTARROW;
			delay(KEYBOARD_DELAY);
			break;
		}
		else
		{ //notepad 2
			/* CTRL + ->*/
			MouseOrKeybuffer[1] = MODIFERKEYS_LEFT_GUI;
			MouseOrKeybuffer[3] = KEY_RIGHTARROW;
			delay(KEYBOARD_DELAY);
			break;
		}
	default:
		break;
	}

	if (state_g == STATE_10 && direction == LEFT)
	{
		direction = RIGHT;
		state_g = STATE_0;
		delay(KEYBOARD_DELAY);
	}
	else if (state_g == STATE_10 && direction == RIGHT)
	{
		state_g = STATE_0;
		delay(KEYBOARD_DELAY);
		direction = LEFT;
		flag = TRUE;
	}
	else
	{
		state_g++;
	}
	return flag;
}

Boolean_t moveMouse(uint8_t* MouseOrKeybuffer, direction_t direction)
{
	static Boolean_t flag = FALSE;

	if(RIGHT == direction)
	{
		flag = FALSE;
		switch (state_g)
		{
			case STATE_0:
				/* Move right */
				MouseOrKeybuffer[1] = 0U;
				MouseOrKeybuffer[2] = (uint8_t) (-2);
				MouseOrKeybuffer[3] = 0U;
				g_x--;
				if (g_x < 2U) {
					state_g++;
				}
				break;

			case STATE_1:
				/* click */
				MouseOrKeybuffer[1] = 1U;
				MouseOrKeybuffer[2] = 0U;
				MouseOrKeybuffer[3] = 0U;
				state_g++;
				delay(MOUSE_DELAY);
				break;
			case STATE_2:
				/* unclick */
				MouseOrKeybuffer[1] = 0U;
				MouseOrKeybuffer[2] = 0U;
				MouseOrKeybuffer[3] = 0U;
				state_g++;
				delay(MOUSE_DELAY);
				break;
			case STATE_3:
				/* unclick */
				MouseOrKeybuffer[1] = 0U;
				MouseOrKeybuffer[2] = 0U;
				MouseOrKeybuffer[3] = 0U;
				state_g = STATE_0;
				flag = TRUE;
				break;
			default:
				break;
		}
	}
	else
	{
		switch (state_g)
		{
			case STATE_0:
				/* Move left */
				MouseOrKeybuffer[1] = 0U;
				MouseOrKeybuffer[2] = 2U;
				MouseOrKeybuffer[3] = 0U;

				g_x++;
				if (g_x > 200U) {
					state_g++;
				}

				break;

			case STATE_1:
				/* click */
				MouseOrKeybuffer[1] = 1U;
				MouseOrKeybuffer[2] = 0U;
				MouseOrKeybuffer[3] = 0U;
				state_g++;
				delay(MOUSE_DELAY);
				break;
			case STATE_2:
				/* unclick */
				MouseOrKeybuffer[1] = 0U;
				MouseOrKeybuffer[2] = 0U;
				MouseOrKeybuffer[3] = 0U;
				delay(MOUSE_DELAY);
				state_g++;
				break;
			case STATE_3:
				/* unclick */
				MouseOrKeybuffer[1] = 0U;
				MouseOrKeybuffer[2] = 0U;
				MouseOrKeybuffer[3] = 0U;
				state_g = STATE_0;
				flag = TRUE;
				break;
			default:
				break;
		}
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
		delay(KEYBOARD_DELAY);
		break;
	case STATE_1:
		/*  write A*/
		MouseOrKeybuffer[3] = KEY_O;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_2:
		/*  write I*/
		MouseOrKeybuffer[3] = KEY_L;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_3:
		/*  write L*/
		MouseOrKeybuffer[3] = KEY_A;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_4:
		/*  SPACEBAR */
		MouseOrKeybuffer[3] = KEY_SPACEBAR;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_5:
		/*  write P*/
		MouseOrKeybuffer[3] = KEY_M;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_6:
		/*  write I*/
		MouseOrKeybuffer[3] = KEY_U;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_7:
		/*  write Z*/
		MouseOrKeybuffer[3] = KEY_N;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_8:
		/*  write A*/
		MouseOrKeybuffer[3] = KEY_D;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_9:
		/*  write N*/
		MouseOrKeybuffer[3] = KEY_O;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_10:
		/*  write O*/
		MouseOrKeybuffer[3] = KEY_O;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_11:
			realese_Key(MouseOrKeybuffer);
		break;
	default:
		break;
	}

	if (state_g == STATE_12) {
		state_g = STATE_0;
		realese_Key(MouseOrKeybuffer);
		flag = TRUE;
		delay(10 * KEYBOARD_DELAY);
	} else {
		state_g++;
	}

	return flag;
}

Boolean_t copyText(uint8_t* MouseOrKeybuffer)
{
	static Boolean_t flag = FALSE;

	switch (state_g) {
	case STATE_0:
		/* CRTL */
		MouseOrKeybuffer[1] = MODIFERKEYS_LEFT_CTRL;
		/* DependS on the language of the computer, it could be KEY_A or KEY_E*/
		MouseOrKeybuffer[3] = KEY_E;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_2:
		delay(10 * KEYBOARD_DELAY);
		break;
	case STATE_3:
		/*  CTRL + C*/
		MouseOrKeybuffer[1] = MODIFERKEYS_LEFT_CTRL;
		MouseOrKeybuffer[3] = KEY_C;
		delay(KEYBOARD_DELAY);
		break;
	case STATE_4:
		realese_Key(MouseOrKeybuffer);
		flag = TRUE;
		delay(KEYBOARD_DELAY);
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
			MouseOrKeybuffer[1] = MODIFERKEYS_LEFT_CTRL;
			MouseOrKeybuffer[3] = KEY_V;
			delay(KEYBOARD_DELAY);

			break;
		case STATE_2:
			realese_Key(MouseOrKeybuffer);
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


static void realese_Key (uint8_t* keybuffer)
{
	keybuffer[1] = 0U;
	keybuffer[3] = 0U;
	keybuffer[4] = 0U;
	keybuffer[5] = 0U;
}
