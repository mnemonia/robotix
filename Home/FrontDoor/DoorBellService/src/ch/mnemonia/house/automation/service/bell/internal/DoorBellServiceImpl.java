package ch.mnemonia.house.automation.service.bell.internal;

import ch.mnemonia.house.automation.service.bell.DoorBellService;

import com.pi4j.io.gpio.service.PinListener;

public final class DoorBellServiceImpl implements DoorBellService, PinListener {
    final SoundJLayer soundToPlay = new SoundJLayer("bubbling_water_1.mp3");

    public DoorBellServiceImpl(){
    	ring();
    }
    
	@Override
	public void ring() {
        soundToPlay.play();
	}
	
	public static void main(String[] args) {
		new DoorBellServiceImpl().ring();
	}

	@Override
	public void pinHigh() {
		ring();
	}

	@Override
	public void pinLow() {
	}

}
