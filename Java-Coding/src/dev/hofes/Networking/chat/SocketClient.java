package dev.hofes.Networking.chat;

import dev.hofes.Networking.chat.packet.ClientConnectPacket;
import dev.hofes.Networking.chat.packet.ClientDisconnectPacket;
import dev.hofes.Networking.chat.packet.MessagePacket;
import dev.hofes.Networking.chat.packet.Packet;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.SocketException;
import java.util.Scanner;

public class SocketClient implements Runnable {

    private static final String HOST = "localhost";
    private static final int PORT = 3000;

    private final Socket socket;
    private final PrintWriter out;
    private final BufferedReader in;
    private final Scanner sc;

    private String clientName;

    public SocketClient() throws IOException {
        this.socket = new Socket(HOST, PORT);
        this.out = new PrintWriter(socket.getOutputStream(), true);
        this.in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        this.sc = new Scanner(System.in);
    }

    @Override
    public void run() {
        System.out.print("Enter your name: ");
        this.clientName = this.sc.nextLine();

        out.println(new ClientConnectPacket(clientName));

        new InputThread().start();
        new OutputThread().start();
    }

    private class InputThread extends Thread {
        @Override
        public void run() {
            String inputLine;
            try {
                while ((inputLine = in.readLine()) != null) {
                    System.out.println(Packet.from(new JSONObject(inputLine)).toNiceString());
                }
            } catch (SocketException ignored) {
            } catch (IOException e) {
                e.printStackTrace();
                try {
                    if (socket != null && !socket.isClosed()) {
                        socket.close();
                    }
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            }
        }
    }

    private class OutputThread extends Thread {
        @Override
        public void run() {
            System.out.println("Enter a message or 'exit' to close the connection.");
            while (true) {
                String message = sc.nextLine();

                if (message.equals("exit")) {
                    out.println(new ClientDisconnectPacket(clientName));
                    out.flush();
                    try {
                        if (socket != null && !socket.isClosed()) {
                            socket.close();
                        }
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                } else {
                    out.println(new MessagePacket(clientName, message));
                }
            }
        }
    }
}