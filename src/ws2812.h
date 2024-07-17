/*
 * ws2812.h
 *
 *  Created on: 2024年7月16日
 *      Author: hp
 */

#ifndef SRC_WS2812_H_
#define SRC_WS2812_H_

#include "CH59x_common.h"


#define SNUM       3//灯珠数量
#define SNUM1       3//灯珠数量
#define SNUM2       3//灯珠数量

void Set0Code(void);
void Set0Code1(void);
void Set0Code2(void);
void Set1Code(void);
void Set1Code1(void);
void Set1Code2(void);
void SendOnePix(unsigned char *ptr);
void SendOnePix1(unsigned char *ptr1);
void SendOnePix2(unsigned char *ptr2) ;
void SendOneFrame(unsigned char *ptr);
void SendOneFrame1(unsigned char *ptr1);
void SendOneFrame2(unsigned char *ptr2);
void chuli_proc(char message[]);

#endif /* SRC_WS2812_H_ */
