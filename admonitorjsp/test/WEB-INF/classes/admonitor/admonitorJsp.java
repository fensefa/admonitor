package admonitor;

import java.io.*;
import java.util.*;
import java.*;
import java.math.*;
import java.text.*;

public class admonitorJsp {
	public String fileToString(String filename) {

		String str = "";
		//System.out.println("filename" + filename);

		try {
			//String path = request.getRealPath("/");
			//File fp = new File("/data0/1.txt");
			File fp=new File(_path+filename);//System.out.println("/data0/myfiles/"+filename);
			FileReader freader=new FileReader(fp);
			BufferedReader bfdreader=new BufferedReader(freader);
			String str_line=bfdreader.readLine();
			//System.out.println("str=" + str_line);
			while(str_line!=null) {
				str += str_line;
				str += ",";
				str_line=bfdreader.readLine();
			}
			bfdreader.close();
			freader.close();
		}
		catch(IOException e) { System.out.println("wrong");
		}

		return str;
	}

	public Date addDate(Date date, int offect) {
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		cal.add(Calendar.DATE, offect);
		return cal.getTime();
	}
	
	public String fileToJson(String filename) {
		String str = "[";
		str += fileToString(filename);
		str += "]";
		return str;
	}

	public String getDataJson(Date begindate,Date enddate,String fineness,String module)
	{
		SimpleDateFormat dateform = new SimpleDateFormat("yyyyMMdd");
		String filename = null;
		String ret = "[";
		enddate = addDate(enddate,1);
		System.out.println("begindate" + begindate);
		System.out.println("enddate" + enddate);
		while(begindate.before(enddate))
		{
			String path =dateform.format(begindate);
			filename = path + "/" + module + fineness + ".txt";
			ret += fileToString(filename);
			begindate = addDate(begindate,1);
		}
		ret += "]";
		return ret;
	}
	
	public void setFilePath(String path)
	{
		_path = path;
	}

	private String _path;
}
