package ch.mnemonia.service.time;

import java.util.Date;

public interface TimeService {
	Date getCurrentDate();
	boolean isMorning();
	boolean isNoon();
	boolean isAfternoon();
	boolean isEvening();
	boolean isNight();
}
