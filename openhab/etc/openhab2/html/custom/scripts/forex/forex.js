function forex(){
	$.get('https://cors.io/?https://panel.walutomat.pl/api/v1/best_offers.php', function (data) {
        for (var i = 0; i < data.offers.length; i++){
            if (data.offers[i].pair === "EURPLN"){
                var currRate = data.offers[i].buy.replace('.','');
                var prevRate = data.offers[i].buy_old.replace('.','');
                
                //if (currRate < prevRate) {
                //    chrome.browserAction.setBadgeBackgroundColor({ color: [255, 0, 0, 255] });
                //}
                //else if (currRate > prevRate) {
                //    chrome.browserAction.setBadgeBackgroundColor({ color: [0, 255, 0, 255] });
                //}
                document.getElementById("forex").innerText = data.offers[i].buy;
                document.getElementById("forex").textContent = data.offers[i].buy;
                setTimeout(forex, window.repeatTime);
            }
        }
    });
};