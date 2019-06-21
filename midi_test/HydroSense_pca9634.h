/* See the file "LICENSE" for the full license governing this code. 
 * Alan Marchiori 2015
 * Bucknell University
 * */

#ifndef __pca9634__
#define __pca9634__


#define PCA9634_REG_MODE1		0x00		// Mode register 1
#define PCA9634_REG_MODE2		0x01		// Mode register 2
#define PCA9634_REG_PWM0		0x02		// brightness control LED0
#define PCA9634_REG_PWM1		0x03		// brightness control LED1
#define PCA9634_REG_PWM2		0x04		// brightness control LED2
#define PCA9634_REG_PWM3		0x05		// brightness control LED3
#define PCA9634_REG_PWM4		0x06		// brightness control LED4
#define PCA9634_REG_PWM5		0x07		// brightness control LED5
#define PCA9634_REG_PWM6		0x08		// brightness control LED6
#define PCA9634_REG_PWM7		0x09		// brightness control LED7
#define PCA9634_REG_GRPPWM		0x0A		// group duty cycle
#define PCA9634_REG_GRPFREQ		0x0B		// group frequency
#define PCA9634_REG_LEDOUT0		0x0C		// LED output state 0
#define PCA9634_REG_LEDOUT1		0x0D		// LED output state 1
#define PCA9634_REG_SUBADR1		0x0E		// I2C-bus subaddress 1
#define PCA9634_REG_SUBADR2		0x0F		// I2C-bus subaddress 2
#define PCA9634_REG_SUBADR3		0x10		// I2C-bus subaddress 3
#define PCA9634_REG_ALLCALLADR	0x11		// LED All I2C-bus address

#define PCA9634_ALL_LED_TO_OFF				0x00
#define PCA9634_ALL_LED_TO_ON				0x55
#define PCA9634_ALL_LED_TO_PWM				0xAA
#define PCA9634_ALL_LED_TO_GRPPWM			0xFF

#define ADDRESS_HI							0x12
#define ADDRESS_LO							0x34

#define PCA9634_ERROR_INVALID_LED           -1

#include <Arduino.h>
#include <Wire.h>
enum HydroSense_led_name { LED_SIGNAL, LED_GPS, LED_ERROR };
enum HydroSense_led_color { LED_OFF, LED_GREEN, LED_YELLOW, LED_RED };

class HydroSense_pca9634
{
    public:
        
        // address is the i2c bus adderss of the pca9634 chip
        HydroSense_pca9634(uint8_t address);

        // sets up pca9634 and turns all leds off
        void begin(void);

        // these 3 functions do writes directly to pca9634 registers
        // read that manual if you want to use them.
        uint8_t set_mode2(uint8_t mode2);
        uint8_t set_mode1(uint8_t mode1);
        uint8_t set_brightness(uint8_t led, uint8_t duty_cycle);

        // the value "on" will be written to the PWM duty cycle
        // when using the set_led function. This is how bright the
        // leds will turn on by default. The default is 50.
        // this should be in the range 0-255. 0 is off, 255 is full on.
        void set_on_value(uint8_t on);

        // set the named led/color to the current on value. 
        // The other colors in that group are turned off for you.
        uint8_t set_led ( HydroSense_led_name led,
                          HydroSense_led_color color );

    private:
        uint8_t _address;
        uint8_t _on_value;
        uint8_t write_reg(uint8_t reg, uint8_t value);     
};
#endif
