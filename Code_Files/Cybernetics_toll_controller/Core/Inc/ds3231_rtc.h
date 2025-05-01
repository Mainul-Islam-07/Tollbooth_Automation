#ifndef INC_DS3231_RTC_H_
#define INC_DS3231_RTC_H_

#include "main.h"
#include "i2c.h"

typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t dayofweek;
	uint8_t dayofmonth;
	uint8_t month;
	uint8_t year;
} TIME;

uint8_t decToBcd(int val);
int bcdToDec(uint8_t val);
void Set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);
void Get_Time (void);


void rtcDatafetch (void);
void rtcInit (void);

extern I2C_HandleTypeDef hi2c1;

#endif /* INC_DS3231_RTC_H_ */
