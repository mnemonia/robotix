package ch.mnemonia.home.automation.desk;

import com.sun.speech.freetts.Voice;
import com.sun.speech.freetts.VoiceManager;

public class Answer {
	private final Voice helloVoice;

	Answer(){
        VoiceManager voiceManager = VoiceManager.getInstance();
        for (Voice voice : voiceManager.getVoices()){
        	System.out.println(voice.getName());
        }
        helloVoice = voiceManager.getVoice("kevin16");
        
        /* Allocates the resources for the voice.
         */
        helloVoice.allocate();
	}
	
	void say(String message){
        helloVoice.speak(message);
	}
	
	public void dispose(){
        helloVoice.deallocate();
	}
}
