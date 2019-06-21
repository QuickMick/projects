/* See the file "LICENSE" for the full license governing this code. */

#include "HydroSense_pca9634.h"

static const uint8_t HydroSense_led_map[] = {2,  // signal strength green
                                             6,  // gps green
                                             7}; // error

HydroSense_pca9634::HydroSense_pca9634(uint8_t address)
{
    _address = address;
    _on_value = 50;
}

void HydroSense_pca9634::begin()
{
    // initalize all leds to default PWM control
    int i;
    write_reg(PCA9634_REG_MODE1, 0);
    write_reg(PCA9634_REG_MODE2, 0x16); // INVRT | OUTDRV | OUTNE1
    write_reg(PCA9634_REG_LEDOUT0, PCA9634_ALL_LED_TO_PWM);
    write_reg(PCA9634_REG_LEDOUT1, PCA9634_ALL_LED_TO_PWM);
    for (i = 0; i < 8; i++)
    {
        set_brightness(i, 0);
    }
}

void HydroSense_pca9634::set_on_value(uint8_t on)
{
    _on_value = on;
}

uint8_t HydroSense_pca9634::set_mode1(uint8_t mode1)
{
    return write_reg(PCA9634_REG_MODE1, mode1);
}

uint8_t HydroSense_pca9634::set_mode2(uint8_t mode2)
{
    return write_reg(PCA9634_REG_MODE2, mode2);
}

uint8_t HydroSense_pca9634::set_brightness(uint8_t led, uint8_t duty_cycle)
{
    // limit led to a 3-bit unsigned value.
    return write_reg(PCA9634_REG_PWM0 + ((uint8_t)(led & 0x7)),
                     duty_cycle);
}

uint8_t HydroSense_pca9634::set_led(HydroSense_led_name led,
                                    HydroSense_led_color color)
{
    uint8_t i = HydroSense_led_map[led]; // green, yellow, red
    switch (led)
    {
    case LED_SIGNAL:
    case LED_GPS:
        // these are both organized as g/y/r starting at i
        set_brightness(i, (color == LED_GREEN) ? _on_value : 0);
        set_brightness(i - 1, (color == LED_YELLOW) ? _on_value : 0);
        set_brightness(i - 2, (color == LED_RED) ? _on_value : 0);
        break;
    case LED_ERROR:
        // only one led (red), it's either on or off
        set_brightness(i, (color == LED_RED) ? _on_value : 0);
        break;
    default:
        return -1;
    }
}

uint8_t HydroSense_pca9634::write_reg(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(value);
    return Wire.endTransmission();
}
