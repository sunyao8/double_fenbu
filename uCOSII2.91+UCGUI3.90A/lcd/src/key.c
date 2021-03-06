
/* Includes ------------------------------------------------------------------*/
#include <includes.h>

/* Private variables ---------------------------------------------------------*/	
static u8 m=1;
static u8 grafnum=1;
u8 zhongduan_flag=1;
u8 zhongduan_flag_BT=1;
u8 zhongduan_flag_warn_volt=1;
u8 grafnum,tempshuzhi_1,tempshuzhi_2,vernum=108,hguestnum=222,gonglvshishu=0;
u16 dianya_zhi=0,wugongkvar=0;
u32	dianliuzhi=0;
vu8 id_num=1,BT_num=1;
vu8	warn_volt_onlimt=25;//过压值 +400
//#if (FUNCTION_MODULE == DF_THREE)
u16 dianya_zhi_A=0,dianya_zhi_B=0,dianya_zhi_C=0,wugongkvar_A=0,wugongkvar_B=0,wugongkvar_C=0;
u32	dianliuzhi_A=0,dianliuzhi_B=0	,dianliuzhi_C=0;
 u32	dianliuzhi_C_A=0,dianliuzhi_C_B=0,dianliuzhi_C_C=0;
u8 gonglvshishu_A=0,gonglvshishu_B=0,gonglvshishu_C=0;
//#endif
extern u8 flag_ABC;
extern u8 phase_flag;
extern u8 L_C_flag_A;//感性容性标准变量
extern u8 L_C_flag_B;//感性容性标准变量
extern u8 L_C_flag_C;
u8 light_time=30;

//////////////////////////////////////////////////////////////////////////////////	 
//本程序为控制器设计，未经许可，不得复制外传
//实验板栋达电子V3.0-1
//KEY 代码 PA11为显示板设置按键；PA12为手动投切开关	   
//修改日期:2013/3/13
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 济宁市栋达电子科技有限公司 2013-2023
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//按键初始化函数
void KEY_Init(void)
{/*
	RCC->APB2ENR|=1<<2;     //使能PORTA时钟
	GPIOA->CRH&=0XFFF00FFF;	//PA11 PA12设置成输入	  
	GPIOA->CRH|=0X00088000; 
	GPIOA->ODR|=1<11;		// 上拉
	GPIOA->ODR|=1<12;		  //上拉
	*/
		 GPIO_InitTypeDef      GPIO_InitStructure;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
 // GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

} 

extern statusbox status_box;

void key_idset(void)
{
 u8 TR[]={1,2,3,4,5,6,8,10,12,16,20,24,30,40,50,60,80,100,120};
	
	u8 h=0;
	if((KEY0==0)&&m)
	{
           	  // delay_us(10000);
           	  	
	   m=0;
	 		if(grafnum==1)/*在电压 界面设置  过压上限       */
		{
	 while(KEY0==0)
	   	{
	   	   delay_us(3000);//3000
		   h++;
		   if(h>=180)break;
	   
	   	}
			   if(h>=180)//180
			   {		
					zhongduan_flag_warn_volt=0;

						
				{

					Clera_lcd();
		
			   		Graf_set_warn_volt(warn_volt_onlimt+200);

						}	

			   }
		}

	if(grafnum==4)/*在电流 界面设置变比值*/
		{
	 while(KEY0==0)
	   	{
	   	   delay_us(3000);//3000
		   h++;
		   if(h>=180)break;
	   
	   	}
			   if(h>=180)//180
			   {		
					zhongduan_flag_BT=0;

						
				{

					Clera_lcd();
		
			   		Graf_setBT(TR[BT_num]*50);

						}	

			   }
		}

	if(grafnum==14)/*ID set */
			  	{
	 while(KEY0==0)
	   	{
	   	   delay_us(3000);//3000
		   h++;
		   if(h>=180)break;
	   
	   	}
			   if(h>=180)//180
			   {		
					zhongduan_flag=0;
						
			   		Clera_lcd();
		
			   		Graf_setid(id_num);

			   }
			  		}

	if(h<180)
				   {  
#if (FUNCTION_MODULE == DF_THREE)
				     if(zhongduan_flag==1&&zhongduan_flag_BT==1&&zhongduan_flag_warn_volt==1&&light_time>0)

                          {
					  		grafnum++;
					  		if(grafnum>15)grafnum=1;
					  
					    	  switch(grafnum)
								{				 
									case 1:	//显示A功率因数和电压值
										Clera_lcd();									
										if(phase_flag==0)
											{
										flag_ABC=1;
										Graf_con_u(gonglvshishu_A,dianya_zhi_A,L_C_flag_A);
											}
									   if(phase_flag==1)
											{
										flag_ABC=3;
										Graf_con_u(gonglvshishu_C,dianya_zhi_C,L_C_flag_C);
											}
										break;
									case 2:	//显示B功率因数和电压值
										flag_ABC=2;
									     Clera_lcd();
										Graf_con_u(gonglvshishu_B,dianya_zhi_B,L_C_flag_B);
										
										break;
									case 3:	//显示B功率因数和电压值
										Clera_lcd();									
										if(phase_flag==0)
											{
										flag_ABC=3;
										Graf_con_u(gonglvshishu_C,dianya_zhi_C,L_C_flag_C);
											}
									   if(phase_flag==1)
											{
										flag_ABC=1;
										Graf_con_u(gonglvshishu_A,dianya_zhi_A,L_C_flag_A);
											}
										break;
										
									case 4:	//显示电流
										Clera_lcd();
									if(phase_flag==0)
										{
										flag_ABC=1;
										Graf_cuirrent(dianliuzhi_A);
										}
									if(phase_flag==1)
										{
                                                                       flag_ABC=3;
										Graf_cuirrent(dianliuzhi_C);
										}
										break;
									case 5:	//显示电流
									flag_ABC=2;
										Clera_lcd();
										Graf_cuirrent(dianliuzhi_B);
										break;
									case 6:	//显示电流
										Clera_lcd();
									if(phase_flag==0)
										{
										flag_ABC=3;
										Graf_cuirrent(dianliuzhi_C);
										}
									if(phase_flag==1)
										{
                                                                       flag_ABC=1;
										Graf_cuirrent(dianliuzhi_A);
										}
										break;										
									case 7:	//显示无功功率	 
										Clera_lcd();									
	             								if(phase_flag==0)
	             									{
									flag_ABC=1;
										Graf_qkvar(wugongkvar_A);
	             									}
									if(phase_flag==1)
										{
										flag_ABC=3;
										Graf_qkvar(wugongkvar_C);											
										}
										break;
									case 8:	//显示无功功率	 
									flag_ABC=2;
										Clera_lcd();
										Graf_qkvar(wugongkvar_B);
										break;
									case 9:	//显示无功功率	 
										Clera_lcd();									
	             								if(phase_flag==0)
	             									{
									flag_ABC=3;
										Graf_qkvar(wugongkvar_C);
	             									}
									if(phase_flag==1)
										{
										flag_ABC=1;
										Graf_qkvar(wugongkvar_A);											
										}										
										break;				

											case 10:	//显示A电容电流
									flag_ABC=1;
										Clera_lcd();
										Graf_C_cuirrent(dianliuzhi_C_A);
										break;
					                                case 11:	//显示B 电容电流 
									flag_ABC=2;
										Clera_lcd();
										Graf_C_cuirrent(dianliuzhi_C_B);
										break;	
					                                      case 12:	///显示C电容电流
									flag_ABC=3;
										Clera_lcd();
										Graf_C_cuirrent(dianliuzhi_C_C);
										break;										
									case 13:	//显示温度 
										Clera_lcd();
										 Graf_temp_double(tempshuzhi_1,tempshuzhi_2);
										break;
					
									case 14:	//显示ID 
										Clera_lcd();
										Graf_id(hguestnum,id_num);
										break;
					
									case 15:	//显示VER 
										Clera_lcd();
										Graf_ver(vernum);
										break;
					
								}
					 	}
#endif


#if (FUNCTION_MODULE == COMMON)
					 if(zhongduan_flag==1)
				      	{
					  		grafnum++;
					  		if(grafnum>6)grafnum=1;
					  
					    	  switch(grafnum)
								{				 
									case 1:	//显示功率因数和电压值
										Clera_lcd();
										Graf_con_u(gonglvshishu,dianya_zhi);
										break;
									case 2:	//显示电流
										Clera_lcd();
										Graf_cuirrent(dianliuzhi);
										break;
									case 3:	//显示无功功率	 
										Clera_lcd();
										Graf_qkvar(wugongkvar);
										break;
									case 4:	//显示温度 
										Clera_lcd();
										Graf_temp(tempshuzhi_1);
										break;
					
									case 5:	//显示ID 
										Clera_lcd();
										Graf_id(hguestnum,id_num);
										break;
					
									case 6:	//显示VER 
										Clera_lcd();
										Graf_ver(vernum);
										break;
					
								}
					 	}
					 #endif

					 if(grafnum==1&&zhongduan_flag_warn_volt==0)/*在id 界面设置id号*/
						{
					             light_time=30;
							warn_volt_onlimt=warn_volt_onlimt+5;
					  		if(warn_volt_onlimt>70)warn_volt_onlimt=0;
							Clera_lcd();
			   		   Graf_set_warn_volt(warn_volt_onlimt+200);
							AT24CXX_WriteOneByte(0x1000,warn_volt_onlimt);
						}

						if(grafnum==4&&zhongduan_flag_BT==0)
				      	{

                                              
					             light_time=30;
							BT_num++;
					  		if(BT_num>18)BT_num=0;
							Clera_lcd();
	   						Graf_setBT(TR[BT_num]*50);
							AT24CXX_WriteOneByte(0x0100,BT_num);					


						}

						if(grafnum==14&&zhongduan_flag==0)/*在id 界面设置id号*/
						{
					             light_time=30;
							id_num++;
					  		if(id_num>32)id_num=1;
							Clera_lcd();
	   						Graf_setid(id_num);
							AT24CXX_WriteOneByte(0xa000,id_num);
						}				      	
				   }

	{
           	  	LIGHT_backligt_on(status_box.work_status[0],status_box.work_status[1],status_box.work_status[2]);
           	  	light_time=30;
				}
	}
	else if(KEY0==1)
		{
                  	  // delay_us(10000);
			m=1;
	if(grafnum==1)/*在电压 界面设置过压值  */
		{
			 while(KEY0==1)
			 {
		   	   delay_us(3000);//2500
			   h++;
			   if(h>=250)break;
	   
	   		 } 
			   if(h>=250)//200
				 {
						  zhongduan_flag_warn_volt=1;
			   	}
			   
		}
		if(grafnum==4)/*在电流 界面设置变比值*/
		{
			 while(KEY0==1)
			 {
		   	   delay_us(3000);//2500
			   h++;
			   if(h>=250)break;
	   
	   		 } 
			   if(h>=250)//200
				 {
						  zhongduan_flag_BT=1;
			   	}
			   
		}
			if(grafnum==14)/*在电流 界面设置变比值*/
		{
			 while(KEY0==1)
			 {
		   	   delay_us(3000);//2500
			   h++;
			   if(h>=250)break;
	   
	   		 } 
			   if(h>=250)//200
				 {
						  zhongduan_flag=1;
			   	}
			   
		}
			  
				 {
#if (FUNCTION_MODULE == DF_THREE)

				     if(zhongduan_flag==1&&zhongduan_flag_BT==1&&zhongduan_flag_warn_volt==1)
					  	  switch(grafnum)
							{				 
									case 1:	//显示A功率因数和电压值
										Clera_lcd();									
										if(phase_flag==0)
											{
										flag_ABC=1;
										Graf_con_u(gonglvshishu_A,dianya_zhi_A,L_C_flag_A);
											}
									   if(phase_flag==1)
											{
										flag_ABC=3;
										Graf_con_u(gonglvshishu_C,dianya_zhi_C,L_C_flag_C);
											}
										break;
									case 2:	//显示B功率因数和电压值
										flag_ABC=2;
									     Clera_lcd();
										Graf_con_u(gonglvshishu_B,dianya_zhi_B,L_C_flag_B);
										
										break;
									case 3:	//显示B功率因数和电压值
										Clera_lcd();									
										if(phase_flag==0)
											{
										flag_ABC=3;
										Graf_con_u(gonglvshishu_C,dianya_zhi_C,L_C_flag_C);
											}
									   if(phase_flag==1)
											{
										flag_ABC=1;
										Graf_con_u(gonglvshishu_A,dianya_zhi_A,L_C_flag_A);
											}
										break;
										
									case 4:	//显示电流
										Clera_lcd();
									if(phase_flag==0)
										{
										flag_ABC=1;
										Graf_cuirrent(dianliuzhi_A);
										}
									if(phase_flag==1)
										{
                                                                       flag_ABC=3;
										Graf_cuirrent(dianliuzhi_C);
										}
										break;
									case 5:	//显示电流
									flag_ABC=2;
										Clera_lcd();
										Graf_cuirrent(dianliuzhi_B);
										break;
									case 6:	//显示电流
										Clera_lcd();
									if(phase_flag==0)
										{
										flag_ABC=3;
										Graf_cuirrent(dianliuzhi_C);
										}
									if(phase_flag==1)
										{
                                                                       flag_ABC=1;
										Graf_cuirrent(dianliuzhi_A);
										}
										break;										
									case 7:	//显示无功功率	 
										Clera_lcd();									
	             								if(phase_flag==0)
	             									{
									flag_ABC=1;
										Graf_qkvar(wugongkvar_A);
	             									}
									if(phase_flag==1)
										{
										flag_ABC=3;
										Graf_qkvar(wugongkvar_C);											
										}
										break;
									case 8:	//显示无功功率	 
									flag_ABC=2;
										Clera_lcd();
										Graf_qkvar(wugongkvar_B);
										break;
									case 9:	//显示无功功率	 
										Clera_lcd();									
	             								if(phase_flag==0)
	             									{
									flag_ABC=3;
										Graf_qkvar(wugongkvar_C);
	             									}
									if(phase_flag==1)
										{
										flag_ABC=1;
										Graf_qkvar(wugongkvar_A);											
										}										
										break;										
												case 10:	//显示A电容电流
									flag_ABC=1;
										Clera_lcd();
										Graf_C_cuirrent(dianliuzhi_C_A);
										break;
					                                case 11:	//显示B 电容电流 
									flag_ABC=2;
										Clera_lcd();
										Graf_C_cuirrent(dianliuzhi_C_B);
										break;	
					                                      case 12:	///显示C电容电流
									flag_ABC=3;
										Clera_lcd();
										Graf_C_cuirrent(dianliuzhi_C_C);
										break;										
									case 13:	//显示温度 
										Clera_lcd();
										 Graf_temp_double(tempshuzhi_1,tempshuzhi_2);
										break;
					
									case 14:	//显示ID 
										Clera_lcd();
										Graf_id(hguestnum,id_num);
										break;
					
									case 15:	//显示VER 
										Clera_lcd();
										Graf_ver(vernum);
										break;
					
						
								}	
					 #endif



#if (FUNCTION_MODULE == COMMON)

						  zhongduan_flag=1;
					  	  switch(grafnum)
							{				 
								case 1:	//显示功率因数和电压值
									Clera_lcd();
									Graf_con_u(gonglvshishu,dianya_zhi);
									break;
								case 2:	//显示电流
									Clera_lcd();
									Graf_cuirrent(dianliuzhi);
									break;
								case 3:	//显示无功功率	 
									Clera_lcd();
									Graf_qkvar(wugongkvar);
									break;
								case 4:	//显示温度 
									Clera_lcd();
									Graf_temp(tempshuzhi_1);
									break;
				
								case 5:	//显示ID 
									Clera_lcd();
									Graf_id(hguestnum,id_num);
									break;
				
								case 6:	//显示VER 
									Clera_lcd();
									Graf_ver(vernum);
									break;
				
							}	
					 #endif

			   }

		}
}






























/******************************************************************************/
/*

#include <includes.h>

static u8 m=1;
static u8 grafnum=1;
u8 zhongduan_flag=1;
u8 id_num=0;
u8 grafnum,tempshuzhi,vernum=101,hguestnum=222,gonglvshishu=0;
u16 dianya_zhi=0,wugongkvar=0;
u32	dianliuzhi=0;
//#if (FUNCTION_MODULE == DF_THREE)
u16 dianya_zhi_A=0,dianya_zhi_B=0,dianya_zhi_C=0,wugongkvar_A=0,wugongkvar_B=0,wugongkvar_C=0;
u32	dianliuzhi_A=0,dianliuzhi_B=0	,dianliuzhi_C=0;
u8 gonglvshishu_A=0,gonglvshishu_B=0,gonglvshishu_C=0;
//#endif

//////////////////////////////////////////////////////////////////////////////////	 
//本程序为控制器设计，未经许可，不得复制外传
//实验板栋达电子V3.0-1
//KEY 代码 PA11为显示板设置按键；PA12为手动投切开关	   
//修改日期:2013/3/13
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 济宁市栋达电子科技有限公司 2013-2023
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//按键初始化函数
void KEY_Init(void)
{
		 GPIO_InitTypeDef      GPIO_InitStructure;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
 // GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

} 

void key_idset(void)
{
	
	u8 h=0;
	if((KEY0==0)&&m)
	{
           	  // delay_us(10000);
	   m=0;
	 while(KEY0==0)
	   	{
	   	   delay_us(3000);//3000
		   h++;
		   if(h>=180)break;
	   
	   	}
			   if(h>=180)//180
			   {		
					zhongduan_flag=0;
						
			   		Clera_lcd();
		
			   		Graf_setid(id_num);
			   //Graf_con_u(gonglvshishu,dianya_zhi);

			   }
			   else
				   {  
#if (FUNCTION_MODULE == DF_THREE)
					 if(zhongduan_flag==1)

                          {
					  		grafnum++;
					  		if(grafnum>12)grafnum=1;
					  
					    	  switch(grafnum)
								{				 
									case 1:	//显示A功率因数和电压值
										Clera_lcd();
										Graf_con_u(gonglvshishu_A,dianya_zhi_A);
										break;
									case 2:	//显示B功率因数和电压值
										Clera_lcd();
										Graf_con_u(gonglvshishu_B,dianya_zhi_B);
										break;
									case 3:	//显示B功率因数和电压值
										Clera_lcd();
										Graf_con_u(gonglvshishu_C,dianya_zhi_C);
										break;
										
									case 4:	//显示电流
										Clera_lcd();
										Graf_cuirrent(dianliuzhi_A);
										break;
									case 5:	//显示电流
										Clera_lcd();
										Graf_cuirrent(dianliuzhi_B);
										break;
									case 6:	//显示电流
										Clera_lcd();
										Graf_cuirrent(dianliuzhi_C);
										break;										
									case 7:	//显示无功功率	 
										Clera_lcd();
										Graf_qkvar(wugongkvar_A);
										break;
									case 8:	//显示无功功率	 
										Clera_lcd();
										Graf_qkvar(wugongkvar_B);
										break;
									case 9:	//显示无功功率	 
										Clera_lcd();
										Graf_qkvar(wugongkvar_C);
										break;										
									case 10:	//显示温度 
										Clera_lcd();
										Graf_temp(tempshuzhi);
										break;
					
									case 11:	//显示ID 
										Clera_lcd();
										Graf_id(hguestnum,id_num);
										break;
					
									case 12:	//显示VER 
										Clera_lcd();
										Graf_ver(vernum);
										break;
					
								}
					 	}
#endif


#if (FUNCTION_MODULE == COMMON)
					 if(zhongduan_flag==1)
				      	{
					  		grafnum++;
					  		if(grafnum>6)grafnum=1;
					  
					    	  switch(grafnum)
								{				 
									case 1:	//显示功率因数和电压值
										Clera_lcd();
										Graf_con_u(gonglvshishu,dianya_zhi);
										break;
									case 2:	//显示电流
										Clera_lcd();
										Graf_cuirrent(dianliuzhi);
										break;
									case 3:	//显示无功功率	 
										Clera_lcd();
										Graf_qkvar(wugongkvar);
										break;
									case 4:	//显示温度 
										Clera_lcd();
										Graf_temp(tempshuzhi);
										break;
					
									case 5:	//显示ID 
										Clera_lcd();
										Graf_id(hguestnum,id_num);
										break;
					
									case 6:	//显示VER 
										Clera_lcd();
										Graf_ver(vernum);
										break;
					
								}
					 	}
					 #endif

						if(zhongduan_flag==0)
				      	{
					  		id_num++;
					  		if(id_num>32)id_num=0;
							Clera_lcd();
	   						Graf_setid(id_num);
						AT24CXX_WriteOneByte(0x0010,id_num);
						}
				   }
	
	}
	else if(KEY0==1)
		{
                  	  // delay_us(10000);
			m=1;
			 while(KEY0==1)
			 {
		   	   delay_us(2500);//2500
			   h++;
			   if(h>=200)break;
	   
	   		 } 
			   if(h>=200)//200
				 {
#if (FUNCTION_MODULE == DF_THREE)

						  zhongduan_flag=1;
					  	  switch(grafnum)
							{				 
									case 1:	//显示A功率因数和电压值
										Clera_lcd();
										Graf_con_u(gonglvshishu_A,dianya_zhi_A);
										break;
									case 2:	//显示B功率因数和电压值
										Clera_lcd();
										Graf_con_u(gonglvshishu_B,dianya_zhi_B);
										break;
									case 3:	//显示B功率因数和电压值
										Clera_lcd();
										Graf_con_u(gonglvshishu_C,dianya_zhi_C);
										break;
										
									case 4:	//显示电流
										Clera_lcd();
										Graf_cuirrent(dianliuzhi_A);
										break;
									case 5:	//显示电流
										Clera_lcd();
										Graf_cuirrent(dianliuzhi_B);
										break;
									case 6:	//显示电流
										Clera_lcd();
										Graf_cuirrent(dianliuzhi_C);
										break;										
									case 7:	//显示无功功率	 
										Clera_lcd();
										Graf_qkvar(wugongkvar_A);
										break;
									case 8:	//显示无功功率	 
										Clera_lcd();
										Graf_qkvar(wugongkvar_B);
										break;
									case 9:	//显示无功功率	 
										Clera_lcd();
										Graf_qkvar(wugongkvar_C);
										break;										
									case 10:	//显示温度 
										Clera_lcd();
										Graf_temp(tempshuzhi);
										break;
					
									case 11:	//显示ID 
										Clera_lcd();
										Graf_id(hguestnum,id_num);
										break;
					
									case 12:	//显示VER 
										Clera_lcd();
										Graf_ver(vernum);
										break;
					
								}	
					 #endif



#if (FUNCTION_MODULE == COMMON)

						  zhongduan_flag=1;
					  	  switch(grafnum)
							{				 
								case 1:	//显示功率因数和电压值
									Clera_lcd();
									Graf_con_u(gonglvshishu,dianya_zhi);
									break;
								case 2:	//显示电流
									Clera_lcd();
									Graf_cuirrent(dianliuzhi);
									break;
								case 3:	//显示无功功率	 
									Clera_lcd();
									Graf_qkvar(wugongkvar);
									break;
								case 4:	//显示温度 
									Clera_lcd();
									Graf_temp(tempshuzhi);
									break;
				
								case 5:	//显示ID 
									Clera_lcd();
									Graf_id(hguestnum,id_num);
									break;
				
								case 6:	//显示VER 
									Clera_lcd();
									Graf_ver(vernum);
									break;
				
							}	
					 #endif

			   }

		}
}



*/
















