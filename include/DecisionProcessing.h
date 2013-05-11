#pragma once

#include "Container.h"
#include "Processing.h"

/**
 * Classe interface hérité de l'interface Processing. Toutes les méthodes de prise de décision
 * doivent hériter de cette classe. Cette classe n'a pas besoin d'être modifiée.
 **/

class DecisionProcessing : public Processing
{
public:
	DecisionProcessing(void);
	~DecisionProcessing(void);
	

	virtual void run(Container&) = 0;
};

