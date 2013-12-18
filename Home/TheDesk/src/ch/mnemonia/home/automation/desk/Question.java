package ch.mnemonia.home.automation.desk;

import java.util.HashMap;
import java.util.Map;

import edu.cmu.sphinx.frontend.util.Microphone;
import edu.cmu.sphinx.recognizer.Recognizer;
import edu.cmu.sphinx.result.Result;
import edu.cmu.sphinx.util.props.ConfigurationManager;

public class Question implements Runnable {
	private final Answer answer = new Answer();
	private final Recognizer recognizer;
	private static final String ID = "desk ";
	private final Map<String, Command> qa = create();

	private Map<String, Command> create() {
		Map<String, Command> qna = new HashMap<String, Command>();
		qna.put(ID+"turn lights on", new CommandRunner("turning lights on.",new Runnable() {
			
			@Override
			public void run() {
//				 PIN 13 HIGH
			}
		}, answer));
		qna.put(ID+"turn lights off", new CommandRunner("turning lights off now.",new Runnable() {
			
			@Override
			public void run() {
				// PIN 13 LOW
			}
		}, answer));
		qna.put(ID+"dim lights", new CommandRunner("Dimming lights to 50%.",new Runnable() {
			
			@Override
			public void run() {
				// MUTE LIGHT ON
			}
		}, answer));
		qna.put(ID+"sleep", new CommandRunner("Sleeping now. Wake me up with, "+ID+"hello.",new Runnable() {
			
			@Override
			public void run() {
				// MUTE LIGHT ON
			}
		}, answer));
		qna.put(ID+"hello", new CommandRunner(ID+", is here again. What can I do for you, Nils?",new Runnable() {
			
			@Override
			public void run() {
				// PIN BLINK TWICE
			}
		}, answer));
		qna.put(ID+"goodbye", new CommandRunner("Goodbye Nils. Have a good day. I send you up dates to your mobile phone. Ok?",new Runnable() {
			
			@Override
			public void run() {
				// Sending Twitter
			}
		}, answer));
		qna.put(ID+"thank you", new CommandRunner("Nevermind, Nils. This is my purpose in life.",new Runnable() {
			
			@Override
			public void run() {
				// PIN BLINK
			}
		}, answer));
//		qna.put(ID+"turn lights off", "turning lights off now.");
//		qna.put(ID+"dim lights", "");
//		qna.put(ID+"mute", "Shutting up. Restart me with the "+ID+"listen command.");
//		qna.put(ID+"listen", ID+"is back on frequency");
//		qna.put(ID+"bye", "Goodnight. Give your beloved wife, Marielle, a hug from me.");
//		qna.put(ID+"thank you", "Thank you too for giving me a voice, Nils. I feel human.");
		return qna;
	} 

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

        System.out.println("Say: (Desk) ( Turn Lights Off | Turn Lights On | Dim Lights | Mute | Listen | Bye | Thank You );");
        answer.say("Hello Nils. Welcome back. What can I do for you?");
	}
	
	@Override
	public void run(){
		boolean isMute = false;
        // loop the recognition until the programm exits.
        while (true) {
            System.out.println("Start speaking. Press Ctrl-C to quit.\n");

            Result result = recognizer.recognize();

            if (result != null) {
                String resultText = result.getBestFinalResultNoFiller();
                System.out.println("You said: " + resultText + '\n');
                if(resultText.equals(ID+"sleep")){
                	if(isMute){
                		continue;
                	}
                	qa.get(resultText).execute();
//                	answer.say(qa.get(resultText));
                	isMute = true;
                	continue;
                }else if(resultText.equals(ID+"hello")){
                	qa.get(resultText).execute();
                	
//                	answer.say(qa.get(resultText));
                	isMute = false;
                	continue;
                }
                
            	if(isMute){
            		continue;
            	}
            	
                
            	Command command = qa.get(resultText);
            	if(command==null){
            		continue;
            	}
            	command.execute();
//                String command = qa.get(resultText);
//                if(command == null){
////                	answer.say("Negative. Say again.");
////                	try {
////						Thread.sleep(1000);
////					} catch (InterruptedException e) {
////						// TODO Auto-generated catch block
////						e.printStackTrace();
////					}                	
//                	continue;
//                }
//                answer.say(command);
//                
//                System.out.println(resultText.toLowerCase().compareTo("desk lights on")==0);
//                if(resultText.toLowerCase().compareTo("desk lights on")==0){
//                	answer.say("Yes Nils - I turn the lights on");
//                }else if(resultText.toLowerCase().compareTo("desk lights off")==0){
//                	answer.say("Time to sleep. Goodby.");
//                }else if(resultText.toLowerCase().compareTo("desk goodby")==0){
//                	answer.say("Give a kiss to the beautiful marielle");
//                }

            } else {
                System.out.println("I can't hear what you said.\n");
            }
        }
		
	}
	
	interface Command {
		public void execute();
	}
	abstract class AbstractCommand implements Command {
		private String message;
		private Answer answer;
		
		protected AbstractCommand(String message, Answer answer){
			this.answer = answer;
			this.message = message;
		}
		@Override		
		public void execute(){
			answer.say(message);
			internalExecute();
		}
		
		protected abstract void internalExecute();
	}
	class CommandRunner extends AbstractCommand {
		private final Runnable runner;
		protected CommandRunner(String message, Runnable runner, Answer answer) {
			super(message, answer);
			this.runner = runner;
		}

		@Override
		protected void internalExecute() {
			runner.run();
		}
		
	}
}
