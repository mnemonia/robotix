package com.mnemonia.io.service.mock;

import java.util.Collection;
import java.util.List;
import java.util.Map;

import com.pi4j.io.gpio.GpioPin;
import com.pi4j.io.gpio.GpioPinAnalog;
import com.pi4j.io.gpio.GpioPinAnalogInput;
import com.pi4j.io.gpio.GpioPinAnalogOutput;
import com.pi4j.io.gpio.GpioPinDigital;
import com.pi4j.io.gpio.GpioPinDigitalInput;
import com.pi4j.io.gpio.GpioPinDigitalMultipurpose;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.GpioPinInput;
import com.pi4j.io.gpio.GpioPinPwmOutput;
import com.pi4j.io.gpio.GpioPinShutdown;
import com.pi4j.io.gpio.GpioProvider;
import com.pi4j.io.gpio.Pin;
import com.pi4j.io.gpio.PinMode;
import com.pi4j.io.gpio.PinPullResistance;
import com.pi4j.io.gpio.PinState;
import com.pi4j.io.gpio.RaspiPin;
import com.pi4j.io.gpio.event.GpioPinListener;
import com.pi4j.io.gpio.service.GpioService;
import com.pi4j.io.gpio.service.PinListener;
import com.pi4j.io.gpio.trigger.GpioTrigger;

public final class GpioServiceMock implements GpioService {

	@Override
	public void addListener(GpioPinListener arg0, GpioPinInput... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void addListener(GpioPinListener[] arg0, GpioPinInput... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void addTrigger(GpioTrigger arg0, GpioPinInput... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void addTrigger(GpioTrigger[] arg0, GpioPinInput... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void export(PinMode arg0, GpioPin... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public PinMode getMode(GpioPin arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Collection<GpioPin> getProvisionedPins() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public PinPullResistance getPullResistance(GpioPin arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public PinState getState(GpioPinDigital arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public double getValue(GpioPinAnalog arg0) {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public void high(GpioPinDigitalOutput... arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean isExported(GpioPin... arg0) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean isHigh(GpioPinDigital... arg0) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean isLow(GpioPinDigital... arg0) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean isMode(PinMode arg0, GpioPin... arg1) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean isPullResistance(PinPullResistance arg0, GpioPin... arg1) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean isShutdown() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean isState(PinState arg0, GpioPinDigital... arg1) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void low(GpioPinDigitalOutput... arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public GpioPinAnalogInput provisionAnalogInputPin(Pin arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinAnalogInput provisionAnalogInputPin(GpioProvider arg0, Pin arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinAnalogInput provisionAnalogInputPin(Pin arg0, String arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinAnalogInput provisionAnalogInputPin(GpioProvider arg0, Pin arg1, String arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinAnalogOutput provisionAnalogOutputPin(Pin arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinAnalogOutput provisionAnalogOutputPin(GpioProvider arg0, Pin arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinAnalogOutput provisionAnalogOutputPin(Pin arg0, double arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinAnalogOutput provisionAnalogOutputPin(Pin arg0, String arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinAnalogOutput provisionAnalogOutputPin(GpioProvider arg0, Pin arg1, double arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinAnalogOutput provisionAnalogOutputPin(GpioProvider arg0, Pin arg1, String arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinAnalogOutput provisionAnalogOutputPin(Pin arg0, String arg1, double arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinAnalogOutput provisionAnalogOutputPin(GpioProvider arg0, Pin arg1, String arg2, double arg3) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalInput provisionDigitalInputPin(Pin arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalInput provisionDigitalInputPin(GpioProvider arg0, Pin arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalInput provisionDigitalInputPin(Pin arg0, PinPullResistance arg1) {
		return new GpioPinDigitalInput(){

			@Override
			public PinState getState() {
				return PinState.HIGH;
			}

			@Override
			public boolean isHigh() {
				return true;
			}

			@Override
			public boolean isLow() {
				return false;
			}

			@Override
			public boolean isState(PinState arg0) {
				// TODO Auto-generated method stub
				return false;
			}

			@Override
			public void addListener(GpioPinListener... arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void addListener(List<? extends GpioPinListener> arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void clearProperties() {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void export(PinMode arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public Collection<GpioPinListener> getListeners() {
				// TODO Auto-generated method stub
				return null;
			}

			@Override
			public PinMode getMode() {
				// TODO Auto-generated method stub
				return null;
			}

			@Override
			public String getName() {
				// TODO Auto-generated method stub
				return null;
			}

			@Override
			public Pin getPin() {
				return RaspiPin.GPIO_01;
			}

			@Override
			public Map<String, String> getProperties() {
				// TODO Auto-generated method stub
				return null;
			}

			@Override
			public String getProperty(String arg0) {
				// TODO Auto-generated method stub
				return null;
			}

			@Override
			public String getProperty(String arg0, String arg1) {
				// TODO Auto-generated method stub
				return null;
			}

			@Override
			public GpioProvider getProvider() {
				// TODO Auto-generated method stub
				return null;
			}

			@Override
			public PinPullResistance getPullResistance() {
				// TODO Auto-generated method stub
				return null;
			}

			@Override
			public GpioPinShutdown getShutdownOptions() {
				// TODO Auto-generated method stub
				return null;
			}

			@Override
			public Object getTag() {
				// TODO Auto-generated method stub
				return null;
			}

			@Override
			public boolean hasListener(GpioPinListener... arg0) {
				// TODO Auto-generated method stub
				return false;
			}

			@Override
			public boolean hasProperty(String arg0) {
				// TODO Auto-generated method stub
				return false;
			}

			@Override
			public boolean isExported() {
				// TODO Auto-generated method stub
				return false;
			}

			@Override
			public boolean isMode(PinMode arg0) {
				// TODO Auto-generated method stub
				return false;
			}

			@Override
			public boolean isPullResistance(PinPullResistance arg0) {
				// TODO Auto-generated method stub
				return false;
			}

			@Override
			public void removeAllListeners() {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void removeListener(GpioPinListener... arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void removeListener(List<? extends GpioPinListener> arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void removeProperty(String arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void setMode(PinMode arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void setName(String arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void setProperty(String arg0, String arg1) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void setPullResistance(PinPullResistance arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void setShutdownOptions(GpioPinShutdown arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void setShutdownOptions(Boolean arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void setShutdownOptions(Boolean arg0, PinState arg1) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void setShutdownOptions(Boolean arg0, PinState arg1, PinPullResistance arg2) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void setShutdownOptions(Boolean arg0, PinState arg1, PinPullResistance arg2, PinMode arg3) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void setTag(Object arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void unexport() {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void addTrigger(GpioTrigger... arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void addTrigger(List<? extends GpioTrigger> arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public Collection<GpioTrigger> getTriggers() {
				// TODO Auto-generated method stub
				return null;
			}

			@Override
			public void removeAllTriggers() {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void removeTrigger(GpioTrigger... arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void removeTrigger(List<? extends GpioTrigger> arg0) {
				// TODO Auto-generated method stub
				
			}};
	}

	@Override
	public GpioPinDigitalInput provisionDigitalInputPin(Pin arg0, String arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalInput provisionDigitalInputPin(GpioProvider arg0, Pin arg1, PinPullResistance arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalInput provisionDigitalInputPin(GpioProvider arg0, Pin arg1, String arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalInput provisionDigitalInputPin(Pin arg0, String arg1, PinPullResistance arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalInput provisionDigitalInputPin(GpioProvider arg0, Pin arg1, String arg2, PinPullResistance arg3) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalMultipurpose provisionDigitalMultipurposePin(Pin arg0, PinMode arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalMultipurpose provisionDigitalMultipurposePin(GpioProvider arg0, Pin arg1, PinMode arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalMultipurpose provisionDigitalMultipurposePin(Pin arg0, PinMode arg1, PinPullResistance arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalMultipurpose provisionDigitalMultipurposePin(Pin arg0, String arg1, PinMode arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalMultipurpose provisionDigitalMultipurposePin(GpioProvider arg0, Pin arg1, PinMode arg2,
			PinPullResistance arg3) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalMultipurpose provisionDigitalMultipurposePin(GpioProvider arg0, Pin arg1, String arg2,
			PinMode arg3) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalMultipurpose provisionDigitalMultipurposePin(Pin arg0, String arg1, PinMode arg2,
			PinPullResistance arg3) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalMultipurpose provisionDigitalMultipurposePin(GpioProvider arg0, Pin arg1, String arg2,
			PinMode arg3, PinPullResistance arg4) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalOutput provisionDigitalOutputPin(Pin arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalOutput provisionDigitalOutputPin(GpioProvider arg0, Pin arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalOutput provisionDigitalOutputPin(Pin arg0, PinState arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalOutput provisionDigitalOutputPin(Pin arg0, String arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalOutput provisionDigitalOutputPin(GpioProvider arg0, Pin arg1, PinState arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalOutput provisionDigitalOutputPin(GpioProvider arg0, Pin arg1, String arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalOutput provisionDigitalOutputPin(Pin arg0, String arg1, PinState arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinDigitalOutput provisionDigitalOutputPin(GpioProvider arg0, Pin arg1, String arg2, PinState arg3) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPin provisionPin(Pin arg0, PinMode arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPin provisionPin(GpioProvider arg0, Pin arg1, PinMode arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPin provisionPin(Pin arg0, String arg1, PinMode arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPin provisionPin(GpioProvider arg0, Pin arg1, String arg2, PinMode arg3) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinPwmOutput provisionPwmOutputPin(Pin arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinPwmOutput provisionPwmOutputPin(GpioProvider arg0, Pin arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinPwmOutput provisionPwmOutputPin(Pin arg0, int arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinPwmOutput provisionPwmOutputPin(Pin arg0, String arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinPwmOutput provisionPwmOutputPin(GpioProvider arg0, Pin arg1, int arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinPwmOutput provisionPwmOutputPin(GpioProvider arg0, Pin arg1, String arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinPwmOutput provisionPwmOutputPin(Pin arg0, String arg1, int arg2) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public GpioPinPwmOutput provisionPwmOutputPin(GpioProvider arg0, Pin arg1, String arg2, int arg3) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void pulse(long arg0, GpioPinDigitalOutput... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void removeAllListeners() {
		// TODO Auto-generated method stub

	}

	@Override
	public void removeAllTriggers() {
		// TODO Auto-generated method stub

	}

	@Override
	public void removeListener(GpioPinListener arg0, GpioPinInput... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void removeListener(GpioPinListener[] arg0, GpioPinInput... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void removeTrigger(GpioTrigger arg0, GpioPinInput... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void removeTrigger(GpioTrigger[] arg0, GpioPinInput... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void setMode(PinMode arg0, GpioPin... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void setPullResistance(PinPullResistance arg0, GpioPin... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void setShutdownOptions(GpioPinShutdown arg0, GpioPin... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void setShutdownOptions(Boolean arg0, GpioPin... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void setShutdownOptions(Boolean arg0, PinState arg1, GpioPin... arg2) {
		// TODO Auto-generated method stub

	}

	@Override
	public void setShutdownOptions(Boolean arg0, PinState arg1, PinPullResistance arg2, GpioPin... arg3) {
		// TODO Auto-generated method stub

	}

	@Override
	public void setShutdownOptions(Boolean arg0, PinState arg1, PinPullResistance arg2, PinMode arg3, GpioPin... arg4) {
		// TODO Auto-generated method stub

	}

	@Override
	public void setState(PinState arg0, GpioPinDigitalOutput... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void setState(boolean arg0, GpioPinDigitalOutput... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void setValue(double arg0, GpioPinAnalogOutput... arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void shutdown() {
		// TODO Auto-generated method stub

	}

	@Override
	public void toggle(GpioPinDigitalOutput... arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void unexport(GpioPin... arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void unexportAll() {
		// TODO Auto-generated method stub

	}

	@Override
	public void unprovisionPin(GpioPin... arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void addPinListener(Pin pin, PinListener pinListener) {
		// TODO Auto-generated method stub

	}

}
