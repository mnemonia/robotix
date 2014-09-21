package ch.mnemonia.house.automation.service.bell.internal;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;
import org.osgi.framework.ServiceReference;

import ch.mnemonia.house.automation.service.bell.DoorBellService;

import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.PinState;
import com.pi4j.io.gpio.RaspiPin;
import com.pi4j.io.gpio.service.GpioService;

public class Activator implements BundleActivator {

	private DoorBellServiceImpl doorBellService;

	public void start(BundleContext bundleContext) throws Exception {
		System.out.println("Starting BellService ...");
		doorBellService = new DoorBellServiceImpl();
		bundleContext.registerService(
				DoorBellService.class.getName(), 
				doorBellService, null);
		System.out.println("Hello BellService!!");
		ServiceReference<GpioService> serviceReference = bundleContext.getServiceReference(GpioService.class);
		GpioService gpioService = bundleContext.getService(serviceReference);
//		gpioService.addPinListener(RaspiPin.GPIO_02, doorBellService);
		final GpioPinDigitalOutput pin = gpioService.provisionDigitalOutputPin(RaspiPin.GPIO_01, "MyLED", PinState.HIGH);
//		pin.addListener(doorBellService);
		System.out.println("Starting BellService DONE");
	}
	
	public void stop(BundleContext bundleContext) throws Exception {
		ServiceReference<GpioService> serviceReference = bundleContext.getServiceReference(GpioService.class);
		if(serviceReference!=null){
			GpioService gpioService = bundleContext.getService(serviceReference);
			if(gpioService!=null){
				final GpioPinDigitalOutput pin = gpioService.provisionDigitalOutputPin(RaspiPin.GPIO_01, "MyLED", PinState.LOW);
			}
		}
		System.out.println("Goodbye BellService!!");
	}

}
