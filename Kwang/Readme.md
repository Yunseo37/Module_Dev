### Kwang Directory 설명

<hr>

### 1. Blinky_LED

#### 1.1 실제 LED Port

- MODULE_P10, 2

#### 1.2 목적

- GPIO를 제어하여 LED를 500초마다 깜빡이게 한다.

#### 1.3 사용함수

- Blinky_LED.h

```
void initLED(void)
{
    // PinMode를 Output으로 설정
    IfxPort_setPinModeOutput(LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

    IfxPort_setPinHigh(LED); // LED를 켠다
}
```

```
void blinkLED(void)
{
    IfxPort_togglePin(LED); // LED Off -> On, On -> Off로 변환
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME)); // WAIT_TIME만큼 기다리는 함수
}
```

#### 1.4 CPU0_main.c
```
    ...

    initLED();
    while()
    {
        blinkLED();
    }
    ...
```    

<hr>

### 2. ERUInterrupt

#### 2.1 PORT 설정

- Button Input Pin : P02, 1
- LED Output Pint : P10,1 , P10,2

#### 2.2 목적

- Interrupt를 통해서 LED를 toggle한다

#### 2.3 사용 변수 & 함수

- ERUconfig

```
typedef struct
{
    IfxScu_Req_In *reqPin;                      /* External request pin                                             */
    IfxScuEru_InputChannel inputChannel;        /* Input channel EICRm depending on input pin                       */
    IfxScuEru_InputNodePointer triggerSelect;   /* Input node pointer                                               */
    IfxScuEru_OutputChannel outputChannel;      /* Output channel                                                   */
    volatile Ifx_SRC_SRCR *src;                 /* Service request register                                         */
} ERUconfig;
```

- initPeripheralsAndERU()
```
    // Port 설정 
    IfxPort_setPinMode(TRIGGER_PIN, IfxPort_Mode_inputPullUp);              
    IfxPort_setPinMode(LED1, IfxPort_Mode_outputPushPullGeneral);            
    IfxPort_setPinMode(LED2, IfxPort_Mode_outputPushPullGeneral);            
    IfxPort_setPinState(LED1, IfxPort_State_high);                           
    IfxPort_setPinState(LED1, IfxPort_State_low);                           

    // Interrupt Trigger가 발생할 External Request pin 추가
    g_ERUconfig.reqPin = REQ_IN_D3; /* Select external request pin */

    // 요청 External Request pin 초기화
    IfxScuEru_initReqPin(g_ERUconfig.reqPin, IfxPort_InputMode_pullDown);

    // Input Pin에 따른 Input Channel 설정
    g_ERUconfig.inputChannel = (IfxScuEru_InputChannel) g_ERUconfig.reqPin->channelId;

    // RisingEdge에서 inputChannel에 trigger를 하도록 설정
    IfxScuEru_enableRisingEdgeDetection(g_ERUconfig.inputChannel);     

    // Falling Edge 제거
    // IfxScuEru_enableFallingEdgeDetection(g_ERUconfig.inputChannel);        

    // 시그널 도착지 설정
    g_ERUconfig.outputChannel = IfxScuEru_OutputChannel_0;                  /* OGU channel 0                    */
    // Output Gating Unit과 연결
    g_ERUconfig.triggerSelect = IfxScuEru_InputNodePointer_0;

    /* 연결 매트릭스, 이벤트 트리거 로직 ETL 블록 */
    /* 트리거 이벤트 생성 활성화(EIENx 등록) */
    IfxScuEru_enableTriggerPulse(g_ERUconfig.inputChannel);
    // Input Channel과 Output Channel 설정
    IfxScuEru_connectTrigger(g_ERUconfig.inputChannel, g_ERUconfig.triggerSelect);

    // 출력 채널 구성, 출력 게이팅 유닛 OGU(IGPy 등록)
    IfxScuEru_setInterruptGatingPattern(g_ERUconfig.outputChannel, IfxScuEru_InterruptGatingPattern_patternMatch);

    // 서비스 요청 설정
    // 출력 채널에 따라 소스 포인터 가져오기(출력 채널0의 경우 SRC_SCUERU0)
    g_ERUconfig.src = &MODULE_SRC.SCU.SCU.ERU[(int) g_ERUconfig.outputChannel % 4];
    IfxSrc_init(g_ERUconfig.src, IfxSrc_Tos_cpu0, ISR_PRIORITY_SCUERU_INT0);
    IfxSrc_enable(g_ERUconfig.src);
```

![외부 인터럽트 Unit Overview](./../images/외부%20인터럽트.jpg)

<hr>

### 3. AppScheduler

#### 3.1 목적

- STM을 활용해서 시간을 측정하고, 이를 활용한 AppScheduler를 만든다.

#### 3.1 Driver_Stm 원리

- STM을 사용해서 Flag 마다 Interrupt를 on 한다
- 일정 시간마다 Flag 실행되면 실제 함수를 진행

#### 3.2 Driver_Stm 함수

- Interrupt 등록

```
    IFX_INTERRUPT(STM_Int0Handler, 0, 100); // IFX_INTERRUPT(ISR, 0, 우선순위)
```

- Driver_Stm_Init()

```
    g_Stm.stmConfig.ticks = 100000u; // 100000마다, 즉 1ms마다 진행되도록
```

- STM_Int0Handler()

```
    IfxCpu_enableInterrupts();

    IfxStm_clearCompareFlag(g_Stm.stmSfr, g_Stm.stmConfig.comparator); // 0으로 다시 세팅
    IfxStm_increaseCompare(g_Stm.stmSfr, g_Stm.stmConfig.comparator, 100000u); // 1ms마다 인터럽트 실행
```

#### 3.3 AppScheduler 함수

- AppScheduling() : stSchedulingInfo 진행되는 것에 따라 함수를 실행
- AppTask{N}ms() : {N}ms 마다 주기적으로 반복하는 함수