#include "..\include\BackgroundSubstract.h"


BackgroundSubstract::BackgroundSubstract()
{
}


BackgroundSubstract::~BackgroundSubstract()
{
}

void BackgroundSubstract::run(Container& cont)
{
	if(tool.updateBackgroundModel(cont.getImg()))
	{
		cont.getImg() = tool.getForeground();
	}
	
}
