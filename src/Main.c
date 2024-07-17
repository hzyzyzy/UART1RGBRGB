/********************************** (C) COPYRIGHT *******************************
 * File Name          : Main.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2020/08/06
 * Description        : 串口1收发演示
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "CH59x_common.h"
#include "ws2812.h"

char data[]="010120020020013517694168392";

uint8_t TxBuff[] = "This is a tx exam\r\n";
uint8_t RxBuff[100];
uint8_t trigB;
uint16_t MAX_BUFFER_SIZE=100;
uint8_t GlobalRxBuffer[100];
uint8_t NewRxBuffer[100];
char message[100];
volatile uint8_t GlobalRxBufferIndex ;

void UART1_IRQHandler(void);
void uint8ArrayToCharArray(uint8_t* uint8Array, int length, char* charArray);
/*********************************************************************
 * @fn      main
 *
 * @brief   主函数
 *
 * @return  none
 */
int main()
{
    uint8_t len;

    SetSysClock(CLK_SOURCE_PLL_60MHz);

    /* 配置串口1：先配置IO口模式，再配置串口 */
    GPIOA_SetBits(GPIO_Pin_9);
    GPIOA_ModeCfg(GPIO_Pin_8, GPIO_ModeIN_PU);      // RXD-配置上拉输入
    GPIOA_ModeCfg(GPIO_Pin_9, GPIO_ModeOut_PP_5mA); // TXD-配置推挽输出，注意先让IO口输出高电平
    GPIOB_ModeCfg(GPIO_Pin_7, GPIO_ModeOut_PP_20mA);  // PB7 - PWM9
    GPIOB_ModeCfg(GPIO_Pin_6, GPIO_ModeOut_PP_20mA);  // PB7 - PWM9
    GPIOB_ModeCfg(GPIO_Pin_4, GPIO_ModeOut_PP_20mA);  // PB7 - PWM9
    UART1_DefInit();



//#if 0 // 中断方式：接收数据后发送出去
    UART1_ByteTrigCfg(UART_7BYTE_TRIG);
    trigB = 1;
    UART1_INTCfg(ENABLE, RB_IER_RECV_RDY | RB_IER_LINE_STAT);
    PFIC_EnableIRQ(UART1_IRQn);
//#endif

    chuli_proc(message);
    memset(message, 0, sizeof(message));

    while(1){
        chuli_proc(message);
            memset(message, 0, sizeof(message));

    }
}

/*********************************************************************
 * @fn      UART1_IRQHandler
 *
 * @brief   UART1中断函数
 *
 * @return  none
 */
__INTERRUPT
__HIGH_CODE
void UART1_IRQHandler(void)
{



    volatile uint8_t i;

    switch(UART1_GetITFlag())
    {
        case UART_II_LINE_STAT: // 线路状态错误
        {
            UART1_GetLinSTA();//获取当前的通讯状态
            break;
        }

        case UART_II_RECV_RDY: // 数据达到设置触发点

                i = UART1_RecvString(RxBuff);

                strncpy(GlobalRxBuffer + GlobalRxBufferIndex, RxBuff, i);
                GlobalRxBufferIndex += i;

                break;

        case UART_II_RECV_TOUT: // 接收超时，暂时一帧数据接收完成
                i = UART1_RecvString(RxBuff);

                strncpy(GlobalRxBuffer + GlobalRxBufferIndex, RxBuff, i);
                GlobalRxBufferIndex += i;

                UART1_SendString(GlobalRxBuffer, strlen(GlobalRxBuffer));
//                memcpy(NewRxBuffer, GlobalRxBuffer, sizeof(GlobalRxBuffer));
                uint8ArrayToCharArray(GlobalRxBuffer, strlen(GlobalRxBuffer), message);
                memset(GlobalRxBuffer, 0, sizeof(GlobalRxBuffer));
                GlobalRxBufferIndex = 0;

                break;


        case UART_II_THR_EMPTY: // 发送缓存区空，可继续发送
            break;

        case UART_II_MODEM_CHG: // 只支持串口0
            break;

        default:
            break;
    }
}

void uint8ArrayToCharArray(uint8_t* uint8Array, int length, char* charArray) {
    for (int i = 0; i < length; ++i) {
        charArray[i] = (char)uint8Array[i];
    }
    charArray[length] = '\0';  // 添加字符串终止符
}




