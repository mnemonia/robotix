package ch.mnemonia.house.automation.service.bell.internal;

import org.osgi.service.log.LogService;

import ch.mnemonia.house.automation.service.bell.DoorBellService;

import com.mnemonia.io.Disposable;
import com.mnemonia.io.IoListener;
import com.mnemonia.io.IoSystemService;

public final class DoorBellServiceImpl implements DoorBellService, IoListener {
	private final LogService logService;
	private final IoSystemService ioSystemService;
	private Disposable listenerDisposable;
	private State currentState = Idle.INSTANCE;
	private SoundProvider soundProvider;

    public DoorBellServiceImpl(final IoSystemService ioSystemService, final SoundProvider soundProvider, final LogService logService){
    	this.ioSystemService = ioSystemService;
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

	@Override
	public void changed(boolean isHigh) {
		if(isHigh){
			logService.log(LogService.LOG_INFO, "isHigh");
			ring();
		}
	}

	@Override
	public void start() {
    	listenerDisposable = ioSystemService.addListener(1, this);
    	ring();
	}

	@Override
	public void stop() {
		listenerDisposable.dispose();
	}

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
}
