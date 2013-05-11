#pragma once

#include "Container.h"
#include "Processing.h"

/**
 * Classe interface hérité de l'interface Processing. Toutes les méthodes de preprocessing
 * doivent hériter de cette classe. Cette classe n'a pas besoin d'être modifiée.
 **/

class PreProcessing : public Processing
{
public:
	PreProcessing(void);
	~PreProcessing(void);
	

	virtual void run(Container&) = 0;

private:
	
};

