package dev.hofes.Networking.chat;

import java.io.IOException;

public class ClientMain1 {
    public static void main(String[] args) throws IOException {
        new SocketClient().run();
    }
}