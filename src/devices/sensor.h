#pragma once

/* Interface */ class Sensor
{
        public:
                ~Sensor() {};

                /*
                 * Access the output registers and write the raw-typed data
                 * to private variables of this sensor.
                 *
                 * The data will be input and stored by the relevant controllers.
                 */
                virtual void read() = 0;

                /*
                 * Access the configuration registers and writes the chosen
                 * hexadecimal configuration values.
                 */
                virtual void configure() = 0;

                /*
                 * Access the status registers and write the states to private
                 * variables of this sensor.
                 *
                 * The states of this sensor will be passed to the controller
                 * and thrown as an event.
                 */
                virtual void status() = 0;
        private:
                Sensor& operator = (const Sensor&);
};
