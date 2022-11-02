/*
 * Jovihanni Caseñas
 * BSCpE 4A
 * CPE 411 Embedded Systems
 * Activity 6
 * Shortest Job First algorithm
 * TinkerCAD implementation
 *
 * ON led = task is executing
 * OFF led = task is waiting/done executing
 *
 * Assume that arrival time is based on led number
 *
 * This simulation asks for burst time input
 * from the user
 * The LEDs are then turned on in the order
 * of its burst time from shortest
 * to longest
 */

int led[10] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11
};
int led_on_time[10];
int i, j, temp, int_data;
char burst_time[10][3], data_input;
bool received_input = false;
bool input_complete = false;

void setup() {
  /* put your setup code here, to run once: */
  Serial.begin(9600);
  i = 0;
  j = 0;
  
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
  	get_burst_time();
  }
  received_input = false;
  
  if (input_complete) {
    chars_to_int();
    input_complete = false;
    sjf();
    Serial.print("\nFinished...");
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
void get_burst_time() {
  if (Serial.available() > 0) {
    data_input = Serial.read();
    
    if (data_input == 'e') {
      i++;
      j = 0;
      print_msg();
    } else {
      burst_time[i][j] = data_input;
      Serial.print(burst_time[i][j]);
      received_input = true;
      j++;
    }
  }
}

/* converting char input to int*/
void chars_to_int() {
  for (int i = 0; i < 10; i++) {
    int_data = 0;
    for (int j = 0; burst_time[i][j] != NULL; j++) {
      int_data = (int_data * 10) + (int)(burst_time[i][j] - '0');
    }
    led_on_time[i] = int_data;
  }
}

/* shortest job first algorithm implementation*/
void sjf() {
  sort_data();
  for (int i = 0; i < 10; i++) {
    digitalWrite(led[i], HIGH);
    delay(led_on_time[i] * 1000); /* 
    							   * multiplying with
    							   * 1000 to convert
                                   * seconds to milliseconds
                                   */
    digitalWrite(led[i], LOW);
  }
}

/* sorting data according to burst time */
void sort_data() {
  for (int i = 0; i < 10; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (led_on_time[i] > led_on_time[j]) {
        /* 
         * swapping pins according to
         * shortest to longest
         * burst time
         */
      	temp = led[i];
        led[i] = led[j];
        led[j] = temp;
        
        /* 
         * sorting led ON duration
         * according to burst time
         */
        temp = led_on_time[i];
        led_on_time[i] = led_on_time[j];
        led_on_time[j] = temp;
      }
    }
  }
}
