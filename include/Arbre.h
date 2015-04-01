#ifndef ARBRE_H
#define ARBRE_H


class Arbre  // d�claration de la classe Abstraite Arbre
{

    // m�thodes de la classe Arbre
    public:
        Arbre(); // constructeur d'Arbre

        /*cr�ation de fonction virtuelle pour rendre la classe abstraite pour la r�solution dynamique des liens:
        2 possibilit�s s'offrents � nous
        -utilisation de pointeur ou r�f�rence
        - utilisation de fonction virtuelle comme c'est le cas ici
        */


        virtual void construire();
        virtual void requeteVoisinage();
        virtual void requeteContenu();

        virtual ~Arbre(); // destructeur d'Arbre

    private:

        const int nombreNoeud = 1;// taille du tableau
        int m_tabNoeud[]; // d�claration du tableau





};

#endif // ARBRE_H
