#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������Ϊ��������ƣ�δ�����ɣ����ø����⴫
//ʵ��嶰�����V3.0-1
//KEY ���� PA11Ϊ��ʾ�����ð�����PA12Ϊ�ֶ�Ͷ�п���	   
//�޸�����:2013/3/13
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �����ж�����ӿƼ����޹�˾ 2013-2023
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

//#define KEY0 PAin(11)   	//PA11Ϊ��ʾ�����ð���
#define KEY0 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)
#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)


void KEY_Init(void);//IO��ʼ��
void key_idset(void);					    
#endif
