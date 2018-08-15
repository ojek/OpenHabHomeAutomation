if (window.jQueryPending == undefined){
    window.jQueryPending = false;
}
if (window.interval == undefined){
    window.interval = null;
}
if (window.repeatTime == undefined){
    window.repeatTime = 300000; //5m
}
if (window.repeatInterval == undefined){
    window.repeatInterval = null;
}
if (window.calendarRefreshInterval == undefined){
    window.calendarRefreshInterval = null;
}

if (window.loadJQuery == undefined) 
{
    window.loadJQuery = function(){
        var newscript = document.createElement('script');
        newscript.type = 'text/javascript';
        newscript.async = true;
        newscript.src = '/static/custom/scripts/jQuery/jquery-3.2.1.min.js';
        (document.getElementsByTagName('head')[0]||document.getElementsByTagName('body')[0]).appendChild(newscript);
    };
}

if (window.loadContent == undefined) 
{
    window.loadContent = function(source, element){
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
}

if (window.updateCalendar == undefined) 
{
    window.updateCalendar = function()
    {
        var currentWeekRowNumber = 3;
        var rows = 6;
        var columns = 7;
        var totalCells = rows*columns;
        var todayDate = new Date();
        var dayInWeek = todayDate.getDay();
        var dateOptions = { weekday: 'long', year: 'numeric', month: 'long', day: 'numeric' };
        
        var calendarRows = $('table.calendar tr');
        if (calendarRows.length === 0) return;
        $('.calendarTitle').text(todayDate.toLocaleDateString('en-GB', dateOptions));
        var currentCell = $(calendarRows[currentWeekRowNumber]).children()[dayInWeek];
        $(currentCell).addClass('today');
        var currentCellNumber = ((currentWeekRowNumber-1) * 7) + dayInWeek;
        var remainingDays = totalCells - currentCellNumber;
        var maxDate = todayDate.addDays(remainingDays);
        
        for (var i = rows-1; i > 0; i--)
        {
            var calendarCells = $(calendarRows[i]).children();
            for (var z = calendarCells.length-1; z >= 0; z--)
            {
                var currentDay = maxDate.getDate();
                $(calendarCells[z]).text(currentDay);
                maxDate = maxDate.addDays(-1);
            }
        }
    };
}

if (Date.prototype.addDays == undefined) {
    Date.prototype.addDays = function(days) {
        var date = new Date(this.valueOf());
        date.setDate(date.getDate() + days);
        return date;
    }
}

if (window.jQueryPending == false) { 
    window.jQueryPending = true;
    loadJQuery();
}

if (window.interval == null) {
    window.interval = window.setInterval(function(){
        if (typeof jQuery === undefined || typeof($) === "undefined") return;
        clearInterval(window.interval);
        window.loadContent('.content .src', '<iframe src="@replace@"></iframe>');
        window.updateCalendar();

        if (window.repeatInterval === null) {
            window.repeatInterval = window.setInterval(function(){loadContent('.content .src', '<iframe src="@replace@"></iframe>'); },repeatTime);                
        }
        if (window.calendarRefreshInterval === null) {
            window.calendarRefreshInterval = window.setInterval(function(){updateCalendar();}, repeatTime);                
        }
    }, 1000);
}