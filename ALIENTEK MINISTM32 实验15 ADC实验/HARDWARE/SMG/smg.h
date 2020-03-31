#ifndef __HC595_H
#define __HC595_H

// 74HC595
#define HC595_PORT  GPIOD
#define HC595_DATA  GPIO_Pin_12    // serial data input, pin14
#define HC595_SCLK  GPIO_Pin_10    // shift register clock input, pin11
#define HC595_RCLK  GPIO_Pin_8     // storage register clock input, pin12

#define HC595_DELAY DelayUs(100);

void hc595_init(void);
void hc595_write_byte(uint8 t byte);
void hc595_latch(void);
void hc595_display(uint8 t data[]);

#endif

