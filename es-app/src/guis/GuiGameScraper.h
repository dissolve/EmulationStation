#pragma once

#include "components/ScraperSearchComponent.h"
#include "components/NinePatchComponent.h"

#include "GuiComponent.h"

class GuiGameScraper : public GuiComponent
{
public:
	GuiGameScraper(Window* window, ScraperSearchParams params, std::function<void(const ScraperSearchResult&)> doneFunc);

	void onSizeChanged() override;

	bool input(InputConfig* config, Input input) override;
	void update(int deltaTime);
	virtual std::vector<HelpPrompt> getHelpPrompts() override;

private:
	bool mClose;
	void close();

	ComponentGrid mGrid;
	NinePatchComponent mBox;

	std::shared_ptr<TextComponent> mGameName;
	std::shared_ptr<TextComponent> mSystemName;
	std::shared_ptr<ScraperSearchComponent> mSearch;
	std::shared_ptr<ComponentGrid> mButtonGrid;

	ScraperSearchParams mSearchParams;

	std::function<void()> mCancelFunc;
};
