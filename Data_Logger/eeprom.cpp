#include "eeprom.h"

// Instantiating
Adafruit_EEPROM_I2C i2ceeprom;

unsigned long addr = 0;
unsigned long eepromSize = MAXADD;


// Initialising the EEPROM
void eeprom_init() {

  // Turning Power Supply On for EEPROM 
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
   
  delay(300);
  Serial.println("Power on.............");

  // Checking the Connection Access Status
  if (i2ceeprom.begin(EEPROM_ADDR))
    {  
      Serial.println("Found I2C EEPROM");
    }
   else 
    {      
      while (1)
      {
        Serial.println("I2C EEPROM not identified ... check your connections?\r\n");
        delay(10);
      }     
    }
}


// Getting the current Counter
long getCounter(){
  // read Bytes 1 to 3
  char byte1 = i2ceeprom.read(0);
  char byte2 = i2ceeprom.read(1);
  char byte3 = i2ceeprom.read(2);

  // Split the unnecessary part four last bits by shifting right
  byte3 = byte3 >> 4;
  

  // Concate the 3 Bytes to one long by shifting them beginnig by  (0 ... 8 ... 16 ... 24)
  // Byte 1 (Shift Left 2^16) 0000 0001
  // Byte 2 (Shift Left 2^ 8) 0000 0001
  // Byte 3 (No Shift needed) 0000 0001
  // 0000 0001 | 0000 0001 | 0000 0001    
  
  // Convert them to long and add them together 
  // 0000 0001 0000 0000 0000 0000
  // 0000 0000 0000 0001 0000 0000
  // 0000 0000 0000 0000 0000 0001

  long part1 = (long) byte1 << 16;
  long part2 = (long) byte2 <<  8;
  long part3 = (long) byte3      ;

  long addressNumber = part1 + part2 + part3;

	return addressNumber;

}


// Replacing the current Counter with the new Value
void setCounter(long counter){

// splitting into Bytes by shifting and doing bitwise "and" with predefined 32 Bitmasks accordingly
// long mask1 = 4278190080; // 1111 1111 0000 0000 0000 0000 0000 0000 don t need because we know that it will be maximum 20 Bits ca. 1 Million
long mask2 = 16711680;  // 0000 0000 1111 1111 0000 0000 0000 0000
long mask3 = 65280;     // 0000 0000 0000 0000 1111 1111 0000 0000
long mask4 = 255;       // 0000 0000 0000 0000 0000 0000 1111 1111

// long firstByte = counter & mask1;
long secondByte = counter & mask2;
long thirdByte = counter & mask3;
long lastByte = counter & mask4;

// char byte1 = firstByte >> 24;
char byte2 = secondByte >> 16;
char byte3 = thirdByte >> 8;
char byte4 = lastByte;

// ---------------------- Stopped Here-----------------

// 0100 1100 | 0001 0010 | 1010 0001 | 0001 0010 // no need for First one limit 1 Mio 2 ^20  
//      | 0001 0010 | 1010 0001 | 0001 0010      // 24 Bits need to be reduced to 20 
//       0010 | 1010 0001 | 0001 0010      // Shift left 4 and right 
//       0010 | 1010 0001 | 0001 0010      //  need to be fitted in the part from 21 - 38 . Bit 
// 

// Shift 4 Bits left for getting rid of the unnecessary part
byte2 = byte2 << 4;
// Shift 4 Bits right reposition
byte2 = byte2 >> 4;


// before we can set the third Byte we have to save the four last bits from the eeprom

// i2ceeprom.write(0,byte1);


// now combine the last four Bits with the 
// i2ceeprom.write(2,data);
}


// Getting the current Address
long getAddress(){

  // read Bytes 3 to 5
  char byte1 = i2ceeprom.read(2);
  char byte2 = i2ceeprom.read(3);
  char byte3 = i2ceeprom.read(4);

  // Split the unnecessary part two last bits by shifting right 4 at beginning and 2 at the end
  byte1 = byte1 << 4;
  byte3 = byte3 >> 2;
  

  // Concate the 3 Bytes to one long by shifting them beginnig by  (0 ... 8 ... 16 ... 24)

  long part1 = (long) byte1 << 16;
  long part2 = (long) byte2 <<  8;
  long part3 = (long) byte3      ;

  long addressNumber = part1 + part2 + part3;

	return addressNumber;
}

// Replacing the current Address with the new Value
void setAddress(int address){

// Split the int into 4 Bytes and write from 21 to 38

}

// Calculating the new Address
long calculateNewAddress(long address, int increase) {
    // increading the current value by the amount of written values multiplied with 8 * 4 (Conversion from 8 to 32 Bit for ever entry)  
    
    long addressNew = address + ((increase * 8) * 4);
    
    // Checking overflow
    if (addressNew >= eepromSize) {
       // if full than -> strategy needed
    }
    return 0;
}

// Reading Data from EEPROM
void readData(long address) {
  i2ceeprom.read(address);
  // Hex Conversion if needed when decode String(buffer[i], HEX)
}


// Writing Data
void writeData(long address, unsigned char data){
  i2ceeprom.write(address,data);
  // Increase The Address Counter for the next Entry
    
}