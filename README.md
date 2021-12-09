# smart_home
A system of individual components to automate the control in a single building function.
Using agents to represent hardware components, a user can customize his own agent class to fit his hardware needs.
By using a Thread Pool and TCP data communication, Agents can publish events which other agents (that are registered to them) will receive.
Registration to event is done by choosing the type and location of the event to register to.

# example
This example demonstrate the use of event distribution system.
An event is published by an agent representing a smoke detector, and received at an agent representing a sprinkler, which had been registed to the smoke event.

# how to use
1. It is recommended to use Linux OS to compile and run this program, otherwise some issues may occur due to unsupported libraries.
2. Download the the repository.
3. Hold "ctrl" + "alt" + "t" to open terminal.
4. Type "cd <YOUR DOWNLOAD PATH>/smart_home/test/hub" to navigate to the makefile.
5. Type "make clean check" to generate new executable and run the hub. 
6. Wait until a test GUI apears - this means the server is now running.
7. Repeat stages 3 - 5 with the path "cd <YOUR DOWNLOAD PATH>/smart_home/test/smart_home_tcp_client". Make sure you do not close the first terminal.
8. Wait until you see the program output on the terminal.
9. Output should include:<br />
  a. Terminal-1: prints called by main thread which accepts the connection requests from agents(sensor, sprinkler) and receive event &nbsp;&nbsp;&nbsp;&nbsp;published by the sensor.<br />
  b. Terminal-1: More prints called by the thread executing the event routing to the the sprinkler.<br />
  c. Terminal-2: The event details and data load received at the agent representing the sprinkler.
