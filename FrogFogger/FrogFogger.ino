#include <Wire.h>
#include <Event.h>
#include <Timer.h>
#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
#include <dht11.h>
#include <DallasTemperature.h>

//Initialize Dallas Temperature Waterproof Module on pin D9
#define ONE_WIRE_BUS 9
OneWire ourWire(ONE_WIRE_BUS);
DallasTemperature sensors(&ourWire);

//Initialize 16x2 LCD on pins A4 and A5
LiquidCrystal_I2C lcd(0x27,16,2);

//Initialize DHT11 Humidity/Temperature Sensor
dht11 DHT11;

//Setup Pins
//ANALOG
#define BACKLIGHT_BTN A0
#define RUN_POT A1
#define PAUSE_POT A2
#define FAN_POT A3
//A4 - LCD
//A5 - LCD
//DIGITAL
#define RELAY_1 0
#define RELAY_2 1
#define RELAY_3 2
#define RELAY_4 3
//D4 - Unused
#define FLOAT_SWITCH 5
#define HUMID_SENS 6
//D7 - Unused
//D8 - Unused/Future Refiller
//D9 - Dallas Temperature Sensor - Set in initialization
//D10 - Unused
#define FAN_PWM 11
//D12 - Unused

long baseTime = millis();
boolean started = false;
boolean stopped = true; 
boolean reset = true;
  
void setup() {

	lcd.init();
	//Setup Digital Outputs
	pinMode(RELAY_1,OUTPUT);
	pinMode(RELAY_2,OUTPUT);
	pinMode(RELAY_3,OUTPUT);
	pinMode(RELAY_4,OUTPUT);
	pinMode(FAN_PWM,OUTPUT);
	//Setup Digital Inputs
	pinMode(FLOAT_SWITCH,INPUT);
	
	baseTime = millis(); 
  
}

void loop() {
	// put your main code here, to run repeatedly:
  
	long currentTime = millis();
  
  
	//Gather Sensor and Input Values  long
	
  //Read Time set pots and convert the returned 0-1023 value
  //to a value of 0-99 (minutes)
	int runValue = (((1023-analogRead(RUN_POT))/1023)*99);
	int pauseValue = (((1023-analogRead(PAUSE_POT))/1023)*99);
	
	
	//Start Fogging
	if (currentTime > baseTime && reset == true) {
		//Start Code
  
		started = true; 
		reset = false;
	}
	//Stop Fogging
	if (currentTime > (baseTime + ((runValue * 60) * 1000)) && started == true) {
		//Stop Code
	
		started = false;
		stopped = true;

	}
	//Reset Fogging Cycle
	if (currentTime > (baseTime + (((runValue * 60) * 1000) + ((pauseValue * 60) * 1000))) && stopped == true) {
		//Stop Stop and Reset
     
		stopped = false;
		reset = true;
		baseTime = millis();

	}
  
  
  
}

void lcdUpdate()
{
  //XXXXXXXXXXXXXXXX
  //AT:XX WT:XX H:XX
  //O:XX X:XX F:XX%
  lcd.setCursor(0,0);
  lcd.print("AT:");
  //lcd.print(airtempvar);
  lcd.print(" WT:");
  //lcd.print(watertempvar);
  lcd.print(" H:");
  //lcd.print(humidityvar);
  lcd.setCursor(0,1);
  lcd.print("O:");
  //lcd.print(ontimevar);
  lcd.print(" X:");
  //lcd.print(offtimevar);
  lcd.print(" FS:");
  //lcd.print(fanspeedvar);
  lcd.print("%");
  
}
