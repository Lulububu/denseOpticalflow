#pragma once

#include "Container.h"
#include "Processing.h"

/**
 * Classe interface hérité de l'interface Processing. Toutes les méthodes de détection
 * doivent hériter de cette classe. Cette classe n'a pas besoin d'être modifiée.
 **/

class DetectionProcessing : public Processing
{
public:
	DetectionProcessing(void);
	~DetectionProcessing(void);
	

	virtual void run(Container&) = 0;

};

