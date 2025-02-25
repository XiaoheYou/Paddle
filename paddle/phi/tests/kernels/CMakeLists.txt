cc_test(
  test_copy_dev_api
  SRCS test_copy_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_dot_dev_api
  SRCS test_dot_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_creation_dev_api
  SRCS test_creation_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_flatten_dev_api
  SRCS test_flatten_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_matmul_dev_api
  SRCS test_matmul_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_mean_dev_api
  SRCS test_mean_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_scale_dev_api
  SRCS test_scale_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_cast_dev_api
  SRCS test_cast_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_elementwise_dev_api
  SRCS test_elementwise_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_reshape_dev_api
  SRCS test_reshape_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_sum_dev_api
  SRCS test_sum_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_conj_dev_api
  SRCS test_conj_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_concat_dev_api
  SRCS test_concat_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_split_dev_api
  SRCS test_split_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_sparse_utils_dev_api
  SRCS test_sparse_utils_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_sparse_conv3d_dev_api
  SRCS test_sparse_conv3d_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_sparse_pool_dev_api
  SRCS test_sparse_pool_dev_api.cc
  DEPS phi phi_api_utils)
cc_test(
  test_sparse_activation_dev_api
  SRCS test_sparse_activation_dev_api.cc
  DEPS phi phi_api_utils)

cc_test(
  test_math_function
  SRCS test_math_function.cc
  DEPS math_function)
if(WITH_GPU)
  nv_test(
    test_math_function_gpu
    SRCS test_math_function.cu
    DEPS math_function)
endif()
if(WITH_ROCM)
  hip_test(
    test_math_function_gpu
    SRCS test_math_function.cu
    DEPS math_function)
endif()

cc_test(
  test_cpu_vec
  SRCS test_cpu_vec.cc
  DEPS blas cpu_info)

# For String Kernels
cc_test(
  test_strings_lower_upper_dev_api
  SRCS test_strings_lower_upper_dev_api.cc
  DEPS phi phi_api_utils)
if(WITH_GPU)
  nv_test(
    test_strings_lower_upper_dev_gpu_api
    SRCS test_strings_lower_upper_dev_api.cu
    DEPS phi phi_api_utils)
elseif(WITH_ROCM)
  hip_test(
    test_strings_lower_upper_dev_gpu_api
    SRCS test_strings_lower_upper_dev_api.cu
    DEPS phi phi_api_utils)
endif()

cc_test(
  test_strings_copy_dev_api
  SRCS test_strings_copy_dev_api.cc
  DEPS phi phi_api_utils)
if(WITH_GPU)
  nv_test(
    test_strings_copy_dev_gpu_api
    SRCS test_strings_copy_dev_api.cu
    DEPS phi phi_api_utils)
elseif(WITH_ROCM)
  hip_test(
    test_strings_copy_dev_gpu_api
    SRCS test_strings_copy_dev_api.cu
    DEPS phi phi_api_utils)
endif()
