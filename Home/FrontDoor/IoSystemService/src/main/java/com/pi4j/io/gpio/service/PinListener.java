package com.pi4j.io.gpio.service;

import java.util.EventListener;

public interface PinListener extends EventListener {
	public void pinHigh();
	public void pinLow();
}
