/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient les méthodes de la classe Fichier. */

#include "../include/Fichier.h"

#include <QTextStream>

Fichier::Fichier() : m_fichier(), m_voxel(), m_nb_points(-1) {

}

Fichier::Fichier(const Fichier &modele) : m_fichier(),
    m_voxel(modele.getVoxel()), m_nb_points(-1) {
    m_fichier.setFileName(modele.cgetFichier().fileName());
}


Fichier& Fichier::operator=(Fichier modele) {
    *this = modele;
    return *this;
}

Fichier::~Fichier()
{
}

bool Fichier::ouvrir(const QString &chemin, QIODevice::OpenMode mode) {
    m_fichier.setFileName(chemin);
    return m_fichier.open(mode);
}

bool Fichier::estOuvert() {
    return m_fichier.isOpen();
}

void Fichier::fermer() {
    m_fichier.close();
}


bool Fichier::ajoutPoint(const Point &p, long pos) {
    if(m_fichier.isOpen()) {
        // position n'est pas implémenté, insère en fin de fichier
        QTextStream out(&m_fichier);
        out << p.toQString() << endl;
        return true;
    }

    return false;
}

Point Fichier::getPoint(long pos)
{
    // renvoie le pos-ième point du fichier
}

long Fichier::getNbPoints() { // compte le nombre de points dans le fichier
    if(m_nb_points < 0 && estOuvert()) {
        //comptage du nombre de lignes
        m_fichier.readLine();
        long pointCount=0;
        while (m_fichier.readLine().length() > 0)
        {
            pointCount++;
        }

        m_nb_points = pointCount;
    }

    return m_nb_points; // si le fichier n'a pas été ouvert, renvoie -1
}

Point** Fichier::getPoints(){ // récupère tous les points du fichier
    long nbPoints = getNbPoints();
    if(nbPoints < 0) {
        return NULL;
    }

    Point   **liste = new Point *[nbPoints];

    if (estOuvert()) // si le fichier est ouvert
    {
        // lecture de la première ligne pour savoir quoi faire
        QByteArray info = m_fichier.readLine();
        if(info=="ply")
            std::cout<< "le fichier ouvert est un fichier .ply"<< std::endl;

        // lecture des points
        for(long i = 0 ; i < nbPoints ; i++) {
            info = m_fichier.readLine(); // lecture de la ligne

            // extraction des chaînes de caractère correspondant aux coordonnées
            QList<QByteArray> coordonnees = info.split(' '), propre;
            for(int j = 0 ; j < coordonnees.length(); j++) {
                // élimination d'éventuelles chaînes vides
                if(coordonnees[j].count() != 0) {
                   propre.push_back(coordonnees[j]);
                }
            }

            liste[i] = new Point(
                        propre[0].toDouble(),
                    propre[1].toDouble(),
                    propre[2].toDouble());
        }

        return liste;
    }
    else {
        // cerr<< "Impossible d'ouvrir le fichier ! "<< endl;
        delete[] liste;
        return NULL;
    }
}

QVector<Point> Fichier::requete(const Point &centre, double distance) const {
    // renvoie tous les points du fichier se trouvant à une distance 'distance' de 'centre'
}

QVector<Point> Fichier::requete(const Voxel &conteneur) const {
    // renvoie tous les points du fichier contenus dans 'conteneur'
}

/* Accesseurs et mutateurs (1 par attribut) */
const QFile &Fichier::cgetFichier() const {
    return m_fichier;
}

QFile &Fichier::getFichier() {
    return m_fichier;
}

void Fichier::setFichier(QFile &nouveau) {

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
