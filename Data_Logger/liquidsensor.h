#ifndef LIQUIDSENSOR_H
#define LIQUIDSENSOR_H

#include <Arduino.h>
#include <stdint.h>
#include "esp_adc_cal.h"  

// Lookup-Tabelle und ADC-Kalibrierung
#define LUT_POINTS                     20
#define LUT_VREF_LOW                   1000
#define LUT_VREF_HIGH                  1200
#define LUT_ADC_STEP_SIZE              64
#define LUT_LOW_THRESH                 2880
#define LUT_HIGH_THRESH                (LUT_LOW_THRESH + LUT_ADC_STEP_SIZE)

#define VREF_OFFSET                    1100
#define VREF_STEP_SIZE                 7
#define VREF_MASK                      0x1F

#define NO_OF_SAMPLES                  128  

// Funktionsdeklarationen
bool liquidsensor_init();
unsigned long getCurrent();
uint32_t calculate_voltage_lut(uint32_t adc, uint32_t vref);
uint32_t read_efuse_vref(void);
uint32_t esp_adc_cal_raw_to_voltage(uint32_t adc_raw);
int decode_bits(uint32_t bits, uint32_t mask, bool is_twos_compl);
uint32_t interpolate_two_points(uint32_t y1, uint32_t y2, uint32_t x_step, uint32_t x);

#endif  // LIQUIDSENSOR_H
