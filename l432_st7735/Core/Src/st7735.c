#include "st7735.h"
extern SPI_HandleTypeDef ST7735_SPI_PORT;
extern const uint8_t image[];

// vang D11, nau GND, xanh la A4, xanh duong A2, tim A1, do 3V3, cam D13
void ST7735_Reset()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET); //reset
	HAL_Delay(5);	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET); //reset
}


void SPI_WriteByte(uint8_t data)
{
	A0_HIGH;
  HAL_SPI_Transmit(&ST7735_SPI_PORT, &data, sizeof(data), HAL_MAX_DELAY);

}
void ST7735_sendCommand(uint8_t cmd)
{
  A0_LOW;
  HAL_SPI_Transmit(&ST7735_SPI_PORT, &cmd, sizeof(cmd), HAL_MAX_DELAY);
	
}


void ST7735_SetWindow(uint8_t x, uint8_t y, uint8_t x1, uint8_t y1)
{
	CS_LOW;
  ST7735_sendCommand(ST7735_CASET);
  SPI_WriteByte(0x00);
  SPI_WriteByte(x + ST7735_XSTART);
  SPI_WriteByte(0x00);
  SPI_WriteByte(x1 + ST7735_XSTART);

  ST7735_sendCommand(ST7735_RASET);
  SPI_WriteByte(0x00);
  SPI_WriteByte(y + ST7735_YSTART);
  SPI_WriteByte(0x00);
  SPI_WriteByte(y1 + ST7735_YSTART);

	// write to RAM
  ST7735_sendCommand(ST7735_RAMWR);
}


void ST7735_Clr(void)
{
  ST7735_SetWindow(0, 0, 160, 128);
  for(unsigned int i = 0; i < (160 * (128)); i++)
	{
    SPI_WriteByte(0x00);
    SPI_WriteByte(0x00);
  }
	CS_HIGH;
}


void inhinhanh(void)
{
	ST7735_SetWindow(0,0,160,128);
	for(int i=0;i<160*128*2;i++)
		SPI_WriteByte(image[i]);
}



void ST7735_init(void)
{
	
	CS_LOW;
	ST7735_Reset();
	
  ST7735_sendCommand(ST7735_SWRESET); //Software Reset
  HAL_Delay(150);
  ST7735_sendCommand(ST7735_SLPOUT); //exit Sleep
  HAL_Delay(255);

  
  ST7735_sendCommand(ST7735_FRMCTR1);  //Frame rate ctrl
  SPI_WriteByte(0x01);
  SPI_WriteByte(0x2C);
	SPI_WriteByte(0x2D);

  ST7735_sendCommand(ST7735_FRMCTR2);  //Frame rate ctrl
  SPI_WriteByte(0x01);
  SPI_WriteByte(0x2C);
	SPI_WriteByte(0x2D);

  ST7735_sendCommand(ST7735_FRMCTR3);  //Frame rate ctrl
  SPI_WriteByte(0x01);
  SPI_WriteByte(0x2C);
	SPI_WriteByte(0x2D);
  SPI_WriteByte(0x01);
  SPI_WriteByte(0x2C);
	SPI_WriteByte(0x2D);
	
	
	ST7735_sendCommand(ST7735_INVCTR);  //Display Inversion Control
  SPI_WriteByte(0x07);
	
	
	ST7735_sendCommand(ST7735_PWCTR1); //Power Control 2
  SPI_WriteByte(0xA2);
	SPI_WriteByte(0x02);
	SPI_WriteByte(0x84);
	
  ST7735_sendCommand(ST7735_PWCTR2); //Power Control 2
  SPI_WriteByte(0xC5);
  
  
  ST7735_sendCommand(ST7735_PWCTR3);  //Power Control 3 (in Normal mode/ Full colors)
  SPI_WriteByte(0x0A);
  SPI_WriteByte(0x00);
  
  ST7735_sendCommand(ST7735_PWCTR4);  //Power Control 3 (in Normal mode/ Full colors)
  SPI_WriteByte(0x8A);
  SPI_WriteByte(0x2A);
	
	ST7735_sendCommand(ST7735_PWCTR5);  //Power Control 3 (in Normal mode/ Full colors)
  SPI_WriteByte(0x8A);
  SPI_WriteByte(0xEE);


  ST7735_sendCommand(ST7735_VMCTR1);  //VCOM Control 1
  SPI_WriteByte(0x0E);

	ST7735_sendCommand(ST7735_INVOFF);
	
	ST7735_sendCommand(ST7735_MADCTL);
	SPI_WriteByte(0xA0);
  
	ST7735_sendCommand(ST7735_COLMOD); //16-bit color
	SPI_WriteByte(0x05);
	
	
	ST7735_sendCommand(ST7735_CASET); //Column address set
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x7F);
  
  
  ST7735_sendCommand(ST7735_RASET); //Row address set
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x9F);
	

  ST7735_sendCommand(ST7735_GMCTRP1); //Gamm adjustment (+ polarity)
  SPI_WriteByte(0x02);
  SPI_WriteByte(0x1C);
  SPI_WriteByte(0x07);
  SPI_WriteByte(0x12);
  SPI_WriteByte(0x37);
  SPI_WriteByte(0x32);
  SPI_WriteByte(0x29);
  SPI_WriteByte(0x2D);
  SPI_WriteByte(0x29);
  SPI_WriteByte(0x25);
  SPI_WriteByte(0x2B);
  SPI_WriteByte(0x39);
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x01);
  SPI_WriteByte(0x03);
  SPI_WriteByte(0x10);
  
  
  ST7735_sendCommand(ST7735_GMCTRN1);  //Gamma adjustment(- polarity)
  SPI_WriteByte(0x03);
  SPI_WriteByte(0x1D);
  SPI_WriteByte(0x07);
  SPI_WriteByte(0x06);
  SPI_WriteByte(0x2E);
  SPI_WriteByte(0x2C);
  SPI_WriteByte(0x29);
  SPI_WriteByte(0x2D);
  SPI_WriteByte(0x2E);
  SPI_WriteByte(0x2E);
  SPI_WriteByte(0x37);
  SPI_WriteByte(0x3F);
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x00);
  SPI_WriteByte(0x02);
  SPI_WriteByte(0x10);


  ST7735_sendCommand(ST7735_NORON); //Normal display on
  HAL_Delay(10);
	
  ST7735_sendCommand(ST7735_DISPON); //Display on
	HAL_Delay(100);
	
	CS_HIGH;
}

//--------------------------------------------END FILE---------------------------------------
