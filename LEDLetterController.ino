/*
  LED Letter Controller
  Turns the LEDs mounted in large letters on and off based on
  a predefined mode. Each letter has an A, B & C control signals
  for the even outer LED, the odd outer LEDs, and the center LEDs.
  
  written 2016-07-19
  by Matthew G. Switlik
 */
#define MODE_OFF 0                  // All letters off
#define MODE_ALL_ON 1               // All letters on
#define MODE_BLINK_EACH 2           // Blink each letter on/off in succesion.
#define MODE_BLINK_EACH_THEN_ALL 3  // Blink each letter on/off in succesion then blink then all 3 times
#define MODE_CRAWL 4                // alternate every other outer led, turn off the middle ones.
#define MODE_WAVE 5                 // Turn on each letter in succession, then turn them off in succession.

#define LETTERS 4   // The total number of letters in the sign.
#define SIGNALS 3   // The total number of signals per letter.

// Letter signal pins for {A, B, C} led groups
byte lsp[LETTERS][SIGNALS]  = {{2, 3, 4}
                              ,{5, 6, 7}
                              ,{8, 9, 10}
                              ,{11, 12, 13}
                              };

// Per letter signals (bitwise representaions)
#define OFF 0
#define ON 7
#define A 4
#define B 2
#define C 1

// Set the default mode.
byte mode = MODE_OFF;


void setup() {
  // Initialize digital output pins for each letter and signal.
  for (byte ltr = 0; ltr<LETTERS; ltr++) {
    for (byte sig = 0; sig<SIGNALS; sig++) {
      pinMode(lsp[ltr][sig], OUTPUT);
    }
  }
  
}

// the loop function runs over and over again forever
void loop() {
  
  if (mode == MODE_OFF) {
    // All letters off
    byte steps = 1;
    byte patterns[][4] =  {{OFF, OFF, OFF, OFF}};
    int durations[] = {1000};
    setleds(steps, patterns, durations);
    
  } else if (mode == MODE_ALL_ON) {
    // All letters on
    byte steps = 1;
    byte patterns[][4] =  {{ON, ON, ON, ON}};
    int durations[] = {1000};
    setleds(steps, patterns, durations);
    
  } else if (mode == MODE_BLINK_EACH) {
    // Blink each letter on/off in succesion.
    byte steps = 8;
    byte patterns[][4] =  {{ON, OFF, OFF, OFF}
                          ,{OFF, OFF ,OFF, OFF}
                          ,{OFF, ON ,OFF, OFF}
                          ,{OFF, OFF, OFF, OFF}
                          ,{OFF, OFF, ON, OFF}
                          ,{OFF, OFF, OFF, OFF}
                          ,{OFF, OFF, OFF, ON}
                          ,{OFF, OFF, OFF, OFF}
                          };
    int durations[] = {1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       };
    setleds(steps, patterns, durations);
    
  } else if (mode == MODE_BLINK_EACH_THEN_ALL) {
    // Blink each letter on/off in succesion then blink then all 3 times
    byte steps = 14;
    byte patterns[][4] =  {{ON, OFF, OFF, OFF}
                          ,{OFF, OFF ,OFF, OFF}
                          ,{OFF, ON ,OFF, OFF}
                          ,{OFF, OFF, OFF, OFF}
                          ,{OFF, OFF, ON, OFF}
                          ,{OFF, OFF, OFF, OFF}
                          ,{OFF, OFF, OFF, ON}
                          ,{OFF, OFF, OFF, OFF}
                          ,{ON, ON, ON, ON}
                          ,{OFF, OFF, OFF, OFF}
                          ,{ON, ON, ON, ON}
                          ,{OFF, OFF, OFF, OFF}
                          ,{ON, ON, ON, ON}
                          ,{OFF, OFF, OFF, OFF}
                          };
    int durations[] = {1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       };
    setleds(steps, patterns, durations);
    
  } else if (mode == MODE_CRAWL) {
    // alternate every other outer led, turn off the middle ones.
    byte steps = 2;
    byte patterns[][4] =  {{A, A, A, A}
                          ,{B, B, B, B}
                          };
    int durations[] = {1000
                      ,1000
                      };
    setleds(steps, patterns, durations);
    
  } else if (mode == MODE_WAVE) {
    // Turn on each letter in succession, then turn them off in succession.
    byte steps = 8;
    byte patterns[][4] =  {{ON, OFF, OFF, OFF}
                          ,{ON, ON, OFF, OFF}
                          ,{ON, ON, ON, OFF}
                          ,{ON, ON, ON, ON}
                          ,{OFF, ON, ON, ON}
                          ,{OFF, OFF, ON, ON}
                          ,{OFF, OFF, OFF, ON}
                          ,{OFF, OFF, OFF, OFF}
                          };
    int durations[] = {1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       ,1000
                       };
    setleds(steps, patterns, durations);
    
  }
}

void setleds(byte steps, byte patterns[][4], int durations[]) 
{
    // For each step.
    for (byte s=0; s<steps; s++) {
      // For each Letter
      for (byte ltr=0; ltr<LETTERS; ltr++) {
        // Get the patterns bitwise representation.
        byte pat = patterns[s][ltr];

        // Bitwise AND the pattern with the A signal bit. On if matches else off.
        if (pat & A == A) {
          digitalWrite(lsp[ltr][0], HIGH);
        } else {
          digitalWrite(lsp[ltr][0], LOW);
        }

        // Bitwise AND the pattern with the B signal bit. On if matches else off.
        if (pat & B == B) {
          digitalWrite(lsp[ltr][1], HIGH);
        } else {
          digitalWrite(lsp[ltr][1], LOW);
        }

        // Bitwise AND the pattern with the C signal bit. On if matches else off.
        if (pat & C == C) {
          digitalWrite(lsp[ltr][2], HIGH);
        } else {
          digitalWrite(lsp[ltr][2], LOW);
        }
      }
      delay(durations[s]);
    }
}
