package ch.mnemonia.service.time;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;

import ch.mnemonia.service.time.internal.TimeServiceImpl;

public class Activator implements BundleActivator {

	/*
	 * (non-Javadoc)
	 * @see org.osgi.framework.BundleActivator#start(org.osgi.framework.BundleContext)
	 */
	public void start(BundleContext bundleContext) throws Exception {
        bundleContext.registerService(TimeService.class.getName(), new TimeServiceImpl(), null);
	}
	
	/*
	 * (non-Javadoc)
	 * @see org.osgi.framework.BundleActivator#stop(org.osgi.framework.BundleContext)
	 */
	public void stop(BundleContext bundleContext) throws Exception {
	}

}
