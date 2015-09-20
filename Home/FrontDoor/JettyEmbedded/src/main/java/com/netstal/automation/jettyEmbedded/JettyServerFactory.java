package com.netstal.automation.jettyEmbedded;

import com.netstal.automation.jettyEmbedded.internal.JettyServerImpl;

public class JettyServerFactory {

	public static JettyServer getJettyServer() {
		return new JettyServerImpl().init();
	}
	
	public static JettyServer getJettyServer(int port) {
		return new JettyServerImpl().init(port);
	}
	
}
