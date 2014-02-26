package ch.mnemonia.home.automation.service.frontdoor.bell.http;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.osgi.framework.BundleContext;
import org.osgi.framework.FrameworkUtil;
import org.osgi.framework.ServiceReference;

import ch.mnemonia.house.automation.service.bell.DoorBellService;

public final class HttpDoorBellService extends HttpServlet {
	private static final long serialVersionUID = 1L;

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse response)
			throws ServletException, IOException {
		PrintWriter printWriter = response.getWriter();
		printWriter.print("ringing...");
		BundleContext bundleContext = 
		        FrameworkUtil.
		        getBundle(this.getClass()).
		        getBundleContext();
		ServiceReference<DoorBellService> serviceReference = bundleContext.getServiceReference(DoorBellService.class);
		DoorBellService doorBellService = bundleContext.getService(serviceReference);
		doorBellService.ring();
		printWriter.println(" done.");

	}

}
