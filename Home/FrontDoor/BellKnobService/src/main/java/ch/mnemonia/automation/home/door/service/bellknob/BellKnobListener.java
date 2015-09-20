package ch.mnemonia.automation.home.door.service.bellknob;


public final class BellKnobListener {
//	private final EventAdmin eventAdmin;
//	private Runnable ioSystemPoller;
//	private volatile boolean isRunning = false;
//	
//	public BellKnobListener(EventAdmin eventAdmin) {
//		this.eventAdmin = eventAdmin;
//	}
//	
//	public void start(){
//		isRunning = true;
//		ioSystemPoller = new Runnable() {
//			
//			@Override
//			public void run() {
//				while(isRunning){
//					System.out.println("BellKnobListener: poll.");
//					try {
//						Map<String, Object> params = new HashMap<String, Object>();
//						eventAdmin.postEvent(new Event("ch/mnemonia/automation/home/door/knob/ring",params));
//						Thread.sleep(20000);						
//					} catch (InterruptedException e) {;}
//				}
//			}
//		};
//		new Thread(ioSystemPoller).start();
//	}
//
//	public void stop() {
//		isRunning = false;
//	}

}
