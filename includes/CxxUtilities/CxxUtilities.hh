/*
 * CxxUtilities.hh
 *
 *  Created on: Jun 22, 2011
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_HH_
#define CXXUTILITIES_HH_

/** @mainpage CxxUtilities
 * @section intro Overview
 * CxxUtilities is a header-only C++ class library
 * that provides Java-like or Ruby-like utilitiy classes.
 *
 * @section install Installation and Build
 * Git repository is hosted on the github.com.
 * To install the latest source tree, execute git clone like below.
 * @code
 * git clone https://github.com/yuasatakayuki/CxxUtilities.git
 * @endcode
 *
 * cmake followed by make install will install CxxUtilities to /usr/local/include
 * by default.
 * @code
 * cd CxxUtilities
 * mkdir build
 * cd build
 * cmake ..
 * make install
 * @endcode
 *
 * If you want to change the install destination, use -DCMAKE_INSTALL_PREFIX
 * option of cmake. For example, the following cmake command will generate
 * Makefile which installs CxxUtilities/ to $HOME/include/CxxUtilities/
 * @code
 * cmake .. -DCMAKE_INSTALL_PREFIX=$HOME
 * @endcode
 *
 * To use classes defined in the CxxUtilities, just include the main
 * header file CxxUtilities/CxxUtilities.hh.
 * @code
 * #include "CxxUtilities/CxxUtilities.hh"
 * ...your source...
 * @endcode
 *
 * If you have installed the
 * library to non-default include path of your compiler, specify the
 * install path using -I option like:
 * @code
 * clang++ -I$HOME/include yourApplication.cc -o yourApplication
 * @endcode
 *
 * @section classes Classes
 *
 * - CxxUtilities/CxxUtilities.hh: top-level header file (just include this)
 * - CxxUtilities/CommonHeader.hh: includes commonly used header files like string or iostream (not for users)
 * - CxxUtilities::Action: provides action interface.
 * - CxxUtilities::Array: provides an array wrapper
 * - CxxUtilities::Bitset: provides a bitset wrapper
 * - CxxUtilities::Bitstream: provides bitstream data structure
 * - CxxUtilities::ClassInformation: provides accessors to class information
 * - CxxUtilities::CommandLineApplication: provide a template of CLI application
 * - CxxUtilities::Condition: provides Condition object (pthread_condition wrapper)
 * - CxxUtilities::Counter: provides counter for statistics within a user program
 * - CxxUtilities::Directory: provides directory access interface
 * - CxxUtilities::Env: environmental variable access interface
 * - CxxUtilities::Exception: a superclass of exceptions thrown by CxxUtilities classes
 * - CxxUtilities::File: file access interface
 * - CxxUtilities::Histogram: provides a simple histogram for statistics within a user program
 * - Interfaces: defines commonly used interfaces (Java-like)
 *   - ClassnameInterface: setClassName(string) and getClassName()
 *   - InstanceNameInterface: setInstanceName(sting) and getInstanceName()
 *   - TerminateInterface: terminate()
 * - CxxUtilities::Logger: provides text log interface
 * - CxxUtilities::Message: inter-thread communication message (pthread wrapper)
 * - CxxUtilities::Mutex: inter-thread communication message (pthread wrapper)
 * - CxxUtilities::RandomMT: MT wrapper
 * - CxxUtilities::String: string wrapper
 * - CxxUtilities::TCPSocket: provides simple TCPSocket interface (POSIX TCP socket wrapper)
 * - CxxUtilities::TerminalControl: controls terminal (text color, clear screen, etc)
 * - CxxUtilities::Thread: provides Thread class for multi threading (pthread wrapper)
 * - CxxUtilities::Time: time interface
 * - CxxUtilities::Timer: provides a timer (pthread wrapper)
 * - CxxUtilities::Verbosity: controls verbostiy (not widely used yet)
 *
 * See <a href="annotated.html">Class List</a> for complete API reference.
 *
 * @section Authors
 * <a href="https://github.com/yuasatakayuki">Takayuki Yuasa</a> and <a href="https://github.com/sakuraisoki">Soki Sakurai</a>
 * (written while they were staying at University of Tokyo, JAXA and RIKEN)
 */

#ifndef uint8_t
#include <stdint.h>
#endif

#include "CxxUtilities/CommonHeader.hh"
#include "CxxUtilities/CommandLineApplication.hh"
#include "CxxUtilities/Exception.hh"
#include "CxxUtilities/Counter.hh"
#include "CxxUtilities/String.hh"
#include "CxxUtilities/File.hh"
#include "CxxUtilities/Date.hh"
#include "CxxUtilities/Directory.hh"
#include "CxxUtilities/Logger.hh"
#include "CxxUtilities/Interfaces.hh"
#include "CxxUtilities/Time.hh"
#include "CxxUtilities/Bitset.hh"
#include "CxxUtilities/Array.hh"
#include "CxxUtilities/Mutex.hh"
#include "CxxUtilities/Message.hh"
#include "CxxUtilities/Condition.hh"
#include "CxxUtilities/Thread.hh"
#include "CxxUtilities/Timer.hh"
#include "CxxUtilities/TCPSocket.hh"

#include "CxxUtilities/TerminalControl.hh"
#include "CxxUtilities/Random.hh"
#include "CxxUtilities/Numerical.hh"

#include "CxxUtilities/Env.hh"

#include "CxxUtilities/Verbosity.hh"

#include "CxxUtilities/Histogram.hh"
#include "CxxUtilities/Bitstream.hh"

#include "CxxUtilities/FitsUtility.hh"

#ifdef CXXUTILITIES_USE_YAML
#include "yaml-cpp/yaml.h"
#endif /*CXXUTILITIES_USE_YAML*/

#endif /* CXXUTILITIES_HH_ */
