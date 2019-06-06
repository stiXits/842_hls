#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_POSIX_SIGNALS

#include "Catch2/single_include/catch2/catch.hpp"

int main( int argc, char* argv[] ) {
  // global setup...

  int result = Catch::Session().run( argc, argv );

  // global clean-up...

  return result;
}
