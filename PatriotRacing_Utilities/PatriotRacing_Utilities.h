/*
 
	Program name: Bob Jones Patriot Racing F24 race car data logger
	 
	Revision table
	rev   author      date        description
	1.0   Kris   5/9/2018 	Initial creation
	2.0   Kris 	4/24/2020	modified struct for board 6, added driver array
	3.0   Kris 	4/28/2020	added a few elements to the main struct
	4.0   Kris 	5/23/2020	renamed many elements in struct
	5.0   Kris 	11/18/2020	updated driver list
	6.0   Kris 	12/3/2020	create menu library
	7.0   Kris 	07/22/2022  updated driver list
	8.0   Kris 	07/22/2023  updated driver list  
	9.0   Kris 	02/22/2024  added struct definition for race monitor 
	10.0   Kris 08/09/2024  updated driver list for 2024-2025 season
	11.0   Kris 09/06/2024  updated Transceiver struct to pass altitude

*/

#ifndef PATRIOT_RACING_UTILITIES_H
#define PATRIOT_RACING_UTILITIES_H
#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif

#ifdef __cplusplus
#include "Arduino.h"
#endif
#include "Colors.h"


#define UTILITIES_VERSION 11.0

#define I2C_SLAVE_ADDR 0x55
#define SDA_PIN 12
#define SCL_PIN 13
#define FLAG_NONE 0
#define FLAG_GREEN 1
#define FLAG_YELLOW 2
#define FLAG_RED 3
#define I2C_BUS_SPEEED 600000


// note the wirelss will not send at 300 or even 1.2 but needed to keep the byte index matching the
// constants used by EBYTE libs
const char *AirRateText[] = {"300", "1.2k", "2.4k", "4.8k", "9.6k", "19.2k"};    

//setup screen text transmitter power level 1 w  verstion
const char *HighPowerText[] = {"30 db",  "27 db", "24 db", "21 db"};

//setup screen text transmitter power level 100 mw  verstion
const char *PowerText[] = {"20 db",  "17 db", "14 db", "10 db"};

//setup screen text for the sensor type connected to the I2C bus
const char *SensorTypeText[] = {"None",  "GPS", "Load"};

// complete list of team members--never know who will drive
// we can have a maximum of 32 drivers, 18 listed below
const char *DriverNames[] = 	{"Adi", "Andrew", "Ben", "Brooks", "Bryce", "CJ", 
		"Conrado", "Delmont", "Elliot", "Grace", "Isaac", "Julia", "Liam", 
		"Lyla", "Michael", "Nathan", "Nikita","Susan", "Tucker"};

const char *ReadText[] = 	{"Read"};          //setup screen text for background color

const char *InvertText[] = 	{"Black", "White"};          //setup screen text for background color
const char *OrientationText[] = {"Up", "Down"};          //setup screen text for screen orientation
const char *YesNoText[] = 	{"No", "Yes"};               //show diagnostics

// index of array matches time in seconds, value==element number
const char *SendTimeText[] = 	{"Off", "1 sec", "2 sec", "3 sec", "4 sec","5 sec"};  //duration for transceiver send time


//delay for when GPS records start time
// I think GPS read is more accurate when the car is moving
// so let's wait a few seconds until the car starts moving
const char *GPSReadTimeText[] = 	{"0 sec", "5 sec", "10 sec"};  // text for the menu option
uint32_t GPSReadTime[] = {0, 5000, 10000}; // actual delay value in millis

// index of array matches distance in meters, value==element number
//const char *GPSToleranceText[] = {"Off", "1 m", "2 m", "3 m", "4 m","5 m", "6 m", "7 m", "8 m", "9 m", "10 m", "11 m", "12 m", "13 m", "14 m", "15 m"};  //tolerance for GPS start location

// GPS tolerance distance in feet, index of array is in meters which is what the GPS lib uses
const char *GPSToleranceText[] = {"Off", "3 ft", "6 ft", "9 ft", "13 ft","16 ft", "19 ft", "23 ft", "26 ft", "29 ft"};  //tolerance for GPS start location
  
 
 // accelerometer 
const char *AccelFSRange[] = 	{"+/- 2 G", "+/- 4 G", "+/- 8 G", "+/- 16 G"};  
float AccelFSBits[] = {16384.0, 8192.0, 4096.0, 2048.0};

const char *AccelLPFilterText[] = 	{"256 Hz", "188 Hz", "98 Hz", "42 Hz", "20 Hz", "10 Hz", "5 Hz"}; 

const char *AccelHPFilterText[] = 	{"Off", "5 Hz", "2.5 Hz", "1.25 Hz", "0.63 Hz"}; 


// constants for 10K NTC thermistors

#define NTC_A  3.354016E-03  // from the data sheet
#define NTC_B  2.569850E-04  // from the data sheet
#define NTC_C  2.620131E-06  // from the data sheet
#define NTC_D  6.383091E-08  // from the data sheet
#define NTC_R1  9800.0       // resistor for thermsitor voltage divider


/* 
car designator
*/
 
#define BLUE_CAR 	0
#define RED_CAR 	1
#define WHITE_CAR 	2

const char *CarText[] = {"Blue", "Red", "White"};  


/* 
tires types
*/

const char *MotorText[] = {"C0", "C1", "C2", "C3", "U0", "U1", "U2", "U3", "U4", "U5", "U6", "U7", "U8", "U9"}; 

const char *TireText[] = {"Kojaks", "Duranos", "Ones", "Pro Ones", "Test"}; 

/* 
tire pressures
let the team know what the rated PSI is
*/

int TirePSIVal[] = {90, 120, 165, 115, 45}; 


/* 
tire diameters
note the last element is for the data logger test stand so the car speed is somewhat real given the 2200 rpm the fan spins at

 Radius calculations for ones
 old ones were 8.897646066
 ones
 circumference with 100 lb driver = 56 inches
 circumference with 144 lb driver = 57.25
 spit the difference 56.625, r = 9.012156264821

 kojaks
 circumference with 100 lb driver = 58.75 inches
 circumference with 144 lb driver = 58.5
 spit the difference 58.625, r = 9.3304664198
*/

float TireRadius[] = {9.3304664198, 9.085624504, 9.012156264821, 9.085624504, 1.95 }; 

// restore data types
#define STATUS_OK 0
#define STATUS_RESTORE 1
#define STATUS_PITSTOP 2

 // for Warnings
#define SD_WARNING 1
#define BAT_WARNING 2
#define TEMP_WARNING 4
#define RACE_START 8
#define AMP_WARNING 16
#define LAPAMP_WARNING 32		// 5 BIT
#define GFORCE_WARNING 64
#define GPS_WARNING 128
#define REPLAY_RACE 256 		
#define KEY_OFF 512 			
#define SPEED_FAIL 1024 		//10 BIT
#define AMBIENT_FAIL 2048 		
#define EBYTE_FAIL 4096 
#define SSD_FAIL 8192 

/*
structure definition for serial transceiver communications
*/

struct Transceiver {

	// max is 58 bytes per packet
	uint16_t RPM;            	    // RPM(12)
    uint16_t WARNINGS;    			// WARNINGS(16)
	uint16_t TEMPF_TEMPX;       	// TEMPF(8) TEMPX(8) (Motor and auxiliary temp)
    uint16_t VOLTS_LAPS;        	// VOLTS(9) LAPS(7)
    uint16_t SPEED_EREM;        	// SPEED(9) EREM (7)
    uint16_t DISTANCE_TREM;     	// DISTANCE(9) TREM(7)
    uint16_t AMPS_D0ID;         	// AMPS(11) D0ID(5) 
    uint16_t ENERGY_D1ID;     	    // ENERGY(10) D1ID(5)
    uint16_t LAP2AMPS_D2ID;   	    // LAP2AMPS(9) D2ID(5)
    uint16_t RACETIME;          	// RACETIME(16)
    uint16_t D0TIME_ALTITUDE;      	// D0TIME(12) ALTITUDE(4-1)	
    uint16_t D1TIME_ALTITUDE;      	// D1TIME(12) ALTITUDE(4-2)
    uint16_t D2TIME_ALTITUDE;      	// D2TIME(12) ALTITUDE(4-3)
    uint16_t LT;            	    // LAPTIME(16)
    uint16_t GFORCE_DRIVERNO;       // GFORCE(9) DRIVER NUMBER(2) DISTANCE TO START(2) (lsb)
    uint16_t TWHR_LAPAMPS; 			// TotalEnergy(7) LAPAMPS(9)  (TotalEngery / 10, Lap Amps / 10)	
	uint16_t LAPENERGY_DTS; 	 	// LAPENERGY(9)  DISTANCE TO START(7) (msb)	

} ; // __attribute__((packed, aligned(4)));


/*
structure definition for I2C communications between race monitor and wifi server
1 2
2 4
3 8
4 16
5 32
6 64
7 128
8 256
9 512
10 1024
11 2048

*/


struct RACE_MONITOR {

	char CARNUM0[5];
	char CARNUM1[5];
	char CARNUM2[5];
	char CARNUM3[5];
	char CARNUM4[5];
	char CARNUM5[5];
	char CARNUM6[5];
	char CARNUM7[5];
	uint32_t CAR0;       // RED  	best lap time (10 bits) 2. lap time 0-8 min (10) 3. position0-32 (5) 4. laps (7) 
	uint32_t CAR1;       // WHITE 	best lap time (10 bits) 2. lap time 0-8 min (10) 3. position0-32 (5) 4. laps (7)
	uint32_t CAR2;       // BLUE 	best lap time (10 bits) 2. lap time 0-8 min (10) 3. position0-32 (5) 4. laps (7)
	uint32_t CAR3;       // Car3 1. best lap time (10 bits) 2. lap time 0-8 min (10) 3. position0-32 (5) 4. laps (7)
	uint32_t CAR4;       // Car4 1. best lap time (10 bits) 2. lap time 0-8 min (10) 3. position0-32 (5) 4. laps (7)
	uint32_t CAR5;       // Car5 1. best lap time (10 bits) 2. lap time 0-8 min (10) 3. position0-32 (5) 4. laps (7)
	uint32_t CAR6;       // Car6 1. best lap time (10 bits) 2. lap time 0-8 min (10) 3. position0-32 (5) 4. laps (7)
	uint32_t CAR7;       // Car7 1. best lap time (10 bits) 2. lap time 0-8 min (10) 3. position0-32 (5) 4. laps (7)

	uint32_t FS;       // FlagStatus (2)

} ; // __attribute__((packed, aligned(4)));



#endif