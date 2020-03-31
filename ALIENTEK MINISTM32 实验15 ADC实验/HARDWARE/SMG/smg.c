#include "smg.h"

uint8 seg_table_p[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6};
uint8 seg_table_n[]={0x03,0x9F,0x25,0x0D,0x99,0x49,0x41,0x1F,0x01,0x09};

void hc595_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = HC595_DATA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(HC595_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = HC595_SCLK;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(HC595_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = HC595_RCLK;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(HC595_PORT, &GPIO_InitStructure);

	GPIO_ResetBits(HC595_PORT, HC595_DATA);
	GPIO_ResetBits(HC595_PORT, HC595_SCLK);
	GPIO_ResetBits(HC595_PORT, HC595_RCLK);

}

void hc595_write_byte(uint8_t byte)
{
	uint8_t i, num;
	num = byte;
	for (i=0; i<8; i++)
	{
		GPIO_ResetBits(HC595_PORT, HC595_SCLK);
		if ((num&0x01)==0x01)
			GPIO_SetBits(HC595_PORT, HC595_DATA);
		else
			GPIO_ResetBits(HC595_PORT, HC595_DATA);
		GPIO_SetBits(HC595_PORT, HC595_SCLK);
		num = num>>1;
	}
}

void hc595_latch(void)
{
	GPIO_ResetBits(HC595_PORT, HC595_RCLK);
	GPIO_SetBits(HC595_PORT, HC595_RCLK);
	GPIO_ResetBits(HC595_PORT, HC595_RCLK);
}

void hc595_display(uint8_t data[])
{
	hc595_write_byte(0x01);
	hc595_write_byte(seg_table_n[data[7]]);
	hc595_latch();
  Delay(10);
	hc595_write_byte(0x02);
	hc595_write_byte(seg_table_n[data[6]]);
	hc595_latch();
	Delay(10);
	hc595_write_byte(0x04);
	hc595_write_byte(seg_table_n[data[5]]);
	hc595_latch();
	Delay(10);
	hc595_write_byte(0x08);
	hc595_write_byte(seg_table_n[data[5]]);
	hc595_latch();
	Delay(10);
	hc595_write_byte(0x10);
	hc595_write_byte(seg_table_n[data[3]]);
	hc595_latch();
	Delay(10);
	hc595_write_byte(0x20);
	hc595_write_byte(seg_table_n[data[2]]);
	hc595_latch();
	Delay(10);
	hc595_write_byte(0x40);
	hc595_write_byte(seg_table_n[data[1]]);
	hc595_latch();
	Delay(10);
	hc595_write_byte(0x80);
	hc595_write_byte(seg_table_n[data[0]]);
	hc595_latch();
	Delay(10);
}