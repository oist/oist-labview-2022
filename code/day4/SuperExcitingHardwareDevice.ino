// Super Exciting Hardware Device
// Made for Mini Course: LabVIEW
// Specifications by Christian Butcher
// Coded by Jeremie Gillet

String input; //main captured String

void setup() {
  Serial.begin(9600);
  Serial.print("Thank you for using Super Exciting Hardware Device.\n");
}

void loop() {
  if (Serial.available())  {
    char c = Serial.read();  //gets one byte from serial buffer
    if (c != '\n') {
      input += c; //makes the string input
    }
    else {
      parseInput();
      input=""; //clears variable for new input
    }
  }
}

// accumulation functions
float add(float a, float b) {return a + b;}
float mult(float a, float b) {return a * b;}

void parseInput() {
  if (input == "STATUS") {
    Serial.print("STATUS,Hello World!\n");
  } else if (input == "STATUS,") {
    Serial.print("STATUS,,Hello World!\n");
  } else if(input.indexOf(',') == -1) {
    Serial.print("Error\n");
  } else {
    int index;
    int nextIndex;
    String data;
    float acc;
    float (*function)(float, float);

    index = input.indexOf(',');
    data = input.substring(0 , index);

    if (data == "ADD") {
        function = &add;
        acc = 0;
    } else if (data == "MUL") {
        function = &mult;
        acc = 1;
    } else {
        Serial.print("Error\n");
        return;
    }

    input += ","; // terminate string with "," for ease of parsing and printing output

    while(input.indexOf(',', index + 1) != -1) {
      nextIndex = input.indexOf(',', index + 1);
      data = input.substring(index + 1, nextIndex);

      if (!isDigit(data[0]) && data[0] != '-' ){
        Serial.print("Error\n");
        return;
      }

      // float conversion stops at unexpected characters: "1.2a" => 1.2
      acc = function(acc, data.toFloat());
      index = nextIndex;
    }

    Serial.print(input);
    Serial.print(acc);
    Serial.print("\n");
  }
}
