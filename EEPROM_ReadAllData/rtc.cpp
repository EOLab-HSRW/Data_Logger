#include "rtc.h"

String formatToUTC(time_t time) {
  setTime(time);
  String utc = String(year()) + "-" + String(month()) + "-" + String(day()) + "T" + String(hour()) + ":" + String(minute()) + ":" + String(second()) + "Z";
  return utc;
}
