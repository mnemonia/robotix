package com.netstal.automation.jettyEmbedded;

import org.osgi.framework.BundleActivator;

import org.osgi.framework.BundleContext;
import org.osgi.framework.ServiceReference;

import com.netstal.automation.jettyEmbedded.demoServlets.TestServlet;
import com.netstal.automation.jettyEmbedded.demoServlets.TestServlet2;
import com.netstal.automation.jettyEmbedded.demoServlets.WebsocketEchoServlet;
import com.netstal.automation.jettyEmbedded.demoServlets.WebsocketEchoServlet2;

public class Activator implements BundleActivator {
	
	public static final int port = 80;
	
	private JettyServer server;

	public void start(BundleContext context) throws Exception {	
		server = JettyServerFactory.getJettyServer(port).start();
		registerJettyServerService(context, server);
		System.out.println(context.getBundle().getSymbolicName() + ": start");
		
		addStandardServlets(server);
	}

	public void stop(BundleContext context) throws Exception {
		server.stop();
		unregisterJettyServerService(context);
		System.out.println(context.getBundle().getSymbolicName() + ": stop");	
	}
	
	private void registerJettyServerService(BundleContext context, JettyServer service) throws Exception {
		context.registerService(JettyServer.class.getName(), service, null);
	}

	private void unregisterJettyServerService(BundleContext context) {
		ServiceReference<?> reference = context.getServiceReference(JettyServer.class.getName());
		//JettyServer server = (JettyServer)context.getService(reference);
		context.ungetService(reference);		
	}
	
	public static void addStandardServlets(JettyServer server) {
		server.addServlet("/test", TestServlet.class)
              .addServlet("/test2", TestServlet2.class)
              .addServlet("/ws", WebsocketEchoServlet.class)
              .addServlet("/ws2", WebsocketEchoServlet2.class)
	          .addResource("/web", System.getProperty("user.dir") + "/webContent", true);
	}
}
