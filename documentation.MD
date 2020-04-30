# Final Design Documentation (Coding) -- Section 5
## Detailed Description (provide code/code images)

Q. How will your design function?

The embedded system has x essential functions:
1. to acquire accelerometer z axis acceleration data
        1.1 with a rolling buffer, allowing the system to record pre-impact data
        2.2 on z-axis HIGH interrupt event, allowing the system to record post-impact data
2. to acquire GPS latitude and longitude
3. to acquire date and time of record acquisition
4. to acquire environmental temperature, humidity, and pressure data
5. to temporarily save data locally in CSV format
6. to upload local data to permanent web database

Given that the device is attached to a vehicle, it is important that the device
changes its behaviour depending on the STATE of the vehicle.

The vehicle STATE is selected based upon the SPEED of the vehicle. The vehicle
speed is identfied using the GPS.

CODE:
gps.getGroundSpeed -> vehicle speed
CODE

THREE vehicle states have been associated with the respecitve device behaviours
implemented with software:
1. MOVING -> the device acquires data from the acceleromter, GPS, and
environmental sensors.
        1.1 Impact events generating an accelerometer z-axis HIGH interrupt
        event are immediately recorded and saved to local SD storage.
        1.2 Non-Impact data (identfied as "travel" data) is periodically
        saved and placed into a buffer until the buffer is full. When the
        buffer is full, the buffer is recorded to a unique file in CSV format.
2. IDLE -> the device attempts to establish a WiFi connection to a known network
and upload local data to permenant web database.
        2.1 If no wifi connection is established, the device will NOT upload
        files.
        2.2 If any data uploaded in a file is NOT successful -> HTTP code != 200
        the file is NOT uploaded or archived, and the next file will be attempt

## As many detailed hand sketches and drawings (production -> buffer -> consumption)
## Summary of Specifications (device dimensions, measurements, weight, material info, electrical, etc)
## Material/Tools List (Components, etc)