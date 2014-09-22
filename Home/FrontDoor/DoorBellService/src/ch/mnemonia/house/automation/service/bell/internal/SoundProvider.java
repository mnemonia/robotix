package ch.mnemonia.house.automation.service.bell.internal;

import org.osgi.service.log.LogService;

import ch.mnemonia.service.time.TimeService;

public final class SoundProvider {
    private final SoundJLayer soundToPlay = new SoundJLayer("bubbling_water_1.mp3");
    private final SoundJLayer morningSoundToPlay = soundToPlay;    		
    private final SoundJLayer noonSoundToPlay = soundToPlay;    		
    private final SoundJLayer afternoonSoundToPlay = soundToPlay;    		
    private final SoundJLayer eveningSoundToPlay = new SoundJLayer("Pfiff01.mp3");;    		
    private final SoundJLayer nightSoundToPlay = soundToPlay;    		
	private final TimeService timeService;
	private final LogService logService;
	
    SoundProvider(TimeService timeService, LogService logService){
		this.timeService = timeService;
		this.logService = logService;
    }
    
    public Playable currentSoundToPlay() {
		if(timeService.isMorning()){
			logService.log(LogService.LOG_INFO, "Providing morning sound.");
			return  asPlayable(morningSoundToPlay);
		}else if(timeService.isNoon()){
			logService.log(LogService.LOG_INFO, "Providing noon sound.");
			return  asPlayable(noonSoundToPlay);
		}else if(timeService.isAfternoon()){
			logService.log(LogService.LOG_INFO, "Providing afternoon sound.");
			return  asPlayable(afternoonSoundToPlay);
		}else if(timeService.isEvening()){
			logService.log(LogService.LOG_INFO, "Providing evening sound.");
			return  asPlayable(eveningSoundToPlay);
		}else if(timeService.isNight()){
			logService.log(LogService.LOG_INFO, "Providing night sound.");
			return  asPlayable(nightSoundToPlay);
		}
		logService.log(LogService.LOG_INFO, "Providing default sound.");
		return asPlayable(soundToPlay);
	}

	private Playable asPlayable(final SoundJLayer soundToPlay) {
		return new Playable() {
			
			@Override
			public void play() {
				soundToPlay.play();
			}
		};
	}
}
