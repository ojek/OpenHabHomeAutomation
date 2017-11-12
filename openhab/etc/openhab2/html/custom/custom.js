if (interval === 'undefined'){
    var interval = null;
}

if (typeof loadJQuery != "function") { 
    function loadJQuery(){
        var newscript = document.createElement('script');
        newscript.type = 'text/javascript';
        newscript.async = true;
        newscript.src = '/static/custom/jQuery/jquery-3.2.1.min.js';
        (document.getElementsByTagName('head')[0]||document.getElementsByTagName('body')[0]).appendChild(newscript);
    };
    loadJQuery();
}

if (typeof loadIframes != "function") {   
    interval = window.setInterval(function(){
        if (typeof jQuery != 'undefined' && typeof loadIframes != "function") {
            function loadIframes(){
                var iframeDivs = $('div.iframe');
                for(var i = 0; i < iframeDivs.length; i++){
                    var text = $(iframeDivs[i]).text();
                    $(iframeDivs[i]).text('');
                    $(iframeDivs[i]).append('<iframe src="'+text+'"></iframe>');
                }
            };
            clearInterval(interval);
            loadIframes();
        } else {
            clearInterval(interval);
        }
    }, 1000);
}

if (typeof loadIframes === "function") { 
    loadIframes();
}
