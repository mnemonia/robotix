package ch.mnemonia.home.automation.desk;

public final class Desk {
	
	public void start(){
		Question q = new Question();
		new Thread(q).start();
	}

	public static void main(String[] args) {
		new Desk().start();
	}

}
