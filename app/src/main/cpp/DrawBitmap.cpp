#include "DrawBitmap.h"
#include "ShaderModule.h"
#include "GLTexture.h"

DrawBitmap::DrawBitmap(GLTexture *tex):DrawObject("DrawBitmap")
{
    texture=tex;

    shader=GetShaderModule(InlineShader::SimpleTexture);

    blend=false;
}

void DrawBitmap::Start()
{
    BindVAO();

    texture->Bind(shader->GetTextureLocation());
    render_layout.BindToShader(shader->GetPositionLocation());
    texture_uv.BindToShader(shader->GetTexCoordLocation());
}

void DrawBitmap::Draw()
{
    if(blend)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
        glDisable(GL_BLEND);
    }

    shader->Begin();

        BindVAO();

        glDrawArrays(GL_TRIANGLE_STRIP,0,4);

        texture->Unbind(shader->GetTextureLocation());

        UnbindVAO();

    shader->End();

    glDisable(GL_BLEND);
}