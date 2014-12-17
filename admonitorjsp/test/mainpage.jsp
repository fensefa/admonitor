<!--[if IE]>
<h1>抱歉，网页对IE不能很好支持，请更换chrome或firefox浏览器</h1>
<![endif]-->

<head>

	<title>Admonitor</title>
	
	<!meta http-equiv="refresh" content="60"></meta>

	<script src="lib/jquery-1.11.1.min.js"></script>
	<script src="lib/raphael-min.js"></script>
	<script src="lib/morris.js"></script>
	<script src="lib/prettify.min.js"></script>
	<script src="lib/example.js"></script>
	<script src="lib/admonit.js"></script>
	<!link rel="stylesheet" href="lib/example.css">
	<link rel="stylesheet" href="lib/prettify.min.css">
	<link rel="stylesheet" href="lib/morris.css">

</head>

<jsp:useBean id='admonitor' scope='page' class='admonitor.admonitorJsp' />

<%@ page language="java" contentType="text/html;charset=utf-8"%>
<%@ page import="java.io.*" %>
<%@ page import="java.util.*" %>
<%@ page import="java.*" %>
<%@ page import="java.math.*" %>
<%@ page import="java.text.*" %>
<%@ page import="javax.servlet.http.*" %>
<%! int i=0; %>
<%= i++%>

<%
	Date date0 = new Date();
	DateFormat dateformat0 = new SimpleDateFormat("yyyyMMdd");
	String module0 = "mock2";
	String datestr0 = dateformat0.format(date0);
	String suffix0 = "m1.txt";
	String filename0 = datestr0 + "/" + module0 + suffix0;
	String data0 = admonitor.fileToJson(filename0);
%>

<script language="javascript">
	var str0 = <%= data0 %>
	var mydata0 = new Array()
	var total0  = new Object()
	total0.y = 0
	total0.z = 0
	total0.w = 0
	for(i=0;i<str0.length;i++)
	{
		if(str0[i] == null)
			break;
		mydata0[i] = new Object()
		mydata0[i].x = parseInt(str0[i]["time"]) * 1000
		mydata0[i].y = str0[i]["kpis"][0]["views"][0]["dims"]["man"]
		mydata0[i].z = str0[i]["kpis"][2]["views"][0]["dims"]["man"]
		mydata0[i].w = str0[i]["kpis"][3]["views"][0]["dims"]["man"]
		total0.z += mydata0[i].z
		total0.y += mydata0[i].y
		total0.w  = mydata0[i].w
	}
</script>
<div id=maingraph>
<div align="left" style="width:30%;height:33%;float:left;">
<h2 align="center"> the data of click</h2>
</div>
<div id="graph1" style="height:33%;width:70%;float:right;background-color:bule"></div>
<div align="left" style="width:30%;height:33%;float:left;">
<h2 align="center"> the date of show</h2>
</div>
<div id="graph2" style="height:33%;width:70%;float:right;backgrount-color:yellow"></div>
<div align="left" style="width:30%;height:33%;float:left;">
<h2 align="center"> the data of ctr</h2>
</div>
<div id="graph3" style="height:33%;width:70%;float:right;"></div>
</div>

<script type="text/javascript">
	var colors = ['#000000','#C71585', '#800000', '#8B4513', '#006400', '#2F4F4F',  '#0000CD'];
	Morris.Line({
		element: 'graph1',
  		data: mydata0,
  		xkey: 'x',
  		ykeys:	'y',
		labels: ["click"],
  		lineWidth: 2,
  		pointSize: 0,
  		lineColors: colors,
  		pointFillColors: colors,
  		pointStrokeColors: colors
	})

	Morris.Line({
		element: 'graph2',
  		data: mydata0,
  		xkey: 'x',
  		ykeys:	'z',
		labels: ["show"],
  		lineWidth: 2,
  		pointSize: 0,
  		lineColors: colors,
  		pointFillColors: colors,
  		pointStrokeColors: colors
   	});
	Morris.Line({
		element: 'graph3',
  		data: mydata0,
  		xkey: 'x',
  		ykeys:	'w',
		labels: ["ctr"],
  		lineWidth: 2,
  		pointSize: 0,
  		lineColors: colors,
  		pointFillColors: colors,
  		pointStrokeColors: colors
   	});
</script>

<script>
	var h1 = document.createElement('h1')
	h1.align = 'center'
	h1.innerHTML = total0.y
	document.getElementById("graph1").previousElementSibling.appendChild(h1)
	var h1 = document.createElement('h1')
	h1.align = 'center'
	h1.innerHTML = total0.z
	document.getElementById("graph2").previousElementSibling.appendChild(h1)
	var h1 = document.createElement('h1')
	h1.align = 'center'
	h1.innerHTML = (total0.y/total0.z).toFixed(2)
	document.getElementById("graph3").previousElementSibling.appendChild(h1)
</script>
