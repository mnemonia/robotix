package ch.mnemonia.house.automation.service.bell.internal;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;
import org.osgi.service.log.LogService;
import org.osgi.util.tracker.ServiceTracker;

import ch.mnemonia.house.automation.service.bell.DoorBellService;
import ch.mnemonia.service.time.TimeService;

public class Activator implements BundleActivator {

	private DoorBellServiceImpl doorBellService;
	private ServiceTracker<?, LogService> logServiceTracker;
	private ServiceTracker<?, TimeService> timeServiceTracker;
	private LogService logService;
	private TimeService timeService;

	public void start(BundleContext bundleContext) throws Exception {
	    // create a tracker and track the log service
	    logServiceTracker = new ServiceTracker(bundleContext, LogService.class.getName(), null);
	    logServiceTracker.open();

	    // grab the service
	    logService = logServiceTracker.getService();

	    if(logService != null){ 
	        System.out.println("There is a LogService available"); 
	        logService.log(LogService.LOG_INFO, "Yee ha, I'm logging!"); 
		} 
		else { 
		        System.out.println("Terminating the BellService since there is no LogService available"); 
		        return;
		}
	    
	    timeServiceTracker = new ServiceTracker(bundleContext, TimeService.class.getName(), null);
	    timeServiceTracker.open();

	    // grab the service
	    timeService = timeServiceTracker.getService();

	    if(timeService == null){ 
	        System.out.println("Terminating the BellService since there is no TimeService available"); 
	        return;
		}
	    
		logService.log(LogService.LOG_INFO, "Starting BellService ...");
		
		System.out.println("Starting BellService ...");
		SoundProvider soundProvider = new SoundProvider(timeService, logService);
		doorBellService = new DoorBellServiceImpl(soundProvider, logService);
		bundleContext.registerService(
				DoorBellService.class.getName(), 
				doorBellService, null);
		doorBellService.start();
//		ServiceReference<GpioService> serviceReference = bundleContext.getServiceReference(GpioService.class);
//		GpioService gpioService = bundleContext.getService(serviceReference);
////		gpioService.addPinListener(RaspiPin.GPIO_02, doorBellService);
//		final GpioPinDigitalOutput pin = gpioService.provisionDigitalOutputPin(RaspiPin.GPIO_01, "MyLED", PinState.HIGH);
////		pin.addListener(doorBellService);
		logService.log(LogService.LOG_INFO, "Starting BellService DONE");
	}
	
	public void stop(BundleContext bundleContext) throws Exception {
		doorBellService.stop();
//		ServiceReference<GpioService> serviceReference = bundleContext.getServiceReference(GpioService.class);
//		if(serviceReference!=null){
//			GpioService gpioService = bundleContext.getService(serviceReference);
//			if(gpioService!=null){
//				final GpioPinDigitalOutput pin = gpioService.provisionDigitalOutputPin(RaspiPin.GPIO_01, "MyLED", PinState.LOW);
//			}
//		}
		logService.log(LogService.LOG_INFO, "Goodbye BellService!!");
	}

}
