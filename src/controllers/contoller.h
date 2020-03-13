#pragma once

/* Interface */ class Controller
{
       public:
                ~Controller() {};

                /*
                 * Reads data from the sensors dependent upon this Controller
                 * and transforms them to the relevant entity to be imported
                 * to the use case interactor.
                 *
                 * The data is stored inside a buffer until it is full.
                 * This will throw an event and the data will be imported by
                 * the use case interactor and handled for output.
                 */
                virtual void pipe_in(void) = 0;
        private:
                Controller& operator = (const Controller&);
};
