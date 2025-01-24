
//----------------------------------------------------------------
//              VCC  ��5V��3.3v��Դ
//              GND  ��Դ��
//              D1   ��PB15��SDI��
//              D0   ��PB13��SCL��
//              CS   ��PB12 Ƭѡ    
//              RST  ��PB14 ϵͳ��λ
//              DC   ��PB1  ����/����  
//              NC   ����                     
//----------------------------------------------------------------
//******************************************************************************/
#include "u8g2_oled.h"
#include "spi.h"
#include "u8g2.h"
#include "u8x8.h"

uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,void *arg_ptr)
{
    switch (msg)
    {
        case U8X8_MSG_BYTE_SEND: /*ͨ��SPI����arg_int���ֽ�����*/
          HAL_SPI_Transmit_DMA(&hspi2, (uint8_t *)arg_ptr, arg_int);while(hspi2.TxXferCount);
			//ʹ��DMA���Խ������ע�ͽ���������治��DMA�ĸ�ע�͵�
//			HAL_SPI_Transmit(&hspi2,(uint8_t *)arg_ptr,arg_int,200);
            break;
        case U8X8_MSG_BYTE_INIT: /*��ʼ������*/
            break;
        case U8X8_MSG_BYTE_SET_DC: /*����DC����,�������͵������ݻ�������*/
			HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin,arg_int);
            break;
        case U8X8_MSG_BYTE_START_TRANSFER: 
            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);
            u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->post_chip_enable_wait_ns, NULL);
            break;
        case U8X8_MSG_BYTE_END_TRANSFER: 
            u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->pre_chip_disable_wait_ns, NULL);
            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
            break;
        default:
            return 0;
    }
    return 1;
}
 
uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8,
    U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,
    U8X8_UNUSED void *arg_ptr) 
{
    switch (msg)
    {
        case U8X8_MSG_GPIO_AND_DELAY_INIT: /*delay��GPIO�ĳ�ʼ������main���Ѿ���ʼ�������*/
            break;
        case U8X8_MSG_DELAY_MILLI: /*��ʱ����*/
            HAL_Delay(arg_int);     //����˭stm32ϵͳ��ʱ����
            break;
        case U8X8_MSG_GPIO_CS: /*Ƭѡ�ź�*/ //����ֻ��һ��SPI�豸������Ƭѡ�ź��ڳ�ʼ��ʱ�Ѿ�����ΪΪ����Ч
            HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, arg_int);
            break;
        case U8X8_MSG_GPIO_DC: /*����DC����,�������͵������ݻ�������*/
            HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin,arg_int);
            break;
        case U8X8_MSG_GPIO_RESET:
            break;
    }
    return 1;
}
 
 /********************************************     
U8G2_R0     //����ת��������     
U8G2_R1     //��ת90��
U8G2_R2     //��ת180��   
U8G2_R3     //��ת270��
U8G2_MIRROR   //û����ת��������ʾ���Ҿ���
U8G2_MIRROR_VERTICAL    //û����ת��������ʾ����
********************************************/
void u8g2Init(u8g2_t *u8g2)
{
	MD_OLED_RST_Set(); //��ʾ����λ����
	u8g2_Setup_ssd1306_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_4wire_hw_spi,             
    u8x8_stm32_gpio_and_delay);  // ��ʼ��0.96��OLED u8g2 �ṹ��
	u8g2_InitDisplay(u8g2);     //��ʼ����ʾ
	u8g2_SetPowerSave(u8g2, 0); //������ʾ
}
/********************************* end_of_file **********************************/
