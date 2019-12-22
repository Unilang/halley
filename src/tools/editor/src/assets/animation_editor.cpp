#include "animation_editor.h"
#include "halley/tools/project/project.h"
using namespace Halley;

AnimationEditor::AnimationEditor(UIFactory& factory, Resources& resources, Project& project, const String& animationId)
	: UIWidget("animationEditor", {}, UISizer())
	, factory(factory)
	, project(project)
{
	animation = resources.get<Animation>(animationId);
	setupWindow();

	/*
	Metadata meta = project.getMetadata(AssetType::Animation, animationId).get();
	Logger::logInfo("Reading pivot " + toString(Vector2i(meta.getInt("pivotX", 0), meta.getInt("pivotY", 0))));
	meta.set("pivotX", 42);
	project.setMetaData(AssetType::Animation, animationId, meta);
	*/
}

void AnimationEditor::setupWindow()
{
	add(factory.makeUI("ui/halley/animation_editor"), 1);
	const auto bounds = Rect4f(animation->getBounds());

	auto animationDisplay = getWidgetAs<UIAnimation>("display");
	animationDisplay->getPlayer().setAnimation(animation);
	animationDisplay->setMinSize(bounds.getSize());
	animationDisplay->setOffset(-bounds.getTopLeft());

	auto sequenceList = getWidgetAs<UIDropdown>("sequence");
	sequenceList->setOptions(animation->getSequenceNames());

	auto directionList = getWidgetAs<UIDropdown>("direction");
	directionList->setOptions(animation->getDirectionNames());

	setHandle(UIEventType::DropboxSelectionChanged, "sequence", [=] (const UIEvent& event)
	{
		animationDisplay->getPlayer().setSequence(event.getData());
	});

	setHandle(UIEventType::DropboxSelectionChanged, "direction", [=] (const UIEvent& event)
	{
		animationDisplay->getPlayer().setDirection(event.getData());
	});
}