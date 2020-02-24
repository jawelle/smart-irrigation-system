#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
#include <DHT.h>   

#define DHTTYPE DHT11                                                           

#define WIFI_SSID "samet1"
#define WIFI_PASSWORD "12345678"


#define FIREBASE_HOST "akilli-sulama-f948c.firebaseio.com"
#define FIREBASE_AUTH "6gy46WfMj0NJ74hMTiKXl8eQrERAC9KMtAxL1LGY"   
String fan="";
String pumpstatus="";


 #define pump D4                                

const int topraknem =A0;
#define dht_dpin D2
DHT dht(dht_dpin, DHTTYPE);      

void setup() {
  pinMode(D6,OUTPUT);
   pinMode(pump,OUTPUT);
   digitalWrite(pump,HIGH);
   pinMode(D0,OUTPUT);
 pinMode(topraknem,OUTPUT);
  dht.begin();    
  
  Serial.begin(9600);

  Serial.println("Humidity and temperature \n\n");  
           
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  
  
  // connect to firebase
                                                             //Start reading dht sensor
}

void loop() { 


 
 if (Firebase.failed())
  { delay(500);
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Serial.println(Firebase.error());
  
  delay(500);
  }

  else {
    Serial.println("Everything is ready!");
    delay(300); Serial.println("Everything is ready!");
    delay(300); Serial.println("Everything is ready!");
    delay(300); Serial.println("Everything is ready!");
    delay(300);
  }


  int sonuc =analogRead(topraknem);
  float h = dht.readHumidity();                                              // Reading humidity
  float t = dht.readTemperature();                                           // Reading temperature
    
    String lampstatus=Firebase.getString("light");
   Serial.print("lampstatus");
   Serial.println(lampstatus);
   fan=Firebase.getString("fan");
   pumpstatus=Firebase.getString("pump");
  
   
 
 
Serial.print(" humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
    Serial.print("Toprak nemi = ");
    Serial.print(sonuc); 
     Serial.print("motor= ");
    Serial.print(pumpstatus); 
     Serial.print("fan = ");
    Serial.print(fan); 
     Serial.print("light= ");
    Serial.print(lampstatus); 


  Firebase.setInt("Toprak nemi:",sonuc);
  Firebase.setFloat("Sicaklik:",t);
  Firebase.setFloat("Nem:",h);
  
     
 
if (lampstatus=="1"){
    digitalWrite(D6,HIGH);
    
    }
    else if(lampstatus=="0") {
    digitalWrite(D6,LOW);
    
      }
if (pumpstatus=="1"){
    digitalWrite(pump,LOW);
    
    }
     else if(pumpstatus=="0") {
    digitalWrite(pump,HIGH);
   
      
      if (fan=="1"){
   digitalWrite(D0,HIGH);
    
    }
    else if(fan=="0") {
    digitalWrite(D0,LOW);
   
      }
     }
}
  
  
 
