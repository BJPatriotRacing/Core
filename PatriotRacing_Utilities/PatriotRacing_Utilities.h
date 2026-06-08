/*
 
	Program name: Bob Jones Patriot Racing F24 race car data logger
	 
	Revision table
	rev   author    date        description
	1.0    Kris     5/9/2018 	Initial creation
	2.0    Kris 	4/24/2020	modified struct for board 6, added driver array
	3.0    Kris 	4/28/2020	added a few elements to the main struct
	4.0    Kris 	5/23/2020	renamed many elements in struct
	5.0    Kris 	11/18/2020	updated driver list
	6.0    Kris 	12/3/2020	create menu library
	7.0    Kris 	07/22/2022  updated driver list
	8.0    Kris 	07/22/2023  updated driver list  
	9.0    Kris 	02/22/2024  added struct definition for race monitor 
	10.0   Kris 	08/09/2024  updated driver list for 2024-2025 season
	11.0   Kris 	09/06/2024  updated Transceiver struct to pass altitude
	12.0   Kris 	10/03/2024  added accelerometer menu text for directon and send data and updated EBYTE struct
	13.0   Kris 	12/12/2024  added GPS data to EBYTE struct so we can plot race lines (and now ADDING VERSION TO FILELAME)
	14.0   Kris 	12/12/2024  added chars for cyborg
	15.0   Kris 	03/09/2025  added direction text for accelerometer install direction
	16.0   Kris 	03/14/2026  move #defines that are not changeable
	16.1   Kris 	05/27/2026  added CYBORG selector for amps 

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

#define UTILITIES_VERSION 16.3


/*


These definitions are listed in this .h, hidden away from the .ino programmer--namely because many are tied to hardware and cannot
be changed. Others are ID type and there are no need to change them

defines like colors and text locations can be changed and are in the .ino file


*/
// restore data types
#define STATUS_OK 0
#define STATUS_RESTORE 1
#define STATUS_PITSTOP1 2
#define STATUS_PITSTOP2 3

#define KEYSTATUS_NO_CHANGE 0
#define KEYSTATUS_TURNED_ON 1

// for Warnings
#define KEY_OFF 1
#define GPS_WARNING 2
#define RACE_START 4
#define AME_STATUS 8 
#define TURBO_STATUS 16

#define LAPAMP_WARNING 32		// 5 BIT
#define GFORCE_WARNING 64
#define AMP_WARNING 128
#define EXTADC_WARNING 256 		
#define BAT_WARNING 512		
#define SPEED_FAIL 1024 		//10 BIT
#define TEMP_WARNING 2048		
#define EBYTE_FAIL 4096 
#define SSD_FAIL 8192 

#define I2C_SLAVE_ADDR 0x55
#define SDA_PIN 12
#define SCL_PIN 13
#define FLAG_NONE 0
#define FLAG_GREEN 1
#define FLAG_YELLOW 2
#define FLAG_RED 3
#define I2C_BUS_SPEEED 600000

#define MENU_ENTER_TIMEOUT 3000
#define MENU_EXIT_TIMEOUT 20000

// we had an issue where batteries were dropped very low and caused error key stat reads
// this setting allows us to set the key voltage limit
// inside the current sensor the battery voltage goes through voltage divider (1/11 ohms, so
// the math sets the key on voltage to be around 3.5 volts
#define DIGITAL_ON_LIMIT 200

// location for large data font--need to change if different font is used
// #define DATA_X 55 code based to account for left / right justification
#define GRAPH_X 45
#define GRAPH_Y 210
#define GRAPH_W 255
#define GRAPH_H 160
#define DATA_Y 55
#define LADATA_X 305
#define LADATA_Y 182
#define NO_BUTTON 0
#define L_BUTTON 1
#define C_BUTTON 2
#define R_BUTTON 3
#define EITHER_BUTTON 4
#define C_BUTTON_LONG 5

#define DISABLE_WDT 0
#define ENABLE_WDT 1
#define RESET_WDT 2

// error codes for data file re-reading
#define RR_ERROR -1
#define RT_HEADER 0x01
#define RT_DATA 0x02


#define DATA_DELIMITER 44
#define METERS_TO_FEET 3.28084f
#define MPH_TO_KMPH 1.60934f
#define UPDATE_LIMIT 500  // speed (ms) that we update display and write to chip. changing may have huge impacts
#define RACE_NOTSTARTED 0
#define RACE_INPROGRESS 1
#define RACE_FINISHED 2
#define TIME_HEADER "T"
#define RACE_EXTENSION 300  // seconds we add to the 90 min mark to account for posible race time stop (red flag very rare)
#define RACE_TIME_SECONDS 5400
#define STATUS_TYPE 5
#define STATUS_RESULT 145
#define MINIMUM_PULSES 2

// pin defines
#define EXTADC_KEY_PIN CH0
#define EXTADC_AM_PIN CH1
#define EXTADC_THM_PIN CH2
#define EXTADC_THX_PIN CH3
#define EXTADC_THROTTLE_PIN CH4
#define EXTADC_CYBORGFIRSTLIMIT_PIN CH5
#define EXTADC_ENABLE_AME_PIN CH6
#define EXTADC_VM_PIN CH7

// pins 0 and 1 are serial1 for ebyte
#define DRS_PIN 2     // display reset
#define CD_PIN 3      // card detect for SD card
#define OUTPUT_PIN 4  // pin to generate ESC signal (should result in 1 to 3.3 volts)
#define LEFT_PIN 5    // display left button
#define SSD_PIN 6     // flash chip CS pin
// 7 and 8 are serial for GPS
// we remap pin 8 to an ouput for lap trigger LED (GPS Rx since we don't send data to it)
#define LAPLED_PIN 8
#define DCS_PIN 9    // display CS
#define SDCS_PIN 10  // SD card CS
// 11-12-13 are SPI

#define AUX_14_PIN 14  // future
#define AUX_15_PIN 15  // future
#define EXTADC_CS_PIN 16   // chip select pin for the external ADC chip
#define M0_PIN 17      // state pin for EBYTE
#define M1_PIN 17      // state pin for EBYTE
// pins 18 19 are I2C and are for accelerometer and air flow sensor
#define RIGHT_PIN 20  // display right pin
#define TURBO_PIN 21  // button to override CYBORG current limit
#define RPM_PIN 22    // FlexPWM pin for speed (CANNOT CHANGE)
#define AX_PIN 23     // state pin for EBYTE


// constants for 10K NTC thermistors

#define NTC_A  3.354016E-03  // from the data sheet
#define NTC_B  2.569850E-04  // from the data sheet
#define NTC_C  2.620131E-06  // from the data sheet
#define NTC_D  6.383091E-08  // from the data sheet
#define NTC_R1  10000.0       // resistor for thermsitor voltage divider

#define WARNING_BATTERY 21.0f  // default voltage for batter warning
#define WARNING_MTEMP 140.0f   // default temp for motor warning
#define WARNING_LAPAMP 19.5f

/* 
car designator
*/
 
#define BLUE_CAR 	0
#define RED_CAR 	1
#define WHITE_CAR 	2

// external ADC
#define EXADC_BIT_CONVERSION 4096.0f

// onboard ADC (analogRead())
#define BIT_CONVERSION 4096
#define REFERENCE_VOLTAGE 3.3f
#define SD_SPI_SPEED 30  // SPI bus speed for SD card (in MHZ)

// UART ports
#define ESerial Serial1  // setup serial port for Exx-TTL-100
#define GPSSerial Serial3  // setup serial port for GPS Teensy 3.2

// constant for flow sensor
#define FLOW_SENSOR_K 8192

// note the wirelss will not send at 300 or even 1.2 but needed to keep the byte index matching the
// constants used by EBYTE libs
const char *AirRateText[] = {"2.4-0", "2.4-1k", "2.4-2k", "4.8k", "9.6k", "19.2k", "38.4k", "62.5k"};    

//setup screen text transmitter power level 1 w  version
const char *HighPowerText[] = {"30 dB",  "27 dB", "24 dB", "21 dB"};

//setup screen text transmitter power level 100 mw  version
const char *PowerText[] = {"22 dB",  "17 dB", "13 dB", "10 dB"};

const char *ReadText[] = 	{"Read"};          //setup screen text for background color

const char *ASensorDirectionText[] = {"+X", "-X", "+Y", "-X", "+Z", "-Z"}; 	//how the accelerometer is installed
const char *ThemeText[] = 	{"Dark", "Light"};          			//setup screen text for background color
const char *OrientationText[] = {"Below", "Above"};          		//setup screen text for screen orientation
const char *YesNoText[] = 	{"No", "Yes"};               			//show diagnostics

const char *TextJustifyText[] = 	{"Left", "Right"}; 

const char *CyborgInputText[] = 	{"Amps", "Speed"}; 

// index of array matches time in seconds, value==element number
const char *SendTimeText[] = 	{"Off", "1 sec", "2 sec", "3 sec", "4 sec","5 sec"};  //duration for transceiver send time


// delay for when GPS records start time
// GPS read is more accurate when the car is moving
// so let's wait a few seconds until the car starts moving
// or if start location is not on the track	
const char *GPSReadTimeText[] = 	{"0 sec", "5 sec", "10 sec", "20 sec"};  // text for the menu option
uint32_t GPSReadTime[] = {0, 5000, 10000, 20000}; // actual delay value in millis

// index of array matches distance in meters, value==element number

// GPS tolerance distance in feet, index of array is in feet (lib uses meters but converted in software)
const char *GPSToleranceText[] = {"Off", "3 ft", "6 ft", "9 ft", "13 ft","16 ft", "19 ft", "23 ft", "26 ft", "29 ft", "31 ft"};  //tolerance for GPS start location
  
// accelerometer 
const char *AccelFSRange[] = 	{"+/- 2 G", "+/- 4 G", "+/- 8 G", "+/- 16 G"};  
float AccelFSBits[] = {16384.0, 8192.0, 4096.0, 2048.0};

const char *AccelLPFilterText[] = 	{"256 Hz", "188 Hz", "98 Hz", "42 Hz", "20 Hz", "10 Hz", "5 Hz"}; 

const char *AccelHPFilterText[] = 	{"Off", "5 Hz", "2.5 Hz", "1.25 Hz", "0.63 Hz"}; 

const char *CarText[] = {"Blue", "Red", "White"};  

/* 
tires types
*/

const char *MotorText[] = {"C0", "C1", "C2", "C3", "U0", "U1", "U2", "U3", "U4", "U5", "U6", "U7", "U8", "U9"}; 

const char *TireText[] = {"Kojaks", "Duranos", "Ones", "Pro Ones", "Test"}; 

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



/*
structure definition for serial transceiver communications
*/

// max is 58 bytes per packet
#pragma pack(push,1)
struct Transceiver  {
	uint16_t RPM_DNO_DID;           // 16 RPM(12) DRIVER NUMBER(2) DEVICEID(2) for id of incoming data-repeaters
    uint16_t WARNINGS_PE;           // 16 WARNINGS(6) PREDICTENERGY (10)
	uint16_t TEMPF_TEMPX;       	// 16 TEMPF(8) TEMPX(8) (Motor and auxiliary temp)
    uint16_t VOLTS_LAPS;        	// 16 VOLTS(9) LAPS(7)
    uint16_t SPEED_EREM;        	// 16 SPEED(9) EREM(7)
    uint16_t DISTANCE_TREM;     	// 16 DISTANCE(9) TREM(7)
	uint16_t TWHR_LAPAMPS; 			// 16 TotalEnergy(7) LAPAMPS(9)  (TotalEngery / 10, Lap Amps / 10)	
    uint16_t AMPS_D0TIME;	    	// 16 AMPS(11) D0TIME(5)
	uint16_t LAP2AMPS_D0TIME;   	// 16 LAP2AMPS(9) D0TIME(7)		
	uint16_t ENERGY;				// 16 ENERGY(10) 
	uint16_t D1TIME_GFORCEY;      	// 16 D1TIME(12) GFORCEY(4)	
	uint16_t D2TIME_GFORCEY;      	// 16 D2TIME(12) GFORCEY(4)	
	uint16_t ALTITUDE_SID;   		// 14 ALTITUDE(12) SOURCEID(2) for source of incoming data-repeaters	
    uint16_t RACETIME_LAPENERGY;    // 16 RACETIME(13) LAPENERGY(3)
    uint16_t LT_LAPENERGY;          // 16 LAPTIME(10) LAPENERGY(6)
	uint16_t CYBORGOUT_CYBORGLO;    // 15 Cyborg output percet (7) Cyborg limits (9) (0 to 51.2)
	float LAT; 	 					// 32 GPS latitude(32 bits) a float
	float LON; 	 					// 32 GPS longitude(32 bits) a float
} ;
#pragma pack(pop)


#endif