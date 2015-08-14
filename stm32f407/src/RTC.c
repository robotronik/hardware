#include "RTC.h"

RTC_HandleTypeDef Alarme_90secondes;

void init_RTC()
{
    //__HAL_RCC_PWR_CLK_ENABLE();
    ////HAL_PWR_EnableBkUpAccess();
    //if(!(*(volatile uint32_t *) (BDCR_RTCEN_BB)))__HAL_RCC_RTC_ENABLE();
    ////__HAL_RCC_RTC_CONFIG();
    ////__HAL_RCC_RTC_ENABLE();

    //legacy code
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    __PWR_CLK_ENABLE();

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                          |RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    //HAL_RCC_ClockConfig(&RCC_ClkInitStruct, ((uint32_t)0x00000005));

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);



    Alarme_90secondes.Instance = RTC;
    Alarme_90secondes.Init.HourFormat = RTC_HOURFORMAT_24;
    Alarme_90secondes.Init.AsynchPrediv = 127;
    Alarme_90secondes.Init.SynchPrediv = 255;
    Alarme_90secondes.Init.OutPut = RTC_OUTPUT_DISABLE;
    Alarme_90secondes.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    Alarme_90secondes.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    //HAL_RTC_Init(&Alarme_90secondes);

    //HAL_RTC_Init(&Alarme_90secondes);
}

void demarre_alarme_90secondes()
{

    //time
	RTC_TimeTypeDef Time_Structure;
	Time_Structure.Hours=0;
	Time_Structure.Minutes=0;
	Time_Structure.Seconds=0;
	Time_Structure.SubSeconds=0;
	Time_Structure.TimeFormat=RTC_HOURFORMAT12_AM;
	Time_Structure.DayLightSaving=RTC_DAYLIGHTSAVING_NONE;
	Time_Structure.StoreOperation=RTC_STOREOPERATION_RESET; //choisi de manière random
	HAL_RTC_SetTime(&Alarme_90secondes,&Time_Structure,RTC_FORMAT_BIN);

    //date
    RTC_DateTypeDef Date_Structure;
    Date_Structure.WeekDay   =   RTC_WEEKDAY_MONDAY ;
    Date_Structure.Month   =   RTC_MONTH_JANUARY ;
    Date_Structure.Date   =   1 ;
    Date_Structure.Year   =   0 ;
    HAL_RTC_SetDate(&Alarme_90secondes,&Date_Structure,RTC_FORMAT_BIN);

    //alarm
    RTC_AlarmTypeDef Alarm_Structure;
    Alarm_Structure.AlarmTime=Time_Structure;
    Alarm_Structure.AlarmTime.Minutes=Time_Structure.Minutes;
    Alarm_Structure.AlarmTime.Seconds=Time_Structure.Seconds+3; //89 secondes au lieu de 90 (on sait jamais)
    Alarm_Structure.AlarmMask=RTC_ALARMMASK_NONE;
    Alarm_Structure.AlarmSubSecondMask=RTC_ALARMSUBSECONDMASK_ALL;
    Alarm_Structure.AlarmDateWeekDaySel=RTC_ALARMDATEWEEKDAYSEL_DATE;
    Alarm_Structure.AlarmDateWeekDay=1;
    Alarm_Structure.Alarm=RTC_ALARM_A;
    HAL_RTC_SetAlarm_IT(&Alarme_90secondes, &Alarm_Structure,RTC_FORMAT_BIN);

    if(!(*(volatile uint32_t *) (BDCR_RTCEN_BB)))__HAL_RCC_RTC_ENABLE();
}


void RTC_Alarm_IRQHandler(void)
{
    test_led();
}
