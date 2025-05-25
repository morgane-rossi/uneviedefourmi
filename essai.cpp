#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <regex>

using namespace std;

int nbFourmis;
int nbSalles = 2 ;

/*
le code va travailler sur une seule fourmilière
dans un fichier "entree.txt"
*/

vector<string> lireFichier(){

    ifstream entree("entree.txt");
    vector<string> fourmiliere ;

    if(!entree)
    {
        cerr << "Erreur lors du chargement du fichier" << endl ;
        return fourmiliere;
    }
    string instruction ;
    while(getline(entree, instruction))
    {
        fourmiliere.push_back(instruction);
    }
    return fourmiliere ;
}


vector<string> convertirInstructions(){

    vector<string> instructions = lireFichier();
    vector <string> graphes ;
;

    // partie pour trouver le nombre de fourmis
    string ligne = instructions.at(0);
//    regex b = ("\d"); 
    // Trouve la position du caractère '='
    int pos = ligne.find('=');

    // vérifie si "=" a été trouvé
    if (pos != string::npos){

        // extraire la sous-chaîne après "=" et la convertir en entier
        string numberStr = ligne.substr(pos+1);
        nbFourmis = stoi(numberStr);
    }
    cout << "nombre de fourmis : " << nbFourmis <<endl ;

    regex tiret(".* - .*");
    regex regex_single("^S\d+$");
    regex regex_range("");

    // partie pour trouver nombre de fourmilières
    for (unsigned i = 1 ; i < instructions.size() ; i++)
    {
        ligne = instructions.at(i);
        // récupérer RE qui correspond ou non à la présence du caractère dans la ligne
        if (ligne.find('-') != string::npos)
        {
            graphes.push_back(ligne);
        }
        else
        {
            nbSalles++;
        }

    }
    cout << "nombre de salles : " << nbSalles << endl;

    return graphes ;
}

void construire_graphe()
{
    vector<string> schema = convertirInstructions();
    list<int> fourmiliere[nbSalles];

    /*
    remplacer v par zéro et d par nbSalles - 1
    extraire valeur gauche et valeur droite
    */
    for (int i = 0 ; i < schema.size() ; i++)
    {
        string ligne = schema.at(i);
        string v = "v";
        string d = "d";
        string zero = "0";
        string derniere = to_string(nbSalles - 1) ;
        regex vto0(v);
        regex dtolast(d);
        ligne = regex_replace(ligne, vto0, zero);
        ligne = regex_replace(ligne, dtolast, derniere);
        cout << ligne << endl ;
    }
}


int main()

{
    construire_graphe();

    return 0 ;
}