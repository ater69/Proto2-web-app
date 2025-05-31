// Initialisera kartan
    var map = L.map('map', {
      minZoom: 10,
      maxZoom: 18
    }).setView([59.53, 18.074], 13);

    // Lägg till tile layer
    L.tileLayer('https://api.maptiler.com/maps/streets-v2/{z}/{x}/{y}.png?key=574O0vWsBViNeScHREjJ', {
      attribution: '<a href="https://www.maptiler.com/copyright/" target="_blank">&copy; MapTiler</a> <a href="https://www.openstreetmap.org/copyright" target="_blank">&copy; OpenStreetMap contributors</a>'
    }).addTo(map);

    // Lägg till en marker
    var marker1 = L.marker([59.53, 18.074]).addTo(map);
    var marker2 = L.marker([59.501, 18.070]).addTo(map);

    // Koppla en popup till markern

    marker1.bindPopup('<button onclick="location.href=\'latar.html\'" class="btn btn-primary">Välj bänk</button>')

    marker1.on('click', function () {
      marker1.openPopup();
    
      
    });
    marker2.bindPopup('<button onclick="location.href=\'latar.html\'" class="btn btn-primary">Välj bänk</button>')

    marker2.on('click', function () {
      marker2.openPopup();
    
      
    });