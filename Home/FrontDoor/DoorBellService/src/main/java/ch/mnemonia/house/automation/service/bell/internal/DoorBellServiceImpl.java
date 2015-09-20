package ch.mnemonia.house.automation.service.bell.internal;

import org.osgi.service.log.LogService;

import ch.mnemonia.house.automation.service.bell.DoorBellService;

public final class DoorBellServiceImpl implements DoorBellService {
	private final LogService logService;
	private State currentState = Idle.INSTANCE;
	private SoundProvider soundProvider;

    public DoorBellServiceImpl(final SoundProvider soundProvider, final LogService logService){
    	this.logService = logService;
    	this.soundProvider = soundProvider;
    }
    
	@Override
	public void ring() {
		if(currentState.isRunning()){
			return;
		}
		currentState = Ringing.INSTANCE;
		logService.log(LogService.LOG_INFO, "Ringing ...");
		soundProvider.currentSoundToPlay().play();
		logService.log(LogService.LOG_INFO, "Ringing DONE");
		currentState = Idle.INSTANCE;
	}

//	@Override
//	public void pinHigh() {
//		ring();
//	}
//
//	@Override
//	public void pinLow() {
//	}


	interface State{
		boolean isRunning();
	}
	static class Idle implements State{
		public static final State INSTANCE = new Idle();

		@Override
		public boolean isRunning() {
			return false;
		}
	}
	static class Ringing implements State{
		public static final State INSTANCE = new Ringing();

		@Override
		public boolean isRunning() {
			return true;
		}
	}
	@Override
	public void start() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void stop() {
		// TODO Auto-generated method stub
		
	}
}
