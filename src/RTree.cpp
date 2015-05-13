/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe RTree. */

#include "../include/RTree.h"
#include <QDebug>

RTree::RTree() : m_cheminRacine() {
}

RTree::RTree(const QString &rac) : m_cheminRacine(rac)
{
    // Allocation de la racine
    ALLOCATION(racine, NoeudR(NULL, true))

    QDir dossier(rac);
    dossier.exists() ? : dossier.mkpath(rac);
    racine->setDossier(dossier);

    QFile fichier(rac + "/" + FICHIER);
    if(!fichier.exists()) {
        if(!fichier.open(QIODevice::WriteOnly)) {
            throw(2);
        }
        fichier.close();
    }

    Fichier *rf = NULL;
    ALLOCATION(rf, Fichier())
    rf->setChemin(rac + "/" + FICHIER);
    racine->setFichier(rf);
}

RTree::~RTree()
{
}

#define DONNEES "../donneeTestDIAS/SalamandreCloud.txt"
#define FIN_ENTETE "end_header"

void RTree::construire() {
    // ouverture du fichier racine en écriture
    try {
        if(!racine->getFichier()->rouvrir(QIODevice::ReadWrite | QIODevice::Text)) {
            qFatal("Impossible d'avoir l'accès en écriture.");
        }
    } catch(NoeudR::TerminalErreur t) {
        qFatal("Le fichier racine n'est pas initialisé.");
    }

    // ouverture du fichier initial
    Fichier donnees;
    if(!donnees.ouvrir(DONNEES, QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal("Impossible d'ouvrir les données.");
    }

    // lecture de l'en-tête.
    try {
        donnees.passerEntete();
    } catch(int e) {
        switch(e) {
        case 1:
            qFatal("Le fichier de données n'est pas ouvert.");
            return;
        case 100:
            qCritical("Entête plus longue que 100 lignes");
            break;
        default:
            qCritical("Erreur inconnue venant de passerEntete.");
            break;
        }
    }

    Point p;
    for(int compteur = 0 ; compteur < 11 ; compteur++) {
        try {
            p = donnees.getPoint();
        } catch(int e) {
            qCritical("constuire() -> boucle -> impossible de récupérer le point.");
            switch(e) {
            case 1:
                qDebug() << "    Le fichier n'a pas pu être ouvert. i vaut " << compteur;
                break;
                continue;
            case 0:
                qDebug() << "    Fin du fichier atteinte. i vaut " << compteur;
                throw 0;
            default:
                qDebug() << "    Erreur inconnue. i vaut " << compteur;
                throw e;
            }
        }

        try {
            inserer(p);
        } catch(Fichier::FichierFermeErreur) {
            qDebug() << "(construire) Concernait le point n° " << compteur;
            continue;
        }
    }
}

QVector<Point> RTree::requete(const Point &centre, double distance) const {
    return racine->requete(centre, distance);
}

QVector<Point> RTree::requete(const Voxel &conteneur) const {
    return racine->requete(conteneur);
}

void RTree::inserer(const Point &p) { // Gut84 : algorithm Insert
    NoeudR *parent = choisirFeuille(p, racine); // Gut84 : I1
    Fichier& f = *(parent->getFichier());

    // on s'assure que le fichier est ouvert
    if(!f.estOuvert() && !f.rouvrir(f.getMode() | QIODevice::ReadWrite | QIODevice::Append)) {
        qDebug() << "(insérer) Impossible d'ouvrir ni crééer le fichier " << f.getChemin();
        throw new Fichier::FichierFermeErreur;
    }

    // on s'assure que le fichier est lisible et inscrivible
    if(f.estOuvert() && !f.getFichier().isWritable()
            && !f.rouvrir(f.getMode() | QIODevice::ReadWrite | QIODevice::Append)) {
        qDebug() << "(insérer) Impossible d'avoir un fichier inscrivible. " << f.getChemin();
        throw new Fichier::FichierFermeErreur;
    }

    /* Gut84 : I2 */
    if(libre(parent)) {
        f.ajoutPoint(p);
        return;
    } // else

    NoeudR *nouveau = diviserFichier(p, parent);

    /* Gut84 : I3 */
    NoeudR *deuxiemeRacine = ajusterArbre(parent, nouveau);

    /* Gut84 : I4 */
    if(deuxiemeRacine) {
        QDir dossierRacine = parent->getDossier();

        // Archivage des dossiers
        QString archive1 = parent->getDossier().absolutePath(),
                archive2 = nouveau->getDossier().absolutePath();
        dossierRacine.rename(archive1, RECUP_FICHIER_DIVISION(archive1));
        parent->setDossier(RECUP_FICHIER_DIVISION(archive1));
        dossierRacine.rename(archive2, RECUP_FICHIER_DIVISION(archive2));
        nouveau->setDossier(RECUP_FICHIER_DIVISION(archive2));

        // Création de la nouvelle racine
        dossierRacine.mkpath(archive1);
        NoeudR *nouvelleRacine = NULL;
        ALLOCATION(nouvelleRacine, NoeudR(NULL, false))
        nouvelleRacine->setDossier(dossierRacine);
        nouvelleRacine->ajoutEnfant(*racine);
        nouvelleRacine->ajoutEnfant(*deuxiemeRacine);
        racine = nouvelleRacine;
    }
}

void elargissement(const Point &point, const Voxel &v, double &ex, double &ey, double &ez) {
    double exmin, exmax, eymin, eymax, ezmin, ezmax;
    Point3D debut = v.getDebut(),
        fin = v.getFin();

    // Calcul de l'élargissement
    if(debut.getX() < fin.getX()) {
        exmin = point.getX() - debut.getX();
        exmax = point.getX() - fin.getX();
        ex = fin.getX() - debut.getX();
    } else {
        exmin = point.getX() - fin.getX();
        exmax = point.getX() - debut.getX();
        ex = debut.getX() - fin.getX();
    }
    ex += (exmin < 0 ? -exmin : 0) + (exmax > 0 ? exmax : 0);

    if(debut.getY() < fin.getY()) {
        eymin = point.getY() - debut.getY();
        eymax = point.getY() - fin.getY();
        ey = fin.getY() - debut.getY();
    } else {
        eymin = point.getY() - fin.getY();
        eymax = point.getY() - debut.getY();
        ey = debut.getY() - fin.getY();
    }
    ey += (eymin < 0 ? -eymin : 0) + (eymax > 0 ? eymax : 0);

    if(debut.getZ() < fin.getZ()) {
        ezmin = point.getZ() - debut.getZ();
        ezmax = point.getZ() - fin.getZ();
        ez = fin.getZ() - debut.getZ();
    } else {
        ezmin = point.getZ() - fin.getZ();
        ezmax = point.getZ() - debut.getZ();
        ez = debut.getZ() - fin.getZ();
    }
    ez += (ezmin < 0 ? -ezmin : 0) + (ezmax > 0 ? ezmax : 0);
}

NoeudR* calculElargissement(const Point &point, const NoeudR *courant) {
    NoeudR *reponse = NULL, *enfant = NULL;
    Voxel vox;
    double etot, ex, ey, ez;
    double elarg, volume;
    for(long i = 0 ; i < courant->getNbEnfants() ; i++) {
        ALLOCATION(enfant, NoeudR(courant->getEnfant(i)));

        // Calcul de la différence de voxels
        vox = enfant->getVoxel();

        elargissement(point, vox, ex, ey, ez);

        etot = ex + ey + ez;

        // ce voxel est-il plus étroit ?
        if(etot < elarg) {
            elarg = etot;
            volume = ex*ey*ez;
            reponse = enfant;
        } else {
            if(etot == elarg && ex*ey*ez < volume) {
                // "Resolve ties by choosing the entry with the rectangle of smallest area."
                elarg = etot;
                volume = ex*ey*ez;
                reponse = enfant;
            } else if(ex*ey*ez == volume
                      && enfant->getFichier()->getNbPoints() <
                      reponse->getFichier()->getNbPoints()) {
                // "Then the one with fewer entries" (QS 3)
                elarg = etot;
                volume = ex*ey*ez;
                reponse = enfant;
            }
        }
    }
    return reponse;
}

/* Gut84 : ChooseLeaf */
NoeudR *RTree::choisirFeuille(const Point &point, NoeudR *courant) const {
    if(courant == NULL) {
        throw 0;
    }

    // CL 1
    if(courant->estTerminal()) { // CL 2
        return courant;
    } else { // CL 3
        NoeudR *reponse = calculElargissement(point, courant);

        // CL 4
        try {
            return choisirFeuille(point, reponse); // Récursivité terminale :)
        } catch(int e) {
            if(e == 0) {
                return courant;
            } else {
                qDebug("Exception inconnue dans choisirFeuille.");
                throw e;
            }
        }
    }
}



bool RTree::libre(const NoeudR *feuille) const {
    try {
        long nbPoints = feuille->getFichier()->getNbPoints();
        qDebug() << "(libre) Le fichier contient " << nbPoints << " points.";
        return nbPoints < MAX_FICHIER;
    } catch(NoeudR::TerminalErreur &e) {
        qDebug() << "(libre) Ce nœud n'est pas terminal.";
        throw(e);
    } catch(Fichier::FichierFermeErreur &e) {
        qDebug() << "(libre) Imposible de rouvrir le fichier " << e.fichier << " : " << e.message;
        throw e;
    } catch(Fichier::FichierEnteteErreur &e) {
        qDebug() << "(libre) Entête erreur dans le ficher " << e.fichier << " : " << e.message;
        throw e;
    } catch(Fichier::FichierInvalideErreur &e) {
        qDebug() << "(libre) Le fichier " << e.fichier << " est invalde : " << e.message;
    } catch(Fichier::FichierFinErreur) {
        qDebug("2");
        return true;
    }
}

void choisirSemenceFichier(QVector<Point> &stock, Fichier &un, Fichier &deux) {
    // PS 1
    double volume = 0;
    Voxel *courant = NULL;
    long indice1 = 0, indice2 = 0;
    for(long i = 0 ; i < stock.length() ; i++) {
        for(long j = 0 ; j < stock.length() ; j++) {
            courant = new Voxel(
                        stock[i].getX(), stock[i].getY(), stock[i].getZ(),
                        stock[j].getX(), stock[j].getY(), stock[j].getZ());
            if(courant->volume() > volume) {
                volume = courant->volume();
                indice1 = i;
                indice2 = j;
            }

            delete courant;
        }
    }

    if(un.ajoutPoint(stock[indice1])) {
        stock.remove(indice1);
    }
    if(deux.ajoutPoint(stock[indice2])) {
        stock.remove(indice2);
    }
}

Point choisirSuivantFichier(QVector<Point> &stock, Fichier &un, Fichier &deux) {
    // PN 1
    double ex, ey, ez, d1, d2, d = 0;
    Voxel v;
    int indice = 0;

    for(int i = 0 ; i < stock.length() ; i++) {
        un.calculerVoxel();
        v = un.getVoxel();
        elargissement(stock[i], v, ex, ey, ez);
        d1 = ex*ey*ez - v.volume();

        deux.calculerVoxel();
        v = deux.getVoxel();
        elargissement(stock[i], v, ex, ey, ez);
        d2 = ex*ey*ez - v.volume();

        if(d1-d2 >= 0 && d1-d2 > d) {
            d = d1-d2;
            indice = i;
        } else if(d1-d2 <= 0 && d2-d1 > d) {
            d = d2 - d1;
            indice = i;
        }
    }

    Point res(stock[indice]);
    stock.remove(indice);
    return res;
}

void RTree::divisionQuadratiqueFichier(const Point &p, NoeudR &premier, NoeudR &deuxieme) {
    // Récupération du fichier initial
    Fichier *fichierInit = NULL;
    try {
        fichierInit = premier.getFichier();
    } catch(NoeudR::TerminalErreur t) {
        fichierInit = NULL;
    }

    if(fichierInit == NULL) {
        ALLOCATION(fichierInit, Fichier())
        if(!fichierInit->ouvrir(FICHIER, QIODevice::WriteOnly)) {
            throw(1);
        }
    }

    // Chargement des points du fichier en mémoire
    Point** _pointsFichier = NULL;
    try {
        _pointsFichier = fichierInit->getPoints();
    } catch(int e) {
        qCritical("Dans getPoints : le nombre de points est négatif.");
    }

    if(_pointsFichier == NULL) {
        throw(2); // impossible d'ouvrir le fichier
    }
    QVector<Point> pointsFichier;
    premier.getFichier()->rouvrir(QIODevice::ReadOnly | QIODevice::Text);
    for(int i = 0 ; i < premier.getFichier()->getNbPoints() ; i++) {
        pointsFichier << *(_pointsFichier[i]);
    }
    pointsFichier.append(p);

    // "Suppression" du fichier de départ
    Fichier *depart;
    try {
        depart = premier.getFichier();
    } catch(Fichier::FichierFermeErreur e) {
        throw(e);
    }
    QString nomInit = depart->getChemin();
    depart->getFichier().rename(RECUP_FICHIER_DIVISION(nomInit));

    // Création des deux fichiers
    Fichier un, deux;
    if(!un.ouvrir(premier.getDossier().absoluteFilePath(FICHIER))) {
        throw 3;
    }
    if(!deux.ouvrir(deuxieme.getDossier().absoluteFilePath(FICHIER))) {
        throw 4;
    }

    // Création des deux noeuds correspondants
    premier.setFichier(&un);
    deuxieme.setFichier(&deux);

    // QS 1 initialisation des groupes
    choisirSemenceFichier(pointsFichier, un, deux);

    // Calcul du nouveau voxel englobant
    un.calculerVoxel();
    deux.calculerVoxel();

    // QS 2 terminaison
    while(pointsFichier.length() > 0) {
        if(MIN_FICHIER - un.getNbPoints() == pointsFichier.length()) {
            un.rouvrir(un.getMode() | QIODevice::Append | QIODevice::WriteOnly);
            for(int i = 0 ; i < pointsFichier.length() ; i++) {
                un.ajoutPoint(pointsFichier.takeFirst());
            }
            break;
        }

        if(MIN_FICHIER - deux.getNbPoints() == pointsFichier.length()) {
            deux.rouvrir(deux.getMode() | QIODevice::Append | QIODevice::WriteOnly);
            int leng = pointsFichier.length();
            for(int i = 0 ; i < leng ; i++) {
                deux.ajoutPoint(pointsFichier.takeFirst());
            }
            break;
        }

        // QS 3
        Point suivant = choisirSuivantFichier(pointsFichier, un, deux);
        // calcul de l'élargissement sur chacun des deux
        double ex1, ey1, ez1, ex2, ey2, ez2, elarg1, elarg2;
        Fichier * resultat = NULL;
        elargissement(suivant, un.getVoxel(), ex1, ey1, ez1);
        elargissement(suivant, deux.getVoxel(), ex2, ey2, ez2);
        elarg1 = ex1*ey1*ez1;
        elarg2 = ex2*ey2*ez2;
        // algorithme d'attribution
        if(elarg1 > elarg2) {
            resultat = &un;
        } else if(elarg1 == elarg2) {
            double v1 = premier.getVoxel().volume(),
                    v2 = deuxieme.getVoxel().volume();
            if(v1 < v2) {
                resultat = &un;
            } else if(v1 == v2) {
                if(un.getNbPoints() <= deux.getNbPoints()) {
                    resultat = &un;
                } else {
                    resultat = &deux;
                }
            } else {
                resultat = &deux;
            }
        } else {
            resultat = &deux;
        }
        // écriture du point
        if(resultat->rouvrir(
                    (resultat->getMode() &
                     (QIODevice::Unbuffered | QIODevice::Text)
                    ) | QIODevice::Append | QIODevice::WriteOnly)) {
            resultat->getNbPoints();
            resultat->ajoutPoint(suivant);
        }

        // recalcul
        un.calculerVoxel();
        deux.calculerVoxel();
    }

    // suppression définitive
    premier.getDossier().remove(RECUP_FICHIER_DIVISION(nomInit));
}

NoeudR *RTree::diviserFichier(const Point &nouveauPoint, NoeudR *parent) {
    // création du deuxième nœeud
    NoeudR* deuxieme = NULL;
    ALLOCATION(deuxieme, NoeudR(parent->getParent(), true))
    QString chemin2(parent->getDossier().path()),
            nomParent(parent->getDossier().dirName()),
            nouveauNom;
    int numParent = nomParent.toInt();
    int nouveauNum = numParent +1;
    nouveauNom.setNum(nouveauNum);
    QDir nouveauDossier(chemin2);
    nouveauDossier.cdUp();
    nouveauDossier.mkdir(nouveauNom);
    nouveauDossier.cd(nouveauNom);
    deuxieme->setDossier(nouveauDossier);

    // division
    try {
        divisionQuadratiqueFichier(nouveauPoint, *parent, *deuxieme);
    } catch(int e) {
        QDir dossier;
        QString nom;
        switch(e) {
        case 1:
            qCritical("Impossible de trouver ni créer le fichier initial.");
            return NULL;
        case 2:
            qCritical("La liste de points est vide : impossible de rouvrir le fichier");
            return NULL;
        case 3:
            qCritical("(divisionF) Impossible de créer le premier fichier. Annulation.");
            dossier = parent->getDossier();
            nom = dossier.path();
            dossier.rename(
                        nom,
                        nom.left(nom.length() -1)
                        );
            return NULL;
        case 4:
            qCritical("(divisionF) Impossible de créer le deuxième fichier. Annulation.");
            dossier = parent->getDossier();
            dossier.remove(parent->getFichier()->getChemin());
            nom = dossier.path();
            dossier.rename(
                        nom,
                        nom.left(nom.length() -1)
                        );
        default:
            qDebug("Exception inconnue dans divisionQuadratiqueFichier.");
            throw e;
        }
    }

    return deuxieme;
}

NoeudR *RTree::diviserNoeud(NoeudR *enfant, NoeudR *parent) {
    // non implémenté
    return NULL;
}

NoeudR* RTree::ajusterArbre(NoeudR *feuille, NoeudR *nouveau) {
    // AT 1
    NoeudR *parent = feuille->getParent();

    // Condition d'arrêt
    if(feuille == racine) { // AT 2
        return nouveau;
    }

    // Mise à jour du Voxel parent (AT 3)
    parent->calculerVoxel();

    // Si nouveau frère (AT 4)
    if(parent->getNbEnfants() < parent->getNbMaxEnfants()) { // il y a de la place
        parent->ajoutEnfant(*nouveau);
    } else {
        nouveau = diviserNoeud(nouveau, parent);
    }

    // AT 5
    return ajusterArbre(parent, nouveau);
}
