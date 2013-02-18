#pragma once

class Abacus : public ramBaseScene
{
	
	const int box_size = 20;
	const float margin = 5.0;
	const float width = 500.0;
	
	ofLight light;
	
public:
	
	Abacus() {}
	
	void setupControlPanel(ofxUICanvas* panel)
	{
		ofAddListener(panel->newGUIEvent, this, &Abacus::onValueChanged);
	}
	
	void setup()
	{
		light.setPosition(300, 0, 300);
	}
	
	void update()
	{
		
	}
	
	void draw()
	{
		ramBeginCamera();
		
		light.enable();
		glEnable(GL_DEPTH_TEST);
		
		int numNodeArrays = getNumNodeArray();
		
		for(int i=0; i<numNodeArrays; i++)
		{
			drawAbacus(getNodeArray(i), i, numNodeArrays);
		}
		
		ramEndCamera();
	}
	
	void drawActor(ramActor& actor)
	{
		
	}
	
	void drawRigid(ramRigidBody &rigid)
	{
		
	}
	
	void onValueChanged(ofxUIEventArgs& e)
	{
		
	}
	
	const string getName() { return "Abacus"; }
	
	
	
#pragma mark - 
	
	
	
	void drawAbacus(ramNodeArray& nodeArray, int index, int numNodeArrays)
	{
		const int numNodes = nodeArray.getNumNode();
		
		ofColor c1 = ramColor::BLUE_DEEP;
		ofColor c2 = ramColor::GREEN_DEEP;
		
		glTranslatef(0.0, -(margin+box_size) * numNodes / 2, 0.0);
		
		ofPushStyle();
		for(int i=0; i<numNodes; i++)
		{
			glPushMatrix();
			ramNode& node = nodeArray.getNode(i);
			ofVec3f pos = node.getGlobalPosition();
			
			pos.y = i*margin + i*box_size;
			pos.z = 0;
			
			ofSetColor(i%2==0 ? c1 : c2);
			ofSetLineWidth(2);
			ofLine(ofVec3f(-width, pos.y, 0), ofVec3f(width, pos.y, 0));
			
			glTranslatef(width*2/(numNodeArrays+1)*(index+1) - width, 0, 0);
			ofBox(pos, box_size);
			
			glPopMatrix();
		}
		ofPopStyle();
	}
};