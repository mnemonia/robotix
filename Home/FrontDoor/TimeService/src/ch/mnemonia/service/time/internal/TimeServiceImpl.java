package ch.mnemonia.service.time.internal;

import java.util.Calendar;
import java.util.Date;

import ch.mnemonia.service.time.TimeService;

public final class TimeServiceImpl implements TimeService {

	@Override
	public Date getCurrentDate() {
		return new Date();
	}

	@Override
	public boolean isMorning() {
		return getHourOfTheDay() >= 8 && getHourOfTheDay() < 12;
	}

	private int getHourOfTheDay() {
		return Calendar.getInstance().get(Calendar.HOUR_OF_DAY);
	}

	@Override
	public boolean isNoon() {
		return getHourOfTheDay() >= 12 && getHourOfTheDay() < 13;
	}

	@Override
	public boolean isAfternoon() {
		return getHourOfTheDay() >= 13 && getHourOfTheDay() < 18;
	}

	@Override
	public boolean isEvening() {
		return getHourOfTheDay() >= 18 && getHourOfTheDay() < 20;
	}

	@Override
	public boolean isNight() {
		return (getHourOfTheDay() >= 20 && getHourOfTheDay() <= 24) &&
				(getHourOfTheDay() >= 1 && getHourOfTheDay() < 8);
	}

}
