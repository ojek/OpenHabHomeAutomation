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

if (typeof loadContent != "function") {   
    interval = window.setInterval(function(){
        if (typeof jQuery != 'undefined' && typeof loadContent != "function") {
            function loadContent(selector, element){
                var iframeDivs = $(selector);
                for(var i = 0; i < iframeDivs.length; i++){
                    var text = $(iframeDivs[i]).text();
                    if (text.indexOf('#loading_') === -1) continue;
                    text = text.replace('#loading_', '');
                    $(iframeDivs[i]).text('');
                    $(iframeDivs[i]).append(element.replace('@replace@', text));
                }
            };
            clearInterval(interval);
            loadContent('div.iframe', '<iframe src="@replace@"></iframe>');
            loadContent('div.icon', '<svg viewBox="0 0 48 48"><use xlink:href="/static/custom/icons.svg#@replace@"/></svg>');
        } else {
            clearInterval(interval);
        }
    }, 1000);
}

if (typeof loadContent === "function") { 
    loadContent('div.iframe', '<iframe src="@replace@"></iframe>');
    loadContent('div.icon', '<svg viewBox="0 0 48 48"><use xlink:href="/static/custom/icons.svg#@replace@"/></svg>');
}
