package com.pi4j.service.osgi;

/*
 * #%L
 * **********************************************************************
 * ORGANIZATION  :  Pi4J
 * PROJECT       :  Pi4J :: OSGi Service
 * FILENAME      :  Activator.java  
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


import java.util.Properties;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;
import org.osgi.service.log.LogService;
import org.osgi.util.tracker.ServiceTracker;

import com.mnemonia.io.IoSystemService;
import com.mnemonia.io.internal.IoSystemServiceImpl;
import com.pi4j.io.gpio.service.impl.GpioServiceImpl;
import com.pi4j.system.service.NetworkInformationService;
import com.pi4j.system.service.SystemInformationService;
import com.pi4j.system.service.impl.NetworkInformationServiceImpl;
import com.pi4j.system.service.impl.SystemInformationServiceImpl;

public class Activator implements BundleActivator
{
	private ServiceTracker<?, LogService> logServiceTracker;
	private LogService logService;
	private GpioServiceImpl gpioServiceImpl;

	public void start(BundleContext bundleContext) throws Exception
    {
	    // create a tracker and track the log service
	    logServiceTracker = new ServiceTracker(bundleContext, LogService.class.getName(), null);
	    logServiceTracker.open();

	    // grab the service
	    logService = logServiceTracker.getService();

	    if(logService != null){ 
	        System.out.println("There is a LogService available"); 
	        logService.log(LogService.LOG_INFO, "Yee ha, I'm logging!"); 
		} 
		else { 
		        System.out.println("There is no LogService available"); 
		        return;
		}
	    
	    logService.log(LogService.LOG_INFO, "Starting IoSystemService ...");
//    	if(System.getProperty("os.name").startsWith("Windows")){
//    		System.out.println("GPIO Service is NOT running on Windows.");
//    		throw new BundleException("GPIO Service is NOT running on Windows");
//    	}
        // create OSGi bundle properties
    	Properties props = new Properties();
        props.put("Language", "English");

        gpioServiceImpl = new GpioServiceImpl(logService);
        
        // create a new GPIO service instance
        // and register services with OSGi
        bundleContext.registerService(IoSystemService.class.getName(), new IoSystemServiceImpl(gpioServiceImpl), null);
        bundleContext.registerService(SystemInformationService.class.getName(), new SystemInformationServiceImpl(), null);
        bundleContext.registerService(NetworkInformationService.class.getName(), new NetworkInformationServiceImpl(), null);        

        gpioServiceImpl.start();
        
	    logService.log(LogService.LOG_INFO, "Starting IoSystemService DONE");
    }

    public void stop(BundleContext bundleContext) throws Exception
    {      
    	gpioServiceImpl.stop();
    	logServiceTracker.close();
    }
}
