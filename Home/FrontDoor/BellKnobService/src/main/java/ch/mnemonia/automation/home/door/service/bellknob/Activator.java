package ch.mnemonia.automation.home.door.service.bellknob;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;
import org.osgi.framework.ServiceReference;

import com.pi4j.io.gpio.service.GpioService;

import ch.mnemonia.house.automation.service.bell.DoorBellService;

public class Activator implements BundleActivator {

	private BellKnobListener knobListener;
	private DoorBellKnobService doorBellKnobService;	

	/*
	 * (non-Javadoc)
	 * @see org.osgi.framework.BundleActivator#start(org.osgi.framework.BundleContext)
	 */
	public void start(BundleContext bundleContext) throws Exception {
		System.out.print("Starting BellKnobListener ...");
		startBellKnobListener(bundleContext);
		
		startDoorBellKnobService(bundleContext);
	}

	private void startDoorBellKnobService(BundleContext bundleContext) {
		ServiceReference<DoorBellService> doorBellServiceReference = bundleContext.getServiceReference(DoorBellService.class);
		if(doorBellServiceReference==null){
			System.out.println("failed. No DoorBellService service available.");
			return;
		}
		
		ServiceReference<GpioService> gpioServiceReference = bundleContext.getServiceReference(GpioService.class);
		if(gpioServiceReference==null){
			System.out.println("failed. No GpioService available.");
			return;
		}

		doorBellKnobService = new DoorBellKnobService(
				bundleContext.getService(doorBellServiceReference),
				bundleContext.getService(gpioServiceReference));
		doorBellKnobService.start();
	}

	private void startBellKnobListener(BundleContext bundleContext) {
//		ServiceReference<EventAdmin> serviceReference = bundleContext.getServiceReference(EventAdmin.class);
//		if(serviceReference==null){
//			System.out.println("failed. No EventAdmin service available.");
//			return;
//		}
//		
//		EventAdmin eventAdmin = bundleContext.getService(serviceReference);
//		knobListener = new BellKnobListener(eventAdmin);
//		knobListener.start();
	}

	/*
	 * (non-Javadoc)
	 * @see org.osgi.framework.BundleActivator#stop(org.osgi.framework.BundleContext)
	 */
	public void stop(BundleContext bundleContext) throws Exception {
//		knobListener.stop();
		doorBellKnobService.stop();
	}

}
