#include "storage.h"

void setup()
{
        // Setup debugging.
        delay(1000);  // UNIX
        Serial.begin(115200);  // debugging

        /** @test **/
        Storage storage;
        storage.mkdir("/today");
        //storage.mkdir("/today/impacts");
        //storage.write("/today/impacts/HHMMSSss.imp", "some impact data");
        //storage.mkdir("/uploaded");
        //String *out;
        //storage.read("/today/impacts/HHMMSSss.imp", out);
        //storage.mv("/today/impacts/HHMMSSss.imp", "/uploaded/HHMMSSss.imp");
        //storage.rm("/uploaded/HHMMSSss.imp");


        //const int buffer_len = 10;
        //String buffer[buffer_len];
        //for (int i = 0; i < buffer_len; i++) {
                //buffer[i] = "Message ";
                //buffer[i] += i;
        //}
        //storage.write("/today/travel/HHMMSS.trv", buffer, buffer_len);
}

void loop()
{

}
