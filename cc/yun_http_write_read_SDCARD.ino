#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <FileIO.h>
#include <Process.h>

 
YunServer server;
String msg;

void setup () {
   
  Serial.begin(9600);
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();  
 while (!Serial);
runREAD();

   
}
  
void loop () 


{


  
  YunClient client = server.accept(); //check new clients
   
  if(client) {
    String command = client.readStringUntil('/');  //read the incoming data 
    if (command == "msg") {      
       msg = client.readStringUntil('/');             // read the incoming data
        File dataFile = FileSystem.open("/mnt/sd/param4.txt",FILE_WRITE);
       dataFile.print(msg);
       dataFile.close();
   
    }
    client.stop();   
  }  

   
}

void runREAD() {
  Process p;
  p.begin("cat");  
  p.addParameter("/mnt/sd/param4.txt");     
  p.run();

    while (p.available()>0) {
    char c = p.read();
    Serial.print(c);
  }
  Serial.flush();


} 
