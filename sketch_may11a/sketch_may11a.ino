int LED_CR = 11;
int LED_CB = 12;
int LED_D = 10;
int LED_E = 9;
int LED_F = 8;
int LED_G = 7;
int LED_A = 6;
int LED_B = 5;

int knobPin = A3;
int baseDelay = 275;
bool isPlaying = false;
unsigned long lastNoteTime = 0;

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

    pinMode(knobPin, INPUT);
}

int getDynamicDelay() {
    int knobValue = analogRead(knobPin);
    Serial.print("Knob value (delay): ");
    Serial.println(knobValue);
    return map(knobValue, 0, 1023, 50, 500);
}

void indicateSpeed() {
    if (!isPlaying) {
        int knobValue = analogRead(knobPin);
        int numberOfLEDs = map(knobValue, 0, 1023, 8, 1);

        // Stäng av alla
        digitalWrite(LED_CR, LOW);
        digitalWrite(LED_CB, LOW);
        digitalWrite(LED_D, LOW);
        digitalWrite(LED_E, LOW);
        digitalWrite(LED_F, LOW);
        digitalWrite(LED_G, LOW);
        digitalWrite(LED_A, LOW);
        digitalWrite(LED_B, LOW);

        // Tänd utifrån delay
        if (numberOfLEDs >= 1) digitalWrite(LED_CR, HIGH);
        if (numberOfLEDs >= 2) digitalWrite(LED_CB, HIGH);
        if (numberOfLEDs >= 3) digitalWrite(LED_D, HIGH);
        if (numberOfLEDs >= 4) digitalWrite(LED_E, HIGH);
        if (numberOfLEDs >= 5) digitalWrite(LED_F, HIGH);
        if (numberOfLEDs >= 6) digitalWrite(LED_G, HIGH);
        if (numberOfLEDs >= 7) digitalWrite(LED_A, HIGH);
        if (numberOfLEDs >= 8) digitalWrite(LED_B, HIGH);
    }
}

void blinkalillastjarna() {
    isPlaying = true;
    
    // Släck alla lampor innan melodin startar
    digitalWrite(LED_CR, LOW);
    digitalWrite(LED_CB, LOW);
    digitalWrite(LED_D, LOW);
    digitalWrite(LED_E, LOW);
    digitalWrite(LED_F, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_A, LOW);
    digitalWrite(LED_B, LOW);
    delay(50); // Låt alla lampor stängas av ordentligt

    // Spela melodin
    C_note(); C_note(); G_note(); G_note();
    A_note(); A_note(); G_note();
    F_note(); F_note(); E_note(); E_note();
    D_note(); D_note(); C_note();

    // Återställ efter melodin
    isPlaying = false;
    lastNoteTime = millis();
}

void playNote(int ledPin) {
    int delayTime = getDynamicDelay();
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
    digitalWrite(ledPin, LOW);
    delay(delayTime);
    lastNoteTime = millis();
}

void C_note() { 
    int delayTime = getDynamicDelay();
    digitalWrite(LED_CR, HIGH); 
    digitalWrite(LED_CB, HIGH); 
    delay(delayTime);
    digitalWrite(LED_CR, LOW); 
    digitalWrite(LED_CB, LOW);
    delay(delayTime);
    lastNoteTime = millis();
}

void D_note() { playNote(LED_D); }
void E_note() { playNote(LED_E); }
void F_note() { playNote(LED_F); }
void G_note() { playNote(LED_G); }
void A_note() { playNote(LED_A); }
void B_note() { playNote(LED_B); }

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
}

void loop() {
    // Kontrollera om melodin är klar (efter 100ms från sista noten)
    if (isPlaying && (millis() - lastNoteTime) > 100) {
        isPlaying = false;
    }

    indicateSpeed();

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