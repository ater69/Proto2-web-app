let port;
let writer;

// Funktion för att ansluta till Arduino (endast om den inte redan är ansluten)
async function connectArduino() {
    if (port) {
        console.log("Port redan ansluten.");
        return;  // Om porten redan är ansluten, gör inget
    }

    try {
        port = await navigator.serial.requestPort();  // Begär att användaren väljer port
        await port.open({ baudRate: 9600 });  // Öppna porten
        writer = port.writable.getWriter();  // Spara skrivaren
        console.log("Ansluten till Arduino!");
        document.getElementById('statusMessage').innerText = "Ansluten till Arduino";
    } catch (err) {
        console.error("Det gick inte att ansluta till Arduino:", err);
        document.getElementById('statusMessage').innerText = "Fel vid anslutning till Arduino.";
    }
}

// Funktion för att spela upp låt
async function playSong(song) {
    if (!writer) {
        await connectArduino();  // Om porten inte är öppen, försök ansluta
    }

    if (song === 'twinkle') {
        await writer.write(new TextEncoder().encode('1'));  // Spela låt
        document.getElementById('statusMessage').innerText = "Spelar: Blinka Lilla Stjärna";
    }
}

// Funktion för att stoppa uppspelning
async function stopPlayback() {
    if (writer) {
        await writer.write(new TextEncoder().encode('0'));  // Skicka stoppkommandot
        document.getElementById('statusMessage').innerText = "Uppspelning stoppad.";
    }
}

// Lägg till en knapp för att manuellt parkoppla
async function manualPairing() {
    await connectArduino();  // Tryck på knappen för att manuellt ansluta till Arduino
}
