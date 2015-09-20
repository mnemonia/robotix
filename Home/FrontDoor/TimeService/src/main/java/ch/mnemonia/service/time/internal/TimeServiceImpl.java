package ch.mnemonia.service.time.internal;

import java.util.Calendar;
import java.util.Date;

import ch.mnemonia.service.time.TimeService;

public final class TimeServiceImpl implements TimeService {

	public Date getCurrentDate() {
		return new Date();
	}

	public boolean isMorning() {
		return getHourOfTheDay() >= 8 && getHourOfTheDay() < 12;
	}

	private int getHourOfTheDay() {
		return Calendar.getInstance().get(Calendar.HOUR_OF_DAY);
	}

	public boolean isNoon() {
		return getHourOfTheDay() >= 12 && getHourOfTheDay() < 13;
	}

	public boolean isAfternoon() {
		return getHourOfTheDay() >= 13 && getHourOfTheDay() < 18;
	}

	public boolean isEvening() {
		return getHourOfTheDay() >= 18 && getHourOfTheDay() < 20;
	}

	public boolean isNight() {
		return (getHourOfTheDay() >= 20 && getHourOfTheDay() <= 24) &&
				(getHourOfTheDay() >= 1 && getHourOfTheDay() < 8);
	}


}
