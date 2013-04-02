#include "PlaybackSegment.h"

#pragma mark -
#pragma mark constructor, destructor

PlaybackSegment::PlaybackSegment(string segmentName)
{
    name = segmentName;
    
	init();
	
	btnHideActor = new ofxUIImageToggle(32, 32, &bHideActor, ramToResourcePath("Images/show.png"),"show");
	btnPlayActor = new ofxUIImageToggle(32, 32, &bPlaying, ramToResourcePath("Images/play.png"),"play");
	btnCueActor = new ofxUIImageButton(32, 32, &bNeedsResetPos, ramToResourcePath("Images/reset.png"),"cue");
	btnDeleteActor = new ofxUIImageButton(32, 32, false, ramToResourcePath("Images/delete.png"),"delete");
}

PlaybackSegment::~PlaybackSegment()
{
	delete btnHideActor;
	delete btnPlayActor;
	delete btnCueActor;
	delete btnDeleteActor;
}




#pragma mark -
#pragma mark public methods
ramActorUISegmentType PlaybackSegment::getType()
{
    return RAM_UI_SEGMENT_TYPE_PLAYBACK;
}

void PlaybackSegment::update()
{
	session.updatePlayhead();
}

ofxUICanvasPlus* PlaybackSegment::createPanel(const string targetName)
{
    name = targetName;
    
	const float width = ramGetGUI().kLength;
	const float height = ramGetGUI().kDim+3;
	
	
	ofxUICanvasPlus *child = new ofxUICanvasPlus();
	child->disableAppDrawCallback();
	child->disableAppEventCallbacks();
	child->disableKeyEventCallbacks();
	child->disableMouseEventCallbacks();
	
	
	/// section title
	child->addWidgetDown(new ofxUILabel(name, OFX_UI_FONT_MEDIUM));
	child->addSpacer(width, 2);
	
	
	/// Icons
	child->addWidgetDown(btnHideActor);
	child->addWidgetRight(btnPlayActor);
	child->addWidgetRight(btnCueActor);
	child->addWidgetRight(btnDeleteActor);
	
	
	/// actor color
	child->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	child->addSlider("R", 0, 1, &jointColor.r, 43, height);
	child->addSlider("G", 0, 1, &jointColor.g, 43, height);
	child->addSlider("B", 0, 1, &jointColor.b, 43, height);
	child->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	
    //	child->addWidgetDown(sliderProgress);
    //	child->addSlider("Progress", 0, src.getDuration(), &progress, width, height);
	
	child->autoSizeToFitWidgets();
	
	ofAddListener(child->newGUIEvent, this, &PlaybackSegment::onValueChanged);
	
	return child;
}

//void PlaybackSegment::setVisible(const bool value)
//{
//	bHideActor = value;
//}
//
//void PlaybackSegment::setPlay(const bool value)
//{
//	if (!value)
//		session.play();
//	else
//		session.stop();
//}
//
//void PlaybackSegment::cue()
//{
//	session.setPlayhead(0);
//}


#pragma mark -
#pragma mark Events

void PlaybackSegment::onValueChanged(ofxUIEventArgs& e)
{
	const string widgetName = e.widget->getName();
	
	
	if (widgetName == "show")
	{
//		ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;
//		const bool value = toggle->getValue();
//		setVisible(value);
	}
    
	if (widgetName == "play")
	{
//		ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;
//		const bool value = toggle->getValue();
//		setPlay(value);
	}
    
	if (widgetName == "cue")
	{
//		cue();
	}
    
	if (widgetName == "delete")
	{
//		parent->removeControlSegment(session.getNodeArrayName());
	}
	
	saveCache();
}




#pragma mark -
#pragma mark private methods

void PlaybackSegment::init()
{
    BaseSegment::init();
}

