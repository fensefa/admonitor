<!--[if IE]>
<h1>抱歉，网页对IE不能很好支持，请更换chrome或firefox浏览器</h1>
<![endif]-->

<head>

	<title>Admonitor</title>

	<script src="lib/jquery-1.11.1.min.js"></script>
	<script src="lib/raphael-min.js"></script>
	<script src="lib/morris.js"></script>
	<!script src="lib/prettify.min.js"></script>
	<script src="lib/admonit.js"></script>
	<!link rel="stylesheet" href="lib/prettify.min.css">
	<link rel="stylesheet" href="lib/morris.css">

	<style type="text/css">
		div#div1 {background-color:#0000ff;height:0;width:20%;float:left;}
		div#div0 {background-color:CCFFCC;height:100%;width:20%;float:left;}
		div#div2 {backgrount-color:00CC99;height:200;width:79%;float:right;}
		div#div3 {background-color:00CC99;height:200;width:79%;float:right;}
		div#menu {background-color:#000352;height:300px;width:79%;float:right;}
		div#graph {background-color:#ffff99;height:400px;width:79%;float:right;}
		div#chart {background-color:3366CC;width:79%;float:right;}
		div#maingraph {height:100%;width:80%;float:right;}
	</style>
</head>

<%@ page language="java" contentType="text/html;charset=utf-8"%>
<%@ page import="java.io.*" %>
<%@ page import="java.util.*" %>
<%@ page import="java.*" %>
<%@ page import="java.math.*" %>
<%@ page import="java.text.*" %>
<%@ page import="javax.servlet.http.*" %>

<jsp:useBean id='admonitor' scope='page' class='admonitor.admonitorJsp' />
<% admonitor.setFilePath("/home/public/testfiles/"); %>

<%
	String module = request.getParameter("module");
	if(module == null)
		module = "mock";
	String kpiname = request.getParameter("kpiname");
	if(kpiname == null)
		kpiname = "show";
	String layout = request.getParameter("layout");
	if(layout == null)
		layout = "mainpage";
	String viewname = request.getParameter("viewname");
	if(viewname == null)
		viewname = "platform";
	String view = request.getParameter("views");
	if(view == null)
		view = "all";
	String width = request.getParameter("width");
	if(width == null)
		width = "m";
	String fineness = request.getParameter("fineness");
	if(fineness == null)
		fineness = "m1";
	SimpleDateFormat dateform1 = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm");
	String begindate = request.getParameter("begindate");//out.println(begindate);
	if(begindate == null  || begindate.equals(""))
		begindate = dateform1.format(admonitor.addDate(new Date(),-1));
	String enddate = request.getParameter("enddate");
	if(enddate == null  || enddate.equals(""))
		enddate = dateform1.format(new Date());
%>

<%
	int interval = 0;
	String suffix = null;
	Date date1 = new Date();
	SimpleDateFormat dateform = new SimpleDateFormat("yyyyMMdd");
	String datestr1 = dateform.format(date1);
	Date date2 = new Date();
	Calendar cal = Calendar.getInstance();
	cal.setTime(date1);
	if(width.equals("m"))
	{
		cal.add(Calendar.DATE,-1);
		date2 = cal.getTime();
		interval = 300;
		suffix = "day";
	}
	if(width.equals("w"))
	{
		cal.add(Calendar.DATE,-1);
		cal.set(Calendar.DAY_OF_WEEK,1);
		date2 = cal.getTime();
		interval = 3600;
		suffix = "week";
	}
	if(width.equals("M"))
	{
		cal.set(Calendar.DATE,1);
		cal.add(Calendar.DATE,-1);
		date2 = cal.getTime();
		interval = 86400;
		suffix = "month";
	}
	if(width.equals("y"))
	{
		cal.set(Calendar.DATE,1);
		cal.set(Calendar.MONTH,0);
		cal.add(Calendar.DATE,-1);
		date2 = cal.getTime();
		interval = 86400;
		suffix = "year";
	}
	Date bdate1 = new Date();
	Date bdate2 = new Date();
	if(width.equals("o"))
	{
		String s1[] = begindate.split("[T:-]");
		cal.set(Integer.parseInt(s1[0]),Integer.parseInt(s1[1])-1,Integer.parseInt(s1[2]));
		bdate1 = cal.getTime();
		String s2[] = enddate.split("[T:-]");
		cal.set(Integer.parseInt(s2[0]),Integer.parseInt(s2[1])-1,Integer.parseInt(s2[2]));
		bdate2 = cal.getTime();
		suffix = "time";
	}
	String datestr2 = dateform.format(date2);
	String filename1 = datestr1+"/" + module + fineness + ".txt";
	String filename2 = datestr2+"/" + module + fineness + ".txt";
	String data1 = "[]";
	String data2 = "[]";
	if(width.equals("o"))
	{
		data1 = admonitor.getDataJson(bdate1,bdate2,fineness,module);
	}
	else
	{
		String str = fineness.substring(1,fineness.length());
		//out.println(filename1);
		interval *= Integer.parseInt(str);
		data1 = admonitor.fileToJson(filename1);
		data2 = admonitor.fileToJson(filename2);
	}
%>


<form methord=post action="test10.jsp" name="form1" id="form1">
	<div id="test" style="display:">
	<select name="module" onchange="getKpiname()">
	</select>
	<select name="kpiname" onchange="getViewname()">
	</select>
	<select name="layout" id='layout'>
		<option value="more">more</option>
		<option value="mainpage">mainpage</option>
	</select>
	</div>

	<div id="div2" style="display:;background-color:CC9999">
	<div style='height:150;width:20%;background-color:CC9999;float:left'>视图<br>
	<select name="viewname" onchange="getDims()">
		<option value="total">total</option>
	</select></div>
	<div style='height:150;width:20%;background-color:CC9999;float:left'>维度<br>
	<select name="views">
		<option value="all">all</option>
	</select></div>
	<div style='height:150;width:20%;background-color:CC9999;float:left'>区间<br>
	<select name="width" id="width" onchange="getFineness()">
		<option value="m">a day</option>
		<option value="w">a week</option>
		<option value="M">a month</option>
		<option value="y">a year</option>
		<option value="o">coustomer</option>
	</select></div>
	<div style='height:150;width:20%;background-color:CC9999;float:left' id='date2'>
	<div id="date1">
	请输入开始日期：<br />
	<input name="begindate" type=datetime-local onchange="getFineness()"></input>
	<br />
	请输入结束日期：<br />
	<input name="enddate"  type=datetime-local onchange="getD()"></input>
	</div></div>
	<div style='height:150;width:20%;background-color:CC9999;float:left' id='fine'>粒度<br>
	<select name="fineness" id="fineness">
	</select></div>
	<br />
	<div style='width:80%;'>
	<input type=submit value="确认"></input>
	<br /></div>
	</div>
</form>
<div id="div0"></div>
<hr align="right"  color="white" width="79%" />
<div id="div3" style="display:">
	<h4>Total Data</h4>
</div>
<hr align="right" width="79%" color="white" />
<div id="graph" style="display:"></div>
<hr align="right" width="79%" color="white" />
<div id="chart" style="display:">
	<table border="1" id="table">
		<tr></tr>
	</table>
</div>
<div id=maingraph style="display:;width:80%;float:right;">
<iframe src=mainpage.jsp width=100% height=100%></iframe>
</div>

<script>
	var dataArray1 = new Array()
	var dataArray2 = new Array()
	var metaArray  = new Array()
	var totalArray = new Array()
	var ykeyArray  = new Array()
</script>

<script>
	metaArray = <%= admonitor.fileToJson("meta.conf") %>
	getMenu(metaArray,'div0')
	getModule()
	document.form1.module.value = "<%= module  %>"
	getKpiname()
	document.form1.kpiname.value = "<%= kpiname %>"
	getViewname()
	document.form1.viewname.value = "<%= viewname %>"
	getDims()
	document.form1.views.value = "<%= view %>"
	document.form1.width.value = "<%= width %>"
	document.form1.begindate.value = "<%= begindate %>"
	document.form1.enddate.value = "<%= enddate %>"
	getFineness()
	document.form1.fineness.value = "<%= fineness %>"
	var ulid = "<%= module %>" + 'ul'
	var ul = document.getElementById(ulid)
	ul.setAttribute('style','display:block;')
</script>

<script>
	var str1 = <%= data1 %>
	var str2 = <%= data2 %>
	var interval = <%= interval * 1000 %>
	var suffix = "<%= suffix %>"
	var mydata = new Array()
	var myykey = new Array()
	var total = new Object()
	getData()
	getTable("table",mydata)
</script>

<script>
	for (var v1 in total)
	{
		document.getElementById("div3").innerHTML += v1
		document.getElementById("div3").innerHTML += ":"+total[v1]+"<br>"
	}
</script>

<script>
	var colors = ['#000000','#C71585', '#800000', '#8B4513', '#006400', '#2F4F4F',  '#0000CD'];
	Morris.Line({
		element: 'graph',
  		data: mydata,
  		xkey: 'x',
  		ykeys:	myykey,
		labels: myykey,
  		lineWidth: 2,
  		pointSize: 0,
  		lineColors: colors,
  		pointFillColors: colors,
  		pointStrokeColors: colors,
   	});

</script>

<script>
	var layout = "<%= layout %>"
	setTimeout("setLayout(layout)",1)
</script>

<script>
/*function refresh(divid)
{
	var div = document.getElementById(divid)
	var v1  = document.getElementById('layout')
	if(v1.vaule == 'mainpage')
		div.location.reload()
}*/
setInterval("refresh('maingraph')",60000)
</script>
