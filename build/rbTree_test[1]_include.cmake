if(EXISTS "/Users/lorenzoesposito/Desktop/università/sda/rbTrees/build/rbTree_test[1]_tests.cmake")
  include("/Users/lorenzoesposito/Desktop/università/sda/rbTrees/build/rbTree_test[1]_tests.cmake")
else()
  add_test(rbTree_test_NOT_BUILT rbTree_test_NOT_BUILT)
endif()
