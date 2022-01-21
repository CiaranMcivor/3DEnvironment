#include "GBuffer.h"

void GBuffer::init(float screenWidth, float screenHeight)
{
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    // position color buffer
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
    // normal color buffer
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
    // color + specular color buffer
    glGenTextures(1, &gDiffSpec);
    glBindTexture(GL_TEXTURE_2D, gDiffSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gDiffSpec, 0);
    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
    glDrawBuffers(3, attachments);

    // create a renderbuffer object for depth and stencil attachment 
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth, screenHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer); // now actually attach it

    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        std::cout << "FRAMEBUFFER:: Framebuffer is complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    loadTextures();
}

void GBuffer::loadTextures()
{
    //normals.init("..\\res\\backpack\\normal.png");
    //normals.Bind(1);
    diffuse.init("..\\res\\backpack\\diffuse.jpg");
    specular.init("..\\res\\backpack\\specular.jpg");

    lightingPassShader.Bind();
    // send light relevant uniforms
    lightingPassShader.setInt("gPosition", 0);
    lightingPassShader.setInt("gNormal", 1);
    lightingPassShader.setInt("gDiffSpec", 2);

}

void GBuffer::initShader()
{
    geometryPassShader.init("..\\res\\gBuffer.vert", "..\\res\\gBuffer.frag");
    lightingPassShader.init("..\\res\\lightingPass.vert", "..\\res\\lightingPass.frag");
}

void GBuffer::bind()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GBuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::generateQuad()
{
    float quadVertices[] = {
        // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f

         // vertex attributes for a quad that fills the half of the screen
         //-0.5f,  0.5f,  0.0f, 1.0f,
         //-0.5f, -0.5f,  0.0f, 0.0f,
         // 0.5f, -0.5f,  1.0f, 0.0f,

         //-0.5f,  0.5f,  0.0f, 1.0f,
         // 0.5f, -0.5f,  1.0f, 0.0f,
         // 0.5f,  0.5f,  1.0f, 1.0f
    };
    // cube VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    
}

void GBuffer::geometryPass(GameObject* object, Camera* camera)
{
    geometryPassShader.Bind();
    geometryPassShader.setMat4("view", camera->getView());
    geometryPassShader.setMat4("projection", camera->getProjection());
    for (int i = 0; i < 3; i++) {
        object[i].getDiffuse()->Bind(4);
        geometryPassShader.setInt("diffuse", 4);
        object[i].getSpecular()->Bind(3);
        geometryPassShader.setInt("specular", 3);
        geometryPassShader.setMat4("model", object[i].getTransform().GetModel());

        object[i].draw();
    }
}

void GBuffer::lightingPass(Camera* camera)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    lightingPassShader.Bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gDiffSpec);


    // send light relevant uniforms

    lightingPassShader.setVec3("light.Position", glm::vec3(20, 20,-20));
    lightingPassShader.setVec3("light.Color", glm::vec3(255,255,255));
    // update attenuation parameters and calculate radius
    const float linear = 0.7f;
    const float quadratic = 0.9f;
    lightingPassShader.setFloat("light.Linear", linear);
    lightingPassShader.setFloat("light.Quadratic", quadratic);

    lightingPassShader.setVec3("viewPos", camera->getPos());
}

void GBuffer::render()
{
    //Geometry pass: load scene's geometry/color data into gbuffer
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);


}
