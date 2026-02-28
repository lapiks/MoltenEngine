#include <vector>

struct TextureDesc {

};

struct BufferDesc {

};

struct RenderPipelineDesc {

};

struct ShaderDesc {

};

class RenderDevice {
public:
	// Init
	bool Initialize(const std::vector<const char*>& instanceExtensions);
	void Shutdown();

	// Resources creation
	void CreateTexture();
	void CreateBuffer();
	void CreateRenderPipeline();
	void CreateShader();

	// Resources destruction
	void DestroyTexture();
	void DestroyBuffer();
	void DestroyRenderPipeline();
	void DestroyShader();

	// Drawing
	void SetRenderPipeline();
	void Draw();

private:

};