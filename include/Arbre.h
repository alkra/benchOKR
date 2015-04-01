#ifndef ARBRE_H
#define ARBRE_H


class Arbre  // déclaration de la classe Abstraite Arbre
{

    // méthodes de la classe Arbre
    public:
        Arbre(); // constructeur d'Arbre

        /*création de fonction virtuelle pour rendre la classe abstraite pour la résolution dynamique des liens:
        2 possibilités s'offrents à nous
        -utilisation de pointeur ou référence
        - utilisation de fonction virtuelle comme c'est le cas ici
        */


        virtual void construire();
        virtual void requeteVoisinage();
        virtual void requeteContenu();

        virtual ~Arbre(); // destructeur d'Arbre

    private:

        const int nombreNoeud = 1;// taille du tableau
        int m_tabNoeud[]; // déclaration du tableau





};

#endif // ARBRE_H
