#include <vector>
#include <memory>

struct TextureDesc {

};

struct BufferDesc {

};

struct RenderPipelineDesc {

};

struct ShaderDesc {

};

class Window;

class RenderDevice {
public:
	RenderDevice();
	~RenderDevice();

	// Init
	bool Initialize(const Window& window);
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
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};