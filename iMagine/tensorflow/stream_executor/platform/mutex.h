/* Copyright 2015 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_STREAM_EXECUTOR_PLATFORM_MUTEX_H_
#define TENSORFLOW_STREAM_EXECUTOR_PLATFORM_MUTEX_H_

#include "tensorflow/core/platform/mutex.h"
#include "tensorflow/core/platform/types.h"

#if defined(PLATFORM_GOOGLE)
#include "tensorflow/stream_executor/platform/google/mutex.h"
#else
#include "tensorflow/stream_executor/platform/default/mutex.h"
#endif

#endif  // TENSORFLOW_STREAM_EXECUTOR_PLATFORM_MUTEX_H_
