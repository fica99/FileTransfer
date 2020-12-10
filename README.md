# FileTransfer

## Example

### Client example:
![Client example](https://i.ibb.co/1v6CjSk/Screen-Shot-2020-12-10-at-4-54-13-PM.png)

### Server example:
![Server example](https://i.ibb.co/KLq6qfX/Screen-Shot-2020-12-10-at-4-56-40-PM.png)



## Introduction

This project is a client-server application. The client transmits the file to the server using the UDP protocol. After receiving the file, the server calculates its checksum and returns it to the client.

## Protocol

To transfer a file, the client splits it into packets in a special format and sends them to the server in random order. After sending the whole file, the client receives the checksum packet from the server and compares the received checksum
with the checksum calculated by the client.

The checksum will be calculated as follows:
```
uint32_t	crc32c(uint32_t crc, const byte *buf, size_t len)
{
	int k;

	crc = ~crc;
	while (len--) {
		crc ^= to_integer<unsigned char>(*buf);
		++buf;
		for (k = 0; k < 8; k++)
			crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
	}
	return ~crc;
}
```

For client-server communication we define the following header format packets:
```
	uint32_t				seq_number; // number of the packet
	uint32_t				seq_total; // count of packets
	uint8_t					type; // type of packet: 0 == ACK, 1 == PUT
	std::byte				id[8]; // file id
	std::byte				*data; // file data
```

The maximum size of a UDP packet is 1472 bytes.

The file is complete if seq_total equals the number of data packets received.

Consider two types of packets defined by the numeric type field:
* `PUT`: this is the type used when sending data from a client to a server
* `ACK`: this is the type used used for confirmation


When forming a `PUT` packet, the `seq_number` field is set to the number of the current packet to be sent, and `seq_total` is set to the number of packets needed to fully transmit the file for a given id. The remaining length of the UDP packet is left under the data.


When forming an `ACK` packet: `seq_number` is set to the number of the received packet, `seq_total` is the total number of packets received for the given `id`. Such UDP data packet does not contain any more data, except for the special case when the transmission is over.

If the server considers the file completed, then it sends the last `ACK` packet,
and writes the calculated checksum to the data section. On the client such a packet is easy to detect: its `seq_total` will be equal to the originally calculated number of packets for the given `id`.

The interaction protocol we define is as follows:
1. The client starts sending data to the server using `PUT` packets.
2. The server receives the data and writes them into memory, after each received
packet received, sending the client `ACK` packets.
3. if the client on some sent packet doesn't receive `ACK` within timeout, the sent packet is resent (timeout for confirmation from server is 0.5 sec).

Server requirements:

1. Client transmissions to the server are idempotent - packets with the same `seq_number` can be resent several times - this will not compromise either
data integrity or the server's behavior in general
2. Transmission of data chunks can go in any order (the seq_number
will be inconsistent): 1 2 39 27 18 3 24 25 26 10 ... but the server must
reorder them and calculate the checksum correctly.
3. Between the packets referring to one file there can go packets to another file: the server must store all the packets received earlier, send the correct packet
packets previously received and send the correct `ACK` packets according to all received packets for all `id`.

Client requirements:
* To demonstrate how the transfer works, the client must specifically send
packets in random order

## Installation

```
git clone https://github.com/fica99/FileTransfer.git
cd FileTransfer
make
```

## Usage

### Server

To start the server use the command:
```
./FileServer -p port
```
Server has timeout. If no data arrives within 8 seconds, the server stops its work.

### Client

To start the client use the command:
```
./FileClient -i host -p port -f file ...
```
The client has a timeout of half a second, if the confirmation does not come, the data continues to be sent in random order. Each file in order is assigned its own `id`.

### Testing

To test the program, open two terminals, in one type:
```
make run_server
```
and in the other
```
make run_client
```
