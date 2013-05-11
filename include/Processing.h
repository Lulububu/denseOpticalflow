#pragma once

#include <string>
#include <map>
/**
 * Classe mère de tous les processus pouvant être ajoutés à un AlgorithManager. 
 * Toutes les classes qui héritent de Processing peuvent charger des paramètres
 * depuis le fichier INI de configuration. Pour cela, il suffit d'implémenter
 * les méthodes getClassName() pour qu'elle renvoie un identifiant unique et 
 * la méthode setParameters() pour qu'elle initialise ses propres attributs avec 
 * les valeurs contenus dans la map. Pour plus de précisions, voir la partie
 * sur le chargement des paramètres dans la documentation.
 **/

class Processing
{
public:
	Processing(void);
	~Processing(void);

	/**
	 * Méthode à implémenter dans les classes filles renvoyant un identifiant unique correspondant 
	 * à la classe dont on veut charger les paramètres. C'est ce nom qui correspondra au nom entre 
	 * crochets dans le fichier INI.
	 * @param string Identifiant unique de la classe.
	 **/ 
	virtual std::string getClassName() = 0;

	/**
	 * Méthode à implémenter qui devra initialiser les paramètres d'une classe fille. 
	 * @param parameters Map mettant en relation l'identifiant d'un paramètre (partie gauche 
	 * d'une attribution dans le fichier INI) avec sa valeur (partie droite). La valeur de 
	 * chaque paramètre est conservée sous la forme de string pour pouvoir charger la valeur 
	 * de paramètres int, double, string, etc... Il suffit de convertir la valeur dans le bn format.
	 **/
	virtual void setParameters(std::map<std::string, std::string> parameters) = 0;

private:
	std::string className;
};

