if(WITH_CUSTOM_DEVICE)
  cc_library(
    custom_context
    SRCS custom_context.cc
    DEPS phi_device_context device_manager)
  cc_library(
    custom_device
    SRCS custom_device.cc
    DEPS device_base device_context)
  cc_test(
    custom_device_test
    SRCS custom_device_test.cc
    DEPS device_manager device_context)
endif()
