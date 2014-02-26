package com.netstal.automation.jettyEmbedded;

import javax.servlet.Servlet;
import javax.servlet.ServletException;

import org.eclipse.jetty.server.Server;

public interface JettyServer {
	
	public abstract JettyServer init();
	
	public abstract JettyServer init(int port);

	public abstract JettyServer addServlet(String path, Class<? extends Servlet> servlet);

	public abstract JettyServer start() throws Exception;

	public abstract JettyServer stop() throws Exception;
	
	public abstract Server getServer();

	/**
	 * sample:
	 *   webPath = "/web"
	 *   resourcePath = "C:/java_ee_dev/ws/JettyEmbedded/web"  ("/" or "\")
	 *   stylesheet-locaton: resourcePath + ("/") + "jetty-dir.css"
	 * @throws ServletException 
 	 */
	public abstract JettyServer addResource(String webPath, String resourcePath, boolean showExplorePage);

}