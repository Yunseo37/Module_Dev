#include "main.h"
#define PI 3.14159265358979323
#define SAMPLE_TIME 0.001
#define ENC_A_CH &MODULE_P00,8
#define ENC_B_CH &MODULE_P00,9

boolean ENCA;
boolean ENCB;
boolean ENCA_old;
boolean ENCB_old;
uint32 trig_A;
uint32 trig_B;
boolean intr_A;
boolean intr_B;
float32 duty[2];
float32 Vin;
int S;
int S_old;
int PosCnt=0;
int PosCntd=0;
float32 Direction;
float32 Pos_rad;
float32 ome_d;
float32 Pos_rad_d;
int Pos_deg;
float32 theta;
float32 theta_old;
float32 theta_d_old;
float32 w=0;
float32 Wd;
float32 w_old=0;
float32 error_w=0;
uint32 W_RPM;
uint32 ACnt;
float32 error_w_int_old;
float32 error_w_int;
float32 error_w_det_old;
float32 error_w_det;
float32 du_w;
float32 kp=0.5;
float32 ki=0.8;
float32 kd=0.1;
float32 t;
float32 per;
float32 per_old;
float32 W_st;
float32 V_st;

IfxCpu_syncEvent g_cpuSyncEvent = 0;
int motor_pid(int w_ref);

int core0_main(void)
{
    IfxCpu_enableInterrupts();
    
    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    Init_Mystdio();
    init_gpt2();
    Init_DCMotors();
    init_gpt2();
    Init_GPIO();

    int target_PWM;
    int now_PWM = 0;

    while(1)
    {
        target_PWM = 30;

        setcntDelay(0);
        while (getcntDelay() < 1000000)
        {
            now_PWM = target_PWM - motor_pid(now_PWM);
            movChA_PWM(now_PWM, 0);

        }

        target_PWM = 80;
        setcntDelay(0);
        while (getcntDelay() < 1000000)
        {
            now_PWM = target_PWM - motor_pid(now_PWM);
            movChA_PWM(now_PWM, 0);

        }

    }
    return (1);
}

float32 LPF(float32 y_old, float32 x, float32 Ts, float32 band)
{
    double A1=Ts/(Ts+1/band);
    float32 y = y_old+A1*(x-y_old);

    return y;
}

int motor_pid(int w_ref)
{
    ACnt++;
    Wd=2;
    float32 Ts=SAMPLE_TIME;
    t = ACnt * Ts;

    ENCA = IfxPort_getPinState(ENC_A_CH); // Encoder A signal state
    ENCB = IfxPort_getPinState(ENC_B_CH); // Encoder B signal state
    if (ENCA == FALSE && ENCB == FALSE)
    {
        S = 0;
    }
    else if(ENCA == FALSE && ENCB == TRUE)
    {
        S = 1;
    }
    else if(ENCA == TRUE && ENCB == TRUE)
    {
        S = 2;
    }
    else if(ENCA == TRUE && ENCB == FALSE)
    {
        S = 3;
    }

    if (S - S_old==1 || S - S_old == -3)
    {
        PosCnt = PosCntd + 1;
        Direction = 1;
    }
    else if (S - S_old ==-1 || S - S_old == 3)
    {
        PosCnt = PosCntd - 1;
        Direction = -1;
    }
    S_old = S;



    Pos_rad = PosCnt * 2 * PI/48;   
    Pos_deg = (int)(PosCnt*360/48);
    PosCntd=PosCnt;
    ENCA_old=ENCA;
    ENCB_old=ENCB;
    theta=Pos_rad;
    w=(theta-theta_old)/Ts;
    w=LPF(w_old, w, Ts, 200);
    w_old=w;
    W_RPM=(uint32)(60*w/(2*PI));
    theta_old=theta;

    error_w = (float)w_ref - w;
    error_w_int=error_w_int_old+(error_w)*Ts;
    error_w_int_old=error_w_int;
    error_w_det=(error_w_det_old-error_w)/Ts;
    error_w_det_old=error_w_det;

//    if (error_w_int>10)
//    {error_w_int=10;}

    Vin = kp*error_w + ki*error_w_int + kd*error_w_det;

    if (Vin>90)
    {
        Vin=90;
    }
    else if(Vin<0)
    {
        Vin=0;
    }

    my_printf("error_w: %.1f, Vin: %.1f\n", error_w, Vin);
    return (int)Vin;
}
