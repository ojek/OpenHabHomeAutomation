if (typeof loadJQuery != "function") { 
    function loadJQuery(){
        var newscript = document.createElement('script');
        newscript.type = 'text/javascript';
        newscript.async = true;
        newscript.src = '/static/custom/jQuery/jquery-3.2.1.min.js';
        (document.getElementsByTagName('head')[0]||document.getElementsByTagName('body')[0]).appendChild(newscript);
    }
    loadJQuery();
}

if (typeof loadIframes != "function") { 
    function loadIframes(){
        var iframeDivs = $('div.iframe');
        for(var i = 0; i < iframeDivs.length; i++){
            var text = $(iframeDivs[i]).text();
            $(iframeDivs[i]).text('');
            $(iframeDivs[i]).append('<iframe src="'+text+'"></iframe>');
        }
    }
}

loadIframes();