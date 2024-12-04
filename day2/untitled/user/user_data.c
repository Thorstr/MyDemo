/*
 * user_data.c
 *
 *  Created on: Dec 4, 2024
 *      Author: Thor
 */
#include "user_data.h"

// 电压、电流、功率数组存储
uint16_t voltage_array[SAMPLE_COUNT];
uint16_t current_array[SAMPLE_COUNT];  // 当前电流的数组（单位：mA）

void Init_USB_Data()
{
	float time;
	float omega = 2 * M_PI * FREQ;  // 角频率 = 2π * F

	for (int i = 0; i < SAMPLE_COUNT; i++)
	{
		time = i * SAMPLE_PERIOD;  // 计算每个采样点的时间

		// 生成电压和电流的正弦波形（电流与电压相差90°）
		voltage_array[i] = V_MAX * (sinf(omega * time) + 1) / 2.0f; // 电压正弦波，范围 [0, V_max]
		        current_array[i] = I_MAX * (sinf(omega * time + M_PI / 2) + 1) / 2.0f; // 电流正弦波，相位差 90°，范围 [0, I_max]
	}
}
