/****************************************************************************
* Fichier: Utilisateur.cpp
* Auteur : Aldric Lopez et Juliette Morin
* Date :  12 févr. 2020
* Mise a jour : 29 févr. 2020
* Description : Implémentation de la classe Utilisateur
* ***************************************************************************/

#include "Utilisateur.h"

//! Constructeur de la classe Utilisateur
//! \param nom          Le nom de l'utilisateur
//! \param age          L'âge de l'utilisateur
//! \param estPremium   Bool représentant si l'utilisateur est premium
//! \param pays         Pays de l'utilisateur
Utilisateur::Utilisateur(const std::string& nom, unsigned int age, bool estPremium, Pays pays)
    : nom_(nom)
    , age_(age)
    , nbMediasVus_(0)
    , estPremium_(estPremium)
    , pays_(pays)
{
}

//! Méthode qui retourne si le film est disponible pour un utilisateur
//! \param film Le film à évaluer
//! \return Un bool représentant si un film est disponible à l'utilisateur
bool Utilisateur::mediaEstDisponible(const Media& media) const
{
    static constexpr unsigned int AGE_MINIMUM_POUR_FILMS_RESTREINTS = 16;

    bool ageApproprie = true;
    if (age_ < AGE_MINIMUM_POUR_FILMS_RESTREINTS)
    {
        ageApproprie = media.estRestreintParAge() == false;
    }
    return (ageApproprie == true && media.estRestreintDansPays(pays_) == false);
}

//! Méthode qui retourne si un utilisateur a atteint le nombre limite de films qu'il peut regarder
//! \return Un bool représentant si un utilisateur a atteint le nombre limite de films qu'il peut
//! regarder
bool Utilisateur::nbLimiteMediasAtteint() const
{
    return estPremium_ == false && nbMediasVus_ >= NB_FILMS_GRATUITS;
}

//! Méthode qui incrémente le nombre de films vus par l'utilisateur
//! \return Un bool représentant si l'utilisateur a pu regarder le film
bool Utilisateur::regarderMedia(const Media& media)
{
    if (nbLimiteMediasAtteint() == false && mediaEstDisponible(media))
    {
        nbMediasVus_++;
        return true;
    }
    return false;
}

//! Méthode qui retourne le nombre de films vus par l'utilisateur
//! \return Le nombre de films vus par l'utilisateur
unsigned int Utilisateur::getNbMediasVus() const
{
    return nbMediasVus_;
}
