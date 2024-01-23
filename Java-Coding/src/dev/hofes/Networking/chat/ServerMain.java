package dev.hofes.Networking.chat;

import dev.hofes.Networking.chat.packet.MessagePacket;
import dev.hofes.Networking.chat.packet.Packet;
import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Scanner;

public class ServerMain {

    private final static ArrayList<SocketServer> clients = new ArrayList<>();
    private final static int port = 3000;
    private final static String name = "SYSTEM";

    public static void main(String[] args) throws IOException {
        try (ServerSocket serverSocket = new ServerSocket(ServerMain.port)) {
            System.out.printf("Listening on port %d...\n", ServerMain.port);

            new OutputThread().start();

            while (true) {
                final Socket clientSocket = serverSocket.accept();
                SocketServer client = new SocketServer(clientSocket);
                clients.add(client);
                client.start();
            }
        }
    }

    protected static void broadcast(@NotNull Packet packet) {
        for (SocketServer client : clients) {
            client.sendMessage(packet);
        }
    }

    private static class OutputThread extends Thread {
        @Override
        public void run() {
            String inputLine;
            final Scanner sc = new Scanner(System.in);
            while ((inputLine = sc.nextLine()) != null) {
                Packet p = new MessagePacket(name, inputLine);
                SocketServer.addPacketToHistory(p);
                broadcast(p);
            }
        }
    }
}