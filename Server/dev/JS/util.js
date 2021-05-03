'use strict';

window.chartColors = {
    red: 'rgb(255, 51, 76)',
    orange: 'rgb(255, 159, 64)',
    yellow: 'rgb(255, 205, 86)',
    green: 'rgb(57, 255, 51)',
    blue: 'rgb(54, 162, 235)',
    purple: 'rgb(153, 102, 255)',
    grey: 'rgb(201, 203, 207)'
};

var util = {};

util.methods = {

    dateUnix: function(timeUnix) {
        const unixTime = timeUnix;
        const dateStamp = new Date(unixTime * 1000);
        //console.log(date.toLocaleDateString("en-US"));
        //console.log(date);

        var tiempo = "" + dateStamp.getHours() + ":" + dateStamp.getMinutes() + ":" + dateStamp.getSeconds();
        return tiempo;
    }
}