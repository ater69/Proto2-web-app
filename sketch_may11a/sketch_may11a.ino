int LED_CR = A5;
int LED_CB = A4;
int LED_D = 7;
int LED_E = 8;
int LED_F = 9;
int LED_G = 10;
int LED_A = 11;
int LED_B = 12;
int LED_C2 = 5;

int knobPin = A3; // Potentiometer för att justera delay
int baseDelay = 300;
bool isPlaying = false;

void setup() {
    Serial.begin(9600);

    pinMode(LED_CR, OUTPUT);
    pinMode(LED_CB, OUTPUT);
    pinMode(LED_D, OUTPUT);
    pinMode(LED_E, OUTPUT);
    pinMode(LED_F, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_A, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(LED_C2, OUTPUT);

    pinMode(knobPin, INPUT);
}

int getDynamicDelay() {
    int knobValue = analogRead(knobPin);
    return map(knobValue, 0, 1023, 100, 600); // Justerar delay mellan 100ms och 600ms
}

void blinkalillastjarna() {
    isPlaying = true;

    C_note(); C_note(); G_note(); G_note();
    A_note(); A_note(); G_note();
    F_note(); F_note(); E_note(); E_note();
    D_note(); D_note(); C_note();

    isPlaying = false;
}

void playNote(int ledPin) {
    int delayTime = getDynamicDelay();
    delay(delayTime);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
    digitalWrite(ledPin, LOW);
    delay(10);  
}

void C_note() { playNote(LED_CR); playNote(LED_CB); }
void D_note() { playNote(LED_D); }
void E_note() { playNote(LED_E); }
void F_note() { playNote(LED_F); }
void G_note() { playNote(LED_G); }
void A_note() { playNote(LED_A); }
void B_note() { playNote(LED_B); }
void C2_note() { playNote(LED_C2); }

void stopSong() {
    isPlaying = false;
    digitalWrite(LED_CR, LOW);
    digitalWrite(LED_CB, LOW);
    digitalWrite(LED_D, LOW);
    digitalWrite(LED_E, LOW);
    digitalWrite(LED_F, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_A, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_C2, LOW);
}

void loop() {
    if (Serial.available() > 0) {
        char command = Serial.read();
        Serial.print("Mottaget kommando: ");
        Serial.println(command);
        if (command == '1' && !isPlaying) {
            blinkalillastjarna();
        } else if (command == '0') {
            stopSong();
        }
    }
}