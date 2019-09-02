////软件spi
////




#include "spi.h"


volatile uint32_t Spi_cs_port;
volatile uint8_t Spi_cs_pin;


void spi_init()		//SPI0初始化
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_6);
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_7);
}

void spi_set_cspin(uint32_t port, uint8_t pin)
{
	Spi_cs_port = port;
	Spi_cs_pin = pin;
}
void spi_cs_enable()
{
	 GPIOPinWrite(Spi_cs_port, Spi_cs_pin, 0);
}
void spi_cs_disable()
{
	 GPIOPinWrite(Spi_cs_port, Spi_cs_pin, Spi_cs_pin);
}


uint8_t SOFT_SPI_RW(uint8_t byte)
{
    uint8_t i,Temp=0;
    for(i=0;i<8;i++)     // 循环8次
    {
     			SPICLK_Clr();         //拉低时钟
     			if(byte&0x80) MOSI_Set();                             //若最到位为高，则输出高
          else       MOSI_Clr();                             //若最到位为低，则输出低
					byte <<= 1;     // 低一位移位到最高位
					SPICLK_Set();     //拉高时钟
					Temp <<= 1;     //数据左移
					if(MISO_Read()) Temp++;     //若从从机接收到高电平，数据自加一
					SPICLK_Clr();     //拉低时钟
    }
       return (Temp);     //返回数据
}

void spi_write_reg(uint8_t reg, uint8_t data)
{
	spi_cs_enable();
	SOFT_SPI_RW(reg);
	SOFT_SPI_RW(data);
	spi_cs_disable();
}

uint8_t spi_read_reg(uint8_t reg)
{
	uint8_t data;

	spi_cs_enable();
	SOFT_SPI_RW(reg);
	data = SOFT_SPI_RW(0);
	spi_cs_disable();

	return data;
}

//在指定位置写指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
void spi_write_buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
	uint8_t i;
	spi_cs_enable();
	SOFT_SPI_RW(reg);
	for(i = 0; i < len; i++)
	{
		SOFT_SPI_RW(*pBuf++);
	}
	spi_cs_disable();
}
void spi_read_buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
	uint8_t i;
	spi_cs_enable();
	SOFT_SPI_RW(reg);
	for(i = 0; i < len; i++)
	{
		pBuf[i] = SOFT_SPI_RW(0xff);
	}
	spi_cs_disable();
}


