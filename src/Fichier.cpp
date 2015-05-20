/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient les méthodes de la classe Fichier. */

#include "../include/Fichier.h"

#include <QTextStream>
#include <QDebug>

/*
 * EXCEPTIONS
 */

Fichier::FichierErreur::FichierErreur() throw() : message(), fichier() {
}
Fichier::FichierErreur::FichierErreur(const QString mess) throw() :
    message(mess), fichier() {
}
Fichier::FichierErreur::FichierErreur(const QString fich, const QString mess)
throw() : message(mess), fichier(fich) {
}
Fichier::FichierErreur::FichierErreur(Fichier::FichierErreur &modele) throw():
    message(modele.message), fichier(modele.fichier) {
}
const char* Fichier::FichierErreur::what() const throw() {
    return QString("Erreur dans le fichier %1 : %2").arg(
                fichier).arg(
                message).toLocal8Bit().data();
}


Fichier::FichierFermeErreur::FichierFermeErreur() throw() : mode() {
}
Fichier::FichierFermeErreur::FichierFermeErreur(const QString mess) throw() :
    Fichier::FichierErreur(mess), mode() {
}
Fichier::FichierFermeErreur::FichierFermeErreur(const QString &fich,
                                                const QString mess) throw() :
    Fichier::FichierErreur(fich, mess), mode() {
}
Fichier::FichierFermeErreur::FichierFermeErreur(const QString &fich,
                                                const QString md,
                                                const QString mess) throw() :
    Fichier::FichierErreur(fich, mess), mode(md) {
}
Fichier::FichierFermeErreur::FichierFermeErreur(const FichierFermeErreur &e) throw()
    : Fichier::FichierErreur(e.fichier, e.message), mode(e.mode) {
}
const char* Fichier::FichierFermeErreur::what() const throw() {
    return QString("Impossible d'ouvrir le fichier %1 en mode %2 : %3").arg(
                fichier).arg(
                mode).arg(
                message).toLocal8Bit().data();
}


Fichier::FichierEnteteErreur::FichierEnteteErreur() throw() :
    Fichier::FichierErreur() {
}
Fichier::FichierEnteteErreur::FichierEnteteErreur(const QString mess) throw():
    Fichier::FichierErreur(mess) {
}
Fichier::FichierEnteteErreur::FichierEnteteErreur(const QString fich,
                                                  const QString mess) throw():
    Fichier::FichierErreur(fich, mess) {
}
Fichier::FichierEnteteErreur::FichierEnteteErreur(
        const Fichier::FichierEnteteErreur &e) throw()
    : Fichier::FichierErreur(e.fichier, e.message) {
}
const char* Fichier::FichierEnteteErreur::what() const throw() {
    return QString("Erreur d'en-tête dans le fichier %1 : %2").arg(
                fichier).arg(
                message).toLocal8Bit().data();
}


Fichier::FichierInvalideErreur::FichierInvalideErreur() throw() :
    Fichier::FichierErreur() {
}
Fichier::FichierInvalideErreur::FichierInvalideErreur(const QString mess)
throw() : Fichier::FichierErreur(mess) {
}
Fichier::FichierInvalideErreur::FichierInvalideErreur(const QString fich,
                                                      const QString mess)
throw() : Fichier::FichierErreur(fich, mess) {
}
Fichier::FichierInvalideErreur::FichierInvalideErreur(
        const Fichier::FichierInvalideErreur &e) throw()
    : Fichier::FichierErreur(e.fichier, e.message) {
}
const char* Fichier::FichierInvalideErreur::what() const throw() {
    return QString("Erreur dans le format du fichier %1 : %2").arg(
                fichier).arg(
                message).toLocal8Bit().data();
}


Fichier::FichierFinErreur::FichierFinErreur() throw() :
    Fichier::FichierErreur() {
}
Fichier::FichierFinErreur::FichierFinErreur(const QString mess) throw():
    Fichier::FichierErreur(mess) {
}
Fichier::FichierFinErreur::FichierFinErreur(const QString fich,
                                            const QString mess) throw():
    Fichier::FichierErreur(fich, mess) {
}
Fichier::FichierFinErreur::FichierFinErreur(
        const Fichier::FichierFinErreur &e) throw()
    : Fichier::FichierErreur(e.fichier, e.message) {
}
const char* Fichier::FichierFinErreur::what() const throw() {
    return QString("Fin du fichier %1 atteinte inopinément. %2").arg(
                fichier).arg(
                message).toLocal8Bit().data();
}






/*
 * MÉTHODES
 */



/* Constructeurs */

Fichier::Fichier() throw(): m_fichier(), m_chemin(), m_mode(QIODevice::Text),
    m_entete({.terminaison = QString(FICHIER_ENTETE_FIN),
             .longueur = FICHIER_ENTETE_LONGUEUR}),
    m_meta({.format = QIODevice::Text,
           .nomFormat = QString(),
           .nbColonnes = 0,
           .colonnes = QVector<QString>(),
           .autre = QString()}), m_voxel(), m_nb_points(0) {
}

Fichier::Fichier(const QString &chemin, QIODevice::OpenMode mode) throw() :
    m_fichier(chemin), m_chemin(chemin), m_mode(mode),
    m_entete({.terminaison = QString(FICHIER_ENTETE_FIN),
             .longueur = FICHIER_ENTETE_LONGUEUR}),
    m_meta({.format = QIODevice::Text,
           .nomFormat = QString(),
           .nbColonnes = 0,
           .colonnes = QVector<QString>(),
           .autre = QString()}), m_voxel(), m_nb_points(0) {
}

Fichier::Fichier(Fichier &modele) throw() : m_fichier(),
    m_chemin(modele.getChemin()), m_mode(modele.getMode()),
    m_entete(modele.getEntete()), m_meta(modele.getMeta()),
    m_voxel(modele.getVoxel()), m_nb_points(modele.getNbPoints()) {
    m_fichier.setFileName(m_chemin);
}


Fichier::~Fichier()
{
}


/* Fonctions d'ouverture et de fermeture */

bool Fichier::ouvrir(const QString &chemin, QIODevice::OpenMode mode) throw(){
    m_chemin = chemin;
    m_mode = mode;
    m_fichier.setFileName(chemin);
    return m_fichier.open(mode);
}

bool Fichier::estOuvert() throw() {
    return m_fichier.isOpen();
}

void Fichier::fermer() throw() {
}

bool Fichier::rouvrir(QIODevice::OpenMode mode) throw() {
    fermer();
    if(!(mode & QIODevice::Text) && !(mode & QIODevice::Unbuffered)) { // si pas précisé
        mode |= QIODevice::Text;
    }
    m_mode = mode;
    m_nb_points = 0;
    return ouvrir(m_chemin, m_mode);
}



/* Fonctions de déplacement, lecture, et écriture */

void Fichier::passerEntete() {
    /* Réouverture du fichier */
    if(!rouvrir((m_mode
                 & (~QIODevice::Append)) // on doit revenir au début !
                | QIODevice::ReadOnly)) {
        FichierFermeErreur e(m_chemin, "ra", "(passerEntete)");
        throw e;
    }

    /* Lecture ligne par ligne */
    QByteArray ligne;

    for(int compteur = 0; compteur < FICHIER_ENTETE_LONGUEUR ; compteur++) {
        if(compteur == m_entete.longueur) {
            return;
        }

        FichierFinErreur fin_prematuree(m_chemin, "passerEntete a atteint la fin du fichier.");
        if(m_fichier.atEnd()) {
            return; //throw(fin_prematuree);
        }

        ligne = m_fichier.readLine();

        if(ligne.length() <= 0) {
            throw fin_prematuree;
        }

        // on s'arrête si on a trouvé la balise
        if(QString(ligne).indexOf(
                      m_entete.terminaison, 0, Qt::CaseInsensitive) >= 0) {
            return;
        }
    }

    FichierEnteteErreur ete(
                    m_chemin,
                    QString("passerEntete n'a pas vu la fin de l'en-tête."));
    throw ete;
}

Fichier::MetaDonnees Fichier::lireEntete(const QString& fin, long longueur)
throw(FichierFermeErreur, FichierEnteteErreur) {
}
Fichier::MetaDonnees Fichier::lireEntete(long longueur, const QString &fin)
throw(FichierFermeErreur, FichierEnteteErreur) {
}
Fichier::MetaDonnees Fichier::lireEntete(const EnTete& entete)
throw(FichierFermeErreur) { // tente de lire l'entête du fichier, le rouvrant au besoin. Si FICHIER_ENTETE_LONGUEUR est atteint et que fin n'a pas été précisé, annule tout et lève FichierEnteteErreur.
}



void Fichier::calculerVoxel()
throw(FichierFermeErreur, FichierEnteteErreur, FichierInvalideErreur) {
    Point **points = getPoints();
    Voxel provisoire;
    Point3D debut, fin;
    if(m_nb_points > 0) {
        provisoire.setDebut(*(points[0]));
        provisoire.setFin(*(points[0]));
    }

    for(int i=1 ; i  < m_nb_points ; i++) {
        try {
            if(!provisoire.intersecte(*(points[i]))) {
                // alors ce point agrandit le voxel
                debut = provisoire.getDebut();
                fin = provisoire.getFin();
                debut.setX(std::min<double>(
                                std::min<double>(debut.getX(), fin.getX()),
                                points[i]->getX()
                                ));
                debut.setY(std::min<double>(
                                std::min<double>(debut.getY(), fin.getY()),
                                points[i]->getY()
                                ));
                debut.setZ(std::min<double>(
                                std::min<double>(debut.getZ(), fin.getZ()),
                                points[i]->getZ()
                                ));
                fin.setX(std::max<double>(
                                std::max<double>(debut.getX(), fin.getX()),
                                points[i]->getX()
                                ));
                fin.setY(std::max<double>(
                                std::max<double>(debut.getY(), fin.getY()),
                                points[i]->getY()
                                ));
                fin.setZ(std::max<double>(
                                std::max<double>(debut.getZ(), fin.getZ()),
                                points[i]->getZ()
                                ));
                provisoire.setDebut(debut);
                provisoire.setFin(fin);
            }
        } catch(...) {
            break;
        }
    }

    m_voxel = provisoire;
}



long Fichier::getNbPoints()
throw(FichierFermeErreur, FichierEnteteErreur, FichierInvalideErreur) { // compte le nombre de points dans le fichier
    bool enteteErreur = false;
    FichierEnteteErreur err;
    long nbPoints = -1;

    if(m_nb_points == 0) { // jamais calculé auparavant
        // Lecture de l'en-tête
        try {
            passerEntete();
        } catch(FichierEnteteErreur &e) {
            enteteErreur = true;
            err = e;
        } catch(...) {
            throw;
        }

        // Comptage
        nbPoints = 0;
        while (!m_fichier.atEnd() && m_fichier.readLine().length() > 0) {
            nbPoints++;
        }

        m_nb_points = nbPoints;
    } else {
        // On reprend le résultat précédent
        nbPoints = m_nb_points;
    }

    if(enteteErreur) {
        // Attention, m_nb_points est potentiellement faux
        throw FichierEnteteErreur(err);
    }
    return nbPoints;
}



Point Fichier::getPoint(long pos)
throw(FichierFermeErreur, FichierFinErreur, FichierInvalideErreur)
{
    if(!m_fichier.isOpen() || !m_fichier.isReadable()) {
        if(!rouvrir(m_mode | QIODevice::ReadOnly)) {
            throw new FichierFermeErreur(m_chemin, "r", "(getPoint) Le fichier n'est pas accessible en lecture.");
        }
    }

    if(m_fichier.atEnd()) {
        throw FichierFinErreur(m_chemin);
    }

    if(pos < 0) {
        QByteArray ligne = m_fichier.readLine();
        if(ligne.length() <= 0) {
            throw new FichierFinErreur(m_chemin, QString("(getPoint) La ligne lue a une longueur négative %1").arg(ligne.length()));
        }

        Point resultat;
        char *reste = ligne.data();
        resultat.setX(strtod(reste, &reste));
        resultat.setY(strtod(reste, &reste));
        resultat.setZ(strtod(reste, NULL));

        return resultat;
    }
}

bool Fichier::ajoutPoint(const Point &p, long pos) throw(FichierFermeErreur) {
    if(!m_fichier.isOpen() || !m_fichier.isWritable()) {
        if(!rouvrir(m_mode | QIODevice::Append | QIODevice::WriteOnly)) {
            throw new FichierFermeErreur(m_chemin, "wa", "(ajoutPoint) Le fichier n'est pas accessible en écriture.");
        }
    }

    // position n'est pas implémenté, insère en fin de fichier
    QTextStream out(&m_fichier);
    out << p.toQString() << endl;
    m_nb_points++;
}



Point** Fichier::getPoints() throw() { // récupère tous les points du fichier
    // calcul de la taille
    long nbPoints = getNbPoints();
    if(nbPoints < 0) {
        return NULL;
    }

    // zappe l'en-tete
    try {
        passerEntete();
    } catch(Fichier::FichierEnteteErreur &e) {
    }

    Point **liste = new Point*[nbPoints];

    // lecture de la première ligne pour savoir quoi faire
    //QByteArray info = m_fichier.readLine();
    //if(info=="ply")
    //    std::cout<< "le fichier ouvert est un fichier .ply"<< std::endl;

    // lecture des points
    try {
        for(long i = 0 ; i < nbPoints ; i++) {
            liste[i] = new Point(getPoint());
        }
    } catch (Fichier::FichierFinErreur &e) {
    }


    return liste;
}

QVector<Point> Fichier::getVPoints() throw(FichierFermeErreur) {
    // calcul de la taille
    try {
        getNbPoints();
    } catch(FichierEnteteErreur &e) {
        qDebug() << "(getVPoints) (getNbPoints) a renvoyé une erreur d'en-tête : " << e.what();
    } catch(FichierInvalideErreur &e) {
        qDebug() << "(getVPoints) (getNbPoints) signale que ce fichier est invalide : " << e.what();
    }

    // zappe l'en-tete
    try {
        passerEntete();
    } catch(FichierEnteteErreur &e) {
        qDebug() << "(getVPoints) (passerEntete) a renvoyé une erreur d'en-tête : " << e.what();
    } catch(FichierInvalideErreur &e) {
        qDebug() << "(getVPoints) (passerEntete) signale que ce fichier est invalide : " << e.what();
    }

    QVector<Point> v(m_nb_points);

    // lecture des points
    try {
        for(long i = 0 ; i < m_nb_points ; i++) {
            v.append(getPoint());
        }
    } catch (Fichier::FichierFinErreur&) {
    }

    return v;
}

QVector<Point> Fichier::requete(const Point &centre, double distance)
throw(FichierFermeErreur, FichierEnteteErreur, FichierInvalideErreur) {
    // renvoie tous les points du fichier se trouvant à une distance 'distance' de 'centre'
    Voxel v(centre.getX() - distance,
            centre.getY() - distance,
            centre.getZ() - distance,
            centre.getX() + distance,
            centre.getY() + distance,
            centre.getZ() + distance);
    return Fichier::requete(v);
}

QVector<Point> Fichier::requete(const Voxel &conteneur)
throw(FichierFermeErreur, FichierEnteteErreur, FichierInvalideErreur) {
    // renvoie tous les points du fichier contenus dans 'conteneur'
    passerEntete();

    QList<Point> resultat;
    Point *p;

    try {
        while(true) {
            p = new Point(getPoint());
            if(conteneur.intersecte(*p)) {
                resultat.append(*p);
            } else {
                delete p;
            }
        }
    } catch(FichierFinErreur&) {
    } catch(FichierInvalideErreur &e) {
        qDebug() << "(requete) (getPoint) signale que ce fichier est invalide : " << e.what();
    }

    return resultat.toVector();
}

/* Accesseurs et mutateurs (1 par attribut) */
const QFile &Fichier::cgetFichier() const throw() {
    return m_fichier;
}
QFile &Fichier::getFichier() throw() {
    return m_fichier;
}
void Fichier::setFichier(QFile &nouveau) throw() {
    fermer();
    m_chemin = nouveau.fileName();
    m_mode = nouveau.openMode();
    m_fichier.setFileName(m_chemin);
    if(m_mode) {
        m_fichier.open(m_mode);
    }
}

QString Fichier::getChemin() const throw() {
    return m_chemin;
}
void Fichier::setChemin(const QString &nom) throw() {
    m_chemin = nom;
}

QIODevice::OpenMode Fichier::getMode() const throw() {
    return m_mode;
}

Fichier::EnTete Fichier::getEntete() const throw() {
    return m_entete;
}
void Fichier::setEntete(Fichier::EnTete entete) throw() {
    m_entete = entete;
}
void Fichier::setEntete(const QString& fin, long longueur) throw() {
    m_entete = {
        .terminaison = fin,
        .longueur = longueur
    };
}

Fichier::MetaDonnees Fichier::getMeta() const throw() {
    return m_meta;
}

Voxel Fichier::getVoxel() const throw() {
    return m_voxel;
}
