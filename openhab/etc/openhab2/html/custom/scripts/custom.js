if (interval == undefined){
    var interval = null;
}
if (repeatTime == undefined){
    var repeatTime = 300000; //5m
}
if (repeatInterval == undefined){
    var repeatInterval = null;
}

if (typeof loadJQuery != "function") { 
    function loadJQuery(){
        var newscript = document.createElement('script');
        newscript.type = 'text/javascript';
        newscript.async = true;
        newscript.src = '/static/custom/scripts/jQuery/jquery-3.2.1.min.js';
        (document.getElementsByTagName('head')[0]||document.getElementsByTagName('body')[0]).appendChild(newscript);
    };
    loadJQuery();
}

if (typeof loadContent != "function" && window.interval === null) {   
    window.interval = window.setInterval(function(){
        if (typeof loadContent != "function") {
            if (typeof jQuery === undefined || typeof($) === "undefined") return;
            function loadContent(source, element){
                var srcElems = $(source);
                for(var i = 0; i < srcElems.length; i++){
                    var text = $(srcElems[i]).text();
                    if (text.indexOf('#loading_') === -1) continue;
                    text = text.replace('#loading_', '');
                    var adjacentElem = $(srcElems[i]).next();
                    $(adjacentElem).text('');
                    $(adjacentElem).append(element.replace('@replace@', text));
                }
            };
            clearInterval(window.interval);
            loadContent('td.iframe .src', '<iframe src="@replace@"></iframe>');

            if (window.repeatInterval === null) {
                window.repeatInterval = window.setInterval(function(){loadContent('td.iframe .src', '<iframe src="@replace@"></iframe>')},repeatTime);                
            }
        } 
        else {
            clearInterval(window.interval);
        }
    }, 1000);
}