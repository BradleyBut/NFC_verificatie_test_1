//ARDUINO 1.0+ ONLY
//ARDUINO 1.0+ ONLY
#include <Ethernet.h>
#include <SPI.h>

////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////
byte server[] = { 131,180,122,144 }; //ip Address of the server you will connect to

//The location to go to on the server
//make sure to keep HTTP/1.0 at the end, this is telling it what type of file it is
String location = "/NFC/index.htm HTTP/1.0";


// if need to change the MAC address (Very Rare)
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x1E, 0x4B };
IPAddress ip(131,180,92,208);
////////////////////////////////////////////////////////////////////////

EthernetClient client;

char inString[4096]; // string for incoming serial data
int stringPos = 0; // string index counter
boolean startRead = false; // is reading?

void setup(){
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
}

void loop(){
  String pageValue = connectAndRead(); //connect to the server and read the output

  Serial.println(pageValue); //print out the findings.

  delay(5000); //wait 5 seconds before connecting again
}

String connectAndRead(){
  //connect to the server

  Serial.println("connecting...");

  //port 80 is typical of a www page
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.print("GET ");
    client.println(location);
    client.println();

    //Connected - Read the page
    return readPage(); //go and read the output

  }else{
    return "connection failed";
  }

}

String readPage(){


  stringPos = 0;
  memset( &inString, 0, 4096 ); 

  while(true){

    if (client.available()) {
      char c = client.read();

      if (c == '[' ) { 
        startRead = true;
       
      }else if(startRead){

        if(c != ']'){
          inString[stringPos] = c;
          //stringPos ++;
          Serial.print(inString);
        }else{
        
          client.flush();
          Serial.println("disconnecting.");
          return inString;

        }

      }
    }

  }

}
