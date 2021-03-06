/****************************************************************************
* Fichier: GestionnaireAuteurs.cpp
* Auteur : Aldric Lopez et Juliette Morin
* Date :  12 févr. 2020
* Mise a jour : 29 févr. 2020
* Description : Implémentation de la classe GestionnaireAuteurs
* ***************************************************************************/

#include "GestionnaireAuteurs.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

//! Constructeur de la classe GestionnaireAuteurs
GestionnaireAuteurs::GestionnaireAuteurs(): auteurs_(std::vector<Auteur>(NB_AUTEURS_MAX))
{
}


//! Méhode qui cherche un auteur par son nom complet
//! \param nomAuteur Le nom de l'auteur à trouver
//! \return          Un pointeur vers l'auteur. Le pointeur est nullptr si l'auteur n'existe pas.
Auteur* GestionnaireAuteurs::chercherAuteur(const std::string& nomAuteur)
{
    for (std::size_t i = 0; i < auteurs_.size(); i++)
    {
        if (auteurs_[i] == nomAuteur)
        {
            return &auteurs_[i];
        }
    }

    return nullptr;
}

//! Méthode qui prend un nom de fichier en paramètre et qui charge les auteurs
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool représentant si le chargement a été un succès
bool GestionnaireAuteurs::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
		auteurs_.clear();

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
			std::istringstream stream(ligne);
			Auteur auteur;
			if (!(stream >> auteur))
				return false;
			(*this) += auteur;
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui retourne le nombre d'auteurs
//! \return		Le nombre d'auteurs
std::size_t GestionnaireAuteurs::getNbAuteurs() const
{
    return auteurs_.size();
}

//! opérateur qui ajoute un auteur à la liste des auteurs
//! \param auteur L'auteur à ajouter
//! \return       Un bool représentant si l'opération a fonctionnné
bool GestionnaireAuteurs::operator+=(const Auteur& auteur)
{
	if (auteurs_.size() >= NB_AUTEURS_MAX)
	{
		return false;
	}
	auteurs_.push_back(auteur);
	return true;
}

//! opérateur qui affiche le film
//! \param os						Le stream dans lequel afficher
//! \param gestionnaireAuteurs		Le gestionnaire que l'on veut afficher
std::ostream& operator<<(std::ostream& o, const GestionnaireAuteurs& gestionnaireAuteurs) 
{
	for (std::size_t i = 0; i < gestionnaireAuteurs.auteurs_.size(); i++)
	{
		o << gestionnaireAuteurs.auteurs_[i];
	}
	return o;
}