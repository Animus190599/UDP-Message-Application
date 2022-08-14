
1. Assumption

All the message is within the data segment of an UDP message, not the header, for simplification purpose.
This is because the network stack will automatically include UDP headers. 

What you write to the UDP packet buffer is the content of the structure starting at the address of the structure. 
The receiving end should copy the received data into a buffer of the same size, then cast it to the exact same struct, defined the exact same way.

Assume that the test was 2 hrs, so you only gave me 1 payload version. And that's all I have to worry about


struct2str: unsuccessful use of memcpy, return to snprintf