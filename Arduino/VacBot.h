class VacBot()

methods
public 
	void alignToHeading(int desiredHeading);
	
	private
		int m_xpos;
		int m_ypos;
		int m_heading; // Bot Heading -> Deg
		
		int m_wheelSpdEst; // estimation of wheel speed rad/sec
		int m_timeToStop; // Time before stopping bot for drives use => Might be in other proc ?
		
		
		
end
