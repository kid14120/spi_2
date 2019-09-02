#ifndef		__SPI_H
#define		__SPI_H

#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"

#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "driverlib/ssi.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/fpu.h"
#include "driverlib/i2c.h"
#include "driverlib/pwm.h"
#include "driverlib/uart.h"
#include "driverlib/adc.h"
#include "driverlib/systick.h"
#include "driverlib/flash.h"
#include "driverlib/eeprom.h"
#include "driverlib/qei.h"



#define	SYSCTL_PERIPH_GPIO_SPI	SYSCTL_PERIPH_GPIOB
#define GPIO_PORT_SPICLK_BASE		GPIO_PORTB_BASE
#define SPICLK      						GPIO_PIN_5
#define GPIO_PORT_MOSI_BASE			GPIO_PORTB_BASE
#define MOSI      							GPIO_PIN_6
#define GPIO_PORT_MISO_BASE			GPIO_PORTB_BASE
#define MISO     							  GPIO_PIN_7
#define SPICLK_Clr()    GPIOPinWrite(GPIO_PORT_SPICLK_BASE,SPICLK, 0)//CLK
#define SPICLK_Set()  	GPIOPinWrite(GPIO_PORT_SPICLK_BASE,SPICLK, SPICLK)
#define MOSI_Clr()		GPIOPinWrite(GPIO_PORT_MOSI_BASE,MOSI, 0)//DIN
#define MOSI_Set() 	  GPIOPinWrite(GPIO_PORT_MOSI_BASE,MOSI, MOSI)
#define MISO_Clr() 		GPIOPinWrite(GPIO_PORT_MISO_BASE,MISO, 0)//RES
#define MISO_Set()		GPIOPinWrite(GPIO_PORT_MISO_BASE,MISO, MISO)
#define MISO_Read()   GPIOPinRead(GPIO_PORT_MISO_BASE,MISO)

void spi_init(void);		//SPI0≥ı ºªØ
void spi_set_cspin(uint32_t port, uint8_t pin);

void spi_write_byte(uint8_t data);
void spi_write_reg(uint8_t reg, uint8_t data);
uint8_t spi_read_reg(uint8_t reg);
void spi_write_buf(uint8_t reg, uint8_t *pBuf, uint8_t len);
void spi_read_buf(uint8_t reg, uint8_t *pBuf, uint8_t len);

static void spi_cs_disable(void);
//static uint8_t spi_rw(uint8_t data);
#endif
