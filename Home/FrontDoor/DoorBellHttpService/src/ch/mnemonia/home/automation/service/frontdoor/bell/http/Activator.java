package ch.mnemonia.home.automation.service.frontdoor.bell.http;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;
import org.osgi.framework.FrameworkUtil;
import org.osgi.framework.ServiceReference;

import com.netstal.automation.jettyEmbedded.JettyServer;

public class Activator implements BundleActivator {

	public void start(BundleContext context) throws Exception {
		JettyServer jetty = lookupJettyEmbedded();
		jetty.addServlet("/bell", HttpDoorBellService.class);
//		jetty.addResource(webPath, resourcePath, showExplorePage)
		System.out.println("Hello Bell Http Service!!");
	}
	
	public void stop(BundleContext context) throws Exception {
		System.out.println("Goodbye Bell Http Service!!");
	}
	
	private JettyServer lookupJettyEmbedded() {
		BundleContext bundleContext = FrameworkUtil.getBundle(this.getClass()).getBundleContext();		
		ServiceReference<?> serviceReference = bundleContext.getServiceReference(JettyServer.class.getName());
		return (JettyServer) bundleContext.getService(serviceReference);
	}
}
