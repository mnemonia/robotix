package com.netstal.automation.jettyEmbedded.internal;

import java.io.IOException;
import java.net.MalformedURLException;

import javax.servlet.Servlet;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.DefaultServlet;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import org.eclipse.jetty.util.resource.Resource;

import com.netstal.automation.jettyEmbedded.JettyServer;

public class JettyServerImpl implements JettyServer {

	private Server server;
    
	//private HandlerCollection  rootHandler;   //funktioniert für nur Servlets
	//private HandlerList  rootHandler;         //funktioniert für nur Servlets
	private ServletContextHandler rootHandler;
	
	public JettyServerImpl init() {
		return init(80);
	}
	
	public JettyServerImpl init(int port) {
		server = new Server(port);

		//bei nur servlets:
		//  servletHandler = new ServletHandler();
		//  server.setHandler(servletHandler);  
		
		rootHandler = new ServletContextHandler();
		rootHandler.setContextPath("/");
		server.setHandler(rootHandler);
				
	    return this;
	}
	
	@Override
	public JettyServerImpl addServlet(String path, Class<? extends Servlet> servlet) {	
	    //servletHandler.addServletWithMapping(servlet,  path);      //funktioniert für nur Servlets
	    
	    ServletHolder holderDynamic = new ServletHolder(path, servlet);
	    rootHandler.addServlet(holderDynamic, path);
	    
	    return this;
	}
	
	@Override
	public JettyServerImpl start() throws Exception {
		server.start();
		//System.out.println("started");
		//System.out.println(server.dump());
		return this;
	}
	
	@Override
	public JettyServerImpl stop() throws Exception {
		server.stop();
		return this;
	}

	@Override
	public Server getServer() {
		return server;
	}
	
	@Override
	public JettyServerImpl addResource(String webPath, String resourcePath, boolean showExplorePage) {
        ServletHolder servletRes = new ServletHolder(webPath, new DefaultServlet());  //name (webPath) eigentlich irgendwas.
        applySettings(servletRes, resourcePath, showExplorePage);
        rootHandler.addServlet(servletRes, addPathEnd(webPath));
		return this;
	}

	private void applySettings(ServletHolder servletRes, String resourcePath, boolean showExplorePage) {
		servletRes.setInitParameter("resourceBase", resourcePath);
        servletRes.setInitParameter("dirAllowed", formatBoolean(showExplorePage));
        servletRes.setInitParameter("pathInfoOnly","true");
        if (showExplorePage) {
        	setStylesheetCatchException(servletRes, resourcePath);
        }
	}
	
	private String formatBoolean(boolean b) {
		if (b) {
			return "true";
		}
		return "false";
	}

	private void setStylesheetCatchException(ServletHolder servletRes, String resourcePath) {
		try {
			setStylesheet(servletRes, resourcePath);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private void setStylesheet(ServletHolder servletRes, String resourcePath)
			throws MalformedURLException, IOException {
		String stylesheet = addSlash(resourcePath) + "jetty-dir.css";
		if (Resource.newResource(stylesheet).exists()) {
			servletRes.setInitParameter("stylesheet", stylesheet);
		}
	}
	
	private String addSlash(String path) {
		if (!path.endsWith("/")) {
			path = path + "/";
		}
        return path;
	}
	
	private String addPathEnd(String path) {
		if (path.endsWith("/")) {
        	path = path + "*";
        }
		if (!path.endsWith("/*")) {
        	path = path + "/*";
        }
		return path;
	}

}
