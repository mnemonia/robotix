package ch.mnemonia.home.automation.desk;

import edu.cmu.sphinx.frontend.util.Microphone;
import edu.cmu.sphinx.recognizer.Recognizer;
import edu.cmu.sphinx.result.Result;
import edu.cmu.sphinx.util.props.ConfigurationManager;

public class Question implements Runnable {
	private final Answer answer = new Answer();
	private final Recognizer recognizer;

	public Question(){
        ConfigurationManager cm;

        cm = new ConfigurationManager(HelloWorld.class.getResource("desk.config.xml"));

        recognizer = (Recognizer) cm.lookup("recognizer");
        recognizer.allocate();

        // start the microphone or exit if the programm if this is not possible
        Microphone microphone = (Microphone) cm.lookup("microphone");
        if (!microphone.startRecording()) {
            System.out.println("Cannot start microphone.");
            recognizer.deallocate();
            System.exit(1);
        }

        System.out.println("Say: (Good morning | Hello) ( Bhiksha | Evandro | Paul | Philip | Rita | Will )");
	}
	
	@Override
	public void run(){
        // loop the recognition until the programm exits.
        while (true) {
            System.out.println("Start speaking. Press Ctrl-C to quit.\n");

            Result result = recognizer.recognize();

            if (result != null) {
                String resultText = result.getBestFinalResultNoFiller();
                System.out.println("You said: " + resultText + '\n');
                System.out.println(resultText.toLowerCase().compareTo("desk lights on")==0);
                if(resultText.toLowerCase().compareTo("desk lights on")==0){
                	answer.say("Yes Nils - I turn the lights on");
                }else if(resultText.toLowerCase().compareTo("desk lights off")==0){
                	answer.say("Time to sleep. Goodby.");
                }

            } else {
                System.out.println("I can't hear what you said.\n");
            }
        }
		
	}
}
