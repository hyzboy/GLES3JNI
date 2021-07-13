#ifndef GLES3JNI_CAMERAINTERFACE_H
#define GLES3JNI_CAMERAINTERFACE_H

#include<stdint.h>

void StartVirtualCameraInterface();                         ///<启用虚拟摄像头
void StopVirtualCameraInterface();                          ///<停用虚拟摄像头

void GetVirtualCameraSize(uint32_t &w,uint32_t &h);         ///<获取虚拟摄像头画面的尺寸

class GLTexture;

bool VirtualCamera2Texture(GLTexture *);
bool Texture2VirtualCamera();

#endif //GLES3JNI_CAMERAINTERFACE_H
