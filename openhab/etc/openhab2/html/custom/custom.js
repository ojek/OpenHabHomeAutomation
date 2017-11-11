(function(){
    var newscript = document.createElement('script');
    newscript.type = 'text/javascript';
    newscript.async = true;
    newscript.src = '/static/custom/jQuery/jquery-3.2.1.min.js';
    (document.getElementsByTagName('head')[0]||document.getElementsByTagName('body')[0]).appendChild(newscript);
})();

function loadIframes(){
    var iframes = $('div.iframe');
    for(var i = 0; i < iframes.length; i++){
        var text = iframes[i].text();
        iframes.appendChild('<iframe src="'+text+'"></iframe>');
    }
}