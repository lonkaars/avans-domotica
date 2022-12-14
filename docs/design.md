# Asynchronous QT Serial port

The serial data communication is done in an asynchronous manner, which allows the program to efficiently handle data that is arriving on a serial port.

## Benefits
Using an asynchronous approach allows the program to efficiently handle incoming data from the serial port, while still allowing the UI to remain responsive. This also prevents the program from having to continuously poll the serial port to check for new data. Without an asynchronous approach, this could freeze the UI and consume a lot of CPU resources. By using an asynchronous approach, the application can handle incoming data as soon as it arrives, without blocking the UI or consuming excessive CPU resources.

## Data processing
When new data arrives at the serial port, it sends out a "ready read" signal. This signal tells the Qt event loop to call the asynchronous serial data read function, which processes the data at the next available opportunity. This ensures that the data is handled efficiently and asynchronously, without blocking the UI or consuming excessive CPU resources.

# General system architecture (loek)
# Custom serial protocol (loek)
# Multitasking on nodes (niels)

# Used software and library versions ()
