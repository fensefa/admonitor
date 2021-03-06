package admonitorHttp;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.AbstractHandler;

import com.autohome.admonitor.AdMonitor;
import com.autohome.admonitor.AdMonitor.E_STATUS;

public class admonitorHttp extends AbstractHandler {
	private Map<String, AdMonitor> monitors = new HashMap<String, AdMonitor>(); 
	
	public E_STATUS reLoad(){
		AdMonitor.E_STATUS e_status=AdMonitor.E_STATUS.D_RETURN_SUCCESS;
			e_status=AdMonitor.init("/home/public/admonitorloghttp/", monitors);
			/*System.out.println(monitors.keySet().toString());
			   System.out.println(monitors.size());
				System.out.println(monitors.containsKey("lop2"));
				System.out.println(e_status);*/
			
	return e_status;
}

	public void handle(String target, Request baseRequest,
			HttpServletRequest request, HttpServletResponse response)
			throws IOException, ServletException {
		
		
		
		response.setContentType("text/html;charset=utf-8");
		response.setStatus(HttpServletResponse.SC_OK);
		baseRequest.setHandled(true);

		//record log
		Map map = request.getParameterMap();
		//recond log
		String service_name = request.getParameter("service_name");
	

		AdMonitor.E_STATUS e_status=AdMonitor.E_STATUS.D_RETURN_SUCCESS;
		if (service_name == null || service_name.length() == 0) {
			response.getWriter().println("{\"status\":-1, \"errmsg\":\"service_name not exist\"}");
			
			return;
		}
		
		String cmd = request.getParameter("cmd");
		if (cmd == null) {
			response.getWriter().println("{\"status\":-1, \"errmsg\":\"cmd must be set\"}");
			//AdMonitor.confLog4j();
			return;
		}
		else if (cmd.equals("init")) {
			int interval = 0;
			String interval_str = request.getParameter("interval");
			if (interval_str == null || interval_str.length() == 0) {
				interval = 300;
			} else {
				try {
					interval = Integer.parseInt(interval_str);
				} catch (NumberFormatException e) {
					response.getWriter().println("{\"status\":-1, \"errmsg\":\"interval not valid: " + interval_str+"\"}");
					return;	
				}
				
			}
		AdMonitor monitor = new AdMonitor();
			if (monitors.get(service_name) == null) {
				e_status = monitor.init(service_name, interval, false, 0, "/home/public/admonitorloghttp/");
				if(e_status == E_STATUS.D_RETURN_SUCCESS)
					monitors.put(service_name, monitor);
			} else {
				response.getWriter().println("{\"status\":-1, \"errmsg\":\"srvice_name("+service_name+") already exists!	\"}");
				return;
			}
		} else if(cmd.equals("register_kpi")) {
			String kpi_name = request.getParameter("kpi_name");
			if (kpi_name == null || kpi_name.length() == 0) {
				response.getWriter().println("{\"status\":-1, \"errmsg\":\"kpi_name must be set\"}");
				return;
			}
			String view_names = request.getParameter("view_names");
			if (view_names == null || view_names.length() == 0) {
				response.getWriter().println("{\"status\":-1, \"errmsg\":\"view_names must be set\"}");
				return;
			}
			AdMonitor monitor = monitors.get(service_name);
			if(monitor == null)
			{
				response.getWriter().println("{\"status\":-1, \"errmsg\":\"servicename not exist!\"}");
				return;
				}
			else
			{
				//response.getWriter().println("{\"status\":0, \"errmsg\":\"servicenamegdfg not exist!\"}");
				e_status=monitor.registerKPI(kpi_name, view_names);
			}
				//response.getWriter().println("{\"status\":0, \"errmsg\":\"regiester success\"}");
			
			
			
			
		}/*else if(cmd.equals("composite")){
			String kpi_name = request.getParameter("kpi_name");
			String view_names=request.getParameter("view_names");
			String op_rule = request.getParameter("op_rule");
			String service_name_l=request.getParameter("service_name_l");
			String kpi_name_l=request.getParameter("");
			
			
		} */
		
		
		else if (cmd.equals("increase")) {
			String kpi_name = request.getParameter("kpi_name");
			if (kpi_name == null || kpi_name.length() == 0) {
				response.getWriter().println("{\"status\":-1, \"errmsg\":\"kpi_name must be set\"}");
				return;
			}
			String views = request.getParameter("views");
			if (views == null || views.length() == 0) {
				response.getWriter().println("{\"status\":-1, \"errmsg\":\"views must be set\"}");
				return;
			}
			/*String dim_name=request.getParameter("dim_name");
			if(dim_name==null || dim_name.length()==0){
				response.getWriter().println("{\"status\":-1, \"errmsg\":\"dim_name must be set\"}");
				return;
				
			}*/
			
			int increment = 1;
			String increment_str = request.getParameter("increment");
			if (increment_str == null || increment_str.length() == 0) {
				increment = 300;
			} else {
				try {
					increment = Integer.parseInt(increment_str);
				} catch (NumberFormatException e) {
					response.getWriter().println("{\"status\":-1, \"errmsg\":\"increment not valid: " + increment_str+"\"}");
					return;	
				}
			}
			AdMonitor monitor = monitors.get(service_name);
			if(monitor == null)
			{
				response.getWriter().println("{\"status\":0, \"errmsg\":\"servicename not exist!\"}");
				return;
				}
			else{
				//response.getWriter().println("{\"status\":0, \"errmsg\":\"abcd\"}");
			e_status=monitor.increase(kpi_name, views, increment);
			
			}
		}else if(cmd.equals("composite"))
		{
			String kpi_name=request.getParameter("kpi_name");
			if(kpi_name==null || kpi_name.length()==0){
				
				response.getWriter().println("{\"status\":-1,\"errmsg\":\"kpi_name not exist!\"}");
				return;
			}
			String op_rule=request.getParameter("op_rule");
			if(op_rule==null || op_rule.length()==0){
				response.getWriter().println("{\"status\":-1,\"errmsg\":\"op_rule not exite!\"}");
				return;
			}
			String param=request.getParameter("param");
			if(param==null || param.length()==0){
				response.getWriter().println("{\"status\":-1,\"errmsg\":\"param not exite!\"}");
				return;
				
			}
			AdMonitor monitor = monitors.get(service_name);
			
			if(monitor==null){
				response.getWriter().println("{\"status\":-1,\"errmsg\":\"services_name not exite!\"}");
			}else {
				e_status=AdMonitor.registerCompositeKPI("/home/public/admonitorloghttp/", service_name, kpi_name, op_rule, param);
			}
			
		}
		else {
			
			response.getWriter().println("{\"status\":-1, \"errmsg\":\"init is not right\"}");
		}
		
		switch(e_status)
		{
		case D_RETURN_SUCCESS:
		response.getWriter().println("{\"status\":0, \"errmsg\":\"D_RETURN_SUCCESS\"}");
		break;
		case D_TIME_INTERVAL_ILLEAGAL:
			response.getWriter().println("{\"status\":-1, \"errmsg\":\"D_TIME_INTERVAL_ILLEAGAL\"}");
		break;
		case D_CREATE_FILE_ERROR:
			response.getWriter().println("{\"status\":-1, \"errmsg\":\"D_CREATE_FILE_ERROR\"}");
			break;
		case D_WRITE_FILE_ERROR:
			response.getWriter().println("{\"status\":-1, \"errmsg\":\"D_WRITE_FILE_ERROR\"}");
			break;
		case D_REGISTER_KPI_ERROR:
			response.getWriter().println("{\"status\":-1, \"errmsg\":\"D_REGISTER_KPI_ERROR\"}");
			break;
		case D_VIEW_NAME_NONEXISTENCE:
			response.getWriter().println("{\"status\":-1, \"errmsg\":\"D_VIEW_NAME_NONEXISTENCE\"}");
			break;
		case D_VIEW_COUNT_NOT_EQ_ONE:
			response.getWriter().println("{\"status\":-1, \"errmsg\":\"D_VIEW_COUNT_NOT_EQ_ONE\"}");
			break;
		case D_STRING_PARSE_ERROR:
			response.getWriter().println("{\"status\":-1, \"errmsg\":\"D_STRING_PARSE_ERROR\"}");
			break;
		case D_THREAD_SLEEP_ERROR:
			response.getWriter().println("{\"status\":-1, \"errmsg\":\"D_THREAD_SLEEP_ERROR\"}");
			break;
		default:
			response.getWriter().println(e_status);
		}
	}

	public static void main(String[] args) throws Exception {
		Server server = new Server(8691);
		        //AdMonitor monitor = new AdMonitor();
				//monitor.init("/home/xujiaxing/torrs", monitors);
				
			    admonitorHttp admonitor = new admonitorHttp();

			    AdMonitor.configLog4j("/home/public/admonitorlog4j/admonitorj.log4j.conf");
			    admonitor.reLoad();
		
		server.setHandler(admonitor);
		server.start();
		server.join();
	}


}
