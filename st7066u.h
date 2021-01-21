/*_____________________________________________________________________________
 │                                                                            |
 │ COPYRIGHT (C) 2020 Mihai Baneu                                             |
 │                                                                            |
 | Permission is hereby  granted,  free of charge,  to any person obtaining a |
 | copy of this software and associated documentation files (the "Software"), |
 | to deal in the Software without restriction,  including without limitation |
 | the rights to  use, copy, modify, merge, publish, distribute,  sublicense, |
 | and/or sell copies  of  the Software, and to permit  persons to  whom  the |
 | Software is furnished to do so, subject to the following conditions:       |
 |                                                                            |
 | The above  copyright notice  and this permission notice  shall be included |
 | in all copies or substantial portions of the Software.                     |
 |                                                                            |
 | THE SOFTWARE IS PROVIDED  "AS IS",  WITHOUT WARRANTY OF ANY KIND,  EXPRESS |
 | OR   IMPLIED,   INCLUDING   BUT   NOT   LIMITED   TO   THE  WARRANTIES  OF |
 | MERCHANTABILITY,  FITNESS FOR  A  PARTICULAR  PURPOSE AND NONINFRINGEMENT. |
 | IN NO  EVENT SHALL  THE AUTHORS  OR  COPYRIGHT  HOLDERS  BE LIABLE FOR ANY |
 | CLAIM, DAMAGES OR OTHER LIABILITY,  WHETHER IN AN ACTION OF CONTRACT, TORT |
 | OR OTHERWISE, ARISING FROM,  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR  |
 | THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                 |
 |____________________________________________________________________________|
 |                                                                            |
 |  Author: Mihai Baneu                           Last modified: 17.Dec.2020  |
 |                                                                            |
 |___________________________________________________________________________*/
 
#pragma once

/* available commands */
#define ST7066U_CMD_CLEAR_DISPLAY                   0x01
#define ST7066U_CMD_RETURN_HOME                     0x02
#define ST7066U_CMD_ENTRY_MODE                      0x04
#define ST7066U_CMD_ON_OFF                          0x08
#define ST7066U_CMD_SHIFT                           0x10
#define ST7066U_CMD_FUNCTION_SET                    0x20
#define ST7066U_CMD_SET_CGRAM                       0x40
#define ST7066U_CMD_SET_DDRAM                       0x80

/* command entry mode */
#define ST7066U_INCREMENT_ADDRESS                   0b00000010
#define ST7066U_DECREMENT_ADDRESS                   0
#define ST7066U_SHIFT_ENABLED                       0b00000001
#define ST7066U_SHIFT_DISABLED                      0

/* display on/of and cursor configuration */
#define ST7066U_DISPLAY_ON                          0b00000100
#define ST7066U_DISPLAY_OFF                         0
#define ST7066U_CURSOR_ON                           0b00000010
#define ST7066U_CURSOR_OFF                          0
#define ST7066U_CURSOR_POSITION_ON                  0b00000001
#define ST7066U_CURSOR_POSITION_OFF                 0

/* screen or cursor shift */
#define ST7066U_SHIFT_SCREEN                        0b00001000
#define ST7066U_SHIFT_CURSOR                        0
#define ST7066U_SHIFT_RIGHT                         0b00000100
#define ST7066U_SHIFT_LEFT                          0

/* display functional settings */
#define ST7066U_8_BITS_DATA                         0b00010000
#define ST7066U_4_BITS_DATA                         0
#define ST7066U_2_LINE_DISPLAY                      0b00001000
#define ST7066U_1_LINE_DISPLAY                      0
#define ST7066U_5x11_SIZE                           0b00000100
#define ST7066U_5x8_SIZE                            0

typedef void (*st7066u_config_func_t)();
typedef void (*st7066u_set_func_t)();
typedef void (*st7066u_write_func_t)(const uint8_t );
typedef uint8_t (*st7066u_read_func_t)();
typedef void (*st7066u_delay_us)(const uint32_t);

typedef struct st7066u_hw_control_t {
    st7066u_config_func_t config_control_out;
    st7066u_config_func_t config_data_out;
    st7066u_config_func_t config_data_in;
    st7066u_set_func_t e_high;
    st7066u_set_func_t e_low;
    st7066u_set_func_t rs_high;
    st7066u_set_func_t rs_low;
    st7066u_write_func_t data_wr;
    st7066u_read_func_t data_rd;
    st7066u_delay_us delay_us;
} st7066u_hw_control_t;

/* basic communication */
void st7066u_init(st7066u_hw_control_t hw_control);
void st7066u_write(char data);
void st7066u_write_str(char *str);

/* simple command that can be processed by the display */
void st7066u_cmd_clear_display();
void st7066u_cmd_return_home();
void st7066u_cmd_entry_mode(uint8_t increment, uint8_t shift);
void st7066u_cmd_on_off(uint8_t display, uint8_t cursor, uint8_t cursor_position);
void st7066u_cmd_shift(uint8_t screen_or_cursor, uint8_t right_or_left);
void st7066u_cmd_function_set(uint8_t bits, uint8_t lines, uint8_t size);
void st7066u_cmd_set_cgram(uint8_t address);
void st7066u_cmd_set_ddram(uint8_t address);
