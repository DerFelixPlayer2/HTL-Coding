package dev.hofes.Networking.chat.packet;

import org.json.JSONObject;

public class ClientConnectPacket extends Packet {

    public ClientConnectPacket(String clientName) {
        super(clientName);
        packet.put("type", 0);
    }

    ClientConnectPacket(JSONObject packet) {
        super(packet);
    }

    @Override
    public String toNiceString() {
        return "[" + getTimestamp() + "] " + getClientName() + " has connected.";
    }

    @Override
    public String toString() {
        return packet.toString();
    }
}