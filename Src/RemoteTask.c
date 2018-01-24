#include <stm32f4xx.h>
#include "RemoteTask.h"

#include "SEGGER_RTT.h"
#include "test_uart.h"
#include "test_app.h"
RC_Ctl_t RC_CtrlData;   //remote control data
extern uint8_t RemoteData[RC_FRAME_LENGTH];
/*ChassisSpeed_Ref_t ChassisSpeedRef;
Gimbal_Ref_t GimbalRef;
FrictionWheelState_e friction_wheel_state = FRICTION_WHEEL_OFF;
static RemoteSwitch_t switch1;   //ң������ದ��
static volatile Shoot_State_e shootState = NOSHOOTING;
static InputMode_e inputmode = REMOTE_INPUT;   //����ģʽ�趨

RampGen_t frictionRamp = RAMP_GEN_DAFAULT;  //Ħ����б��
RampGen_t LRSpeedRamp = RAMP_GEN_DAFAULT;   //mouse�����ƶ�б��
RampGen_t FBSpeedRamp = RAMP_GEN_DAFAULT;   //mouseǰ���ƶ�б��
*/
void testRemoteTask()
{
	static int cnt=0;
	static int cnt1=0;
	cnt++;
	if(cnt>1)
	{
		cnt=0;
	RemoteDataPrcess(RemoteData);
	printf("RC_CtrlData: ch0 %d, ch1 %d, ch2 %d, ch3 %d, s1 %d, s2 %d times %d\r\n",
					RC_CtrlData.rc.ch0,RC_CtrlData.rc.ch1,
					RC_CtrlData.rc.ch2,RC_CtrlData.rc.ch3,
					RC_CtrlData.rc.s1,RC_CtrlData.rc.s2,cnt1++);
		printf("Remote Raw Data:");
		for(int i=0;i<18;i++)printf("%d,",RemoteData[i]);
		printf("\n\r");
	}
}

/*Э�鶨�壺




*/
 
void RemoteDataPrcess(uint8_t *pData)
{
    if(pData == NULL)
    { 
        return;
    }
		for (int i=0;i<17;i++)pData[i]=pData[i+1];  // Matbe some bug with mouse-keyboard mode
    RC_CtrlData.rc.ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF; 
    RC_CtrlData.rc.ch1 = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5)) & 0x07FF;
    RC_CtrlData.rc.ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) |
                         ((int16_t)pData[4] << 10)) & 0x07FF;
    RC_CtrlData.rc.ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) & 0x07FF;
    
    RC_CtrlData.rc.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
    RC_CtrlData.rc.s2 = ((pData[5] >> 4) & 0x0003);

    RC_CtrlData.mouse.x = ((int16_t)pData[6]) | ((int16_t)pData[7] << 8);
    RC_CtrlData.mouse.y = ((int16_t)pData[8]) | ((int16_t)pData[9] << 8);
    RC_CtrlData.mouse.z = ((int16_t)pData[10]) | ((int16_t)pData[11] << 8);    

    RC_CtrlData.mouse.press_l = pData[12];
    RC_CtrlData.mouse.press_r = pData[13];
 
    RC_CtrlData.key.v = ((int16_t)pData[14]);// | ((int16_t)pData[15] << 8);
	
	//SetInputMode(&RC_CtrlData.rc);
	
	//RemoteControlProcess(&(RC_CtrlData.rc));
	/*
	switch(GetInputMode())
	{
		case REMOTE_INPUT:
		{
			//ң��������ģʽ
			RemoteControlProcess(&(RC_CtrlData.rc));
		}break;
		case KEY_MOUSE_INPUT:
		{
			//ң��������ģʽ
			MouseKeyControlProcess(&RC_CtrlData.mouse,&RC_CtrlData.key);
		}break;
		case STOP:
		{
			//����ͣ��
		}break;
	}
	*/
	
}
