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
	void Initialize();
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