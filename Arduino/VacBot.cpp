class VacBot()


VacBot::AlignToHeading(int desiredHeading)
{
	int err;
	float errRad;
	
	// Take heading
	//object.omega => Vitesse en rotation
	// Si n'existe pas : utiliser positionnement pas à pas ?
	// ou plutôt afficher erreur ? ou prendre valeur par défaut ?
	err = desiredHeading - m_heading;
	// Puis mettre en pause ? ou gérer durée ?
	
	// Combien de temps va mettre le bot a s'aligner ?
	errRad = deg2rad(err);
	m_timeToStop = errRad/m_wheelSpdEst;
	
	

}