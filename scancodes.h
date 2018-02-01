/* scancodes.h --- 
 * 
 * Filename: scancodes.h
 * Description: An enum to translate keyboard scancodes to the key represented.
 * Author: Jacob Garby
 * URL: https://github.com/j4cobgarby/atomic-kernel/scancodes.h
 * 
 */

/* Code: */


#ifndef SCANCODES_H
#define SCANCODES_H

typedef enum {
    F9 = 0x01,
    F5 = 0x03,
    F3,
    F1,
    F2,
    F12,
    F10 = 0x09,
    F8,
    F6,
    F4,
    TAB,
    BACKTICK,
    L_ALT = 0x11,
    L_SHIFT,
    L_CTRL = 0x14,
    Q,
    ONE,
    Z = 0x1a,
    S,
    A,
    W,
    TWO,
    C = 0x21,
    X,
    D,
    E,
    NUM_FOUR,
    THREE,
    SPACEBAR = 0x29,
    V,
    F,
    T,
    R,
    FIVE,
    N = 0x31,
    B,
    H,
    G,
    Y,
    SIX,
    M = 0x3a,
    J,
    U,
    SEVEN,
    EIGHT,
    COMMA = 0x41,
    K,
    I,
    O,
    ZERO,
    NINE,
    DOT = 0x49,
    FORWARD_SLASH,
    L,
    SEMI_COLON,
    P,
    HYPHON,
    APOSTROPHE = 0x52,
    SQUARE_BRACKET_LEFT = 0x54,
    EQUALS,
    CAPS_LOCK = 0x58,
    R_SHIFT,
    ENTER,
    SQUARE_BRACKET_RIGHT,
    BACKWARDS_SLASH = 0x5d,
    BACKSPACE = 0x66,
    NUMPAD_ONE = 0x69,
    NUMPAD_FOUR = 0x6b,
    NUMPAD_SEVEN = 0x6c,
    NUMPAD_ZERO = 0x70,
    NUMPAD_DOT,
    NUMPAD_TWO,
    NUMPAD_FIVE,
    NUMPAD_SIX,
    NUMPAD_EIGHT,
    ESCAPE,
    NUM_LOCK,
    F11,
    NUMPAD_PLUS,
    NUMPAD_3,
    NUMPAD_HYPHON,
    NUMPAD_ASTERISK,
    NUMPAD_NINE,
    SCROLL_LOCK,
    F7 = 0x83
} SCANCODE;

#endif

/* scancodes.h ends here */
