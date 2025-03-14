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

// Step 1 : Shift the long value 4 Bits to left to match the original position of Counter Mask

counter = counter << 4; 

// Step 2 : Split the long Value in 4 Bytes and get rid of the 1 Byte (because of Limit : 1 Mio)

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

// Step 3 : Save the Value of the Addess Counter in the last Byte (3) by shifting it 4 Bits to left and 4 Bits to right 

char save = i2ceeprom.read(2);
save = save << 4;
save = save >> 4;

// Step 4 : Set the 1 st and 2 nd Byte to the Counter Mask

i2ceeprom.write(0,byte2);
i2ceeprom.write(1,byte3);

// Step 5 : Take the Last Byte and make an OR operation with the saved value

byte4 = byte4 || save ;

// Step 6 : Set the last Byte  

i2ceeprom.write(2,byte4);

// ------------------------------------------ has to be tested -----------

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
void setAddress(long address){


// Step 1 : Shift the long value 2 Bits to left to match the original position of the Address Mask

address = address << 2; 

// Step 2 : Split the long Value in 4 Bytes and get rid of the 1 Byte (because of Limit : 18 Bits for 262.144)

// splitting into Bytes by shifting and doing bitwise "and" with predefined 32 Bitmasks accordingly
// long mask1 = 4278190080; // 1111 1111 0000 0000 0000 0000 0000 0000 don t need because we know that it will be maximum 20 Bits ca. 1 Million
long mask2 = 16711680;  // 0000 0000 1111 1111 0000 0000 0000 0000
long mask3 = 65280;     // 0000 0000 0000 0000 1111 1111 0000 0000
long mask4 = 255;       // 0000 0000 0000 0000 0000 0000 1111 1111

// long firstByte = counter & mask1;
long secondByte = address & mask2;
long thirdByte = address & mask3;
long lastByte = address & mask4;

// char byte1 = firstByte >> 24;
char byte2 = secondByte >> 16;
char byte3 = thirdByte >> 8;
char byte4 = lastByte;

// Step 3 : Save the Value of the Addess Counter in the Byte (3) and Byte (5)  

char save1 = i2ceeprom.read(2);
char save2 = i2ceeprom.read(4);
save1 = save1 >> 4;
save1 = save1 << 4;
save2 = save2 << 6;
save2 = save2 >> 6;

// Step 4 : Set the 2 nd Byte to the Address Mask
i2ceeprom.write(3,byte3);

// Step 5 : Take the Byte 3 and 5 and make an OR operation with the saved values

byte2 = byte2 | save1; 
byte4 = byte4 | save2;

// Step 6 : Set the Bytes 3 and 5  


i2ceeprom.write(2,byte2);
i2ceeprom.write(4,byte4);

// ------------------------------------------ has to be tested -----------

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