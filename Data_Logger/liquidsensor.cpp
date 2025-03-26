#include "liquidsensor.h"
#include <Arduino.h>


bool liquidsensor_init(){
   // Setup
	pinMode(WB_IO1, OUTPUT | PULLUP);
	digitalWrite(WB_IO1, HIGH);

	adcAttachPin(WB_A1);

	analogSetAttenuation(ADC_11db);
	analogReadResolution(12);
  return true;
}


unsigned long getCurrent(){
  int i;
	int sensor_pin = WB_A1; // select the input pin for the potentiometer
	int mcu_ain_raw = 0;
	int average_adc_raw;
	float voltage_mcu_ain;  //mv as unit
	float current_sensor; // variable to store the value coming from the sensor

	for (i = 0; i < NO_OF_SAMPLES; i++)
	{
		mcu_ain_raw += analogRead(sensor_pin);
	}
	average_adc_raw = mcu_ain_raw / NO_OF_SAMPLES;

	voltage_mcu_ain = esp_adc_cal_raw_to_voltage(average_adc_raw);

	current_sensor = voltage_mcu_ain / 149.9*1000; //WisBlock RAK5801 (0 ~ 20mA) I=U/149.9 (mA)
	
  unsigned long curr = (unsigned long)(current_sensor *100);

  return curr;
}

//20 Point lookup tables, covering ADC readings from 2880 to 4096, step size of 64
const uint32_t lut_adc1_low[LUT_POINTS] = {2240, 2297, 2352, 2405, 2457, 2512, 2564, 2616, 2664, 2709,
                                                  2754, 2795, 2832, 2868, 2903, 2937, 2969, 3000, 3030, 3060};
const uint32_t lut_adc1_high[LUT_POINTS] = {2667, 2706, 2745, 2780, 2813, 2844, 2873, 2901, 2928, 2956,
                                                   2982, 3006, 3032, 3059, 3084, 3110, 3135, 3160, 3184, 3209};
//Only call when ADC reading is above threshold
uint32_t calculate_voltage_lut(uint32_t adc, uint32_t vref)
{
    //Get index of lower bound points of LUT
    uint32_t i = (adc - LUT_LOW_THRESH) / LUT_ADC_STEP_SIZE;

    //Let the X Axis be Vref, Y axis be ADC reading, and Z be voltage
    int x2dist = LUT_VREF_HIGH - vref;                 //(x2 - x)
    int x1dist = vref - LUT_VREF_LOW;                  //(x - x1)
    int y2dist = ((i + 1) * LUT_ADC_STEP_SIZE) + LUT_LOW_THRESH - adc;  //(y2 - y)
    int y1dist = adc - ((i * LUT_ADC_STEP_SIZE) + LUT_LOW_THRESH);        //(y - y1)

    //For points for bilinear interpolation
    int q11 = lut_adc1_low[i];                    //Lower bound point of low_vref_curve
    int q12 = lut_adc1_low[i + 1];                //Upper bound point of low_vref_curve
    int q21 = lut_adc1_high[i];                   //Lower bound point of high_vref_curve
    int q22 = lut_adc1_high[i + 1];               //Upper bound point of high_vref_curve

    //Bilinear interpolation
    //Where z = 1/((x2-x1)*(y2-y1)) * ( (q11*x2dist*y2dist) + (q21*x1dist*y2dist) + (q12*x2dist*y1dist) + (q22*x1dist*y1dist) )
    int voltage = (q11 * x2dist * y2dist) + (q21 * x1dist * y2dist) + (q12 * x2dist * y1dist) + (q22 * x1dist * y1dist);
    voltage += ((LUT_VREF_HIGH - LUT_VREF_LOW) * LUT_ADC_STEP_SIZE) / 2; //Integer division rounding
    voltage /= ((LUT_VREF_HIGH - LUT_VREF_LOW) * LUT_ADC_STEP_SIZE);    //Divide by ((x2-x1)*(y2-y1))
    return (uint32_t)voltage;
}

inline int decode_bits(uint32_t bits, uint32_t mask, bool is_twos_compl)
{
    int ret;
    if (bits & (~(mask >> 1) & mask)) 
    {      
        //Check sign bit (MSB of mask)
        //Negative
        if (is_twos_compl) 
        {
            ret = -(((~bits) + 1) & (mask >> 1));   //2's complement
        } 
        else 
        {
            ret = -(bits & (mask >> 1));    //Sign-magnitude
        }
    } 
    else 
    {
        //Positive
        ret = bits & (mask >> 1);
    }
    return ret;
}


uint32_t read_efuse_vref(void) {
    esp_adc_cal_characteristics_t adc_chars;
    
    // Charakterisiere den ADC mit Standard-VREF 1100 mV
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
    
    // Gib die ausgelesene eFuse-VREF zurück
    return adc_chars.vref;
}


inline uint32_t interpolate_two_points(uint32_t y1, uint32_t y2, uint32_t x_step, uint32_t x)
{
    //Interpolate between two points (x1,y1) (x2,y2) between 'lower' and 'upper' separated by 'step'
    return ((y1 * x_step) + (y2 * x) - (y1 * x) + (x_step / 2)) / x_step;
}

uint32_t esp_adc_cal_raw_to_voltage(uint32_t adc_raw)
{
	uint32_t vref = read_efuse_vref();

	uint32_t lut_voltage = calculate_voltage_lut(adc_raw, vref);
	if (adc_raw >= LUT_LOW_THRESH) 
    {
		if(adc_raw <= LUT_HIGH_THRESH)
        {
			uint32_t linear_voltage = (((((vref * 196602 / 4096)) * adc_raw) + (65536/2)) / 65536) + 142;
			return interpolate_two_points(linear_voltage, lut_voltage, LUT_ADC_STEP_SIZE, (adc_raw - LUT_LOW_THRESH));
		} 
        else 
        {
			return lut_voltage;
		}
	}
    else if (adc_raw == 0) 
    {
        return 0;
    }
	else 
    {
		return ((((((vref * 196602 /4096 ) * adc_raw) + (65536/2))) / 65536) + 142);
	}
}