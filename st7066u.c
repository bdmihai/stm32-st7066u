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

#include <stdint.h>
#include "st7066u.h"

st7066u_hw_control_t hw;

void st7066u_init(st7066u_hw_control_t hw_control)
{
    hw = hw_control;
    hw.config_control_out();
    hw.config_data_out();
    hw.e_low();
    hw.rs_low();
    hw.delay_us(42000);
}

static void send_command(uint8_t command)
{
    hw.rs_low();
    hw.data_wr(command);
    hw.e_high();
    hw.delay_us(1);
    hw.e_low();
}

static void send_data(uint8_t data)
{
    hw.rs_high();
    hw.data_wr(data);
    hw.e_high();
    hw.delay_us(1);
    hw.e_low();
    hw.rs_low();
}

void st7066u_write(char data)
{
    send_data(data);
    hw.delay_us(37);
}

void st7066u_write_str(char *str)
{
    while (*str != 0) {
        st7066u_write(*str);
        str++;
    }
}

void st7066u_cmd_clear_display()
{
    send_command(ST7066U_CMD_CLEAR_DISPLAY);
    hw.delay_us(1520);
}

void st7066u_cmd_return_home()
{
    send_command(ST7066U_CMD_RETURN_HOME);
    hw.delay_us(1520);
}

void st7066u_cmd_entry_mode(uint8_t increment, uint8_t shift)
{
    send_command(ST7066U_CMD_ENTRY_MODE | increment | shift);
    hw.delay_us(37);
}

void st7066u_cmd_on_off(uint8_t display, uint8_t cursor, uint8_t cursor_position)
{
    send_command(ST7066U_CMD_ON_OFF | display | cursor | cursor_position);
    hw.delay_us(37);
}

void st7066u_cmd_shift(uint8_t screen_or_cursor, uint8_t right_or_left)
{
    send_command(ST7066U_CMD_SHIFT | screen_or_cursor | right_or_left);
    hw.delay_us(37);
}

void st7066u_cmd_function_set(uint8_t bits, uint8_t lines, uint8_t size)
{
    send_command(ST7066U_CMD_FUNCTION_SET | bits | lines | size);
    hw.delay_us(37);
}

void st7066u_cmd_set_cgram(uint8_t address)
{
    send_command(ST7066U_CMD_SET_CGRAM | (address & 0x3F));
    hw.delay_us(37);
}

void st7066u_cmd_set_ddram(uint8_t address)
{
    send_command(ST7066U_CMD_SET_DDRAM | (address & 0x7F));
    hw.delay_us(37);
}
