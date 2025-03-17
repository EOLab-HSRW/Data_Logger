#include "eeprom.h"

// Instantiating
Adafruit_EEPROM_I2C i2ceeprom;

unsigned long eepromSize = MAXADD;


// Initialising the EEPROM
void eeprom_init() {

  //------------------------------------------------------------------------------ It is possible to extreact the power supply into a seperate function

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
  // Read Bytes 1 to 3
    unsigned char byte1 = i2ceeprom.read(0);
    unsigned char byte2 = i2ceeprom.read(1);
    unsigned char byte3 = i2ceeprom.read(2);

    // Split the unnecessary part (last 4 bits) by shifting right
    byte3 = byte3 >> 4;
    
    // Concatenate the 3 Bytes into one long by shifting them (0 ... 4 ... 12 ... 20)
    long part1 = (long) byte1 << 12;
    long part2 = (long) byte2 << 4;
    long part3 = (long) byte3;

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
  long mask2 = 16711680;      // 0000 0000 1111 1111 0000 0000 0000 0000
  long mask3 = 65280;         // 0000 0000 0000 0000 1111 1111 0000 0000
  long mask4 = 255;           // 0000 0000 0000 0000 0000 0000 1111 1111

  // long firstByte = counter & mask1;
  long secondByte = counter & mask2;
  long thirdByte = counter & mask3;
  long lastByte = counter & mask4;

  // char byte1 = firstByte >> 24;
  unsigned char byte2 = secondByte >> 16;
  unsigned char byte3 = thirdByte >> 8;
  unsigned char byte4 = lastByte;

  // Step 3 : Save the Value of the Addess Counter in the last Byte (3) by shifting it 4 Bits to left and 4 Bits to right 

  unsigned char save = i2ceeprom.read(2);
  save = save << 4;
  save = save >> 4;

  // Step 4 : Set the 1 st and 2 nd Byte to the Counter Mask

  i2ceeprom.write(0,byte2);
  i2ceeprom.write(1,byte3);

  // Step 5 : Take the Last Byte and make an OR operation with the saved value

  byte4 = byte4 | save ;

  // Step 6 : Set the last Byte  

  i2ceeprom.write(2,byte4);
}


// Getting the current Address
long getAddress(){

    // Read the predefined Bytes 3-5

    unsigned char byte1 = i2ceeprom.read(2);
    unsigned char byte2 = i2ceeprom.read(3);
    unsigned char byte3 = i2ceeprom.read(4);
    
    // Shift Byte (1) 4 to left and back to get rid of the unrelevant part
    // Then Shift Byte (3) 2 to Right
    byte1 = byte1 << 4;
    byte1 = byte1 >> 4;
    byte3 = byte3 >> 2;


    // Shift for getting the right Position 
    
    long part1 = (long) byte1 << 14;  // 4 Bits → Position 14-17
    long part2 = (long) byte2 << 6;   // 8 Bits → Position 6-13
    long part3 = (long) byte3;        // 6 Bits → Position 0-5

    // Add their Value to get the Address
    long addressNumber = part1 + part2 + part3;

	  return addressNumber;
}

// Replacing the current Address with the new Value
void setAddress(long address){


  // Step 1 : Shift the long value 2 Bits to left to match the original position of the Address Mask

  // Example :
  // Long Value :        0000 0000 0000 0001 0001 0010 1101 0110

  // Shifted 2 to Left : 0000 0000 0000 0100 0100 1011 0101 1000
  address = address << 2; 

  // Step 2 : Split the long Value in 4 Bytes and get rid of the 1 Byte (because of Limit : 18 Bits for 262.144)

  // splitting into Bytes by shifting and doing bitwise "and" with predefined 32 Bitmasks accordingly
  // long mask1 = 4278190080; // 1111 1111 0000 0000 0000 0000 0000 0000 don t need because we know that it will be maximum 20 Bits ca. 1 Million
  long mask2 = 16711680;  // 0000 0000 1111 1111 0000 0000 0000 0000
  long mask3 = 65280;     // 0000 0000 0000 0000 1111 1111 0000 0000
  long mask4 = 255;       // 0000 0000 0000 0000 0000 0000 1111 1111

  // 1) 0000 0100 >> 16  |   2) 0100 1011 >> 8 |   3) 0101 1000

  // long firstByte = counter & mask1;
  long secondByte = address & mask2;
  long thirdByte = address & mask3;
  long lastByte = address & mask4;

  // char byte1 = firstByte >> 24;
  char byte2 = secondByte >> 16;
  char byte3 = thirdByte >> 8;
  char byte4 = lastByte;

  // Get rid of the first 4 bits from Byte Part 1 << 4 0000 0100 -> 0100 -> 0000 0100
  byte2 = byte2 << 4;
  byte2 = byte2 >> 4;

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

}


// Reading Data from EEPROM
void readData(long address) {
  i2ceeprom.read(address);
  // Hex Conversion if needed when decode String(buffer[i], HEX)
}


// Writing Data
void writeData(long* data, size_t size){
  // Increase The Address Counter for the next Entry
  long address = getAddress();
  long counter = getCounter();
  // Split all Long Values into their Bytes and write them

  for (int i = 0; i< size ; i++){

    // divide the long into 4 Bytes
    unsigned char *byte_ptr = (unsigned char *) &data[i];

    // Write the Bytes
    for(int k = 0; k < sizeof(long) ; k++){
      
      i2ceeprom.write(address,byte_ptr[k]);
      address++;
      counter++;
    }

  }

  // Set Address and Counter
  setAddress(address);
  setCounter(counter);

}