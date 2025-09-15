#include <unistd.h> 
#include "../imx6ul/imx6ul.h"
#include "../bsp/led/bsp_led.h"
#include "../bsp/delay/bsp_delay.h"
#include "../bsp/clk/bsp_clk.h"
#include "../bsp/beep/bsp_beep.h"
#include "../bsp/key/bsp_key.h"
#include "../bsp/int/bsp_int.h"
#include "../bsp/exit/bsp_exit.h"
#include "../bsp/epittimer/bsp_epittimer.h"
#include "../bsp/key_filter/bsp_keyfilter.h"
#include "../bsp/uart/bsp_uart.h"
#include "../stdio/include/stdio.h"
#include "../bsp/lcd/bsp_lcd.h"
#include "../bsp/lcd/bsp_lcdapi.h"
#include "../bsp/rtc/bsp_rtc.h"
#include "../bsp/ap3216c/bsp_ap3216c.h"
#include "../bsp/icm20608/bsp_icm20608.h"

void integer_display(unsigned short x, unsigned short y, unsigned char size, signed int num)
{
	char buf[200];
	
	lcd_fill(x, y, x + 50, y + size, tftlcd_dev.backcolor);
	
	memset(buf, 0, sizeof(buf));
	if(num < 0)
		sprintf(buf, "-%d", -num);
	else 
		sprintf(buf, "%d", num);
	lcd_show_string(x, y, 50, size, size, buf); 
}

void decimals_display(unsigned short x, unsigned short y, unsigned char size, signed int num)
{
	signed int integ;
	signed int fract;
	signed int uncomptemp = num; 
	char buf[200];

	if(num < 0)
		uncomptemp = -uncomptemp;
	integ = uncomptemp / 100;
	fract = uncomptemp % 100;

	memset(buf, 0, sizeof(buf));
	if(num < 0)
		sprintf(buf, "-%d.%d", integ, fract);
	else 
		sprintf(buf, "%d.%d", integ, fract);
	lcd_fill(x, y, x + 60, y + size, tftlcd_dev.backcolor);
	lcd_show_string(x, y, 60, size, size, buf); 
}

 void imx6ul_hardfpu_enable(void)
{
	uint32_t cpacr;
	uint32_t fpexc;

	/* 使能NEON和FPU */
	cpacr = __get_CPACR();
	cpacr = (cpacr & ~(CPACR_ASEDIS_Msk | CPACR_D32DIS_Msk))
		   |  (3UL << CPACR_cp10_Pos) | (3UL << CPACR_cp11_Pos);
	__set_CPACR(cpacr);

	fpexc = __get_FPEXC();
	fpexc |= 0x40000000UL;	
	__set_FPEXC(fpexc);
}

int main()
{
    unsigned char state = OFF;

    imx6ul_hardfpu_enable();

    int_Init();
    imx6u_clkinit();
    delay_Init();
    clk_Enable();
    led_Init();
    beep_Init();
    uart_Init();
    lcd_init();

	tftlcd_dev.forecolor = LCD_RED;
	lcd_show_string(50, 10, 400, 24, 24, (char*)"Bryan TEST");  
	lcd_show_string(50, 40, 200, 24, 2, (char*)"ICM20608 TEST");  
	
	while(icm20608_init())		/* 初始化ICM20608	 			*/
	{
		lcd_show_string(50, 100, 200, 24, 24, (char*)"ICM20608 Check Failed!");
		delayms(500);
		lcd_show_string(50, 100, 200, 24, 24, (char*)"Please Check!        ");
		delayms(500);
	}	

	lcd_show_string(50, 100, 200, 24, 24, (char*)"ICM20608 Ready");
	
	lcd_show_string(50, 130, 200, 24, 24, (char*)"accel x:");  
	lcd_show_string(50, 150, 200, 24, 24, (char*)"accel y:");  
	lcd_show_string(50, 170, 200, 24, 24, (char*)"accel z:");  
	lcd_show_string(50, 190, 200, 24, 24, (char*)"gyro  x:"); 
	lcd_show_string(50, 210, 200, 24, 24, (char*)"gyro  y:"); 
	lcd_show_string(50, 230, 200, 24, 24, (char*)"gyro  z:"); 
	lcd_show_string(50, 250, 200, 24, 24, (char*)"temp   :"); 

	lcd_show_string(50 + 181, 130, 200, 24, 24, (char*)"g");  
	lcd_show_string(50 + 181, 150, 200, 24, 24, (char*)"g");  
	lcd_show_string(50 + 181, 170, 200, 24, 24, (char*)"g");  
	lcd_show_string(50 + 181, 190, 200, 24, 24, (char*)"o/s"); 
	lcd_show_string(50 + 181, 210, 200, 24, 24, (char*)"o/s"); 
	lcd_show_string(50 + 181, 230, 200, 24, 24, (char*)"o/s"); 
	lcd_show_string(50 + 181, 250, 200, 24, 24, (char*)"C");
	
	tftlcd_dev.forecolor = LCD_BLUE;

	while(1)					
	{		
		icm20608_getdata();
		integer_display(50 + 70, 130, 24, icm20608_dev.accel_x_adc);
		integer_display(50 + 70, 150, 24, icm20608_dev.accel_y_adc);
		integer_display(50 + 70, 170, 24, icm20608_dev.accel_z_adc);
		integer_display(50 + 70, 190, 24, icm20608_dev.gyro_x_adc);
		integer_display(50 + 70, 210, 24, icm20608_dev.gyro_y_adc);
		integer_display(50 + 70, 230, 24, icm20608_dev.gyro_z_adc);
		integer_display(50 + 70, 250, 24, icm20608_dev.temp_adc);

		decimals_display(50 + 70 + 50, 130, 24, icm20608_dev.accel_x_act);
		decimals_display(50 + 70 + 50, 150, 24, icm20608_dev.accel_y_act);
		decimals_display(50 + 70 + 50, 170, 24, icm20608_dev.accel_z_act);
		decimals_display(50 + 70 + 50, 190, 24, icm20608_dev.gyro_x_act);
		decimals_display(50 + 70 + 50, 210, 24, icm20608_dev.gyro_y_act);
		decimals_display(50 + 70 + 50, 230, 24, icm20608_dev.gyro_z_act);
		decimals_display(50 + 70 + 50, 250, 24, icm20608_dev.temp_act);

#if 0		
		printf("accel x = %d\r\n",icm20608_dev.accel_x_adc);
		printf("accel y = %d\r\n",icm20608_dev.accel_y_adc);
		printf("accel z = %d\r\n",icm20608_dev.accel_z_adc);
		printf("gyrp  x = %d\r\n",icm20608_dev.gyro_x_adc);
		printf("gyro  y = %d\r\n",icm20608_dev.gyro_y_adc);
		printf("gyro  z = %d\r\n",icm20608_dev.gyro_z_adc);
		printf("temp    = %d\r\n",icm20608_dev.temp_adc);
#endif
		delayms(120);
		state = !state;
		led_Switch(LED0,state);	
	}
    return 0;
}
