
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Exceptions.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 05/05/2019.
 */

#ifndef _ProjectMobius_hpp_RenderServer_Window_Exceptions
#define _ProjectMobius_hpp_RenderServer_Window_Exceptions

#include <exception>

namespace Mobius {
namespace Render {
namespace Window {

/**
 * Base exception of all the WindowManager's exceptions.
 * Facilitates the catching of all errors.
 */
class Exception : public std::exception {
    // ---  Methods ---
        // -- Public Methods --
        public:
            /**
             * Class constructor.
             * Allows a more granulous explanation of the problem.
             *
             * @param message The message to display in the logs.
             */
            Exception(const char * message);
    
        // -- Private Methods --
            /**
             * Returns the message to the exception handler.
             * Adds a few more details to the exception.
             *
             * @return The message of the exception.
             */
            virtual const char * what() const throw();
    // --- /Methods ---
    
    // ---  Attributes ---
        // -- Private Attributes --
            /** Stores the detailed message of the exception. */
            const char * _message;
    // --- /Attributes ---
};

/**
 * Thrown by the manager whenever a window identifier is invalid.
 * This could be due to a duplicate in the creation or a non existing query.
 */
class InvalidIDException : public Exception { using Exception::Exception; };

/**
 * Thrown if an error arose during the window creation.
 * This can happen and is represented by the said function returning an invalid descriptor.
 */
class CreationException : public Exception { using Exception::Exception; };

/**
 * Thrown if an error arose during the window query.
 * This can happen and is represented by the said function returning an invalid descriptor.
 */
class QueryException : public Exception { using Exception::Exception; };

/**
 * Thrown if the parsing of the config node went wrong.
 * More details must be passed for the error to be comprehensible.
 */
class ParsingException : public Exception { using Exception::Exception; };

}
}
}

#endif /* _ProjectMobius_hpp_RenderServer_Window_Exceptions */
