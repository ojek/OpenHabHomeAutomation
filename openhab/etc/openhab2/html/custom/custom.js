var app = angular.module('app', ['ngSanitize']);
app.config(['$sceProvider',function($sceProvider){
    $sceProvider.enabled(false);
}]);