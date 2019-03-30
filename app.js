var express = require('express');
var app = express();
var fs = require('fs');
var mysql = require('mysql');
var dateFormat = require('dateformat')
var userinfo = require('./user_info.js')
var connection  = mysql.createConnection({
	host: 'localhost',
	user: userinfo.sqluser,
	password: userinfo.sqlpw,
	database: userinfo.sqldb
})
connection.connect();

function insert_sensor(value,ip){
	obj = {};
	obj.value = value;
	obj.ip = ip.replace(/^.*:/, '')

	var query = connection.query('insert into sensors set ?', obj, function(err, rows, cols) {
		if (err) throw err;
		console.log("database insertion ok= %j",obj);
	});
}

app.get('/', function (req, res) {
res.end('Nice to meet you');
});


app.get('/graph', function (req, res) {
    console.log('got app.get(graph)');
    var html = fs.readFile('./graph.html', function (err, html) {
    html = " "+ html
    console.log('read file');

    var qstr = 'select * from sensors ';
    connection.query(qstr, function(err, rows, cols) {
      if (err) throw err;

      var data = "";
      var comma = ""
      for (var i=0; i< rows.length; i++) {
         r = rows[i];
  	 data += comma + "[new Date("+dateFormat(r.time,"yyyy")+","+(dateFormat(r.time,"m")-1)+","+dateFormat(r.time,"dd,HH,MM,ss")+ "),"+r.value +"]";
	 /*data += comma + "["+ r.id +","+ r.value +"]";*/
         comma = ",";
      }
      var header = "data.addColumn('datetime', 'Date/Time');"
      header += "data.addColumn('number', 'Temp');"
      html = html.replace("<%HEADER%>", header);
      html = html.replace("<%DATA%>", data);

      res.writeHeader(200, {"Content-Type": "text/html"});
      res.write(html);
      res.end();
    });
  });
})

app.get('/update', function(req, res) {
  r = req.query;
  console.log("GET %j", r);

  insert_sensor(r.value, req.connection.remoteAddress);
  res.end('OK:' + JSON.stringify(req.query));
});

var server = app.listen(userinfo.port, function () {
  var host = server.address().address
  var port = server.address().port
  console.log('listening at http://%s:%s',host,port)
});

