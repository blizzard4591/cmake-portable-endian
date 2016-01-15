# cmake-portable-endian
Uses CMake to check local endian and generates a C header file containing endian-conversion methods.

### Motivation
Trying to write non-platform dependent code in C or C++ is a pain. 
Many protocols or applications require conversions to and from different endian-types.
This CMake bases solutions trys very hard to solve all these issues by providing a simple C header file to be included in your main project.

### Usage
 * If your project uses CMake:
   Add this git repository as a submodule or copy a checkout into your project.
   Use ```add_subdirectory``` in your CMakeLists.txt to execute the CMake scripts, then add ```include_directories``` to include the binary directory where the header file is generated.
   Add ```#include "endianness_config.h"``` in your code.
   
 * If your project does not use CMake:
   Since the header file needs to be generated on each host that will build your application, generating it once is not really a portable option.
   So you can either change your projects workflow to use CMake instead of traditional Makefiles, or you can build a script around this to run CMake as part of your build process.
   
   
### Contents

```endianness_config.h``` defines a large set of functions.

A default set of functions derived from OpenBSDs ```endian.h```-style functions:
* htobe16
* htole16
* betoh16
* letoh16

* htobe32
* htole32
* betoh32
* letoh32

* htobe64
* htole64
* betoh64
* letoh64
 
* htobe16
* htole16
* betoh16
* letoh16

If you do not use the option ```ENDIANNESS_FORCE_NON_SYSTEM_IMPLEMENTATION```, these functions will use system-provided implementations, if available.
If you are unsure, use these functions.
 
The custom, non-system dependant functions, which are defined using values figured out during the CMake tests.
This set of functions will be used to back the macros mentioned above if no suitable system implementation is found, or the option ```ENDIANNESS_FORCE_NON_SYSTEM_IMPLEMENTATION``` is set in CMake.

* uint16_t to_little_endian16(uint16_t value)
* uint16_t to_big_endian16(uint16_t value)
* uint16_t from_little_endian16(uint16_t value)
* uint16_t from_big_endian16(uint16_t value)

* uint32_t to_little_endian32(uint32_t value)
* uint32_t to_big_endian32(uint32_t value)
* uint32_t from_little_endian32(uint32_t value)
* uint32_t from_big_endian32(uint32_t value)

* uint64_t to_little_endian64(uint64_t value)
* uint64_t to_big_endian64(uint64_t value)
* uint64_t from_little_endian64(uint64_t value)
* uint64_t from_big_endian64(uint64_t value)
