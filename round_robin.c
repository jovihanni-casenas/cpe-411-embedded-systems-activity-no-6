/*
 * Jovihanni Caseñas
 * BSCpE 4A
 * CPE 411 Embedded Systems
 * Activity 6
 * Round Robin algorithm
 * TinkerCAD implementation
 *
 * ON led = task is executing
 * OFF led = task is waiting/done executing
 *
 * Assume that arrival time is based on led number
 *
 * This simulation asks for burst time input
 * and quantum time input from the user
 * The LEDs are then turned on in the order
 * of led1 to led10 taking n-second turns
 * and the queue goes circular until the
 * burst time is completed
 */

int led[10] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11
};
int led_on_time[10];
int i, j, temp, int_data, duration, empty_c, qt_time;
char chars_input[10][3], data_input;
bool received_input = false;
bool input_complete = false;
bool get_qt_time = false;

void setup() {
  /* put your setup code here, to run once: */
  Serial.begin(9600);
  i = 0;
  j = 0;
  qt_time = 0;
  
  /* setting all LEDs as output */
  for (int i = 0; i < 10; i++) {
    pinMode(led[i], OUTPUT);
  }
  
  /* user can input up to 99 seconds */
  Serial.println("Ready to receive input burst time in seconds...");
  Serial.println("Type e to end input...");
  Serial.print("Enter led1 burst time: ");
}
  
void loop() {
  /* put your main code here, to run repeatedly: */
  if (!received_input && i < 10) {
  	get_input();
  }
  received_input = false;
  
  if (input_complete) {
    chars_to_int();
    input_complete = false;
    get_qt_time = true;
    Serial.print("\nEnter Quantum Time: ");
    while (!input_complete) {
      get_input();
    }
    Serial.print(qt_time);
    rr();
    Serial.print("\nFinished...");
    input_complete = false;
  }
}

/* printing message to the serial monitor */
void print_msg() {
  if (i < 10) {
  	Serial.print("\nEnter led");
  	Serial.print(led[i] - 1);
  	Serial.print(" burst time: ");
  } else {
    input_complete = true;
  }
}

/* getting burst time input by user from serial monitor */
void get_input() {
  if (Serial.available() > 0) {
    data_input = Serial.read();
    
    if (data_input == 'e') {
      i++;
      j = 0;
      print_msg();
    } else if (get_qt_time == true) {
      qt_time = (qt_time * 10) + (data_input - '0');
    } else {
      chars_input[i][j] = data_input;
      Serial.print(chars_input[i][j]);
      received_input = true;
      j++;
    }
  }
}

/* converting char input to int*/
void chars_to_int() {
  for (int i = 0; i < 10; i++) {
    int_data = 0;
    for (int j = 0; chars_input[i][j] != NULL; j++) {
      int_data = (int_data * 10) + (int)(chars_input[i][j] - '0');
    }
    led_on_time[i] = int_data;
  }
}

/* round robin algorithm implementation*/
void rr() {
  i = 0;
  empty_c = 0;
  while (true) {
    if (empty_c == 10) {
      break;
    }
    if (led_on_time[i] <= 0){
      empty_c++;
    } else if (led_on_time[i] >= qt_time) {
      duration = qt_time;
      turn_on();
    } else if (led_on_time[i] < qt_time) {
      duration = led_on_time[i];
      turn_on();
    }
    led_on_time[i] -= qt_time;
    i = (i + 1) % 10;
  }
}

/* turning on the LED */
void turn_on() {
  digitalWrite(led[i], HIGH);
  delay(duration * 1000); /* 
   						   * multiplying with
  						   * 1000 to convert
                           * seconds to milliseconds
                           */
  digitalWrite(led[i], LOW);
}
