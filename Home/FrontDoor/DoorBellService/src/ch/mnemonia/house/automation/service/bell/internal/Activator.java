package ch.mnemonia.house.automation.service.bell.internal;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;

import ch.mnemonia.house.automation.service.bell.DoorBellService;

public class Activator implements BundleActivator {

	public void start(BundleContext bundleContext) throws Exception {
		bundleContext.registerService(
				DoorBellService.class.getName(), 
				new DoorBellServiceImpl(), null);
		System.out.println("Hello BellService!!");
	}
	
	public void stop(BundleContext context) throws Exception {
		System.out.println("Goodbye BellService!!");
	}

}
