#pragma once

class I_Component {
public:
	virtual ~I_Component() = default;
	
	virtual void receive(int message) = 0; // TODO: Need to advance this to accept specific messages etc
	virtual void activate() = 0;
	virtual void deactivate() = 0;
};