# smart_home
A system of individual components to automate the control in a single building function.
Using agents to represent hardware components, a user can customize his own agent class to fit his hardware needs.
By using a Thread Pool and TCP data communication, Agents can publish events which other agents (that are registered to them) will receive.
Registration to event is done by choosing the type and location of the event to register to.

# example
This example demonstrate the use of event distribution system.
An event is published by an agent representing a smoke detector, and received at an agent representing a sprinkler, which had been registed to the smoke event.

# how to use this code?
1. It is recommended to use Linux OS to compile and run this program, otherwise some issues may occur due to unsupported libraries.
2. Download the the repository.
3. Open terminal and navigate to test/smart_home.
4. Open a second terminal and navigate to test/smart_home_tcp_client.
5. On the first terminal, write the following command: "make clean check".
6. Wait until a test GUI apears - this means the server is now running.
7. On the second terminal, write the following command "make clean check".
8. Wait until you see the program output on the terminal.
9. Output should include:
a. Terminal-1: prints called by the main thread which accepts the connection request from both agents (sensor, sprinkler) and the event published by the sensor.
b. Terminal-1: More prints called by the thread executing the event routing to the the sprinkler.
c. Terminal-2: The event details and data load received at the agent representing the sprinkler.
