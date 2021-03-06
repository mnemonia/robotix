
package com.netstal.automation.jettyEmbedded.demoServlets;

import java.io.IOException;

import org.eclipse.jetty.websocket.api.Session;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketClose;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketConnect;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketError;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketMessage;
import org.eclipse.jetty.websocket.api.annotations.WebSocket;
import org.eclipse.jetty.websocket.servlet.WebSocketServlet;
import org.eclipse.jetty.websocket.servlet.WebSocketServletFactory;

@WebSocket
public class WebsocketEchoServlet2 extends WebSocketServlet {

	private static final long serialVersionUID = 1L;
	
	private Session session;

    @OnWebSocketClose
    public void onClose(int statusCode, String reason) {
        System.out.println("Close2: statusCode=" + statusCode + ", reason=" + reason);
    }

    @OnWebSocketError
    public void onError(Throwable t) {
        System.out.println("Error2: " + t.getMessage());
    }

    @OnWebSocketConnect
    public void onConnect(Session session) {
    	this.session = session;
        System.out.println("Connect2: " + session.getRemoteAddress().getAddress());
        try {
            session.getRemote().sendString("Hello Webbrowser");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @OnWebSocketMessage
    public void onMessage(String message) {
        System.out.println("Message2: " + message);
        try {
			session.getRemote().sendString(message + " (2)");
		} catch (IOException e) {
			e.printStackTrace();
		}
    }

	@Override
	public void configure(WebSocketServletFactory factory) {
		factory.register(WebsocketEchoServlet2.class);
	}
}
