#ifndef FICHIER_H
#define FICHIER_H

#include "Point.h"
#include "Voxel.h"
#include "Noeud.h"
#include <QString>

class Fichier
{
    public:
        Fichier(QString chemin); // constructeur
        ~Fichier(); // destructeur

        Point getPoint(long pos); // renvoie le pos-ième point du fichier

        /* Les fonctions de requête */
        Point* requete(const Point &centre, double distance) const; // renvoie tous les points du fichier se trouvant à une distance 'distance' de 'centre'
        Point* requete(const Voxel &conteneur) const; // // renvoie tous les points du fichier contenus dans 'conteneur'

        /* Accesseurs et mutateurs (1 par attribut) */
        // iofstream getFichier() const;
        // void setFichier(iofstream f);
    protected:
    private:
        /* Une feuille est associée à un fichier : */
        // iofstream *fichier;
};

#endif // FICHIER_H
