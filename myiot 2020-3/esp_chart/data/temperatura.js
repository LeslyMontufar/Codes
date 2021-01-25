/************************************************************
 * MOSTRANDO A TEMPERATURA EM TEMPO REAL
 */

var chartT = new Highcharts.Chart({
  chart:{ renderTo : 'chart-temperature' }, //id
  title: { text: 'Temperatura' },
  series: [{
    showInLegend: false,
    data: []
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    },
    series: { color: '#059e8a' }
  },
  xAxis: { type: 'datetime',
    dateTimeLabelFormats: { second: '%H:%M:%S' }
  },
  yAxis: {
    title: { text: 'Temperatura (Celsius)' }
  },
  credits: { enabled: false }
});

setInterval(function ( ) {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) { //200 é o OK
      var x = (new Date()).getTime() - (3*60*60*1000), // fuso Brasil
          y = parseFloat(this.responseText); 
      document.getElementById("temperature").innerHTML = this.responseText;
      if(chartT.series[0].data.length > 40) {
        chartT.series[0].addPoint([x, y], true, true, true);
      } else {
        chartT.series[0].addPoint([x, y], true, false, true);
      }
    }
};
xhttp.open("GET", "/temperature", true); //no /temperature que está a info que precisamos
xhttp.send();
}, 30000 ) ;


/************************************************************
 * MOSTRANDO SE O AQUECIMENTO ESTÁ LIGADO
 */

// var button, c, ctx;
// button = document.getElementById("toggleButton");
// c = document.getElementById("led");
// ctx = c.getContext("2d");
// ctx.arc(25,25,15,0,2*Math.PI, false);
// ctx.lineWidth = 3;
// ctx.strokeStyle = "black";
// ctx.stroke();
// ctx.fillStyle = "black";
// ctx.fill();

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) { 
      document.getElementById("aquecimento").innerHTML = this.responseText;
      // switch(this.responseText) {
      //   case "0":
      //     console.log("LED desligado");
      //     ctx.fillStyle = "black";
      //     ctx.fill();
      //     break;
      //   case "1":
      //     console.log("LED ligado");
      //     ctx.fillStyle = "#fffa65";
      //     ctx.fill();
      //     break;
      //   default:
      //     break;
      // }
    }
  };
  xhttp.open("GET", "/aquecimento", true); 
  xhttp.send();
}, 30000 ) ;
