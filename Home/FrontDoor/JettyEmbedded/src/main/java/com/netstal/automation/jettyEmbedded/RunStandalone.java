package com.netstal.automation.jettyEmbedded;


public class RunStandalone implements Runnable {
	
	public static void main(String[] args) {
		new RunStandalone().run();
	}

	@Override
	public void run() {
		JettyServer server = JettyServerFactory.getJettyServer(80);
		//oder.. JettyServer server = new JettyServerImpl().init();
		
		Activator.addStandardServlets(server);
		
		try {
			server.start();
			server.getServer().join();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
