package ch.mnemonia.house.automation.service.bell.internal;

import ch.mnemonia.house.automation.service.bell.DoorBellService;

public final class DoorBellServiceImpl implements DoorBellService {

	@Override
	public void ring() {
        SoundJLayer soundToPlay = new SoundJLayer("bubbling_water_1.mp3");
        soundToPlay.play();
	}
	
	public static void main(String[] args) {
		new DoorBellServiceImpl().ring();
	}

}
