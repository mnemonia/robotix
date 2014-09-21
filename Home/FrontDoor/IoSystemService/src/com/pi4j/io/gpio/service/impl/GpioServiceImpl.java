package com.pi4j.io.gpio.service.impl;

/*
 * #%L
 * **********************************************************************
 * ORGANIZATION  :  Pi4J
 * PROJECT       :  Pi4J :: OSGi Service
 * FILENAME      :  GpioServiceImpl.java  
 * 
 * This file is part of the Pi4J project. More information about 
 * this project can be found here:  http://www.pi4j.com/
 * **********************************************************************
 * %%
 * Copyright (C) 2012 - 2013 Pi4J
 * %%
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * #L%
 */


import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalInput;
import com.pi4j.io.gpio.Pin;
import com.pi4j.io.gpio.PinPullResistance;
import com.pi4j.io.gpio.PinState;
import com.pi4j.io.gpio.event.GpioPinDigitalStateChangeEvent;
import com.pi4j.io.gpio.event.GpioPinListenerDigital;
import com.pi4j.io.gpio.impl.GpioControllerImpl;
import com.pi4j.io.gpio.service.GpioService;
import com.pi4j.io.gpio.service.PinListener;

public class GpioServiceImpl extends GpioControllerImpl implements GpioService
{
	final GpioController gpio = GpioFactory.getInstance();
	
	public void start(){
	}
    public void stop(){
        // stop all GPIO activity/threads by shutting down the GPIO controller
        // (this method will forcefully shutdown all GPIO monitoring threads and scheduled tasks)
        gpio.shutdown();           
    }

	@Override
	public void addPinListener(Pin pin, PinListener pinListener) {
        System.out.println("<--Pi4J--> GPIO Listen Example ... started.");

        // provision gpio pin #02 as an input pin with its internal pull down resistor enabled
        final GpioPinDigitalInput myButton = gpio.provisionDigitalInputPin(pin, PinPullResistance.PULL_DOWN);

        // create and register gpio pin listener
        myButton.addListener(new GpioPinListenerDigitalAdapter(pinListener));
        
        System.out.println(" ... complete the GPIO "+pin+" circuit and see the listener feedback here in the console.");
                
        // stop all GPIO activity/threads by shutting down the GPIO controller
        // (this method will forcefully shutdown all GPIO monitoring threads and scheduled tasks)
        // gpio.shutdown();   <--- implement this method call if you wish to terminate the Pi4J GPIO controller        
		
	}
    

	private class GpioPinListenerDigitalAdapter implements GpioPinListenerDigital {
		private final PinListener pinListener;
		
		GpioPinListenerDigitalAdapter(final PinListener pinListener){
			this.pinListener = pinListener;
		}
		
		@Override
		public void handleGpioPinDigitalStateChangeEvent(
				GpioPinDigitalStateChangeEvent event) {
            System.out.println(" --> GPIO PIN STATE CHANGE: " + event.getPin() + " = " + event.getState());
			PinState state = event.getState();
			switch(state){
				case HIGH:
					pinListener.pinHigh();
					break;
				case LOW:
				default:
					pinListener.pinLow();
			}
		}
		
	}
}
