#ifndef FICHIER_H
#define FICHIER_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe Fichier.
 * Nous avons décidé de stocker les points dans un fichier (d'où le nom de la
 * classe) qui seront insérés aux feuilles de notre arborescence de
 * répertoires.
 * Cette classe représente un tel fichier.
 * Lors de la construction de l'arbre, on devra écrire dans ce fichier ;
 * et le lire lors des requêtes. */

/* À faire :
 *  -- Doit-on garder le fichier ouvert (i.e. l'ouvrir dans le constructeur
 *     et le fermer dans le destructeur), permettre de l'ouvrir et de le
 *     fermer manuellement, ou bien l'ouvrir et le fermer à chaque accès ?
 *  -- Si on le garde ouvert, sous quelle forme le stocke-t-on (i/ostream) ?
 *  -- Implémenter les méthodes */

#include "Point.h"
#include "Voxel.h"

#include <QString>
#include <QFile>
#include <QVector>

class Fichier
{
    public:
        Fichier(); // constructeur
        Fichier(const Fichier &modele); // constructeur de recopie
        /*friend void swap(Fichier &un, Fichier &deux) {
            // enable ADL (not necessary in our case, but good practice)
            using std::swap;

            // by swapping the members of two classes,
            // the two classes are effectively swapped
            swap(un.m_fichier, deux.m_fichier);
            swap(un.m_voxel, deux.m_voxel);

            // http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
        }*/
        Fichier &operator=(Fichier);
        ~Fichier(); // destructeur

        bool ouvrir(const QString &chemin,
                    QIODevice::OpenMode mode
                        = QIODevice::Append | QIODevice::Text);
        void fermer(); // appelée dans le destructeur

        Point getPoint(long pos); // renvoie le pos-ième point du fichier
        bool ajoutPoint(const Point &p, long pos = -1); // insère un point dans le fichier (-1 à la fin).

        /* Les fonctions de requête */
        QVector<Point> requete(const Point &centre, double distance) const; // renvoie tous les points du fichier se trouvant à une distance 'distance' de 'centre'
        QVector<Point> requete(const Voxel &conteneur) const; // // renvoie tous les points du fichier contenus dans 'conteneur'

        /* Accesseurs et mutateurs (1 par attribut) */
        const QFile &getFichier() const;
        void setFichier(QFile &nouveau);

        Voxel getVoxel() const;
        void calculerVoxel(); // MARYAME
        void setVoxel(const Voxel &v);
    protected:
    private:
        /* Une feuille est associée à un fichier : */
        QFile m_fichier;
        Voxel m_voxel;
};

#endif // FICHIER_H
