#ifndef GLES3JNI_CAMERAINTERFACE_H
#define GLES3JNI_CAMERAINTERFACE_H

#include<stdint.h>
#include<GLES3/gl32.h>

void StartVirtualCameraInterface();                         ///<启用虚拟摄像头
void StopVirtualCameraInterface();                          ///<停用虚拟摄像头

void GetVirtualCameraSize(uint32_t &w,uint32_t &h);         ///<获取虚拟摄像头画面的尺寸

bool VirtualCamera2Texture(const GLuint texture_id);
bool Texture2VirtualCamera();

#endif //GLES3JNI_CAMERAINTERFACE_H
