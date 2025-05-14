// Songs for xylophone (notes correspond to xylophone keys)
const songs = {
    1: { // Twinkle Twinkle Little Star
        name: "Twinkle Twinkle Little Star",
        notes: ["C", "C", "G", "G", "A", "A", "G", "F", "F", "E", "E", "D", "D", "C"],
        durations: [500, 500, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 500, 500, 1000]
    },
    2: { // Ode to Joy
        name: "Ode to Joy",
        notes: ["E", "E", "F", "G", "G", "F", "E", "D", "C", "C", "D", "E", "E", "D", "D"],
        durations: [500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 750, 500, 1000]
    },
    3: { // Happy Birthday
        name: "Happy Birthday",
        notes: ["C", "C", "D", "C", "F", "E", "C", "C", "D", "C", "G", "F", "C", "C", "C", "A", "F", "E", "D", "A#", "A#", "A", "F", "G", "F"],
        durations: [300, 300, 600, 600, 600, 1200, 300, 300, 600, 600, 600, 1200, 300, 300, 600, 600, 600, 600, 600, 300, 300, 600, 600, 600, 1200]
    }
};

let isPlaying = false;
let currentSong = null;
let currentSongId = null;

function playSong(songNumber) {
    if (isPlaying && currentSongId === songNumber) {
        stopPlayback();
        return;
    } else if (isPlaying) {
        stopPlayback();
    }

    currentSong = songs[songNumber];
    currentSongId = songNumber;
    isPlaying = true;

    // Uppdatera gränssnittet
    document.getElementById('statusMessage').textContent =
        `Spelar: ${currentSong.name}`;

    // Markera aktiv låt
    document.getElementById(`song${songNumber}`).classList.add('playing');
    const btn = document.getElementById(`btn${songNumber}`);
    btn.textContent = 'Avbryt';
    btn.classList.remove('btn-primary');
    btn.classList.add('btn-warning');

    // Simulate playing each note
    playNotes(0);
}

function playNotes(index) {
    if (!isPlaying || index >= currentSong.notes.length) {
        stopPlayback();
        return;
    }

    const note = currentSong.notes[index];
    const duration = currentSong.durations[index];

    // Send command to Arduino (simulated)
    sendToArduino(`PLAY:${note}`);

    setTimeout(() => {
        // Play next note after a short pause
        setTimeout(() => {
            playNotes(index + 1);
        }, 100);
    }, duration - 100);
}

function stopPlayback() {
    if (!isPlaying) return;

    isPlaying = false;

    // Återställ gränssnittet
    if (currentSongId) {
        document.getElementById(`song${currentSongId}`).classList.remove('playing');
        const btn = document.getElementById(`btn${currentSongId}`);
        btn.textContent = 'Spela låt';
        btn.classList.remove('btn-warning');
        btn.classList.add('btn-primary');
    }

    document.getElementById('statusMessage').textContent =
        "Uppspelning stoppad. Välj en låt att spela.";

    sendToArduino("STOP");

    currentSong = null;
    currentSongId = null;
}

function sendToArduino(command) {
    // This is where you would communicate with the Arduino
    console.log("Skickar till Arduino:", command);

    /* Actual Web Serial API code might look like:
    if (port && port.writable) {
        const writer = port.writable.getWriter();
        const encoder = new TextEncoder();
        writer.write(encoder.encode(command + '\n'));
        writer.release();
    }
    */
}