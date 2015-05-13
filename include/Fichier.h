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

#include "Point.h" // Un fichier contient des Point et non des Point3D
#include "Voxel.h"

#include <QString>
#include <QFile>
#include <QVector>

#include <iostream> // Bon, il faudrait savoir



/* La classe Fichier représentant un fichier.
 * Les constantes suivantes décrivent la structure par défaut de l'entête. */
#ifndef FICHIER_ENTETE_FIN
#define FICHIER_ENTETE_FIN "end_header\n"
#endif
#ifndef FICHIER_ENTETE_LONGUEUR
#define FICHIER_ENTETE_LONGUEUR 100
#endif




class Fichier
{
public:
    /* EXCEPTIONS */
    /* Exception de base sur un Fichier */
    class FichierErreur : public std::exception {
    public:
        /* Constructeurs */
        FichierErreur() throw();
        FichierErreur(const QString mess) throw();
        FichierErreur(const QString fich, const QString mess) throw();
        FichierErreur(FichierErreur &modele) throw();

        const char* what() const throw();

        /* Attributs */
        QString message;
        QString fichier;
    };

    /* L'exception levée lorsque le fichier est fermé et ne devrait pas l'être,
     * ou lorsque le fichier n'a pas pu être ouvert.
     * Dans les méthodes de Fichier, toutes les méthodes essaient d'ouvrir le
     * fichier, donc cette exception ne sera levée qu'en cas d'échec. */

    class FichierFermeErreur : public FichierErreur {
    public:
        FichierFermeErreur() throw();
        FichierFermeErreur(const QString mess) throw();
        FichierFermeErreur(const QString &fich, const QString mess) throw();
        FichierFermeErreur(const QString &fich,
                           const QString md,
                           const QString mess = QString()) throw();
        FichierFermeErreur(const FichierFermeErreur &e) throw();

        const char * what() const throw ();

        QString mode;
    };


    /* Exception levée lors de la lecture de l'en-tête du fichier, lorsque la
     * fin du header n'a pas été trouvée. */
    class FichierEnteteErreur : public FichierErreur {
    public:
        FichierEnteteErreur() throw();
        FichierEnteteErreur(const QString mess) throw();
        FichierEnteteErreur(const QString fich, const QString mess) throw();
        FichierEnteteErreur(const FichierEnteteErreur &e) throw();
        const char* what() const throw();
    };

    /* Exception levée lorsque le fichier n'est pas valide. */
    class FichierInvalideErreur : public FichierErreur {
    public:
        FichierInvalideErreur() throw();
        FichierInvalideErreur(const QString mess) throw();
        FichierInvalideErreur(const QString fich, const QString mess) throw();
        FichierInvalideErreur(const FichierInvalideErreur &e) throw();
        const char* what() const throw();
    };

    /* Exception levée lorsque la fin du fichier a été atteinte inopinément */
    class FichierFinErreur : public FichierErreur {
    public:
        FichierFinErreur() throw();
        FichierFinErreur(const QString mess) throw();
        FichierFinErreur(const QString fich, const QString mess) throw();
        FichierFinErreur(const FichierFinErreur &e) throw();
        const char* what() const throw();
    };





    /* EN-TETE */
    struct EnTete {
        QString terminaison;
        long longueur;
    };
    struct MetaDonnees {
        QIODevice::OpenMode format; // texte ou binaire ?
        QString nomFormat; // intitulé exact du format
        long nbColonnes; // nombre de colonnes
        QVector<QString> colonnes; // intitulé des colonnes
        QString autre; // reste de l'entête
    };



    /* ATTRIBUTS */
protected:
    QFile m_fichier;
    QString m_chemin;
    QIODevice::OpenMode m_mode;
    EnTete m_entete;
    /* Attributs calculés */
    MetaDonnees m_meta;
    Voxel m_voxel;
    long m_nb_points;



public:
    /* MÉTHODES */
    Fichier() throw(); // constructeur par défaut
    Fichier(const QString &chemin,QIODevice::OpenMode mode = QIODevice::Text)
        throw(); // constructeur spécialisé
    Fichier(Fichier &modele) throw(); // constructeur de recopie
    ~Fichier() throw(); // destructeur



    /* Fonctions d'ouverture et fermeture */
    bool ouvrir(const QString &chemin = QString(),
                QIODevice::OpenMode mode
                = QIODevice::Append | QIODevice::Text) throw();
    bool rouvrir(QIODevice::OpenMode mode) throw();
    bool estOuvert() throw();
    void fermer() throw(); // appelée dans le destructeur



    /* Fonctions de déplacement, lecture, et écriture */
    void passerEntete(); // rouvre le fichier et positionne le curseur à la fin de l'en-tête. L'en-tête doit avoir été définie préalablement.
    MetaDonnees lireEntete(const QString& fin = QString(),
                           long longueur = FICHIER_ENTETE_LONGUEUR)
        throw(FichierFermeErreur, FichierEnteteErreur); // tente de lire l'entête du fichier, le rouvrant au besoin. Si FICHIER_ENTETE_LONGUEUR est atteint et que fin n'a pas été précisé, annule tout et lève FichierEnteteErreur.
    MetaDonnees lireEntete(long longueur, const QString &fin = QString())
        throw(FichierFermeErreur, FichierEnteteErreur);
    MetaDonnees lireEntete(const EnTete& entete) throw(FichierFermeErreur);

    void calculerVoxel()
        throw(FichierFermeErreur, FichierEnteteErreur, FichierInvalideErreur); // calcule le voxel englobant tous les points du fichier.

    long getNbPoints()
        throw(FichierFermeErreur, FichierEnteteErreur, FichierInvalideErreur);// compte le nombre de points dans le fichier

    Point getPoint(long pos = -1)
        throw(FichierFermeErreur, FichierFinErreur, FichierInvalideErreur); // renvoie le pos-ième point du fichier
    bool ajoutPoint(const Point &p, long pos = -1) throw(FichierFermeErreur); // insère un point dans le fichier (-1 à la fin).

    Point** getPoints() throw(); // récupère tous les points du fichier
    QVector<Point> getVPoints() throw(FichierFermeErreur);

    QVector<Point> requete(const Point &centre, double distance)
        throw(FichierFermeErreur, FichierEnteteErreur, FichierInvalideErreur); // renvoie tous les points du fichier se trouvant à une distance 'distance' de 'centre'
    QVector<Point> requete(const Voxel &conteneur)
        throw(FichierFermeErreur, FichierEnteteErreur, FichierInvalideErreur); // renvoie tous les points du fichier contenus dans 'conteneur'

    /* Accesseurs et mutateurs (1 par attribut) */
    const QFile &cgetFichier() const throw();
    QFile &getFichier() throw();
    void setFichier(QFile &nouveau) throw();

    QString getChemin() const throw();
    void setChemin(const QString &nom) throw();

    QIODevice::OpenMode getMode() const throw();

    EnTete getEntete() const throw();
    void setEntete(EnTete entete) throw();
    void setEntete(const QString& fin = QString(FICHIER_ENTETE_FIN),
                   long longueur = FICHIER_ENTETE_LONGUEUR) throw();

    MetaDonnees getMeta() const throw();

    Voxel getVoxel() const throw();
};

#endif // FICHIER_H
