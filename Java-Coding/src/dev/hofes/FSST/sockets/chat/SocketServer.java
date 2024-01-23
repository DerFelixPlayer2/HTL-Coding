package dev.hofes.FSST.sockets.chat;

import dev.hofes.FSST.sockets.chat.packet.ClientConnectPacket;
import dev.hofes.FSST.sockets.chat.packet.ClientDisconnectPacket;
import dev.hofes.FSST.sockets.chat.packet.MessagePacket;
import dev.hofes.FSST.sockets.chat.packet.Packet;
import org.jetbrains.annotations.NotNull;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.SocketException;
import java.util.ArrayList;

public class SocketServer extends Thread {

    private static final ArrayList<Packet> history = new ArrayList<>();
    private static final String NAME = "SYSTEM";

    private final Socket clientSocket;
    private final BufferedReader in;
    private final PrintWriter out;

    public SocketServer(@NotNull Socket clientSocket) {
        this.clientSocket = clientSocket;
        try {
            this.in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            this.out = new PrintWriter(clientSocket.getOutputStream(), true);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void addPacketToHistory(@NotNull Packet packet) {
        history.add(packet);
    }

    public void sendMessage(@NotNull Packet packet) {
        if (!this.clientSocket.isClosed() && this.out != null) {
            this.out.println(packet);
        }
    }

    @Override
    public void run() {
        try {
            String inputLine;
            while ((inputLine = this.in.readLine()) != null) {
                Packet packet = Packet.from(new JSONObject(inputLine));

                if (packet instanceof ClientConnectPacket) {
                    System.out.println(packet.toNiceString());
                    for (Packet p : history) {
                        this.out.println(p);
                    }
                } else if (packet instanceof ClientDisconnectPacket) {
                    System.out.println(packet.toNiceString());
                    history.add(packet);
                    if (this.clientSocket != null && !this.clientSocket.isClosed()) {
                        this.clientSocket.close();
                    }
                    break;
                } else if (packet instanceof MessagePacket) {
                    System.out.println(packet.toNiceString());
                }

                ServerMain.broadcast(packet);
                history.add(packet);
            }
        } catch (SocketException ignored) {
        } catch (IOException e) {
            e.printStackTrace();
            try {
                if (this.clientSocket != null && !this.clientSocket.isClosed()) {
                    this.clientSocket.close();
                }
            } catch (IOException e1) {
                e1.printStackTrace();
            }
            Thread.currentThread().interrupt();
        }
    }
}