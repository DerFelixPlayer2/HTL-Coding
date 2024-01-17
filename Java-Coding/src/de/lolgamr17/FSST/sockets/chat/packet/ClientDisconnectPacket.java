package de.lolgamr17.FSST.sockets.chat.packet;

import org.json.JSONObject;

public class ClientDisconnectPacket extends Packet {

    public ClientDisconnectPacket(String clientName) {
        super(clientName);
        packet.put("type", 1);
    }

    ClientDisconnectPacket(JSONObject packet) {
        super(packet);
    }

    @Override
    public String toNiceString() {
        return "[" + getTimestamp() + "] " + getClientName() + " has disconnected.";
    }

    @Override
    public String toString() {
        return packet.toString();
    }
}