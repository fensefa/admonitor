function getModule()
{
	var v1 = document.form1.module
	for(i = 0;i<butt.length;i++)
	{
		v1[i] = new Option(butt[i]["modulename"],butt[i]["modulename"])
	}
}

function setModule(moduleValue)
{
	var v1 = document.form1.module
	v1.value = moduleValue
	getKpiname()
}

function getKpiname()
{
	var v1 = document.form1.kpiname
	var i = 0
	var k = document.form1.module.selectedIndex
	var button = butt[k]["kpis"]
	for(var1 in button)
	{
		var var2 = button[var1]
		v1[i] = new Option(var2["kpi_name"],var2["kpi_name"])
		i++
	}
	v1.length = i

	getViewname()
}

function setKpiname(module,kpi)
{
	setModule(module)
	var v2 = document.form1.kpiname
	v2.value = kpi
	getViewname()
}

function getViewname()
{
	var v1 = document.form1.viewname
	var v2 = document.form1.kpiname
	var j  = v2.selectedIndex
	var k  = document.form1.module.selectedIndex
	var button = butt[k]["kpis"][j]["views"]
	var i = 0
	for(var1 in button)
	{
		var var2 = button[var1]
		v1[i] = new Option(var2["view_name"],var2["view_name"])
		i++
	}
	v1[i] = new Option("total(average)","total")
	v1.value = "total"
	i++
	v1.length = i
	getViews()
}

function getViews()
{
	var v1 = document.form1.views
	var v2 = document.form1.kpiname
	var v3 = document.form1.viewname
	var j  = v2.selectedIndex
var k  = v3.selectedIndex
	var m  = document.form1.module.selectedIndex
	if( k == v3.length - 1)
	{
		v1.length = 1
		return
	}
	var button = butt[m]["kpis"][j]["views"][k]["dims"]
	var i = 1
	for(var1 in button)
	{
		v1[i] = new Option(var1,var1)
		i++
	}
	v1.length = i
}

function getFineness()
{
	var optionData = new Array()
	optionData[0] = {"one minute":"m0","five minutes":"m1","ten minutes":"m2","thirty minute":"m6","one hour":"m12"}
	optionData[1] = {"one hour":"w1","two hour":"w2","six hour":"w6","tweleve hour":"w12"}
	optionData[2] = {"one day":"M1"}
	optionData[3] = {"one day":"y1"}
	optionData[4] = {"five minutes":"m1","ten minutes":"m2","thirty minute":"m6","one hour":"m12"}
	optionData[5] = {"one hour":"h1","two hour":"h2","six hour":"h6","tweleve hour":"h12"}
	optionData[6] = {"one day":"d1"}
	setOptions('fineness',0,optionData)
	//return
	var v1 = document.getElementById('width')
	var v3 = v1.selectedIndex
	var v4 = document.getElementById("date2")
	var v5 = document.getElementById('fine')
	if(v3 < 4)
	{
		setOptions('fineness',v3,optionData)
		v4.style.display = 'none'
		v5.style.float = 'left'
	}
	else
	{
		var d1 = new Date(document.form1.begindate.value)
		var d2 = new Date(document.form1.enddate.value)
		if(d1 == null || d1 == null)
			alert("日期不合法，请重新输入!")
		var interval = d2.getTime() - d1.getTime()
		interval /= 24*3600*1000
		if(interval < 2)
			setOptions('fineness',4,optionData)
		else if(interval < 7)
			setOptions('fineness',5,optionData)
		else
			setOptions('fineness',6,optionData)
		v5.style.float = 'right'
		v4.style.display = 'block'
	}
}

//optionData must be an Array of object
function setOptions(selectId,optionType,optionData)
{
	var v1 = document.getElementById(selectId)
	v1.length = 0
	var v2 = optionData[optionType]
	for(var v3 in v2)
		v1.appendChild(new Option(v3,v2[v3]))
}


function getKpiValue(jsvl,a,b,c,d)
{
	if(d == "total")
		return getJsonValue(jsvl,a,"kpi_total")
	else
		return getJsonValue(jsvl,a,"views",b,"dims",c)
}

//function getdims is not used anymore
function getdims(sstr,a,b)
{
	if(sstr == null)
		return null
	if(sstr[a] == null)
		return null
	if(sstr[a]["views"][b] == null)
		return null
	return sstr[a]["views"][b]["dims"]
}

function getJsonValue()
{
	var jsvl = arguments[0]
	for(var i=1;i<arguments.length;i++)
	{
		if(jsvl == null)
			return null
		jsvl = jsvl[arguments[i]]
	}
	return jsvl
}

//function getTable is used to generate an html table element from dataArray.
//dataArray must bu an array of object
//divId is the id of the div where you want to get the table
function getTable(divId,dataArray)
{
   var v1 = document.getElementById(divId)
   var r = v1.insertRow(1)
   var k = 0 
   for(var v2 in dataArray[0])
   {   
      var v3 = r.insertCell(k)
      if(v2 == "x")
         v2 = "time"
      v3.innerHTML = v2 
      k++ 
   }   
   for(var i=0;i<dataArray.length;i++)
   {
      var r = v1.insertRow(v1.rows.length)
      var k = 0
      for(var v2 in dataArray[0])
      {
         var v3 = r.insertCell(k)
         if(v2 == "x")
         {
            var date = new Date(dataArray[i][v2])
            v3.innerHTML = date.toLocaleString()
         }
         else
         {
            var x = dataArray[i][v2]
            if(x == undefined)
               x = "-"
            v3.innerHTML = x
         }
         k++
      }
   }
}

function getData()
{
   var a = document.form1.kpiname.selectedIndex
   var b = document.form1.viewname.selectedIndex
   var d = document.form1.viewname.value
   var c = document.form1.views.value
	var total2 = new Array()
   if(d != "total" && c == "all")
   {
      for(i = 1;i<document.form1.views.length;i++)
      {
         myykey[i-1] = document.form1.views[i].text
         total[myykey[i-1]] = 0
      }
   }
   else
   {
      myykey[0] = "this " + suffix
      myykey[1] = "last " + suffix
      total[myykey[0]] = 0
      total[myykey[1]] = 0
   }
   var i = 0
	if(document.form1.width.value == "o")
	{
		var date1 = new Date(document.form1.begindate.value)
		var datemills1 = date1.getTime() - 3600 * 8 * 1000
		var date2 = new Date(document.form1.enddate.value)
		var datemills2 = date2.getTime() - 3600 * 8 * 1000
		var str3 = new Array()
		for(var j=0,k=0;k<str1.length;k++)
		{
			var time = str1[k]["time"] * 1000
			if(time >= datemills1 && time <= datemills2){
			str3[j] = str1[k]
			j++;}
		}
		str1 = str3
	}
   for(var i=0;i<str1.length;i++)
   {
		var date1 = new Date(str1[i]["time"] * 1000)
		var date2 = new Date(document.form1.begindate.value)
      mydata[i] = new Object()
      mydata[i].x = str1[i]["time"] * 1000
      kpis1 = str1[i]["kpis"]
      var dims = new Object()
      for(s=1;s<document.form1.views.length;s++)
         dims[document.form1.views[s].text] = 0
      if(d != "total" && c == "all")
      {
         for(view1 in dims)
         {
            mydata[i][view1] = getKpiValue(kpis1,a,b,view1,d)
            total[view1] = total[view1] + mydata[i][view1]
				total2[view1] = mydata[i][view1]
         }
      }
      else
      {
         mydata[i][myykey[0]] = getKpiValue(kpis1,a,b,c,d)
         total[myykey[0]] = total[myykey[0]] + mydata[i][myykey[0]]
			total2[myykey[0]] = mydata[i][myykey[0]]
      }
   }
   if(d == "total" || c != "all")
   for(var i=0;i<str2.length;i++)
   {
		if(mydata[i] == null){
      mydata[i] = new Object()
      mydata[i].x = mydata[i-1].x + interval}
      kpis2 = str2[i]["kpis"]
      var dims = getdims(kpis2,a,b)
      mydata[i][myykey[1]] = getKpiValue(kpis2,a,b,c,d)
         total[myykey[1]] = total[myykey[1]] + mydata[i][myykey[1]]
			total2[myykey[1]] = mydata[i][myykey[1]]
   }
	if(getJsonValue(str1,0,"kpis",a,"kpi_op") != null)
	{
      total = total2;
	}
}

function getObject(objectId) {
	if(document.getElementById && document.getElementById(objectId)) {
		return document.getElementById(objectId);
	}
	else if (document.all && document.all(objectId)) {   
		return document.all(objectId);   
	}   
	else if (document.layers && document.layers[objectId]) {   
		return document.layers[objectId];   
	}   
	else {   
		return false;   
	}   
}
   
function showHide(e,objname){    
	var obj = getObject(objname);   
	if(obj.style.display == "none"){   
		obj.style.display = "block";   
		e.className="xias";   
	}
	else{   
		obj.style.display = "none";   
		e.className="rights";   
	}   
}

function setLayout(var1)
{
	var a = document.getElementById('default')
	a.innerHTML = var1
	changeLayout()
}

function changeLayout()
{
	var divs = ['div2','div3','graph','chart','maingraph']
	var a      = document.getElementById('default')
	var layout = document.form1.layout
	if(a.innerHTML == "mainpage")
	{
		for(var i=0;i<divs.length-1;i++)
			document.getElementById(divs[i]).style.display = "none"
		document.getElementById(divs[divs.length-1]).style.display = "block"
		a.innerHTML = "more"
		layout.value = "mainpage"
	}
	else
	{
		for(var i=0;i<divs.length-1;i++)
			document.getElementById(divs[i]).style.display = "block"
		document.getElementById(divs[divs.length-1]).style.display = "none"
		a.innerHTML = "mainpage"
		layout.value = "more"
	}
	$(function(){
		var count;
		var v1 = document.getElementById('maingraph');
		if(v1.style.display == "none")
   		count=$("#chart").height()+730;
		else
			count=$("#maingraph").height();
   	$("#div0").height(count);
	});
}

function getMenu(metaArray,divId)
{
   var v1 = document.getElementById(divId)
   var ul = document.createElement('ul')
	var li = document.createElement('li')
	var a = document.createElement('a')
	a.setAttribute('href','#')
	a.setAttribute('onclick','changeLayout()')
	a.innerHTML = "more"
	a.id = "default"
	li.appendChild(a)
	ul.appendChild(li)
	br = document.createElement('br')
	ul.appendChild(br)
   for(i = 0;i<butt.length;i++)
   {
      var module = metaArray[i]["modulename"]
      var module1 = module+"1"
      var li = document.createElement('li');
      var a = document.createElement('a');
      a.setAttribute('href','#');
      a.setAttribute('onclick',"showHide(this,this.modulename+'ul');setModule(this.modulename)")
      a.modulename = module
      a.innerHTML = module
      li.appendChild(a);
      var ul2 = getSubMenu(metaArray,module,i)
      ul2.id = module+'ul'
      ul2.setAttribute('style','display:none;')
      li.appendChild(ul2)
      ul.appendChild(li)
   }
   v1.appendChild(ul)
}

function getSubMenu(metaArray,module,i)
{
   var v1 = document.getElementById(module)
   var ul = document.createElement('ul')
   var button = metaArray[i]["kpis"]
   for(var1 in button)
   {
      var kpi = button[var1]["kpi_name"]
      var li = document.createElement('li');
      var a = document.createElement('a');
      a.setAttribute('href','#');
      a.setAttribute('onclick',"setLayout('more');setKpiname(this.module,this.id);formSubmit('form1')")
      a.id = kpi
		a.module = module
      a.innerHTML = kpi
      li.appendChild(a);
      ul.appendChild(li);
   }
   return ul
}

function formSubmit(formId)
{
	var form = document.getElementById(formId)
	form.submit()
}

