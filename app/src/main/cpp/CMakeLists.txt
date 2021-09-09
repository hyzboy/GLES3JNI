cmake_minimum_required(VERSION 3.4.1)
# set targetPlatform, will be passed in from gradle when this sample is completed
# openGL Supportability
# platform         status
#   (0 12)           ES2/ES3 not supported
#   [12, 18)         ES2 only; for ES3, app do dynamic load/detection
#                    this applies to the situations that:
#                        - minimum API is set to less than 18. In this case
#                          there is no ES3 header/lib support inside NDK
#                        - the built APK might be running on newer API phones
#                    with dynamic loading of ES3, the same APK would still be able
#                    to use ES3. Otherwise, app would stuck with ES2 even phone is
#                    is newer than the minimum API level (for example, Android-27 etc).
#
#   [18, 24)         ES2 & ES3
#                    If app is built to only support API-18 or later,
#                    set minimum api level to 18 is good enough, NDK supprts ES3
#                    with the right header and lib files. No need to use ES3 dynamic
#                    detection.
#   [24, infinite)   ES2 & ES3 & Vulkan

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")

add_library(gles3jni SHARED
            gles3jni.cpp
            RendererES3.cpp
            GLClass.cpp
            ShaderModule.cpp
            ShaderModuleCreater.cpp
            SMDrawTexture.cpp
            GLFloatBuffer.cpp
            RenderLayout.cpp
            QuadUV.cpp
            GLTexture.cpp
            DrawObject.cpp
            DrawBitmap.cpp
            CameraInterface.cpp)

# Include libraries needed for gles3jni lib
target_link_libraries(gles3jni
            GLESv3
            android
            EGL
            log
            m
        )

add_library(lib_oglsystem STATIC IMPORTED)
set_target_properties(lib_oglsystem PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../../libs/${ANDROID_ABI}/openglsystem.a)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libyuv/include)

SET(LIBYUV_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libyuv/source)

SET(LIBYUV_SOURCE
        ${LIBYUV_PATH}/compare.cc
        ${LIBYUV_PATH}/compare_common.cc
        ${LIBYUV_PATH}/compare_neon64.cc
        ${LIBYUV_PATH}/convert.cc
        ${LIBYUV_PATH}/convert_argb.cc
        ${LIBYUV_PATH}/convert_from.cc
        ${LIBYUV_PATH}/convert_from_argb.cc
        ${LIBYUV_PATH}/convert_jpeg.cc
        ${LIBYUV_PATH}/convert_to_argb.cc
        ${LIBYUV_PATH}/convert_to_i420.cc
        ${LIBYUV_PATH}/cpu_id.cc
        ${LIBYUV_PATH}/mjpeg_decoder.cc
        ${LIBYUV_PATH}/mjpeg_validate.cc
        ${LIBYUV_PATH}/planar_functions.cc
        ${LIBYUV_PATH}/rotate.cc
        ${LIBYUV_PATH}/rotate_any.cc
        ${LIBYUV_PATH}/rotate_argb.cc
        ${LIBYUV_PATH}/rotate_common.cc
        ${LIBYUV_PATH}/rotate_neon64.cc
        ${LIBYUV_PATH}/row_any.cc
        ${LIBYUV_PATH}/row_common.cc
        ${LIBYUV_PATH}/row_neon64.cc
        ${LIBYUV_PATH}/scale.cc
        ${LIBYUV_PATH}/scale_any.cc
        ${LIBYUV_PATH}/scale_argb.cc
        ${LIBYUV_PATH}/scale_common.cc
        ${LIBYUV_PATH}/scale_neon64.cc
        ${LIBYUV_PATH}/scale_uv.cc
        ${LIBYUV_PATH}/video_common.cc)

add_library(vci SHARED vci.cpp ${LIBYUV_SOURCE})
target_link_libraries(vci
                        android
                        m
                        lib_oglsystem)
