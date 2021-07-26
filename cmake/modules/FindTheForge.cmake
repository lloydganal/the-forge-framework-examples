FIND_PATH(THEFORGE_OS_INCLUDE_DIR "lag/lagbase.hpp"
  PATHS
  ../lag-base/include
  PATH_SUFFIXES 
  DOC "lagbase - Headers"
)

FIND_LIBRARY(THEFORGE_OS_LIBRARY NAMES OS
  PATHS
  ../lag-base/builds/current/lib/${CMAKE_BUILD_TYPE}
  PATH_SUFFIXES lib
  DOC "lagbase - Library"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LAGBase DEFAULT_MSG LAGBASE_LIBRARY LAGBASE_INCLUDE_DIR)