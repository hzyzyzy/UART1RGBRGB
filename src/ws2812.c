/*
 * ws2812.c
 *
 *  Created on: 2024年7月16日
 *      Author: hp
 */

#include "CH59x_common.h"
#include "ws2812.h"




//缓存区
unsigned char buf[SNUM][3]={
0
};

//缓存区
 unsigned char buf1[SNUM1][3]={
0
};

//缓存区
 unsigned char buf2[SNUM2][3]={
0
};


 int numberone= 0;
 int numbertwo= 0;
 int numberthree= 0;
 int ione = 0;
 int itwo =0;
 int ithree =0;

 int numberone1= 0;
 int numbertwo2= 0;
 int numberthree3= 0;

 int numberone11= 0;
 int numbertwo22= 0;
 int numberthree33= 0;

 int ioneone = 0;
       int itwoone =0;
       int ithreeone =0;

       int ioneone1 = 0;
       int itwoone2 =0;
       int ithreeone3 =0;
 char segments[2][4][5];


//发0码
void Set0Code(void) {
    GPIOB_SetBits(GPIO_Pin_7);
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_7);
    //       NOP();
}

//发0码
void Set0Code1(void) {
    GPIOB_SetBits(GPIO_Pin_6);
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_6);
    //       NOP();
}

//发0码
void Set0Code2(void) {
    GPIOB_SetBits(GPIO_Pin_4);
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_4);
    //       NOP();
}
//发1码
void Set1Code(void) {
    GPIOB_SetBits(GPIO_Pin_7);
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_7);
}


//发1码
void Set1Code1(void) {
    GPIOB_SetBits(GPIO_Pin_6);
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_6);
}

//发1码
void Set1Code2(void) {
    GPIOB_SetBits(GPIO_Pin_4);
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_4);
}

//发一个像素
void SendOnePix(unsigned char *ptr) {
    unsigned char i, j;
    unsigned char temp;

    for (j = 0; j < 3; j++) {
        temp = ptr[j];
        for (i = 0; i < 8; i++) {
            if (temp & 0x80)        //从高位开始发送
                    {
                Set1Code();
            } else                //发送“0”码
            {
                Set0Code();
            }
            temp = (temp << 1);      //左移位
        }
    }
}


void SendOnePix1(unsigned char *ptr1) {
    unsigned char i1, j1;
    unsigned char temp1;

    for (j1 = 0; j1 < 3; j1++) {
        temp1 = ptr1[j1];
        for (i1 = 0; i1 < 8; i1++) {
            if (temp1 & 0x80)        //从高位开始发送
                    {
                Set1Code1();
            } else                //发送“0”码
            {
                Set0Code1();
            }
            temp1 = (temp1 << 1);      //左移位
        }
    }
}

void SendOnePix2(unsigned char *ptr2) {
    unsigned char i2, j2;
    unsigned char temp2;

    for (j2 = 0; j2 < 3; j2++) {
        temp2 = ptr2[j2];
        for (i2 = 0; i2 < 8; i2++) {
            if (temp2 & 0x80)        //从高位开始发送
                    {
                Set1Code2();
            } else                //发送“0”码
            {
                Set0Code2();
            }
            temp2 = (temp2 << 1);      //左移位
        }
    }
}
//发一帧数据
void SendOneFrame(unsigned char *ptr) {
    uint16_t k;

    //  PWM_RGB=0;//发送帧复位信号
    //  DelayMs(1);

    for (k = 0; k < SNUM; k++)              //发送一帧数据，SNUM是板子LED的个数
            {
        SendOnePix(&ptr[(3 * k)]);
    }

    GPIOB_ResetBits(GPIO_Pin_7);              //发送帧复位信号

}


//发一帧数据
void SendOneFrame1(unsigned char *ptr1) {
    uint16_t k1;

    //  PWM_RGB=0;//发送帧复位信号
    //  DelayMs(1);

    for (k1 = 0; k1 < SNUM1; k1++)              //发送一帧数据，SNUM是板子LED的个数
            {
        SendOnePix1(&ptr1[(3 * k1)]);
    }

    GPIOB_ResetBits(GPIO_Pin_6);              //发送帧复位信号

}


//发一帧数据
void SendOneFrame2(unsigned char *ptr2) {
    uint16_t k2;

    //  PWM_RGB=0;//发送帧复位信号
    //  DelayMs(1);

    for (k2 = 0; k2 < SNUM2; k2++)              //发送一帧数据，SNUM是板子LED的个数
            {
        SendOnePix2(&ptr2[(3 * k2)]);
    }

    GPIOB_ResetBits(GPIO_Pin_4);              //发送帧复位信号

}





void chuli_proc(char message[])
{
    int length = strlen(message);  // 计算字符串长度
    int result = length / 13;   // 计算长度除以13的商
    int b=result+1;

    for(int a=1;a<b;a=a+1)
    {

    strncpy(segments[a-1][0], message+13*(a-1), 4);
    segments[a-1][0][5] = '\0'; // Null-terminate the string

        strncpy( segments[a-1][1], message + 4+13*(a-1), 3);
        segments[a-1][1][4]= '\0';

        strncpy(segments[a-1][2], message + 7+13*(a-1), 3);
        segments[a-1][2][4] = '\0';

        strncpy( segments[a-1][3], message + 10+13*(a-1), 3);
        segments[a-1][3][4] = '\0';




        if(strcmp(segments[a-1][0], "0101") == 0)
               {
            while (segments[a-1][1][ione] != '\0') {
                        // 将字符转换为对应的数字并累加到结果中
                        numberone = numberone * 10 + (segments[a-1][1][ione] - '0');
                        ione++;
                    }

                    while (segments[a-1][2][itwo] != '\0') {
                        // 将字符转换为对应的数字并累加到结果中
                        numbertwo = numbertwo * 10 + (segments[a-1][2][itwo] - '0');
                        itwo++;
                    }

                    while (segments[a-1][3][ithree] != '\0') {
                        // 将字符转换为对应的数字并累加到结果中
                        numberthree = numberthree * 10 + (segments[a-1][3][ithree] - '0');
                        ithree++;
                    }

                                   buf[0][0]=numberone;
                                   buf[0][1]=numbertwo;
                                   buf[0][2]=numberthree;

                                   SendOneFrame(buf);

               }
        else if(strcmp(segments[a-1][0], "0102") == 0)
                       {
            while (segments[a-1][1][ioneone] != '\0') {
                // 将字符转换为对应的数字并累加到结果中
                numberone1 = numberone1 * 10 + (segments[a-1][1][ioneone] - '0');
                ioneone++;
            }

            while (segments[a-1][2][itwoone] != '\0') {
                // 将字符转换为对应的数字并累加到结果中
                numbertwo2 = numbertwo2 * 10 + (segments[a-1][2][itwoone] - '0');
                itwoone++;
                                                  }

           while (segments[a-1][3][ithreeone] != '\0') {
                      // 将字符转换为对应的数字并累加到结果中
                      numberthree3 = numberthree3 * 10 + (segments[a-1][3][ithreeone] - '0');
                      ithreeone++;
                  }


                                           buf[1][0]=numberone1;
                                           buf[1][1]=numbertwo2;
                                           buf[1][2]=numberthree3;

                                           SendOneFrame(buf);
                                           numberone1=0;
                                           numbertwo2=0;
                                           numberthree3=0;

                       }
      else if(strcmp(segments[a-1][0], "0103") == 0)
                               {
                                                   buf[2][0]=numberone;
                                                   buf[2][1]=numbertwo;
                                                   buf[2][2]=numberthree;

                                                   SendOneFrame(buf);

                               }
      else if(strcmp(segments[a-1][0], "0201") == 0)
                        {
                                           buf1[0][0]=numberone;
                                           buf1[0][1]=numbertwo;
                                           buf1[0][2]=numberthree;

                                           SendOneFrame1(buf1);

                       }
      else if(strcmp(segments[a-1][0], "0202") == 0)
                              {
                                                  buf1[1][0]=numberone;
                                                  buf1[1][1]=numbertwo;
                                                  buf1[1][2]=numberthree;

                                                  SendOneFrame1(buf1);

                              }
       else  if(strcmp(segments[a-1][0], "0203") == 0)
                              {
                                                  buf1[2][0]=numberone;
                                                  buf1[2][1]=numbertwo;
                                                  buf1[2][2]=numberthree;

                                                  SendOneFrame1(buf1);

                              }
       else  if(strcmp(segments[a-1][0], "0301") == 0)
                               {
                                                   buf2[0][0]=numberone;
                                                   buf2[0][1]=numbertwo;
                                                   buf2[0][2]=numberthree;

                                                   SendOneFrame2(buf2);

                               }
       else if(strcmp(segments[a-1][0], "0302") == 0)
                                       {
                                                           buf2[1][0]=numberone;
                                                           buf2[1][1]=numbertwo;
                                                           buf2[1][2]=numberthree;

                                                           SendOneFrame2(buf2);

                                       }
     else if(strcmp(segments[a-1][0], "0303") == 0)
                                       {
                                                           buf2[2][0]=numberone;
                                                           buf2[2][1]=numbertwo;
                                                           buf2[2][2]=numberthree;

                                                           SendOneFrame2(buf2);

                                       }
    }


}


