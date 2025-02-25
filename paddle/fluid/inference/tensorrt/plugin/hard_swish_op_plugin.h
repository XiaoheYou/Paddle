// Copyright (c) 2019 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#include <stdio.h>

#include <cassert>
#include <string>
#include <vector>

#include "paddle/fluid/inference/tensorrt/engine.h"
#include "paddle/fluid/inference/tensorrt/plugin/trt_plugin.h"

namespace paddle {
namespace inference {
namespace tensorrt {
namespace plugin {

class HardSwishPlugin : public PluginTensorRT {
 public:
  HardSwishPlugin(const float threshold, const float scale, const float offset)
      : threshold_(threshold), scale_(scale), offset_(offset) {}

  // It was used for tensorrt deserialization.
  // It should not be called by users.
  HardSwishPlugin(void const* serialData, size_t serialLength) {
    deserializeBase(serialData, serialLength);
    DeserializeValue(&serialData, &serialLength, &threshold_);
    DeserializeValue(&serialData, &serialLength, &scale_);
    DeserializeValue(&serialData, &serialLength, &offset_);
  }

  ~HardSwishPlugin() {}
  HardSwishPlugin* clone() const TRT_NOEXCEPT override {
    return new HardSwishPlugin(threshold_, scale_, offset_);
  }

  const char* getPluginType() const TRT_NOEXCEPT override {
    return "hard_swish_plugin";
  }
  int getNbOutputs() const TRT_NOEXCEPT override { return 1; }
  int initialize() TRT_NOEXCEPT override { return 0; }
  nvinfer1::Dims getOutputDimensions(int index, const nvinfer1::Dims* inputs,
                                     int nbInputDims) TRT_NOEXCEPT override;
#if IS_TRT_VERSION_LT(8000)
  int enqueue(int batchSize, const void* const* inputs, void** outputs,
#else
  int enqueue(int batchSize, const void* const* inputs, void* const* outputs,
#endif
              void* workspace, cudaStream_t stream) TRT_NOEXCEPT override;

  size_t getSerializationSize() const TRT_NOEXCEPT override {
    return getBaseSerializationSize() + SerializedSize(threshold_) +
           SerializedSize(scale_) + SerializedSize(offset_);
  }

  // TRT will call this func  to serialize the configuration of TRT
  // It should not be called by users.
  void serialize(void* buffer) const TRT_NOEXCEPT override {
    serializeBase(buffer);
    SerializeValue(&buffer, threshold_);
    SerializeValue(&buffer, scale_);
    SerializeValue(&buffer, offset_);
  }

 protected:
  float threshold_;
  float scale_;
  float offset_;
};

class HardSwishPluginCreator : public TensorRTPluginCreator {
 public:
  const char* getPluginName() const TRT_NOEXCEPT override {
    return "hard_swish_plugin";
  }

  const char* getPluginVersion() const TRT_NOEXCEPT override { return "1"; }

  nvinfer1::IPluginV2* deserializePlugin(
      const char* name, const void* serial_data,
      size_t serial_length) TRT_NOEXCEPT override {
    return new HardSwishPlugin(serial_data, serial_length);
  }
};
REGISTER_TRT_PLUGIN_V2(HardSwishPluginCreator);

#if IS_TRT_VERSION_GE(6000)
class HardSwishPluginDynamic : public DynamicPluginTensorRT {
 public:
  HardSwishPluginDynamic(const float threshold, const float scale,
                         const float offset)
      : threshold_(threshold), scale_(scale), offset_(offset) {}

  // It was used for tensorrt deserialization.
  // It should not be called by users.
  HardSwishPluginDynamic(void const* serialData, size_t serialLength) {
    DeserializeValue(&serialData, &serialLength, &threshold_);
    DeserializeValue(&serialData, &serialLength, &scale_);
    DeserializeValue(&serialData, &serialLength, &offset_);
  }
  ~HardSwishPluginDynamic() {}
  nvinfer1::IPluginV2DynamicExt* clone() const TRT_NOEXCEPT override {
    return new HardSwishPluginDynamic(threshold_, scale_, offset_);
  }
  const char* getPluginType() const TRT_NOEXCEPT override {
    return "hard_swish_plugin_dynamic";
  }
  int getNbOutputs() const TRT_NOEXCEPT override { return 1; }
  int initialize() TRT_NOEXCEPT override { return 0; }
  nvinfer1::DimsExprs getOutputDimensions(
      int output_index, const nvinfer1::DimsExprs* inputs, int nb_inputs,
      nvinfer1::IExprBuilder& expr_builder) TRT_NOEXCEPT override;
  int enqueue(const nvinfer1::PluginTensorDesc* inputDesc,
              const nvinfer1::PluginTensorDesc* outputDesc,
              const void* const* inputs, void* const* outputs, void* workspace,
              cudaStream_t stream) TRT_NOEXCEPT override;

  size_t getSerializationSize() const TRT_NOEXCEPT override {
    return SerializedSize(threshold_) + SerializedSize(scale_) +
           SerializedSize(offset_);
  }

  // TRT will call this func  to serialize the configuration of TRT
  // It should not be called by users.
  void serialize(void* buffer) const TRT_NOEXCEPT override {
    SerializeValue(&buffer, threshold_);
    SerializeValue(&buffer, scale_);
    SerializeValue(&buffer, offset_);
  }
  nvinfer1::DataType getOutputDataType(
      int index, const nvinfer1::DataType* inputTypes,
      int nbInputs) const TRT_NOEXCEPT override;
  bool supportsFormatCombination(int pos,
                                 const nvinfer1::PluginTensorDesc* inOut,
                                 int nbInputs,
                                 int nbOutputs) TRT_NOEXCEPT override;

  void configurePlugin(const nvinfer1::DynamicPluginTensorDesc* in,
                       int nbInputs,
                       const nvinfer1::DynamicPluginTensorDesc* out,
                       int nbOutputs) TRT_NOEXCEPT override {}
  void destroy() TRT_NOEXCEPT override { delete this; }

 protected:
  float threshold_;
  float scale_;
  float offset_;
};

class HardSwishPluginDynamicCreator : public nvinfer1::IPluginCreator {
 public:
  HardSwishPluginDynamicCreator() {}
  const char* getPluginName() const TRT_NOEXCEPT override {
    return "hard_swish_plugin_dynamic";
  }

  const char* getPluginVersion() const TRT_NOEXCEPT override { return "1"; }

  const nvinfer1::PluginFieldCollection* getFieldNames() TRT_NOEXCEPT override {
    return &field_collection_;
  }

  nvinfer1::IPluginV2* createPlugin(const char* name,
                                    const nvinfer1::PluginFieldCollection* fc)
      TRT_NOEXCEPT override {
    return nullptr;
  }

  nvinfer1::IPluginV2* deserializePlugin(
      const char* name, const void* serial_data,
      size_t serial_length) TRT_NOEXCEPT override {
    auto plugin = new HardSwishPluginDynamic(serial_data, serial_length);
    return plugin;
  }

  void setPluginNamespace(const char* lib_namespace) TRT_NOEXCEPT override {
    plugin_namespace_ = lib_namespace;
  }

  const char* getPluginNamespace() const TRT_NOEXCEPT override {
    return plugin_namespace_.c_str();
  }

 private:
  std::string plugin_namespace_;
  std::string plugin_name_;
  nvinfer1::PluginFieldCollection field_collection_{0, nullptr};
  std::vector<nvinfer1::PluginField> plugin_attributes_;
};
REGISTER_TRT_PLUGIN_V2(HardSwishPluginDynamicCreator);

#endif

}  // namespace plugin
}  // namespace tensorrt
}  // namespace inference
}  // namespace paddle
