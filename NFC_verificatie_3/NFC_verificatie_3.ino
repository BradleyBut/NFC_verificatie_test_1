// Newer Ethernet shields have a MAC address printed on a sticker on the shield
#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>
#define SCK  52  
#define MOSI 51  
#define MISO 50
#define SS 53
File dataFile;

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x1E, 0x4B };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(131,180,122,144);  // numeric IP for Google (no DNS)
//char server[] = "srv893.tudelft.net/NFC";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(131,180,92,208);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

char inString[32]; // string for incoming serial data
int stringPos = 0; // string index counter
boolean startRead = false; // is reading?

void setup() {
  SD.begin(53);
  String connectAndRead();
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /NFC/index.htm HTTP/1.1");
    client.println("Host: srv893.tudelft.net");
    client.println("Connection: close");
    client.println();
       dataFile = SD.open("datalog.txt", FILE_WRITE);
         // if the file opened okay, write to it:
  if (dataFile) {
    Serial.print("Writing to datalog.txt...");
    dataFile.println("Reboot");
	// close the file:
    dataFile.close();
    Serial.println("done.");

       
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}
}
void loop()

  
  
 {
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while(true);
  }
}

/*
{

  

{if (client.available()) {
  char c = client.read();
  
  if (c == 'DASMLcardid:') {
    startRead = true;
    Serial.println(c);

  }else{
    startRead = false;
    client.stop();
    client.flush();
    Serial.println("disconecting");
    //return inString;
    
  }
}}}

*/

     
