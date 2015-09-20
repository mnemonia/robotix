package com.mnemonia.io.internal;

import com.mnemonia.io.Disposable;
import com.mnemonia.io.IoListener;
import com.mnemonia.io.IoSystemService;
import com.pi4j.io.gpio.GpioPinDigitalInput;
import com.pi4j.io.gpio.Pin;
import com.pi4j.io.gpio.PinPullResistance;
import com.pi4j.io.gpio.RaspiPin;
import com.pi4j.io.gpio.event.GpioPinDigitalStateChangeEvent;
import com.pi4j.io.gpio.event.GpioPinListenerDigital;
import com.pi4j.io.gpio.service.GpioService;

public final class IoSystemServiceImpl implements IoSystemService {
	private final GpioService gpioService;
	
	public IoSystemServiceImpl(final GpioService gpioService){
		this.gpioService = gpioService;
	}
	
	@Override
	public Disposable addListener(int pin, final IoListener listener) {
        final GpioPinDigitalInput myButton = gpioService.provisionDigitalInputPin(
        		lookup(pin), 
        		PinPullResistance.PULL_DOWN);
        final GpioPinListenerDigital newListener = new GpioPinListenerDigital(){

			@Override
			public void handleGpioPinDigitalStateChangeEvent(GpioPinDigitalStateChangeEvent event) {
				listener.changed(event.getState().isHigh());
			}};
			
        myButton.addListener(newListener);
		return new Disposable() {
			
			@Override
			public void dispose() {
				myButton.removeListener(newListener);
			}
		};
	}

	Pin lookup(int pin){
		switch(pin){
			case 0: return RaspiPin.GPIO_00;
			case 1: return RaspiPin.GPIO_01;
			case 2: return RaspiPin.GPIO_02;
			case 3: return RaspiPin.GPIO_03;
			case 4: return RaspiPin.GPIO_04;
			case 5: return RaspiPin.GPIO_05;
			case 6: return RaspiPin.GPIO_06;
			case 7: return RaspiPin.GPIO_07;
			case 8: return RaspiPin.GPIO_08;
			case 9: return RaspiPin.GPIO_09;
			case 10: return RaspiPin.GPIO_10;
			case 11: return RaspiPin.GPIO_11;
			case 12: return RaspiPin.GPIO_12;
			case 13: return RaspiPin.GPIO_13;
			case 14: return RaspiPin.GPIO_14;
			case 15: return RaspiPin.GPIO_15;
			case 16: return RaspiPin.GPIO_16;
			case 17: return RaspiPin.GPIO_17;
			case 18: return RaspiPin.GPIO_18;
			case 19: return RaspiPin.GPIO_19;
			case 20: return RaspiPin.GPIO_20;
			default:
				throw new RuntimeException("Unknown pin "+pin);
		}
		
	}
}
