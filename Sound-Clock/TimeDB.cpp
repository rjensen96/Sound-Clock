#include <Arduino.h>
#include <WiFi.h>
#include "TimeDB.h"
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <time.h>  

const char *TimeDB::APIKey = "I0K9WRO2BVRO";

TimeDB::TimeDB() : hour(0), minute(0) {
}

bool TimeDB::SetTimezone(String timezone) {
    TimeDB::timezone = timezone;
}


bool TimeDB::UpdateTime() {
//    Make a request to http://api.timezonedb.com/v2.1/get-time-zone?key=I0K9WRO2BVRO&format=json&by=zone&zone=America/Denver
// Example response; {"status":"OK","message":"","countryCode":"US","countryName":"United States","zoneName":"America\/Denver","abbreviation":"MST","gmtOffset":-25200,"dst":"0","zoneStart":1604217600,"zoneEnd":1615712399,"nextAbbreviation":"MDT","timestamp":1607117106,"formatted":"2020-12-04 21:25:06"}

   HTTPClient http;

   String serverPath = "http://api.timezonedb.com/v2.1/get-time-zone?key=I0K9WRO2BVRO&format=json&by=zone&zone=" + timezone;
      
  // Your Domain name with URL path or IP address with path
  http.begin(serverPath.c_str());
      
  // Send HTTP GET request
  int httpResponseCode = http.GET();
      
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    JSONVar myObject = JSON.parse(payload);
    long timestamp = myObject["timestamp"];
    
    struct tm * ptm;
    ptm = gmtime ( &timestamp );
    hour = ptm->tm_hour;
    minute = ptm->tm_min;
    Serial.println("HOUR IS: " + (String)hour);
    Serial.println("MINUTE IS: " + (String)minute);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
}
