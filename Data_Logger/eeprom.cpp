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

  Serial.print("---------------- Get Counter ------------");
  // Read Bytes 1 to 3
    unsigned char byte1 = i2ceeprom.read(0);
    unsigned char byte2 = i2ceeprom.read(1);
    unsigned char byte3 = i2ceeprom.read(2);

    // Testing
    Serial.print("Byte1: 0x"); Serial.println(byte1, HEX);
    Serial.print("Byte2: 0x"); Serial.println(byte2, HEX);
    Serial.print("Byte3: 0x"); Serial.println(byte3, HEX);

    // Split the unnecessary part (last 4 bits) by shifting right
    byte3 = byte3 >> 4;

    // Testing
    Serial.print("Byte3 nach Shift: 0x"); Serial.println(byte3, HEX);
    
    // Concatenate the 3 Bytes into one long by shifting them (0 ... 4 ... 12 ... 20)
    long part1 = (long) byte1 << 12;
    long part2 = (long) byte2 << 4;
    long part3 = (long) byte3;

    long addressNumber = part1 + part2 + part3;

    // Testing
    Serial.print("Part1: "); Serial.println(part1);
    Serial.print("Part2: "); Serial.println(part2);
    Serial.print("Part3: "); Serial.println(part3);
    Serial.print("Berechnete Adresse: "); Serial.println(addressNumber);

    return addressNumber;

}


// Replacing the current Counter with the new Value

void setCounter(long counter){
  Serial.print("---------------- Set Counter ------------");
  // Step 1 : Shift the long value 4 Bits to left to match the original position of Counter Mask
  Serial.print("Original Counter: "); Serial.println(counter);
  counter = counter << 4; 
  Serial.print("Shifted Counter: "); Serial.println(counter);
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

  Serial.print("Byte2: 0x"); Serial.println(byte2, HEX);
  Serial.print("Byte3: 0x"); Serial.println(byte3, HEX);
  Serial.print("Byte4: 0x"); Serial.println(byte4, HEX);

  // Step 3 : Save the Value of the Addess Counter in the last Byte (3) by shifting it 4 Bits to left and 4 Bits to right 

  unsigned char save = i2ceeprom.read(2);
  Serial.print("EEPROM Byte 2 before modification: 0x"); Serial.println(save, HEX);

  save = save << 4;
  save = save >> 4;

  Serial.print("Saved Value after Shift: 0x"); Serial.println(save, HEX);


  // Step 4 : Set the 1 st and 2 nd Byte to the Counter Mask

  i2ceeprom.write(0,byte2);
  i2ceeprom.write(1,byte3);

  // Step 5 : Take the Last Byte and make an OR operation with the saved value

  byte4 = byte4 | save ;
  Serial.print("Final Byte4 after OR operation: 0x"); Serial.println(byte4, HEX);


  // Step 6 : Set the last Byte  

  i2ceeprom.write(2,byte4);

  Serial.println("Counter successfully set.");
}


// Getting the current Address
long getAddress(){

    Serial.print("---------------- Get Address ------------");
    // Read the predefined Bytes 3-5

    unsigned char byte1 = i2ceeprom.read(2);
    unsigned char byte2 = i2ceeprom.read(3);
    unsigned char byte3 = i2ceeprom.read(4);

    Serial.print("Byte1 (Raw): 0x"); Serial.println(byte1, HEX);
    Serial.print("Byte2 (Raw): 0x"); Serial.println(byte2, HEX);
    Serial.print("Byte3 (Raw): 0x"); Serial.println(byte3, HEX);
    
    // Shift Byte (1) 4 to left and back to get rid of the unrelevant part
    // Then Shift Byte (3) 2 to Right
    byte1 = byte1 << 4;
    byte1 = byte1 >> 4;
    byte3 = byte3 >> 2;

    Serial.print("Byte1 (Cleaned): 0x"); Serial.println(byte1, HEX);
    Serial.print("Byte3 (Shifted Right by 2): 0x"); Serial.println(byte3, HEX);


    // Shift for getting the right Position 
    
    long part1 = (long) byte1 << 14;  // 4 Bits → Position 14-17
    long part2 = (long) byte2 << 6;   // 8 Bits → Position 6-13
    long part3 = (long) byte3;        // 6 Bits → Position 0-5

    Serial.print("Part1: "); Serial.println(part1);
    Serial.print("Part2: "); Serial.println(part2);
    Serial.print("Part3: "); Serial.println(part3);

    // Add their Value to get the Address
    long addressNumber = part1 + part2 + part3;

    Serial.print("Final Address: "); Serial.println(addressNumber);


	  return addressNumber;
}

// Replacing the current Address with the new Value
void setAddress(long address){

  Serial.print("---------------- Set Address ------------");
  // Step 1 : Shift the long value 2 Bits to left to match the original position of the Address Mask

  // Example :
  // Long Value :        0000 0000 0000 0001 0001 0010 1101 0110

  // Shifted 2 to Left : 0000 0000 0000 0100 0100 1011 0101 1000
  Serial.print("Original Address: "); Serial.println(address);
  address = address << 2;
  Serial.print("Shifted Address: "); Serial.println(address);

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

  Serial.print("Byte2 (Raw): 0x"); Serial.println(byte2, HEX);
  Serial.print("Byte3 (Raw): 0x"); Serial.println(byte3, HEX);
  Serial.print("Byte4 (Raw): 0x"); Serial.println(byte4, HEX);

  // Get rid of the first 4 bits from Byte Part 1 << 4 0000 0100 -> 0100 -> 0000 0100
  byte2 = byte2 << 4;
  byte2 = byte2 >> 4;

  Serial.print("Byte2 (After Removing First 4 Bits): 0x"); Serial.println(byte2, HEX);



  // Step 3 : Save the Value of the Addess Counter in the Byte (3) and Byte (5)  

  char save1 = i2ceeprom.read(2);
  char save2 = i2ceeprom.read(4);


  Serial.print("EEPROM Byte2 before modification: 0x"); Serial.println(save1, HEX);
  Serial.print("EEPROM Byte4 before modification: 0x"); Serial.println(save2, HEX);



  save1 = save1 >> 4;
  save1 = save1 << 4;
  save2 = save2 << 6;
  save2 = save2 >> 6;

  Serial.print("Save1 (Masked): 0x"); Serial.println(save1, HEX);
  Serial.print("Save2 (Masked): 0x"); Serial.println(save2, HEX);

  // Step 4 : Set the 2 nd Byte to the Address Mask
  i2ceeprom.write(3,byte3);

  // Step 5 : Take the Byte 3 and 5 and make an OR operation with the saved values

  byte2 = byte2 | save1; 
  byte4 = byte4 | save2;

  Serial.print("Final Byte2 after OR operation: 0x"); Serial.println(byte2, HEX);
  Serial.print("Final Byte4 after OR operation: 0x"); Serial.println(byte4, HEX);


  // Step 6 : Set the Bytes 3 and 5  


  i2ceeprom.write(2,byte2);
  i2ceeprom.write(4,byte4);

  
  Serial.println("Address successfully set.");
}


// Reading Data from EEPROM
void readData(long address) {
  i2ceeprom.read(address);
  // Hex Conversion if needed when decode String(buffer[i], HEX)
}


// Writing Data
void writeData(long* data, size_t size){

  Serial.print("---------------- Write Data ------------");
  // Increase The Address Counter for the next Entry
  long address = getAddress();
  long counter = getCounter();

   Serial.print("Initial Address: "); Serial.println(address);
  Serial.print("Initial Counter: "); Serial.println(counter);
  // Split all Long Values into their Bytes and write them

  for (int i = 0; i< size ; i++){
    Serial.print("Writing Data Index "); Serial.println(i);

    // divide the long into 4 Bytes
    unsigned char *byte_ptr = (unsigned char *) &data[i];

    // Write the Bytes & increase the address by k to not overwriting the same address all time
    // Important Arduino uses Big Endian , conversion to Little Endian Format
    for(int k = 3; k >= 0 ; k--){
      Serial.print("Writing Byte "); Serial.print(k);
      Serial.print(" at EEPROM Address: "); Serial.print(address);
      Serial.print(" | Value: 0x"); Serial.println(byte_ptr[k], HEX);
      i2ceeprom.write(address, byte_ptr[k]);
      address ++;

    }
    counter = counter + 4;

  }

  Serial.print("Final Address: "); Serial.println(address);
  Serial.print("Final Counter: "); Serial.println(counter);
  // Set Address and Counter
  setAddress(address);
  setCounter(counter);

  Serial.println("Data successfully written.");

}