#ifndef _DIS_INTEGRATE_MESH_HPP
#define _DIS_INTEGRATE_MESH_HPP

#include <KlayGE/App3D.hpp>
#include <KlayGE/Font.hpp>
#include <KlayGE/CameraController.hpp>
#include <KlayGE/PostProcess.hpp>

class DisIntegrateMeshApp : public KlayGE::App3DFramework
{
public:
	DisIntegrateMeshApp();

private:
	void OnCreate();
	void OnResize(KlayGE::uint32_t width, KlayGE::uint32_t height);

	void CreateCube();

	void DoUpdateOverlay();
	KlayGE::uint32_t DoUpdate(KlayGE::uint32_t pass);

	void InputHandler(KlayGE::InputEngine const & sender, KlayGE::InputAction const & action);

	KlayGE::FontPtr font_;

	KlayGE::SceneNodePtr renderableMesh_;
	std::vector<KlayGE::StaticMeshPtr> meshes;

	KlayGE::SceneNodePtr particles_;
	KlayGE::RenderablePtr particles_renderable_;

	KlayGE::TrackballCameraController tb_controller_;

	KlayGE::TexturePtr scene_tex_;
	KlayGE::FrameBufferPtr scene_buffer_;

	KlayGE::TexturePtr fog_tex_;
	KlayGE::FrameBufferPtr fog_buffer_;

	KlayGE::PostProcessPtr blend_pp_;
};

#endif // _DIS_INTEGRATE_MESH_HPP