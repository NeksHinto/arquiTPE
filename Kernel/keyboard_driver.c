#include <keyboard_driver.h>
#include <std_buffers.h>

#define CAPS_LOCK         0x3A
#define R_SHIFT           0x36
#define R_SHIFT_REALEASE  0xB6
#define L_SHIFT           0x2A
#define L_SHIFT_REALEASE  0xAA

unsigned char keyboard[] = { 0, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
BACKSPACE,TAB, 'q', 'w','e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', ENTER, 0,'a', 's', 'd', 'f', 'g', 'h',
'j', 'k', 'l', ';', '\'', 0, LEFT_SHIFT,'\\','z', 'x', 'c', 'v', 'b', 'n', 'm', ',',
'.', '/', RIGHT_SHIFT, '*', ALT_GR,SPACE, BLOQ_MAYUS_KEY,F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,
NUM_LOCK, SCROLL_LOCK,HOME, UP, REPAG,'-', LEFT, 0, RIGHT, '+', END, DOWN,AVPAG, INSERT,
SUPR, 0, 0, 0, F11, F12 };

unsigned char shifted_keyboard[] = { 0, ESC, '!', '@', '#', '$', '%','^', '&', '*', '(', ')', '_', '+', BACKSPACE,TAB,'Q',
'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', ENTER, 0,'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':','"',
 '|', LEFT_SHIFT, '>','Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, 0,ALT_GR,SPACE,
 BLOQ_MAYUS_KEY,F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, NUM_LOCK,SCROLL_LOCK,HOME, UP, REPAG, '-', LEFT,
 0, RIGHT, '+', END, DOWN,AVPAG, INSERT, SUPR, 0, 0, '>', F11, F12 };

 unsigned char upper_case_keys[] = { 0, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
 BACKSPACE,TAB, 'Q', 'W','E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', ENTER, 0,'A', 'S', 'D', 'F', 'G', 'H',
 'J', 'K', 'L', ';', '\'', 0, LEFT_SHIFT,'\\','Z', 'X', 'C', 'V', 'B', 'N', 'M', ',',
 '.', '/', RIGHT_SHIFT, '*', ALT_GR,SPACE, BLOQ_MAYUS_KEY,F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,
 NUM_LOCK, SCROLL_LOCK,HOME, UP, REPAG,'-', LEFT, 0, RIGHT, '+', END, DOWN,AVPAG, INSERT,
 SUPR, 0, 0, 0, F11, F12 };

int caps_lock = 0;
int shift = 0;

// function that manages the keyboard
void keyboard_handler() {
	unsigned char key = _pressed_key();
	if(key == R_SHIFT || key == L_SHIFT)
		shift = 1;
	else if(key == R_SHIFT_REALEASE || key == L_SHIFT_REALEASE)
		shift = 0;
	else if(key == CAPS_LOCK)
		caps_lock = !caps_lock;

	//returns if its a release or an unprintable key.
	if ((key & 0x80) != 0 || keyboard[key] == 0)
		return;

	if(caps_lock)
		write_char_in_buffer(STD_IN,upper_case_keys[key]);
	else if(shift)
		write_char_in_buffer(STD_IN,shifted_keyboard[key]);
	else
		write_char_in_buffer(STD_IN,keyboard[key]);
}

