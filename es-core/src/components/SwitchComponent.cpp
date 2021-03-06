#include "SwitchComponent.h"

#include "resources/Font.h"

#include "Renderer.h"
#include "Window.h"
#include "Log.h"


SwitchComponent::SwitchComponent(Window* window, bool state) : GuiComponent(window), mImage(window), mState(state)
{
	mImage.setImage(":/off.svg");
	mImage.setResize(0, Font::get(FONT_SIZE_MEDIUM)->getLetterHeight());
	mSize = mImage.getSize();
}

void SwitchComponent::onSizeChanged()
{
	mImage.setSize(mSize);
}

std::string SwitchComponent::getValue() const
{
	return  mState ? "true" : "false";
}

void SwitchComponent::setValue(const std::string& value)
{
	if(value == "true") {
		setState(true);
	} else if(value == "false") {
		setState(false);
	} else {
		LOG(LogWarning) << "SwitchComponent setValue must be \"true\" or \"false\". Defaulting to false.";
		setState(false);
	}
}

bool SwitchComponent::input(InputConfig* config, Input input)
{
	if(config->isMappedTo("a", input) && input.value) {
		mState = !mState;
		onStateChanged();
		return true;
	}

	return false;
}

void SwitchComponent::render(const Eigen::Affine3f& parentTrans)
{
	Eigen::Affine3f trans = parentTrans * getTransform();

	mImage.render(trans);

	renderChildren(trans);
}

bool SwitchComponent::getState() const
{
	return mState;
}

void SwitchComponent::setState(bool state)
{
	mState = state;
	onStateChanged();
}

void SwitchComponent::onStateChanged()
{
	mImage.setImage(mState ? ":/on.svg" : ":/off.svg");
}

std::vector<HelpPrompt> SwitchComponent::getHelpPrompts()
{
	std::vector<HelpPrompt> prompts;
	prompts.push_back(HelpPrompt("a", "change"));
	return prompts;
}
