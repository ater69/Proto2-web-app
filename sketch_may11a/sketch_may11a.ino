int LED_CR = A5;
int LED_CB = A4;
int LED_D = 7;
int LED_E = 8;
int LED_F = 9;
int LED_G = 10;
int LED_A = 11;
int LED_B = 12;
int LED_C2 = 5;

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
}

void blinkalillastjarna() {
    isPlaying = true;

    C_note(); C_note(); G_note(); G_note();
    A_note(); A_note(); G_note();
    F_note(); F_note(); E_note(); E_note();
    D_note(); D_note(); C_note();

    isPlaying = false;
}

void C_note() {
    delay(300);
    digitalWrite(LED_CR, HIGH);   
    digitalWrite(LED_CB, HIGH);
    delay(300);
    digitalWrite(LED_CR, LOW);
    digitalWrite(LED_CB, LOW);
    delay(10);  // Kort delay för att hantera serialkommunikationen
}

void D_note() {
    delay(300);
    digitalWrite(LED_D, HIGH);
    delay(300);
    digitalWrite(LED_D, LOW);
    delay(10);  // Kort delay för att hantera serialkommunikationen
}

void E_note() {
    delay(300);
    digitalWrite(LED_E, HIGH);
    delay(300);
    digitalWrite(LED_E, LOW);
    delay(10);
}

void F_note() {
    delay(300);
    digitalWrite(LED_F, HIGH);
    delay(300);
    digitalWrite(LED_F, LOW);
    delay(10);
}

void G_note() {
    delay(300);
    digitalWrite(LED_G, HIGH);
    delay(300);
    digitalWrite(LED_G, LOW);
    delay(10);
}

void A_note() {
    delay(300);
    digitalWrite(LED_A, HIGH);
    delay(300);
    digitalWrite(LED_A, LOW);
    delay(10);
}

void B_note() {
    delay(300);
    digitalWrite(LED_B, HIGH);
    delay(300);
    digitalWrite(LED_B, LOW);
    delay(10);
}

void C2_note() {
    delay(300);
    digitalWrite(LED_C2, HIGH);
    delay(300);
    digitalWrite(LED_C2, LOW);
    delay(10);
}

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
        Serial.print("Mottaget kommando: "); // För att skriva ut det mottagna kommandot
        Serial.println(command);
        if (command == '1' && !isPlaying) {
            blinkalillastjarna();
        } else if (command == '0') {
            stopSong();
        }
    }
}
