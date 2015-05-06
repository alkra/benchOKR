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

Fichier::Fichier() : m_fichier(), m_voxel(), m_chemin(), m_mode(QIODevice::ReadOnly || QIODevice::Text), m_nb_points(0) {
}

Fichier::Fichier(Fichier &modele) : m_fichier(),
    m_voxel(modele.getVoxel()), m_chemin(modele.getChemin()), m_mode(modele.getMode()), m_nb_points(modele.getNbPoints()) {
    m_fichier.setFileName(m_chemin);
}


Fichier::~Fichier()
{
}

bool Fichier::ouvrir(const QString &chemin, QIODevice::OpenMode mode) {
    m_chemin = chemin;
    m_fichier.setFileName(chemin);
    return m_fichier.open(mode);
}

bool Fichier::estOuvert() {
    return m_fichier.isOpen();
}

void Fichier::fermer() {
}

bool Fichier::rouvrir(QIODevice::OpenMode mode) {
    fermer();
    if(!(mode & QIODevice::Text) && !(mode & QIODevice::Unbuffered)) {
        mode |= QIODevice::Text;
    }
    m_mode = mode;
    m_nb_points = 0;
    return ouvrir(m_chemin, m_mode);
}

QString Fichier::getChemin() const {
    return m_chemin;
}

void Fichier::setChemin(const QString &nom) {
    m_chemin = nom;
}

QIODevice::OpenMode Fichier::getMode() const {
    return m_mode;
}

bool Fichier::ajoutPoint(const Point &p, long pos) {
    if(m_fichier.isOpen()) {
        // position n'est pas implémenté, insère en fin de fichier
        QTextStream out(&m_fichier);
        out << p.toQString() << endl;
        m_nb_points++;
        return true;
    }

    return false;
}

void Fichier::passerEntete(const QString &fin) {
    //std::cerr << "On doit recalculer le nb de points." << std::endl;
    if(!rouvrir((m_mode & (~QIODevice::Append)) | QIODevice::ReadOnly)) {
        throw(1);
    }

    /*QByteArray ligne = m_fichier.readLine();
    int compteur = 0;
    while(!m_fichier.atEnd()
          && ligne.length() > 0
          && QString(ligne) != fin) {
        ligne = m_fichier.readLine();
        compteur++;
        if(compteur == 100) {
            m_nb_points = 100;
            throw 100;
        }
    }*/
}

Point Fichier::getPoint(long pos)
{
    if(!m_fichier.isOpen() || !m_fichier.isReadable()) {
        throw(1);
    }

    if(m_fichier.atEnd()) {
        throw 0;
    }

    if(pos < 0) {
        QByteArray ligne = m_fichier.readLine();
        if(ligne.length() <= 0) {
            throw ligne.length();
        }

        Point resultat;
        char *reste = ligne.data();
        resultat.setX(strtod(reste, &reste));
        resultat.setY(strtod(reste, &reste));
        resultat.setZ(strtod(reste, NULL));

        return resultat;
    }
}

long Fichier::getNbPoints() { // compte le nombre de points dans le fichier
    long nbPoints = -1;
    if(m_nb_points == 0) {
        // Lecture de l'en-tête
        try {
            passerEntete("end_header");
        } catch(int e) {
            if(e != 100) { throw e; }
        }

        // Comptage
        nbPoints = 0;
        while (m_fichier.readLine().length() > 0)
        {
            nbPoints++;
        }

        m_nb_points = nbPoints;
    } else {
        nbPoints = m_nb_points;
    }

    return nbPoints; // si le fichier n'a pas été ouvert, renvoie -1
}

Point** Fichier::getPoints(){ // récupère tous les points du fichier
    if(!rouvrir(m_mode | QIODevice::ReadOnly)) {
        return NULL;
    }

    long nbPoints = getNbPoints();
    std::cerr << "getPoints() : nbPoints vaut " << nbPoints << std::endl;
    if(nbPoints < 0) {
        throw nbPoints;
    }

    if(!rouvrir(m_mode | QIODevice::ReadOnly)) {
        return NULL;
    }

    try {
        passerEntete("end_header");
    } catch(...) {
    }

    Point **liste = new Point*[nbPoints];

    // lecture de la première ligne pour savoir quoi faire
    //QByteArray info = m_fichier.readLine();
    //if(info=="ply")
    //    std::cout<< "le fichier ouvert est un fichier .ply"<< std::endl;

    // lecture des points
    for(long i = 0 ; i < nbPoints ; i++) {
        liste[i] = new Point(getPoint());
    }

    return liste;
}

QVector<Point> Fichier::requete(const Point &centre, double distance) const {
    // renvoie tous les points du fichier se trouvant à une distance 'distance' de 'centre'
}

QVector<Point> Fichier::requete(const Voxel &conteneur) {
    // renvoie tous les points du fichier contenus dans 'conteneur'
    if(!estOuvert() && !rouvrir(m_mode | QIODevice::ReadOnly)) {
        throw 1;
    }

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
    } catch(int e) {
        if(e != 0) {
            throw e;
        }
    }

    return resultat.toVector();
}

/* Accesseurs et mutateurs (1 par attribut) */
const QFile &Fichier::cgetFichier() const {
    return m_fichier;
}

QFile &Fichier::getFichier() {
    return m_fichier;
}

void Fichier::setFichier(QFile &nouveau) {
    fermer();
    m_chemin = nouveau.fileName();
    m_mode = nouveau.openMode();
    m_fichier.setFileName(m_chemin);
    if(m_mode) {
        m_fichier.open(m_mode);
    }
}

Voxel Fichier::getVoxel() const {
    return m_voxel;
}

void Fichier::calculerVoxel() {
    // MARYAME
}

void Fichier::setVoxel(const Voxel &v) {
    // Attention, ne garantit pas que la nouvelle boîte soit cohérente
    // Appeler calculerVoxel plutôt
    m_voxel = v;
}
