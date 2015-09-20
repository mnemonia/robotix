package ch.mnemonia.automation.home.door.service.bellknob;

import ch.mnemonia.house.automation.service.bell.DoorBellService;

import com.pi4j.io.gpio.service.GpioService;

public final class DoorBellKnobService {
	private volatile boolean isRunning = false;
	private final DoorBellService doorBellService;
	private final GpioService gpioService;

	public DoorBellKnobService(DoorBellService doorBellService, GpioService gpioService) {
		this.doorBellService = doorBellService;
		this.gpioService = gpioService;
	}

	public void start(){
		isRunning = true;
		new Thread(new Runnable() {
			
			@Override
			public void run() {
				while(isRunning){
					doorBellService.ring();
					try {
						Thread.sleep(20000);
					} catch (InterruptedException e) {;}
				}
			}
		}).start();
	}
	
	public void stop(){
		isRunning = false;
	}
}
