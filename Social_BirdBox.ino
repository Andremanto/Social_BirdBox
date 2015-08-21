// Social BirdBox [1.0] by Andrea Mantelli
// London, August 2015


// sensors pins
int sensorOut = D3;
int sensorIn = D2;


// variables
int outState = 1;
int inState = 1;
unsigned long tIn;
unsigned long tOut;
int birdsIn = 0;
int totBirdsIn = 0;
char nBirdsIn[40];
boolean in = false;
boolean out = false;


void setup() {
pinMode (sensorOut, INPUT);
pinMode (sensorIn, INPUT);

////////////////////////
// Personalize here...//
////////////////////////

Spark.variable ("Hosted", &totBirdsIn, INT);
Spark.variable ("Inside", &birdsIn, INT);
Spark.variable ("sensorOUT", &outState, INT);
Spark.variable ("sensorIN", &inState, INT);
Spark.publish ("Social BirdBox FabLab London","ON",60,PRIVATE);

////////////
// ...end //
////////////
}

void loop() {
    
    bird_enter();
    if(in == true) {
        //personalize the message when a birds enter in your BirdBox
        Spark.publish ("Alert","in",60,PRIVATE);
        sprintf(nBirdsIn, "%u", birdsIn);
        Spark.publish ("#Birds",nBirdsIn,60,PRIVATE);
    }
    
    bird_exit();
    if(out == true) {
        //personalize the message when a birds exit your BirdBox
        Spark.publish ("Alert","out",60,PRIVATE);
    }
}


//////////////////////////////////////////
// funcions for entry and exit of birds //
//////////////////////////////////////////

void bird_enter() {
  tOut = millis();
  outState = digitalRead (sensorOut);
  inState = digitalRead (sensorIn);
  delay(50);
  if(outState == 0) {
    //Spark.publish ("Bird's standing","OUT",60,PRIVATE);
    while(millis()-tOut < 1000) {
      inState = digitalRead (sensorIn);
      outState = digitalRead (sensorOut);
      delay(50);
      if(inState == 0 & outState == 1) {
        birdsIn++;
        totBirdsIn++;
        in = true;
        tOut = millis()-2000;
      }
      else {
          in = false;
      }
    }
  }
  else {
      in = false;
  }
}

void bird_exit() {
  tIn = millis();
  inState = digitalRead (sensorIn);
  outState = digitalRead (sensorOut);
  delay(50);
  if(inState == 0) {
    //Spark.publish ("Bird's standing","IN",60,PRIVATE);
    while(millis()-tIn < 1000) {
      outState = digitalRead (sensorOut);
      inState = digitalRead (sensorIn);
      delay(50);
      if(outState == 0 & inState == 1) {
        birdsIn--;
        out = true;
        tIn = millis()-2000;
      }
      else {
          out = false;
      }
    }
  }
  else {
      out = false;
  }
}
